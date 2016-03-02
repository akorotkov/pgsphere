/*----------------------------------------------------------------------------
 * Crossmatch algorithm - return pairs of tuples which are give threshold
 * close to each other.
 *
 * This implementation of crossmatch algorithm hierarchically traverse both
 * GiST indexes. It implements depth-first algorithm for page pairs of two
 * indexes. It starts from pair <GIST_ROOT_BLKNO, GIST_ROOT_BLKNO>. Processing
 * of internal page pairs produce more pending page pair into stack. Resulting
 * pending page pairs in the stack potentionally can contain matching leaf
 * index tuples in their subtrees. Processing of leaf page pairs produce
 * resulting pairs of matching item pointers. Since square of number of index
 * tuples in page is significant simple variation of line sweep algorithm is
 * used to compare index tuples inside pages.
 *
 * Author: Alexander Korotkov <aekorotkov@gmail.com>
 *----------------------------------------------------------------------------
 */
#include "crossmatch.h"
#include "gist.h"
#include "key.h"

#include "access/gist.h"
#include "access/gist_private.h"
#if PG_VERSION_NUM >= 90300
#include "access/htup_details.h"
#endif
#if PG_VERSION_NUM >= 90600
#include "catalog/pg_am.h"
#endif
#include "catalog/namespace.h"
#include "funcapi.h"
#include "nodes/pg_list.h"
#include "utils/lsyscache.h"
#include "utils/rel.h"

#if PG_VERSION_NUM >= 90600
#define heap_formtuple heap_form_tuple
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*
 * Pair of pages for pending scan.
 */
typedef struct
{
	GistNSN		parentlsn1,
				parentlsn2;
	BlockNumber blk1,
				blk2;
} PendingPair;

/*
 * Resulting pair of item pointer for return by CRF.
 */
typedef struct
{
	ItemPointerData iptr1,
				iptr2;
} ResultPair;

/*
 * Point information for line sweep algorithm.
 */
typedef struct
{
	float8		v[3];
	ItemPointerData iptr;
} PointInfo;

/*
 * Box3D information for line sweep algorithm.
 */
typedef struct
{
	int32		v[6];
	BlockNumber blk;
	GistNSN		parentlsn;
} Box3DInfo;


/*
 * Add pending pages pair to context.
 */
static void
addPendingPair(CrossmatchContext *ctx, BlockNumber blk1, BlockNumber blk2,
			   GistNSN parentlsn1, GistNSN parentlsn2)
{
	PendingPair *blockNumberPair;

	/* Add pending pair */
	blockNumberPair = (PendingPair *) palloc(sizeof(PendingPair));
	blockNumberPair->blk1 = blk1;
	blockNumberPair->blk2 = blk2;
	blockNumberPair->parentlsn1 = parentlsn1;
	blockNumberPair->parentlsn2 = parentlsn2;
	ctx->pendingPairs = lcons(blockNumberPair, ctx->pendingPairs);
}

/*
 * Add result item pointers pair to context.
 */
static void
addResultPair(CrossmatchContext *ctx, ItemPointer iptr1, ItemPointer iptr2)
{
	ResultPair *itemPointerPair;

	/* Add result pair */
	itemPointerPair = (ResultPair *)
		palloc(sizeof(ResultPair));
	itemPointerPair->iptr1 = *iptr1;
	itemPointerPair->iptr2 = *iptr2;
	ctx->resultsPairs = lappend(ctx->resultsPairs, itemPointerPair);
}

/*
 * Close index relation opened with AccessShareLock.
 */
static void
indexClose(Relation r)
{
	index_close((r), AccessShareLock);
}

/*
 * Do necessary initialization for first SRF call.
 */
