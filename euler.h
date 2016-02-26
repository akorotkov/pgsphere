#ifndef __PGS_EULER_H__
#define __PGS_EULER_H__

#include "point.h"

/*
 * Euler transformation declarations
 */

/*
 * Data structure of spherical (Euler) transformation.
 */
typedef struct
{
	unsigned char	phi_a:2,	/* first axis */
					theta_a:2,	/* second axis */
					psi_a:2;	/* third axis */
	float8			phi,		/* first rotation angle */
					theta,		/* second rotation angle */
					psi;		/* third rotation angle */
} SEuler;


/*
 * Transforms a spherical point and returns the pointer to a transformed spherical
 * point.
 */
void	euler_spoint_trans(SPoint *out, const SPoint *in, const SEuler *se);

/*
 * Transforms a spherical vector from 'spb' to 'spe' into an Euler transformation.
 * Returns true if the transformation was successful.
 */
bool	spherevector_to_euler(SEuler *se, const SPoint *spb, const SPoint *spe);

/*
 * Sets the axes of transformation to ZXZ.
 */
void	seuler_set_zxz(SEuler *se);

/*
 * Checks equality of two transformations.
 */
bool	strans_eq(const SEuler *e1, const SEuler *e2);

/*
 * Transforms a vector using an Euler transformation. Returns the pointer to
 * the result vector.
 */
void	euler_vector_trans(Vector3D *out, const Vector3D *in, const SEuler *se);

/*
 * Inverts an Euler transformation. Returns the pointer to the
 * inverted transformation.
 */
void	spheretrans_inverse(SEuler *se_out, const SEuler *se_in);

/*
 * Inverts an Euler transformation replacing the original Euler transformation.
 * Returns the pointer to the inverted transformation.
 */
void	spheretrans_inv(SEuler *se);

/*
 * Converts an Euler transformation to a ZXZ-axis transformation. Returns
 * the pointer to the converted transformation.
 */
void	strans_zxz(SEuler *ret, const SEuler *se);

/*
 * Transforms an Euler transformation 'in' into 'out' using 'se'. The result
 * is always a ZXZ-axis transformation. Returns the pointer to the transformed
 * transformation.
 */
void	seuler_trans_zxz(SEuler *out, const SEuler *in, const SEuler *se);

/*
 * Input of an Euler transformation.
 */
Datum	spheretrans_in(PG_FUNCTION_ARGS);

/*
 * Input of an Euler transformation with axis Z,X,Z from three angles
 * (phi, theta, psi) in radians.
 */
Datum	spheretrans_from_float8(PG_FUNCTION_ARGS);

/*
 * Returns the first angle of an Euler transformation in radians.
 */
Datum	spheretrans_phi(PG_FUNCTION_ARGS);

/*
 * Returns the second angle of an Euler transformation in radians.
 */
Datum	spheretrans_theta(PG_FUNCTION_ARGS);

/*
 * Returns the third angle of an Euler transformation in radians.
 */
Datum	spheretrans_psi(PG_FUNCTION_ARGS);

/*
 * Returns the axis of an Euler transformation as three letter code.
 */
Datum	spheretrans_type(PG_FUNCTION_ARGS);

/*
 * Returns the Euler transformation (does nothing). This function is needed
 * for +strans operator.
 */
Datum	spheretrans(PG_FUNCTION_ARGS);

/*
 * Returns the inverse Euler transformation.
 */
Datum	spheretrans_invert(PG_FUNCTION_ARGS);

/*
 * Convert an Euler transformation to a ZXZ-axis transformation.
 */
Datum	spheretrans_zxz(PG_FUNCTION_ARGS);

/*
 * This function creates an Euler transformation from 3 angle values in
 * radians and three letter code used for axes. A letter can be X, Y or Z
 * (case-insensitive).
 */
Datum	spheretrans_from_float8_and_type(PG_FUNCTION_ARGS);

/*
 * Checks equality of two Euler transformations.
 */
Datum	spheretrans_equal(PG_FUNCTION_ARGS);

/*
 * Checks inequality of two Euler transformations.
 */
Datum	spheretrans_not_equal(PG_FUNCTION_ARGS);

/*
 * Transforms an Euler transformation.
 */
Datum	spheretrans_trans(PG_FUNCTION_ARGS);

/*
 * Transforms inverse an Euler transformations.
 */
Datum	spheretrans_trans_inv(PG_FUNCTION_ARGS);

/*
 * Transforms a spherical point.
 */
Datum	spheretrans_point(PG_FUNCTION_ARGS);

/*
 * Perform inverse transformation of a spherical point.
 */
Datum	spheretrans_point_inverse(PG_FUNCTION_ARGS);

#endif
