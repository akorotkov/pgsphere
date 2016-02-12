#include "gist.h"

/*
 * GIST's query cache
 */

/* Holds the parent type of PGS_DATA_TYPES for cached key. */
static unsigned keytype = 0;

/* the cached key */
static int32 kcache[6];

/* pointer to cached query */
static void *cquery = NULL;

/* Holds the count of points, if cached query is a path or polygon. */
static int32 npts = 0;

/* If query type and value are equal, this value is true */
static bool res = false;

/*
 * Depending on type of PGS_DATA_TYPES, compare current query and cached query.
 * If query cache and current query are equal, set ref to true.
 */
#define GQ_MEMCMP(type) \
do \
{ \
	if (keytype == PGS_TYPE_##type) \
	{ \
		if (memcmp((void *) cquery, (void *) query, sizeof(type)) == 0) res = true; \
	} \
} while(0);

bool
gq_cache_get_value(unsigned pgstype, const void *query, int32 **key)
{
	if (keytype == 0)
	{
		return false;
	}
	else
	{
		res = false;

		switch (pgstype)
		{
			case PGS_TYPE_SPoint:
				GQ_MEMCMP(SPoint);
				break;
			case PGS_TYPE_SCIRCLE:
				GQ_MEMCMP(SCIRCLE);
				break;
			case PGS_TYPE_SELLIPSE:
				GQ_MEMCMP(SELLIPSE);
				break;
			case PGS_TYPE_SLine:
				GQ_MEMCMP(SLine);
				break;
			case PGS_TYPE_SBOX:
				GQ_MEMCMP(SBOX);
				break;
			case PGS_TYPE_SPATH:
				if (keytype == pgstype && ((SPATH *) query)->npts == npts)
				{
					if (memcmp((void *) cquery,
							   (void *) &((SPATH *) query)->p,
							   ((SPATH *) query)->size) == 0)
						res = true;
				}
				break;
			case PGS_TYPE_SPOLY:
				if (keytype == pgstype && ((SPOLY *) query)->npts == npts)
				{
					if (memcmp((void *) cquery,
							   (void *) &((SPOLY *) query)->p,
							   ((SPOLY *) query)->size) == 0)
						res = true;
				}
				break;
			default:
				res = false;
				break;
		}

		if (res)
		{
			*key = &kcache[0];
		}
		return res;
	}
	return false;
}

/*
 * Depending on type of PGS_DATA_TYPES, copy current query to cache.
 */
#define GQ_MEMCPY(type) \
do \
{ \
	cquery = (void *) malloc(sizeof(type)); \
	memcpy((void *) cquery, (void *) query, sizeof(type)); \
} while(0);


void
gq_cache_set_value(unsigned pgstype, const void *query, const int32 *key)
{
	if (cquery)
	{
		free(cquery);
		cquery = NULL;
	}

	keytype = pgstype;

	switch (pgstype)
	{
		case PGS_TYPE_SPoint:
			GQ_MEMCPY(SPoint);
			break;
		case PGS_TYPE_SCIRCLE:
			GQ_MEMCPY(SCIRCLE);
			break;
		case PGS_TYPE_SELLIPSE:
			GQ_MEMCPY(SELLIPSE);
			break;
		case PGS_TYPE_SLine:
			GQ_MEMCPY(SLine);
			break;
		case PGS_TYPE_SBOX:
			GQ_MEMCPY(SBOX);
			break;
		case PGS_TYPE_SPATH:
			cquery = (void *) malloc(((SPATH *) query)->size);
			npts = ((SPATH *) query)->npts;
			memcpy((void *) cquery,
				   (void *) &((SPATH *) query)->p,
				   ((SPATH *) query)->size);
			break;
		case PGS_TYPE_SPOLY:
			cquery = (void *) malloc(((SPOLY *) query)->size);
			npts = ((SPOLY *) query)->npts;
			memcpy((void *) cquery,
				   (void *) &((SPOLY *) query)->p,
				   ((SPOLY *) query)->size);
			break;
		default:
			keytype = 0;
	}
	if (keytype > 0)
	{
		memcpy((void *) &kcache[0], (void *) key, KEYSIZE);
	}
}