void
setupFirstcall(CrossmatchContext *ctx, Oid idx1, Oid idx2,
			   float8 threshold)
{
	GistNSN		parentnsn = InvalidNSN;

	ctx->box = NULL;

	Assert(idx1 != idx2);

	ctx->indexes[0] = index_open(idx1, AccessShareLock);
	ctx->indexes[1] = index_open(idx2, AccessShareLock);

	ctx->pointThreshold = 2.0 * sin(0.5 * (threshold > M_PI ? M_PI : threshold));
	ctx->box3dThreshold = MAXCVALUE * ctx->pointThreshold;

	/*
	 * Add first pending pair of pages: we start scan both indexes from their
	 * roots.
	 */
	addPendingPair(ctx, GIST_ROOT_BLKNO, GIST_ROOT_BLKNO,
				   parentnsn, parentnsn);
}

void endCall(CrossmatchContext *ctx)
{
	indexClose(ctx->indexes[0]);
	indexClose(ctx->indexes[1]);
}

/*
 * Check if two Box3D keys overlaps with given threshold.
 */
static bool
checkKeys(CrossmatchContext *ctx, int32 key1[6], int32 key2[6])
{
	int			i;

	for (i = 0; i < 3; i++)
	{
		if ((key1[i] > key2[i + 3]) &&
			(key1[i] - key2[i + 3] - 1 > ctx->box3dThreshold))
			return false;
		if ((key2[i] > key1[i + 3]) &&
			(key2[i] - key1[i + 3] - 1 > ctx->box3dThreshold))
			return false;
	}
	return true;
}

/*
 * Compare pointers by given coordinate number.
 */
static int
pointCmp(const void *a1, const void *a2, void *arg)
{
	const PointInfo *p1 = (const PointInfo *) a1;
	const PointInfo *p2 = (const PointInfo *) a2;
	int			i = *((int *) arg);
	float8		v1 = p1->v[i],
				v2 = p2->v[i];

	if (v1 < v2)
		return -1;
	else if (v1 == v2)
		return 0;
	else
		return 1;
}

/*
 * Line sweep algorithm on points for find resulting pairs.
 */
static void
pointLineSweep(CrossmatchContext *ctx, PointInfo *points1, int count1,
			   PointInfo *points2, int count2)
{
	int			i1,
				i2,
				coordIdx;
	float8		bestFactor = -1.0,
				threshold = ctx->pointThreshold;
	int			bestCoord = 0;

	/*
	 * Select best coordinate to line sweep. We would like to use coordinate
	 * where two datasets are most far from each other. Use ratio of
	 * difference of coordinate averages to standard deviation along this
	 * coordinate as selection criteria.
	 */
	for (coordIdx = 0; coordIdx < 3; coordIdx++)
	{
		float8		avg1 = 0.0,
					avg2 = 0.0,
					stddev = 0.0,
					factor;

		for (i1 = 0; i1 < count1; i1++)
			avg1 += points1[i1].v[coordIdx];
		avg1 /= count1;
		for (i1 = 0; i1 < count1; i1++)
			stddev += Sqr(points1[i1].v[coordIdx] - avg1);

		for (i2 = 0; i2 < count2; i2++)
			avg2 += points2[i2].v[coordIdx];
		avg2 /= count2;
		for (i2 = 0; i2 < count2; i2++)
			stddev += Sqr(points2[i2].v[coordIdx] - avg2);

		stddev = sqrt(stddev / (count1 + count2 - 2));
		factor = Abs(avg1 - avg2) / stddev;

		if (factor > bestFactor)
		{
			bestFactor = factor;
			bestCoord = coordIdx;
		}
	}

	/* Sort both datasets along selected coordinate */
	qsort_arg(points1, count1, sizeof(PointInfo), pointCmp, (void *) &bestCoord);
	qsort_arg(points2, count2, sizeof(PointInfo), pointCmp, (void *) &bestCoord);

	/* Do line sweep. Iterate over first dataset. */
	i2 = 0;
	for (i1 = 0; i1 < count1; i1++)
	{
		int			j;

		/*
		 * Skip forever points of second dataset which are more than threshold
		 * behind to current point of first dataset.
		 */
		while (i2 < count2 &&
			 points2[i2].v[bestCoord] < points1[i1].v[bestCoord] - threshold)
		{
			i2++;
		}

		/*
		 * Iterate over second dataset until it more than threshold above to
		 * current point of first dataset.
		 */
		j = i2;
		while (j < count2 &&
			 points2[j].v[bestCoord] <= points1[i1].v[bestCoord] + threshold)
		{

			/* Add result pair if two points is threshold close to each other */
			if (sqrt(Sqr(points2[j].v[0] - points1[i1].v[0]) +
					 Sqr(points2[j].v[1] - points1[i1].v[1]) +
					 Sqr(points2[j].v[2] - points1[i1].v[2])) <= threshold)
			{
				addResultPair(ctx, &points1[i1].iptr, &points2[j].iptr);
			}
			j++;
		}
	}
}

