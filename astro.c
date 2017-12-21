/**
 * Author: HE Boliang <hebl@hebl.org>
 * Date: 2017-12-21
 */

#include "astro.h"

#include "polygon.h"

PG_FUNCTION_INFO_V1(spoint_deg);
PG_FUNCTION_INFO_V1(spoly_deg);

double deg2rad(double deg) { return deg * 0.017453292519943295; }
double rad2deg(double rad) { return rad * 57.29577951308232; }

// see: src/backend/utils/adt/float.c
static float8 *check_float8_array(ArrayType *transarray, const char *caller,
                                  int n) {
  if (ARR_NDIM(transarray) != 1 || ARR_DIMS(transarray)[0] != n ||
      ARR_HASNULL(transarray) || ARR_ELEMTYPE(transarray) != FLOAT8OID)
    elog(ERROR, "%s: expected %d-element float8 array", caller, n);
  return (float8 *)ARR_DATA_PTR(transarray);
}

SPoint *spos(double ra, double dec) {
  SPoint *sp = (SPoint *)palloc(sizeof(SPoint));
  sp->lng = deg2rad(ra);
  sp->lat = deg2rad(dec);
  spoint_check(sp);
  return sp;
}

Datum spoint_deg(PG_FUNCTION_ARGS) {
  double ra_deg = PG_GETARG_FLOAT8(0);
  double dec_deg = PG_GETARG_FLOAT8(1);

  SPoint *sp = spos(ra_deg, dec_deg);

  PG_RETURN_POINTER(sp);
}

Datum spoly_deg(PG_FUNCTION_ARGS) {
  ArrayType *transarray = PG_GETARG_ARRAYTYPE_P(0);
  float8 *values;
  int32 n = ARR_DIMS(transarray)[0];
  values = check_float8_array(transarray, "spoly_deg", n);

  // spoint >= 3
  if ((n >= 6) && (n % 2 == 0)) {
    int32 np = n / 2;
    SPoint arr[np];

    for (int i = 0; i < np; i++) {
      arr[i] = *spos(values[i * 2], values[i * 2 + 1]);
    }
    SPOLY *spoly;
    spoly = spherepoly_from_array(&arr[0], np);
    PG_RETURN_POINTER(spoly);
  } else
    PG_RETURN_NULL();
}
