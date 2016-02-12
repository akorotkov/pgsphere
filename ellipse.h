#ifndef __PGS_ELLIPSE_H__
#define __PGS_ELLIPSE_H__

#include "line.h"

/* Ellipse declarations */

/*
 * Spherical ellipse data structure. A spherical ellipse is represented using
 * two radii and an Euler transformation (ZXZ-axis). The "untransformed" ellipse
 * is located on equator at position (0,0). The large radius is along equator.
 */
typedef struct
{
	/*
	 * rad[0] is the large radius, rad[1] is the small radius of an ellipse in
	 * radians
	 */
	float8		rad[2];

	float8		phi,	/* the first rotation angle around z axis */
				theta,	/* the second rotation angle around x axis */
				psi;	/* the last rotation angle around z axis */
} SELLIPSE;

/*
 * PGS_RELATIONSHIPS
 */

/* PGS_ELLIPSE_LINE_REL Ellipse and line */
#define PGS_ELLIPSE_LINE_AVOID		0	/* ellipse avoids line */
#define PGS_ELLIPSE_CONT_LINE		1	/* ellipse contains line */
#define PGS_ELLIPSE_LINE_OVER		2	/* ellipse overlaps line */

/* PGS_ELLIPSE_CIRCLE_REL Ellipse and circle */
#define PGS_ELLIPSE_CIRCLE_AVOID	0	/* ellipse avoids circle */
#define PGS_CIRCLE_CONT_ELLIPSE		1	/* circle contains ellipse */
#define PGS_ELLIPSE_CONT_CIRCLE		2	/* ellipse contains circle */
#define PGS_ELLIPSE_CIRCLE_EQUAL	3	/* ellipse equals circle */
#define PGS_ELLIPSE_CIRCLE_OVER		4	/* ellipse overlaps circle */

/* PGS_ELLIPSE_ELLIPSE_REL Ellipse and ellipse */
#define PGS_ELLIPSE_AVOID			0	/* ellipse avoids other ellipse */
#define PGS_ELLIPSE_CONT			1	/* ellipse contains other ellipse */
#define PGS_ELLIPSE_OVER			2	/* ellipse overlaps other ellipse */

/*
 * Checks whether two ellipses are equal .
 */
bool	sellipse_eq(const SELLIPSE *e1, const SELLIPSE *e2);

/*
 * Returns the center of an ellipse.
 */
void	sellipse_center(SPoint *sp, const SELLIPSE *e);

/*
 * Checks whether a ellipse contains point.
 */
bool	sellipse_cont_point(const SELLIPSE *se, const SPoint *sp);

/*
 * Returns the large axis of an ellipse as line.
 */
bool	sellipse_line(SLine *sl, const SELLIPSE *e);

/*
 * Relationship between a line and an ellipse as PGS_ELLIPSE_LINE_REL int8 value.
 */
int8	sellipse_line_pos(const SELLIPSE *se, const SLine *sl);

/*
 * Relationship between a circle and an ellipse as PGS_ELLIPSE_CIRCLE_REL int8 value.
 */
int8	sellipse_circle_pos(const SELLIPSE *se, const SCIRCLE *sc);

/*
 * Returns the Euler transformation of an ellipse.
 */
void	sellipse_trans(SEuler *se, const SELLIPSE *e);

/*
 * Input of the spherical ellipse.
 */
Datum	sphereellipse_in(PG_FUNCTION_ARGS);

/*
 * Input of the spherical ellipse from center, axes and inclination.
 */
Datum	sphereellipse_infunc(PG_FUNCTION_ARGS);

/*
 * Returns the inclination of an ellipse.
 */
Datum	sphereellipse_incl(PG_FUNCTION_ARGS);

/*
 * Returns the length of the major axis of an ellipse.
 */
Datum	sphereellipse_rad1(PG_FUNCTION_ARGS);

/*
 * Returns the length of the minor axis of an ellipse.
 */
Datum	sphereellipse_rad2(PG_FUNCTION_ARGS);