/*
 * Fill information about point for line sweep algorithm.
 */
static bool
fillPointInfo(PointInfo *point, CrossmatchContext *ctx, IndexTuple itup,
			  int num)
{
	GiSTSPointKey *key;
	Datum		val;
	bool		isnull;

	/* Get index key value */
	val = index_getattr(itup, 1, ctx->indexes[num - 1]->rd_att, &isnull);

	/* Skip if null */
	if (isnull)
		return false;

	key = (GiSTSPointKey *) DatumGetPointer(val);

	/* Must be leaf key */
	Assert(IS_LEAF(key));

	/* For 1st dataset check if point meets restriction */
	if (num == 1 && ctx->box)
	{
		SPoint		point;

		point.lat = key->lat;
		point.lng = key->lng;
		if (!sbox_cont_point(ctx->box, &point))
			return false;
	}

	/* Fill data structure transforming point into 3D */
	point->v[0] = cos(key->lng) * cos(key->lat);
	point->v[1] = sin(key->lng) * cos(key->lat);
	point->v[2] = sin(key->lat);
	point->iptr = itup->t_tid;

	return true;
}

/* Compare selected dimension lower bound of 3D boxes */
static int
box3dCmp(const void *a1, const void *a2, void *arg)
{
	const Box3DInfo *p1 = (const Box3DInfo *) a1;
	const Box3DInfo *p2 = (const Box3DInfo *) a2;
	int			i = *((int *) arg);
	int32		v1 = p1->v[i],
				v2 = p2->v[i];

	if (v1 < v2)
		return -1;
	else if (v1 == v2)
		return 0;
	else
		return 1;
}

/*
 * Line sweep algorithm on 3D boxes for find pending pairs.
 */
