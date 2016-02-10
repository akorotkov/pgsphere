#ifndef __PGS_POINT_H__
#define __PGS_POINT_H__

#include "vector3d.h"
#include "sbuffer.h"

/* This file contains declarations for spherical point and functions. */

/*
 * The data structure definition of a spherical point.
 */
typedef struct
{
	float8	lng;	/* longitude value in radians */
	float8	lat;	/* latitude value in radians */
} SPoint;

/*
 * Calculate the distance between two spherical points in radians.
 */
float8	spoint_dist(const SPoint *p1, const SPoint *p2);

/*
 * Check whether two points are equal.
 */
bool	spoint_eq(const SPoint *p1, const SPoint *p2);

/*
 * Check the longitude and latitude values of a spherical point.
 */
void	spoint_check(SPoint *spoint);

/*
 * Transforms a 3d vector into a spherical point.
 */
void	vector3d_spoint(SPoint *p, const Vector3D *v);

/*
 * Transforms a spherical point into a 3d vector.
 */
void	spoint_vector3d(Vector3D *v, const SPoint *p);

/*
 * Take the input and store it as a spherical point.
 */
Datum	spherepoint_in(PG_FUNCTION_ARGS);

/*
 * Create a spherical point from longitude and latitude both in radians.
 */
Datum	spherepoint_from_long_lat(PG_FUNCTION_ARGS);

/*
 * Calculate the distance between two spherical points.
 */
Datum	spherepoint_distance(PG_FUNCTION_ARGS);

/*
 * Longitude of a spherical point.
 */
Datum	spherepoint_long(PG_FUNCTION_ARGS);

/*
 * Latitude of a spherical point.
 */
Datum	spherepoint_lat(PG_FUNCTION_ARGS);

/*
 * Cartesian x-value of a spherical point.
 */
Datum	spherepoint_x(PG_FUNCTION_ARGS);

/*
 * Cartesian y-value of a spherical point.
 */
Datum	spherepoint_y(PG_FUNCTION_ARGS);

/*
 * Cartesian z-value of a spherical point.
 */
Datum	spherepoint_z(PG_FUNCTION_ARGS);

/*
 * Cartesian values of a spherical point as an array.
 */
Datum	spherepoint_xyz(PG_FUNCTION_ARGS);

/*
 * Check whether two points are equal.
 */
Datum	spherepoint_equal(PG_FUNCTION_ARGS);

#endif
