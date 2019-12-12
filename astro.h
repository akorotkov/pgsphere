#ifndef __PGS_ASTRO_H__
#define __PGS_ASTRO_H__
/**
 * Author: HE Boliang <hebl@hebl.org>
 * Date: 2017-12-21
 */

#include "postgres.h"

#include "point.h"
#include "circle.h"

float8 deg2rad(float8 deg);
float8 rad2deg(float8 rad);
SPoint *spos(float8 ra, float8 dec);

#endif