static void
box3DLineSweep(CrossmatchContext *ctx, Box3DInfo *boxes1, int count1,
			   Box3DInfo *boxes2, int count2)
{
	int			i1,
				i2,
				coordIdx;
	float8		bestFactor = -1.0;
	int			bestCoord = 0,
				threshold = ctx->box3dThreshold;

	/*
	 * Select best coordinate to line sweep. We would like to use coordinate
	 * where two datasets are most far from each other. Use ratio of
	 * difference of 3D box projection center averages to square average of 3D
	 * box projection size as selection criteria.
	 */
	for (coordIdx = 0; coordIdx < 3; coordIdx++)
	{
		float8		avg1 = 0.0,
					avg2 = 0.0,
					avgsize = 0.0,
					factor;

		for (i1 = 0; i1 < count1; i1++)
		{
			avg1 += (float8) boxes1[i1].v[coordIdx];
			avg1 += (float8) boxes1[i1].v[coordIdx + 3];
			avgsize += Sqr((float8) (boxes1[i1].v[coordIdx + 3]
									 - boxes1[i1].v[coordIdx] + 1));
		}
		avg1 /= 2 * count1;

		for (i2 = 0; i2 < count2; i2++)
		{
			avg2 += (float8) boxes2[i2].v[coordIdx];
			avg2 += (float8) boxes2[i2].v[coordIdx + 3];
			avgsize += Sqr((float8) (boxes2[i2].v[coordIdx + 3]
									 - boxes2[i2].v[coordIdx] + 1));
		}
		avg2 /= 2 * count2;

		avgsize = sqrt(avgsize / (count1 + count2));
		factor = Abs(avg1 - avg2) / avgsize;

		if (factor > bestFactor)
		{
			bestFactor = factor;
			bestCoord = coordIdx;
		}
	}

	/* Sort both datasets along lower bound of selected coordinate */
	qsort_arg(boxes1, count1, sizeof(Box3DInfo), box3dCmp, (void *) &bestCoord);
	qsort_arg(boxes2, count2, sizeof(Box3DInfo), box3dCmp, (void *) &bestCoord);

	/* Do line sweep. Iterate over first dataset. */
	i2 = 0;
	for (i1 = 0; i1 < count1; i1++)
	{
		int			j;

		/*
		 * Skip forever 3D boxes of second datasets which upper bound is more
		 * than threshold behind to current lower bound of the first dataset
		 * 3D box.
		 */
		while (i2 < count2 &&
		boxes2[i2].v[bestCoord + 3] + 1 < boxes1[i1].v[bestCoord] - threshold)
		{
			i2++;
		}

		/*
		 * Iterate over 3D boxes of second datasets until lower bound is more
		 * than threshold above to current upper bound of the first dataset 3D
		 * box.
		 */
		j = i2;
		while (j < count2 &&
		   boxes2[j].v[bestCoord] <= boxes1[i1].v[bestCoord + 3] + threshold)
		{
			/*
			 * Add pending pair if two 3D boxed is threshold close to each
			 * other.
			 */
			int			i;
			bool		result = true;

			for (i = 0; i < 3; i++)
			{
				if ((boxes1[i1].v[i] > boxes2[j].v[i + 3]) &&
					(boxes1[i1].v[i] - boxes2[j].v[i + 3] - 1 > threshold))
				{
					result = false;
					break;
				}
				if ((boxes2[j].v[i] > boxes1[i1].v[i + 3]) &&
					(boxes2[j].v[i] - boxes1[i1].v[i + 3] - 1 > threshold))
				{
					result = false;
					break;
				}
			}
			if (result)
			{
				addPendingPair(ctx, boxes1[i1].blk, boxes2[j].blk,
							   boxes1[i1].parentlsn, boxes2[j].parentlsn);
			}
			j++;
		}
	}
}

/*
 * Fill information about 3D box for line sweep algorithm.
 */
static bool
fillBox3DInfo(Box3DInfo *box3d, CrossmatchContext *ctx, IndexTuple itup,
			  int num, GistNSN parentlsn)
{
	GiSTSPointKey *key;
	Datum		val;
	bool		isnull;

	/* Get index key value */
	val = index_getattr(itup, 1, ctx->indexes[num - 1]->rd_att, &isnull);

	/* Skip if null */
	if (isnull)
		return false;

	key = (GiSTSPointKey *) DatumGetPointer(val);

	/* Must be not leaf key */
	Assert(!IS_LEAF(key));

	/* For 1st dataset check if 3D box meets restriction */
	if (num == 1 && ctx->box)
	{
		if (spherekey_interleave(ctx->boxkey, key->k) == SCKEY_DISJ)
			return false;
	}

	/* Fill data structure */
	memcpy(box3d->v, key->k, 6 * sizeof(int32));
	box3d->blk = ItemPointerGetBlockNumber(&itup->t_tid);
	box3d->parentlsn = parentlsn;

	return true;
}

/*
 * Scan internal page adding corresponding pending pages with its children and
 * given otherblk.
 */
