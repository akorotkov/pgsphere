#include <postgres.h>
#include <fmgr.h>

#include <utils/geo_decls.h>  /* Point */

#include <point.h> /* SPoint from pgsphere */

#include <math.h>

PG_FUNCTION_INFO_V1(gnomonic_proj);
PG_FUNCTION_INFO_V1(gnomonic_inv);

/*
 * Direct gnomonic projection.
 *
 * point gnomonic_proj(spoint spherical_point, spoint tangential_point)
 */
Datum gnomonic_proj(PG_FUNCTION_ARGS)
{
	Point*  g = (Point*)  palloc(sizeof(Point));
	SPoint* p = (SPoint*) PG_GETARG_POINTER(0);
	SPoint* t = (SPoint*) PG_GETARG_POINTER(1);

	double delta_lng = p->lng - t->lng;
	double sin_lat = sin(p->lat);
	double cos_lat = cos(p->lat);
	double sin_lat_t = sin(t->lat);
	double cos_lat_t = cos(t->lat);
	double sin_delta = sin(delta_lng);
	double cos_delta = cos(delta_lng);

	double cos_lat__cos_delta = cos_lat * cos_delta;
	double cos_dist = sin_lat_t * sin_lat + cos_lat_t * cos_lat__cos_delta;

	g->x = cos_lat * sin_delta / cos_dist;
	g->y = (cos_lat_t * sin_lat - sin_lat_t * cos_lat__cos_delta) / cos_dist;

	if (p->lng == t->lng && p->lat == t->lat)
	{
		g->x = 0;
		g->y = 0;
	}
	PG_RETURN_POINTER(g);
}

/*
 * Inverse gnomonic projection.
 *
 * spoint gnomonic_inv(point plane_point, spoint tangential_point)
 */
Datum gnomonic_inv(PG_FUNCTION_ARGS)
{
	SPoint* p = (SPoint*) palloc(sizeof(SPoint));
	Point*  g = (Point*)  PG_GETARG_POINTER(0);
	SPoint* t = (SPoint*) PG_GETARG_POINTER(1);

	double rho_sq = g->x * g->x + g->y * g->y;
	double rho = sqrt(rho_sq);
	double cos_c = 1 / sqrt(1 + rho_sq);
	double sin_c = 1 / sqrt(1 + 1 / rho_sq);
	double cos_lat_t = cos(t->lat);
	double sin_lat_t = sin(t->lat);

	p->lng = t->lng + atan2(g->x * sin_c,
							rho * cos_lat_t * cos_c - g->y * sin_lat_t * sin_c);
	p->lat = asin(cos_c * sin_lat_t + g->y *sin_c * cos_lat_t / rho);

	PG_RETURN_POINTER(p);
}
