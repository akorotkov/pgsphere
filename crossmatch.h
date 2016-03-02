#ifndef __PGS_CROSSMATCH_H_
#define __PGS_CROSSMATCH_H_

#include "types.h"
#include "funcapi.h"

#if PG_VERSION_NUM >= 90300
#define GIST_SCAN_FOLLOW_RIGHT(parentlsn,page) \
	(!XLogRecPtrIsInvalid(parentlsn) && \
	(GistFollowRight(page) || \
	parentlsn < GistPageGetNSN(page)) && \
	GistPageGetOpaque(page)->rightlink != InvalidBlockNumber /* sanity check */ )
#define InvalidNSN 0
#else
#define GIST_SCAN_FOLLOW_RIGHT(parentlsn,page) \
	(!XLogRecPtrIsInvalid(parentlsn) && \
	(GistFollowRight(page) || \
	XLByteLT(parentlsn, GistPageGetOpaque(page)->nsn)) && \
	GistPageGetOpaque(page)->rightlink != InvalidBlockNumber /* sanity check */ )
#define InvalidNSN {0, 0}
#endif

/*
 * Context of crossmatch: represents data which are persistent across SRF calls.
 */
typedef struct
{
	Relation	indexes[2];
	List	   *pendingPairs;
	List	   *resultsPairs;
	float8		pointThreshold;
	int			box3dThreshold;
	SBOX	   *box;
	int32		boxkey[6];

	TupleTableSlot *slot;
	AttInMetadata *attinmeta;
} CrossmatchContext;

void setupFirstcall(CrossmatchContext *ctx, Oid idx1, Oid idx2,
			   float8 threshold);

void endCall(CrossmatchContext *ctx);

void crossmatch(CrossmatchContext *ctx, ItemPointer values);

#endif   /* __PGS_CROSSMATCH_H_ */