static void
scanForPendingPages(CrossmatchContext *ctx, Buffer *buf, BlockNumber otherblk,
	   int num, GistNSN parentlsn, GistNSN otherParentlsn, int32 boundkey[6])
{
	Page		page;
	OffsetNumber maxoff,
				i;
	GISTPageOpaque opaque;

	for (;;)
	{
		/* Get page */
		page = BufferGetPage(*buf);
		opaque = GistPageGetOpaque(page);
		maxoff = PageGetMaxOffsetNumber(page);

		/* Iterate over index tuples producing pending pages */
		for (i = FirstOffsetNumber; i <= maxoff; i++)
		{
			ItemId		iid = PageGetItemId(page, i);
			IndexTuple	idxtuple = (IndexTuple) PageGetItem(page, iid);
			BlockNumber childblkno = ItemPointerGetBlockNumber(&(idxtuple->t_tid));
			GiSTSPointKey *key;
			Datum		val;
			bool		isnull;

			/* Get index key value */
			val = index_getattr(idxtuple, 1, ctx->indexes[num - 1]->rd_att, &isnull);

			/* Skip if null */
			if (isnull)
				continue;

			key = (GiSTSPointKey *) DatumGetPointer(val);

			/* Must be not leaf key */
			Assert(!IS_LEAF(key));

			/* Check if key overlaps boundkey with given threshold */
			if (!checkKeys(ctx, key->k, boundkey))
				continue;

			/* For 1st dataset check if 3D box meets restriction */
			if (num == 1 && ctx->box)
			{
				if (spherekey_interleave(ctx->boxkey, key->k) == SCKEY_DISJ)
					continue;
			}

			/* All checks passed: add pending page pair */
			if (num == 1)
			{
				addPendingPair(ctx, childblkno, otherblk,
							   PageGetLSN(page), otherParentlsn);
			}
			else
			{
				addPendingPair(ctx, otherblk, childblkno,
							   otherParentlsn, PageGetLSN(page));
			}
		}

		/* Traverse to next page if needed according to given parentlsn */
		if (GIST_SCAN_FOLLOW_RIGHT(parentlsn, page))
		{
			BlockNumber rightlink = opaque->rightlink;

			UnlockReleaseBuffer(*buf);
			*buf = ReadBuffer(ctx->indexes[num - 1], rightlink);
			LockBuffer(*buf, GIST_SHARE);
		}
		else
		{
			break;
		}
	}
}

/*
 * Read index tuples of given leaf page into PointInfo structures.
 */
static PointInfo *
readPoints(CrossmatchContext *ctx, Buffer *buf, GistNSN parentlsn, int num,
		   int *count)
{
	Page		page;
	OffsetNumber maxoff,
				i;
	GISTPageOpaque opaque;
	PointInfo  *points = NULL;
	int			j = 0,
				allocated = 0;

	for (;;)
	{
		/* Get page */
		page = BufferGetPage(*buf);
		opaque = GistPageGetOpaque(page);
		maxoff = PageGetMaxOffsetNumber(page);

		/* Allocate memory for result */
		if (!points)
		{
			points = (PointInfo *) palloc(sizeof(PointInfo) * maxoff);
			allocated = maxoff;
		}
		else if (j + maxoff > allocated)
		{
			allocated = j + maxoff;
			points = (PointInfo *) repalloc(points, sizeof(PointInfo) * allocated);
		}

		/* Iterate over page filling PointInfo structures */
		for (i = FirstOffsetNumber; i <= maxoff; i++)
		{
			ItemId		iid = PageGetItemId(page, i);
			IndexTuple	idxtuple = (IndexTuple) PageGetItem(page, iid);

			if (fillPointInfo(&points[j], ctx, idxtuple, num))
				j++;
		}

		/* Traverse to next page if needed according to given parentlsn */
		if (GIST_SCAN_FOLLOW_RIGHT(parentlsn, page))
		{
			BlockNumber rightlink = opaque->rightlink;

			UnlockReleaseBuffer(*buf);
			*buf = ReadBuffer(ctx->indexes[num - 1], rightlink);
			LockBuffer(*buf, GIST_SHARE);
		}
		else
		{
			break;
		}
	}
	*count = j;
	return points;
}

/*
 * Read index tuples of given internal page into Box3DInfo structures.
 */
