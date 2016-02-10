#ifndef __PGS_PATH_H__
#define __PGS_PATH_H__

#include "polygon.h"

/* Path declarations */


/*
 * The definition of spherical path using a list of
 * spherical points.
 */
typedef struct
{
	int32	size;	/* total size in bytes */
	int32	npts;	/* count of points */
	SPoint	p[1];	/* variable length array of SPoints */
} SPATH;



/* Path and circle */
#define PGS_CIRCLE_PATH_AVOID 0		/* circle avoids path */
#define PGS_CIRCLE_CONT_PATH  1		/* circle contains path */
#define PGS_CIRCLE_PATH_OVER  2		/* circle overlaps path */

/* Path and polygon */
#define PGS_POLY_PATH_AVOID   0		/* polygon avoids path */
#define PGS_POLY_CONT_PATH	  1		/* polygon contains path */
#define PGS_POLY_PATH_OVER	  2		/* polygon and path overlap */

/* Path and ellipse */
#define PGS_ELLIPSE_PATH_AVOID 0	/* ellipse avoids path */
#define PGS_ELLIPSE_CONT_PATH  1	/* ellipse contains path */
#define PGS_ELLIPSE_PATH_OVER  2	/* ellipse overlaps path */


#define PG_GETARG_SPATH(arg) \
	( (SPATH *) DatumGetPointer(PG_DETOAST_DATUM(PG_GETARG_DATUM(arg))) )

/*
 * Checks whether two pathes are equal.
 *
 * p1 - pointer to first path
 * p2 - pointer to second path
 *
 * Returns true if equal.
 */
bool	spath_eq(const SPATH *p1, const SPATH *p2);

/*
 * Checks whether a path contains a point.
 *
 * sp   - pointer to point
 * path - pointer to path
 *
 * Returns true if the path contains the point.
 */
bool	spath_cont_point(const SPATH *path, const SPoint *sp);

/*
 * Returns the i-th line segment of a path.
 *
 * sl   - pointer to line segment
 * path - pointer to path
 * i    - number of
 *
 * Returns the pointer to the line segment or NULL if fails.
 */
bool	spath_segment(SLine *sl, const SPATH *path, int32 i);

/*
 * Input function of path.
 */
Datum	spherepath_in(PG_FUNCTION_ARGS);

/*
 * Returns the n-th point of a path.
 *
 * See spherepath_get_point(PG_FUNCTION_ARGS)
 */
Datum	spherepath_get_point(PG_FUNCTION_ARGS);

/*
 * This function interpolates between points of path. Returns the
 * n-th point of a path where n is a float.
 *
 * See spherepath_point(PG_FUNCTION_ARGS)
 */
Datum	spherepath_point(PG_FUNCTION_ARGS);

/*
 * Checks whether two paths are equal.
 */
Datum	spherepath_equal(PG_FUNCTION_ARGS);

/*
 * Checks whether two paths aren't equal.
 */
Datum	spherepath_equal_neg(PG_FUNCTION_ARGS);

/*
 * Returns the length of a path.
 */
Datum	spherepath_length(PG_FUNCTION_ARGS);

/*
 * Returns the number of points in a path.
 */
Datum	spherepath_npts(PG_FUNCTION_ARGS);

/*
 * Changes the direction of a path.
 */
Datum	spherepath_swap(PG_FUNCTION_ARGS);

/*
 * Checks whether a path contains a point.
 */
Datum	spherepath_cont_point(PG_FUNCTION_ARGS);

/*
 * Checks whether a path doesn't contain a point.
 */
Datum	spherepath_cont_point_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a path contains a point.
 */
Datum	spherepath_cont_point_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a path doesn't contain a point.
 */
Datum	spherepath_cont_point_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a path and a line are overlapping.
 */
Datum	spherepath_overlap_line(PG_FUNCTION_ARGS);

/*
 * Checks whether a path and a line aren't overlapping.
 */
Datum	spherepath_overlap_line_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether path and line are overlapping.
 */
Datum	spherepath_overlap_line_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a path and a line aren't overlapping.
 */
Datum	spherepath_overlap_line_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle contains a path.
 */
Datum	spherecircle_cont_path(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle doesn't contain a path.
 */
Datum	spherecircle_cont_path_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle contains a path.
 */
Datum	spherecircle_cont_path_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle doesn't contain a path.
 */
Datum	spherecircle_cont_path_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle and a path are overlapping.
 */
Datum	spherecircle_overlap_path(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle and a path aren't overlapping.
 */
Datum	spherecircle_overlap_path_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle and a path are overlapping.
 */
Datum	spherecircle_overlap_path_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle and a path aren't overlapping.
 */
Datum	spherecircle_overlap_path_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon contains a path.
 */
Datum	spherepoly_cont_path(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon doesn't contain a path.
 */
Datum	spherepoly_cont_path_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon contains path.
 */
Datum	spherepoly_cont_path_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon doesn't contain a path.
 */
Datum	spherepoly_cont_path_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon and a path are overlapping.
 */
Datum	spherepoly_overlap_path(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon and a path aren't overlapping.
 */
Datum	spherepoly_overlap_path_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon and a path are overlapping.
 */
Datum	spherepoly_overlap_path_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a polygon and a path aren't overlapping.
 */
Datum	spherepoly_overlap_path_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether two pathes are overlapping.
 */
Datum	spherepath_overlap_path(PG_FUNCTION_ARGS);

/*
 * Checks whether two pathes aren't overlapping.
 */
Datum	spherepath_overlap_path_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse contains path.
 */
Datum	sphereellipse_cont_path(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse doesn't contain a path.
 */
Datum	sphereellipse_cont_path_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse contains a path.
 */
Datum	sphereellipse_cont_path_com(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse doesn't contain a path.
 */
Datum	sphereellipse_cont_path_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse and a path are overlapping.
 */
Datum	sphereellipse_overlap_path(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse and a path aren't overlapping.
 */
Datum	sphereellipse_overlap_path_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether an ellipse and a path are overlapping.
 */
Datum	sphereellipse_overlap_path_com(PG_FUNCTION_ARGS);

/*
 * Checks whether ellipse and path aren't overlapping.
 */
Datum	sphereellipse_overlap_path_com_neg(PG_FUNCTION_ARGS);

/*
 * Performs an Euler transformation on a path.
 */
Datum	spheretrans_path(PG_FUNCTION_ARGS);

/*
 * Performs an inverse Euler transformation on a path.
 */
Datum	spheretrans_path_inverse(PG_FUNCTION_ARGS);

/*
 * State transition function for aggregate function spath(spoint). Never
 * call this function outside an aggregate function!
 *
 * Adds a point to a path.
 */
Datum	spherepath_add_point(PG_FUNCTION_ARGS);

/*
 * Finalize function for adding spoints to a path.
 */
Datum	spherepath_add_points_finalize(PG_FUNCTION_ARGS);

#endif
