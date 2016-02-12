#ifndef __PGS_LINE_H__
#define __PGS_LINE_H__

#include "circle.h"

/* Spherical line declarations. */

/*
 * Spherical line data structures.
 */
typedef struct
{
	float8	phi,	/* the first rotation angle around z axis */
			theta,	/* the second rotation angle around x axis */
			psi;	/* the last rotation angle around z axis */
	float8	length;	/* the length of the line */
} SLine;

/* PGS_RELATIONSHIPS Object relationships */

/* PGS_CIRCLE_LINE_REL Circle and line */
#define PGS_CIRCLE_LINE_AVOID	0	/* circle avoids line */
#define PGS_CIRCLE_CONT_LINE	1	/* circle contains line */
#define PGS_CIRCLE_LINE_OVER	2	/* circle overlaps line */

/* PGS_LINE_LINE_REL Line and line */
#define PGS_LINE_AVOID			1	/* line avoids other line */
#define PGS_LINE_EQUAL			2	/* lines are equal */
#define PGS_LINE_CONT_LINE		3	/* line contains line */
#define PGS_LINE_CROSS			4	/* lines cross each other */
#define PGS_LINE_CONNECT		5	/* line are "connected" */
#define PGS_LINE_OVER			6	/* lines overlap each other */

/*
 * Makes a line with the starting point 'pbeg' and the ending point 'pend'. Result
 * is placed into sl.
 *
 * Returns false if the distance between the 'pbeg' and the 'pend' is 180deg.
 */
bool	sline_from_points(SLine *sl, const SPoint *pbeg, const SPoint *pend);

/*
 * Returns a meridian line of a given longitude in radians. The result is placed
 * into 'sl'.
 */
void	sline_meridian(SLine *sl, float8 lng);

/*
 * Returns the starting point of a line 'l'. Result is placed into 'p'.
 */
void	sline_begin(SPoint *p, const SLine *l);

/*
 * Returns the ending point of a line 'l'. Result is placed into 'p'.
 */
void	sline_end(SPoint *p, const SLine *l);

/*
 * Puts the minimum and the maximum latitudes of a spherical line 's1' into 'minlat'
 * and 'maxlat'.
 */
void	sline_min_max_lat(const SLine *sl, float8 *minlat, float8 *maxlat);

/*
 * Calculates spherical points with a latitude 'lat' on a spherical line.
 *
 * Returns the number of found points or <0 if undefined.
 */
int32	sphereline_latitude_points(const SLine *sl, float8 lat, SPoint *p1, SPoint *p2);

/*
 * Returns true if two lines are equal.
 */
bool	sline_eq(const SLine *l1, const SLine *l2);

/*
 * Returns the relationship between a line and a circle as PGS_CIRCLE_LINE_REL
 * int8 value.
 */
int8	sphereline_circle_pos(const SLine *sl, const SCIRCLE *sc);

/*
 * Assuming that a line and a circle overlap, this function returns true
 * if the line and the circle are touching. Make sure that the line and the
 * circle overlap before calling this function! Otherwise, the result will be
 * undefined.
 *
 * See sphereline_circle_pos (const SLine *, const SCIRCLE *)
 */
bool	sline_circle_touch(const SLine *sl, const SCIRCLE *sc);

/*
 * Returns the relationship between two lines as PGS_LINE_LINE_REL int8 value.
 */
int8	sline_sline_pos(const SLine *l1, const SLine *l2);

/*
 * Checks whether a point is on a line.
 */
bool	spoint_at_sline(const SPoint *p, const SLine *sl);

/*
 * Returns the Euler transformation of a line.
 *
 * See spheretrans_from_line(PG_FUNCTION_ARGS)
 */
void	sphereline_to_euler(SEuler *se, const SLine *sl);

/*
 * Returns the inverse Euler transformation of a line.
 *
 * See spheretrans_from_line(PG_FUNCTION_ARGS)
 */
void	sphereline_to_euler_inv(SEuler *se, const SLine *sl);

/*
 * Transforms a line using an Euler transformation.
 *
 * out - pointer to the resulting line
 * in  - pointer to the original line
 * se  - pointer to the Euler transformation
 *
 * See spheretrans_line (PG_FUNCTION_ARGS)
 */