static Box3DInfo *
readBoxes(CrossmatchContext *ctx, Buffer *buf, GistNSN parentlsn, int num,
		  int *count)
{
	Page		page;
	OffsetNumber maxoff,
				i;
	GISTPageOpaque opaque;
	Box3DInfo  *boxes = NULL;
	int			j = 0,
				allocated = 0;

	for (;;)
	{
		/* Get page */
		page = BufferGetPage(*buf);
		opaque = GistPageGetOpaque(page);
		maxoff = PageGetMaxOffsetNumber(page);

		/* Allocate memory for result */
		if (!boxes)
		{
			boxes = (Box3DInfo *) palloc(sizeof(Box3DInfo) * maxoff);
			allocated = maxoff;
		}
		else if (j + maxoff > allocated)
		{
			allocated = j + maxoff;
			boxes = (Box3DInfo *) repalloc(boxes, sizeof(Box3DInfo) * allocated);
		}

		/* Iterate over page filling Box3DInfo structures */
		for (i = FirstOffsetNumber; i <= maxoff; i++)
		{
			ItemId		iid = PageGetItemId(page, i);
			IndexTuple	idxtuple = (IndexTuple) PageGetItem(page, iid);

			if (fillBox3DInfo(&boxes[j], ctx, idxtuple, num, PageGetLSN(page)))
				j++;
		}

		/* Traverse to next page if needed according to given parentlsn */
		if (GIST_SCAN_FOLLOW_RIGHT(parentlsn, page))
		{
			BlockNumber rightlink = opaque->rightlink;

			UnlockReleaseBuffer(*buf);
			*buf = ReadBuffer(ctx->indexes[num - 1], rightlink);
			LockBuffer(*buf, GIST_SHARE);
		}
		else
		{
			break;
		}
	}
	*count = j;
	return boxes;
}

/*
 * Get bounding 3D box for set of points in leaf page
 */
static void
getPointsBoundKey(CrossmatchContext *ctx, Buffer *buf, GistNSN parentlsn,
				  int num, int32 resultkey[6])
{
	Page		page;
	OffsetNumber maxoff,
				i;
	GISTPageOpaque opaque;
	bool		first = true;

	for (;;)
	{
		/* Get page */
		page = BufferGetPage(*buf);
		opaque = GistPageGetOpaque(page);
		maxoff = PageGetMaxOffsetNumber(page);

		/* Interate over page tuples */
		for (i = FirstOffsetNumber; i <= maxoff; i++)
		{
			ItemId		iid = PageGetItemId(page, i);
			IndexTuple	idxtuple = (IndexTuple) PageGetItem(page, iid);
			GiSTSPointKey *key;
			Datum		val;
			bool		isnull;
			SPoint		point;
			int32		k[6];

			/* Get index key value */
			val = index_getattr(idxtuple, 1, ctx->indexes[num - 1]->rd_att, &isnull);

			/* Skip if null */
			if (isnull)
				continue;

			key = (GiSTSPointKey *) DatumGetPointer(val);

			/* Key must be leaf */
			Assert(IS_LEAF(key));

			/* Convert point into 3D box */
			point.lat = key->lat;
			point.lng = key->lng;
			spherepoint_gen_key(k, &point);

			/* Adjust resulting key with current key */
			if (first)
			{
				memcpy(resultkey, k, KEYSIZE);
				first = false;
			}
			else
			{
				spherekey_union_two(resultkey, k);
			}
		}

		/* Traverse to next page if needed according to given parentlsn */
		if (GIST_SCAN_FOLLOW_RIGHT(parentlsn, page))
		{
			BlockNumber rightlink = opaque->rightlink;

			UnlockReleaseBuffer(*buf);
			*buf = ReadBuffer(ctx->indexes[num - 1], rightlink);
			LockBuffer(*buf, GIST_SHARE);
		}
		else
		{
			break;
		}
	}
}

/*
 * Process pending page pair producing result pairs or more pending pairs.
 */
