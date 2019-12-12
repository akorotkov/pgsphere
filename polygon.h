#ifndef __PGS_POLYGON_H__
#define __PGS_POLYGON_H__

#include "ellipse.h"

/* Polygon declarations */

/*
 * The definition of spherical polygon using a list of
 * spherical points.
 */
typedef struct {
  int32 size;  /* total size in bytes */
  int32 npts;  /* count of points */
  SPoint p[1]; /* variable length array of SPoints */
} SPOLY;

/* Polygon and ellipse */
#define PGS_ELLIPSE_POLY_AVOID 0 /* ellipse avoids polygon */
#define PGS_POLY_CONT_ELLIPSE 1  /* polygon contains ellipse */
#define PGS_ELLIPSE_CONT_POLY 2  /* ellipse contains polygon */
#define PGS_ELLIPSE_POLY_OVER 3  /* ellipse overlaps polygon */

/* Polygon and circle */
#define PGS_CIRCLE_POLY_AVOID 0 /* circle avoids polygon */
#define PGS_POLY_CONT_CIRCLE 1  /* polygon contains circle */
#define PGS_CIRCLE_CONT_POLY 2  /* circle contains polygon */
#define PGS_CIRCLE_POLY_OVER 3  /* circle overlap polygon */

/* Polygon and line */
#define PGS_LINE_POLY_AVOID 0 /* line avoids polygon */
#define PGS_POLY_CONT_LINE 1  /* polygon contains line */
#define PGS_LINE_POLY_OVER 2  /* line overlap polygon */

/* Polygon and polygon */
#define PGS_POLY_AVOID 0 /* polygon avoids other polygon */
#define PGS_POLY_CONT 1  /* polygon contains other polygon */
#define PGS_POLY_OVER 2  /* polygons overlap */

#define PG_GETARG_SPOLY(arg)                                                   \
  ((SPOLY *)DatumGetPointer(PG_DETOAST_DATUM(PG_GETARG_DATUM(arg))))

/*
 * Checks whether two polygons are equal.
 *
 * p1 - pointer to the first polygon
 * p2 - pointer to the second polygon
 *
 * If 'dir' is true, check with reverse polygon of 'p2'.
 */
bool spoly_eq(const SPOLY *p1, const SPOLY *p2, bool dir);

/*
 * Returns the i-th line segment of a polygon.
 *
 * sl   - pointer to the line segment
 * poly - pointer to the polygon
 * i    - number of the segment
 */
bool spoly_segment(SLine *sl, const SPOLY *poly, int32 i);

/*
 * Checks whether a polygon contains a point.
 *
 * pg - pointer to the polygon
 * sp - pointer to the point
 */
bool spoly_contains_point(const SPOLY *pg, const SPoint *sp);

/*
 * Returns the relationship between a polygon and a line as
 * PGS_LINE_POLY_REL int8 value.
 *
 * poly - pointer to the polygon
 * line - pointer to the line
 */
int8 poly_line_pos(const SPOLY *poly, const SLine *line);

SPOLY *spherepoly_from_array(SPoint *arr, int32 nelem);

/*
 * Input of a spherical polygon.
 */
Datum spherepoly_in(PG_FUNCTION_ARGS);

/*
 * Checks whether two polygons are equal.
 */
Datum spherepoly_equal(PG_FUNCTION_ARGS);

/*
 * Checks whether two polygons are not equal.
 */
Datum spherepoly_equal_neg(PG_FUNCTION_ARGS);

/*
 * Circumstance of a polygon. Returns circumference in radians
 * (float8 datum).
 */
Datum spherepoly_circ(PG_FUNCTION_ARGS);

/*
 * Count points (edges) of a polygon.
 */
Datum spherepoly_npts(PG_FUNCTION_ARGS);

/*
 * Returns area of a polygon.
 */