void	euler_sline_trans(SLine *out, const SLine *in, const SEuler *se);

/*
 * Puts the center of a line 'sl' into point 'c'.
 */
void	sline_center(SPoint *c, const SLine *sl);

/*
 * The input function for spherical line.
 */
Datum	sphereline_in(PG_FUNCTION_ARGS);

/*
 * Create a line from a spherical point.
 */
Datum	sphereline_from_point(PG_FUNCTION_ARGS);

/*
 * This function creates a spherical line using a starting point
 * and an ending point. The distance between the points must not be
 * equal to 180deg.
 */
Datum	sphereline_from_points(PG_FUNCTION_ARGS);

/*
 * This function creates a spherical line using a given Euler transformation
 * and the length of a line. If the length is less than zero, an error occurs.
 * If the length is larger than 360deg, it is set to 360deg.
 */
Datum	sphereline_from_trans(PG_FUNCTION_ARGS);

/*
 * This function creates a meridian running from south to north.
 * The float8 param provides the longitude in radians.
 */
Datum	sphereline_meridian(PG_FUNCTION_ARGS);

/*
 * Swaps the starting point and the ending point of a line.
 */
Datum	sphereline_swap_beg_end(PG_FUNCTION_ARGS);

/*
 * Turns the line while preserving the starting & ending points.
 */
Datum	sphereline_turn(PG_FUNCTION_ARGS);

/*
 * Returns the beginning of a line.
 */
Datum	sphereline_begin(PG_FUNCTION_ARGS);

/*
 * Returns the ending of a line.
 */
Datum	sphereline_end(PG_FUNCTION_ARGS);

/*
 * Returns the length of a line in radians.
 */
Datum	sphereline_length(PG_FUNCTION_ARGS);

/*
 * Checks whether a line contains a point.
 */
Datum	sphereline_cont_point(PG_FUNCTION_ARGS);

/*
 * Checks whether a line doesn't contain a point.
 */
Datum	sphereline_cont_point_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a line contains a point.
 */
Datum	sphereline_cont_point_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a line doesn't contain a point.
 */
Datum	sphereline_cont_point_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle contains a line.
 */
Datum	spherecircle_cont_line(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle doesn't contain a line.
 */
Datum	spherecircle_cont_line_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle contains a line.
 */
Datum	spherecircle_cont_line_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle doesn't contain a line.
 */
Datum	spherecircle_cont_line_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle and a line overlap.
 */
Datum	sphereline_overlap_circle(PG_FUNCTION_ARGS);

/*
 * Checks whether circle and a line don't overlap.
 */
Datum	sphereline_overlap_circle_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle and a line overlap.
 */
Datum	sphereline_overlap_circle_com(PG_FUNCTION_ARGS);

/*
 * Checks whether circle and a line don't overlap.
 */
Datum	sphereline_overlap_circle_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether two lines are equal.
 */
Datum	sphereline_equal(PG_FUNCTION_ARGS);

/*
 * Checks whether two lines are not equal.
 */
Datum	sphereline_equal_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether two lines cross each other.
 */
Datum	sphereline_crosses(PG_FUNCTION_ARGS);

/*
 * Checks whether two lines don't cross each other.
 */
Datum	sphereline_crosses_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether two lines overlap.
 */
Datum	sphereline_overlap(PG_FUNCTION_ARGS);

/*
 * Checks whether two lines are overlap.
 */
Datum	sphereline_overlap_neg(PG_FUNCTION_ARGS);

/*
 * Returns an Euler transformation. An inverse transformation with it puts
 * the line into equator beginning at (0,0) and ending at (0,length).
 */
Datum	spheretrans_from_line(PG_FUNCTION_ARGS);

/*
 * Transforms a line with an Euler transformation.
 */
Datum	spheretrans_line(PG_FUNCTION_ARGS);

/*
 * Transforms a line with an inverse Euler transformation.
 */
Datum	spheretrans_line_inverse(PG_FUNCTION_ARGS);

#endif
