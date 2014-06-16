#ifndef __PGS_CROSSMATCH_H_
#define __PGS_CROSSMATCH_H_

#include "types.h"

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


Datum crossmatch(PG_FUNCTION_ARGS);

#endif /* __PGS_CROSSMATCH_H_ */
