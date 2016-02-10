#ifndef __PGS_VECTOR3D_H__
#define __PGS_VECTOR3D_H__

#include "pg_sphere.h"

/* Vector declarations */

/*
 * The definition of a three dimensional vector data structure.
 */
typedef struct
{
	float8	x;	/* x (-1.0 .. 1.0) */
	float8	y;	/* y (-1.0 .. 1.0) */
	float8	z;	/* z (-1.0 .. 1.0) */
} Vector3D;


/*
 * Calculate the cross product of two vectors. Puts
 * cross product of v1 and v2 into out and returns it.
 */
void	vector3d_cross(Vector3D *out, const Vector3D *v1, const Vector3D *v2);

/*
 * Checks equality of two vectors.
 */
bool	vector3d_eq(const Vector3D *a, const Vector3D *b);

/*
 * Calculate the scalar product of two vectors.
 */
float8	vector3d_scalar(Vector3D *v1, Vector3D *v2);

/*
 * Calculate the length of a vector.
 */
float8	vector3d_length(const Vector3D *v);

#endif
