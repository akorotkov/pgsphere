#ifndef __PGS_BRIN_H__
#define __PGS_BRIN_H__

/*
 * BRIN declarations
 */

#include "postgres.h"
#include "fmgr.h"

#include "key.h"

#include <assert.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include "access/brin_tuple.h"
#include "utils/datum.h"

#define INCLUSION_UNION                 0
#define INCLUSION_UNMERGEABLE           1
#define INCLUSION_CONTAINS_EMPTY        2

Datum		spoint_brin_inclusion_add_value(PG_FUNCTION_ARGS);
Datum		sbox_brin_inclusion_add_value(PG_FUNCTION_ARGS);

Datum		spoint_overlaps_spherekey(PG_FUNCTION_ARGS);
Datum		spoint_contains_spherekey(PG_FUNCTION_ARGS);
Datum		spoint_iscontained_spherekey(PG_FUNCTION_ARGS);
Datum		sbox_overlaps_spherekey(PG_FUNCTION_ARGS);
Datum		sbox_contains_spherekey(PG_FUNCTION_ARGS);
Datum		sbox_iscontained_spherekey(PG_FUNCTION_ARGS);
Datum		spherekey_overlaps_spherekey(PG_FUNCTION_ARGS);
Datum		spherekey_contains_spherekey(PG_FUNCTION_ARGS);
Datum		spherekey_iscontained_spherekey(PG_FUNCTION_ARGS);

Datum		spoint_overlaps_sbox(PG_FUNCTION_ARGS);
Datum		sbox_iscontained_spoint(PG_FUNCTION_ARGS);

#endif