static void
processPendingPair(CrossmatchContext *ctx, BlockNumber blk1, BlockNumber blk2,
				   GistNSN parentlsn1, GistNSN parentlsn2)
{
	Buffer		buf1,
				buf2;
	Page		page1,
				page2;

	/* Read and lock both pages */
	buf1 = ReadBuffer(ctx->indexes[0], blk1);
	buf2 = ReadBuffer(ctx->indexes[1], blk2);
	LockBuffer(buf1, GIST_SHARE);
	LockBuffer(buf2, GIST_SHARE);
	page1 = BufferGetPage(buf1);
	page2 = BufferGetPage(buf2);

	/* Further processing depends on page types (internal/leaf) */
	if (GistPageIsLeaf(page1) && !GistPageIsLeaf(page2))
	{
		/*
		 * First page is leaf while second one is internal. Generate pending
		 * pairs with same first page and children of second page.
		 */
		int32		key[6];

		getPointsBoundKey(ctx, &buf1, parentlsn1, 1, key);
		scanForPendingPages(ctx, &buf2, blk1, 2, parentlsn2, parentlsn1, key);
	}
	else if (!GistPageIsLeaf(page1) && GistPageIsLeaf(page2))
	{
		/*
		 * First page is internal while second one is leaf. Symmetrical to
		 * previous case.
		 */
		int32		key[6];

		getPointsBoundKey(ctx, &buf2, parentlsn2, 2, key);
		scanForPendingPages(ctx, &buf1, blk2, 1, parentlsn1, parentlsn2, key);
	}
	else if (GistPageIsLeaf(page1) && GistPageIsLeaf(page2))
	{
		/* Both pages are leaf: do line sweep for points */
		PointInfo  *points1,
				   *points2;
		int			pi1,
					pi2;

		points1 = readPoints(ctx, &buf1, parentlsn1, 1, &pi1);
		points2 = readPoints(ctx, &buf2, parentlsn2, 2, &pi2);
		pointLineSweep(ctx, points1, pi1, points2, pi2);
	}
	else
	{
		/* Both pages are internal: do line sweep for 3D boxes */
		Box3DInfo  *boxes1,
				   *boxes2;
		int			bi1,
					bi2;

		boxes1 = readBoxes(ctx, &buf1, parentlsn1, 1, &bi1);
		boxes2 = readBoxes(ctx, &buf2, parentlsn2, 2, &bi2);
		box3DLineSweep(ctx, boxes1, bi1, boxes2, bi2);
	}

	UnlockReleaseBuffer(buf1);
	UnlockReleaseBuffer(buf2);
}

/*
 * Crossmatch SRF
 */
void
crossmatch(CrossmatchContext *ctx, ItemPointer values)
{
	/* Scan pending pairs until we have some result pairs */
	while (ctx->resultsPairs == NIL && ctx->pendingPairs != NIL)
	{
		PendingPair blockNumberPair;

		blockNumberPair = *((PendingPair *) linitial(ctx->pendingPairs));
		pfree(linitial(ctx->pendingPairs));
		ctx->pendingPairs = list_delete_first(ctx->pendingPairs);

		processPendingPair(ctx, blockNumberPair.blk1, blockNumberPair.blk2,
					 blockNumberPair.parentlsn1, blockNumberPair.parentlsn2);
	}

	/* Return next result pair if any. Otherwise close SRF. */
	if (ctx->resultsPairs != NIL)
	{
		ResultPair *itemPointerPair = (ResultPair *) palloc(sizeof(ResultPair));

		*itemPointerPair = *((ResultPair *) linitial(ctx->resultsPairs));
		pfree(linitial(ctx->resultsPairs));
		ctx->resultsPairs = list_delete_first(ctx->resultsPairs);

		values[0] = itemPointerPair->iptr1;
		values[1] = itemPointerPair->iptr2;
	}
	else
	{
		ItemPointerSetInvalid(&values[0]);
		ItemPointerSetInvalid(&values[1]);
	}
}