Datum spherepoly_area(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon contains a point.
 */
Datum spherepoly_cont_point(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon doesn't contain a point.
 */
Datum spherepoly_cont_point_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon contains a point.
 */
Datum spherepoly_cont_point_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon doesn't contain a point.
 */
Datum spherepoly_cont_point_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon contains a circle.
 */
Datum spherepoly_cont_circle(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon doesn't contain a circle.
 */
Datum spherepoly_cont_circle_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon contains a circle.
 */
Datum spherepoly_cont_circle_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon doesn't contain a circle.
 */
Datum spherepoly_cont_circle_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle contains a polygon.
 */
Datum spherecircle_cont_poly(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle doesn't contain a polygon.
 */
Datum spherecircle_cont_poly_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle contains a polygon.
 */
Datum spherecircle_cont_poly_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle doesn't contain a polygon.
 */
Datum spherecircle_cont_poly_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon and a circle overlap.
 */
Datum spherepoly_overlap_circle(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon and a circle don't overlap.
 */
Datum spherepoly_overlap_circle_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon and a circle overlap.
 */
Datum spherepoly_overlap_circle_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon and a circle don't overlap.
 */
Datum spherepoly_overlap_circle_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon contains a line.
 */
Datum spherepoly_cont_line(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon doesn't contain a line.
 */
Datum spherepoly_cont_line_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon contains a line.
 */
Datum spherepoly_cont_line_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon doesn't contain a line.
 */
Datum spherepoly_cont_line_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon and a line overlap.
 */
Datum spherepoly_overlap_line(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon and a line don't overlap.
 */
Datum spherepoly_overlap_line_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon and a line overlap.
 */
Datum spherepoly_overlap_line_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon and a line don't overlap.
 */
Datum spherepoly_overlap_line_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon contains other polygon.
 */
Datum spherepoly_cont_poly(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon doesn't contain other polygon.
 */
Datum spherepoly_cont_poly_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon contains other polygon.
 */
Datum spherepoly_cont_poly_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon doesn't contain other polygon.
 */
Datum spherepoly_cont_poly_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether two polygons overlap.
 */
Datum spherepoly_overlap_poly(PG_FUNCTION_ARGS);

/*
 * Checks whether two polygons don't overlap.
 */
Datum spherepoly_overlap_poly_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon contains an ellipse.
 */
Datum spherepoly_cont_ellipse(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon doesn't contain an ellipse.
 */
Datum spherepoly_cont_ellipse_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon contains an ellipse.
 */
Datum spherepoly_cont_ellipse_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon doesn't contain an ellipse.
 */
Datum spherepoly_cont_ellipse_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse contains a polygon.
 */
Datum sphereellipse_cont_poly(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse doesn't contain a polygon.
 */
Datum sphereellipse_cont_poly_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse contains a polygon.
 */
Datum sphereellipse_cont_poly_com(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse doesn't contain a polygon.
 */
Datum sphereellipse_cont_poly_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon and an ellipse overlap.
 */
Datum spherepoly_overlap_ellipse(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon and an ellipse don't overlap.
 */
Datum spherepoly_overlap_ellipse_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon and an ellipse overlap.
 */
Datum spherepoly_overlap_ellipse_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon and an ellipse don't overlap.
 */
Datum spherepoly_overlap_ellipse_com_neg(PG_FUNCTION_ARGS);

/*
 * Performs inverse transform on a polygon using an Euler transformation.
 */
Datum spheretrans_poly(PG_FUNCTION_ARGS);

/*
 * Performs inverse transform on a polygon using an Euler transformation.
 */
Datum spheretrans_poly_inverse(PG_FUNCTION_ARGS);

/*
 * State transition function for the aggregate function spoly(spoint). Never
 * call this function outside an aggregate function! Adds a point to a polygon.
 */
Datum spherepoly_add_point(PG_FUNCTION_ARGS);

/*
 * Finalize function for adding spoints to a polygon.
 */
Datum spherepoly_add_points_finalize(PG_FUNCTION_ARGS);

#endif
