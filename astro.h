#ifndef __PGS_ASTRO_H__
#define __PGS_ASTRO_H__
/**
 * Author: HE Boliang <hebl@hebl.org>
 * Date: 2017-12-21
 */

#include "postgres.h"

#include "point.h"

double deg2rad(double deg);
double rad2deg(double rad);
SPoint *spos(double ra, double dec);

/**
 * (RA,Dec) -> spoint
 */
// Datum spoint_deg(PG_FUNCTION_ARGS);

/**
 * (RA_1,Dec_1,RA_2,Dec_2,RA_3,Dec_3, ... RA_n,Dec_n) -> spoly
 */
// Datum spoly_deg(PG_FUNCTION_ARGS);

#endif