/*
 * Returns the center of an ellipse.
 */
Datum	sphereellipse_center(PG_FUNCTION_ARGS);

/*
 * Returns the Euler transformation of an ellipse.
 */
Datum	sphereellipse_trans(PG_FUNCTION_ARGS);

/*
 * Casts a spherical ellipse as circle. The created circle is the boundary
 * circle of ellipse. The diameter of returned circle is equal to length of
 * major axis of ellipse.
  */
Datum	sphereellipse_circle(PG_FUNCTION_ARGS);

/*
 * Casts a spherical point to an ellipse.
 */
Datum	spherepoint_ellipse(PG_FUNCTION_ARGS);

/*
 * Casts a spherical circle to an ellipse.
 */
Datum	spherecircle_ellipse(PG_FUNCTION_ARGS);

/*
 * Checks whether two ellipses are equal.
 */
Datum	sphereellipse_equal(PG_FUNCTION_ARGS);

/*
 * Checks whether two ellipses are not equal.
 */
Datum	sphereellipse_equal_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse contains a point.
 */
Datum	sphereellipse_cont_point(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse doesn't contain a point.
 */
Datum	sphereellipse_cont_point_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse contains a point.
 */
Datum	sphereellipse_cont_point_com(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse doesn't contain a point.
 */
Datum	sphereellipse_cont_point_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse contains a line.
 */
Datum	sphereellipse_cont_line(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse doesn't contain a line.
 */
Datum	sphereellipse_cont_line_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse contains a line.
 */
Datum	sphereellipse_cont_line_com(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse doesn't contain a line.
 */
Datum	sphereellipse_cont_line_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse and a line overlap.
 */
Datum	sphereellipse_overlap_line(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse and a line don't overlap.
 */
Datum	sphereellipse_overlap_line_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse and a line overlap.
 */
Datum	sphereellipse_overlap_line_com(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse and a line don't overlap.
 */
Datum	sphereellipse_overlap_line_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse contains a circle.
 */
Datum	sphereellipse_cont_circle(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse doesn't contain a circle.
 */
Datum	sphereellipse_cont_circle_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse contains a circle.
 */
Datum	sphereellipse_cont_circle_com(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse doesn't contain a circle.
 */
Datum	sphereellipse_cont_circle_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle contains an ellipse.
 */
Datum	spherecircle_cont_ellipse(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle doesn't contain an ellipse.
 */
Datum	spherecircle_cont_ellipse_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle contains an ellipse.
 */
Datum	spherecircle_cont_ellipse_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle doesn't contain an ellipse.
 */
Datum	spherecircle_cont_ellipse_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle and an ellipse overlap.
 */
Datum	sphereellipse_overlap_circle(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle and an ellipse don't overlap.
 */
Datum	sphereellipse_overlap_circle_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle and an ellipse overlap.
 */
Datum	sphereellipse_overlap_circle_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle and an ellipse don't overlap.
 */
Datum	sphereellipse_overlap_circle_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse contains other ellipse.
 */
Datum	sphereellipse_cont_ellipse(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse doesn't contain other ellipse.
 */
Datum	sphereellipse_cont_ellipse_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse is contained by other ellipse.
 */
Datum	sphereellipse_cont_ellipse_com(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse isn't contained by other ellipse.
 */
Datum	sphereellipse_cont_ellipse_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether two ellipses overlap.
 */
Datum	sphereellipse_overlap_ellipse(PG_FUNCTION_ARGS);

/*
 * Checks whether two ellipses don't overlap.
 */
Datum	sphereellipse_overlap_ellipse_neg(PG_FUNCTION_ARGS);

/*
 * Transforms an ellipse using an Euler transformation.
 */
Datum	spheretrans_ellipse(PG_FUNCTION_ARGS);

/*
 * Transforms an ellipse using an Euler transformation.
 */
Datum	spheretrans_ellipse_inv(PG_FUNCTION_ARGS);

#endif
