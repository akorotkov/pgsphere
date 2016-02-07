#ifndef __PGS_LINE_H__
#define __PGS_LINE_H__

#include "circle.h"

/*
 * Spherical line declarations.
 */

/*
 * Spherical line data structures.
 */
typedef struct
{
	float8		phi,	/* the first rotation angle around z axis */
				theta,	/* the second rotation angle around x axis */
				psi;	/* the last rotation angle around z axis */
	float8		length;	/* the length of the line */
} SLine;

/*
 * PGS_RELATIONSHIPS Object relationships
 */

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
 * Makes a line beginning to pbed and ending at pend. Result is placed into sl.
 * The function returns false, if the distance between begin and end is 180deg.
 */
bool		sline_from_points(SLine *sl, const SPoint *pbeg, const SPoint *pend);

/*
 * Returns a meridian line of given longitude in radian. Result is placed
 * into sl.
 */
void		sline_meridian(SLine *sl, float8 lng);

/*
 * Returns the begin of a line l. Result is placed into p.
 */
void		sline_begin(SPoint *p, const SLine *l);

/*
 * Returns the end of a line l. Result is placed into p.
 */
void		sline_end(SPoint *p, const SLine *l);

/*
 * Puts minimum and maximum latitude of a spherical line s1 into minlat
 * and maxlat.
 */
void		sline_min_max_lat(const SLine *sl, float8 *minlat, float8 *maxlat);

/*
 * Calculates the spherical points with a latitude lat at a spherical line.
 * Returns number of found point or <0 if undefined.
 */
int32		sphereline_latitude_points(const SLine *sl, float8 lat, SPoint *p1, SPoint *p2);

/*
 * Returns true, if the two lines are equal.
 */
bool		sline_eq(const SLine *l1, const SLine *l2);

/*
 * Returns the relationship between line and circle as PGS_CIRCLE_LINE_REL
 * int8 value.
 */
int8		sphereline_circle_pos(const SLine *sl, const SCIRCLE *sc);

/*
 * Assuming that line and circle are overlapping, this function returns true
 * if line and circle are touching. Make sure that line and circle are
 * overlapping before calling this function! Otherwise, the result will be
 * undefined. Dee sphereline_circle_pos (const SLine *, const SCIRCLE *).
 */
bool		sline_circle_touch(const SLine *sl, const SCIRCLE *sc);

/*
 * Returns the relationship between two lines as PGS_LINE_LINE_REL int8 value.
 */
int8		sline_sline_pos(const SLine *l1, const SLine *l2);

/*
 * Returns true if the point is on line.
 */
bool		spoint_at_sline(const SPoint *p, const SLine *sl);

/*
 * Returns the Euler transformation of a line \param se  result
 * pointer to Euler transformation \param sl  input  pointer to the line
 * \return pointer to Euler transformation \see spheretrans_from_line
 * (PG_FUNCTION_ARGS)
 */
void		sphereline_to_euler(SEuler *se, const SLine *sl);

/*
 * Returns the inverse Euler transformation of a line \param se
 * result pointer to Euler transformation \param sl  input  pointer to the
 * line \return pointer to Euler transformation \see spheretrans_from_line
 * (PG_FUNCTION_ARGS)
 */
void		sphereline_to_euler_inv(SEuler *se, const SLine *sl);

/*
 * Transforms a line using  Euler transformation \param out  result
 * pointer to the line \param in	input  pointer of the line \param se
 * pointer to the Euler transformation \return pointer to transformed line
 * \see spheretrans_line (PG_FUNCTION_ARGS)
 */
void		euler_sline_trans(SLine *out, const SLine *in, const SEuler *se);

/*
 * Puts the center of a line "sl" into point "c".
 */
void		sline_center(SPoint *c, const SLine *sl);

/*
 * The input function for spherical lines \return a spherical line
 * datum \note PostgreSQL function
 */
Datum		sphereline_in(PG_FUNCTION_ARGS);

/*
 * Casts spherical point as line \return a spherical line datum
 * \note PostgreSQL function
 */
Datum		sphereline_from_point(PG_FUNCTION_ARGS);

/*
 * ! This function provides the input of a line using begin and end. The
 * distance of begin and end have to be not equal 180deg. \brief input
 * function for spherical lines from spherical points \return a spherical
 * line datum \note PostgreSQL function
 */
Datum		sphereline_from_points(PG_FUNCTION_ARGS);

/*
 * ! This function returns a spherical line from given Euler transformation
 * and length of line. If the length is less than zero, an error occurs. If
 * the length is larger than 360deg, the length is truncated to 360deg.
 * \brief input function for spherical lines from Euler transformation and
 * length \return a spherical line datum \note PostgreSQL function
 */
Datum		sphereline_from_trans(PG_FUNCTION_ARGS);

/*
 * ! This function returns a meridian starting from "south" to north. The
 * float8 param gives the longitude in radians. \brief Creates a line as
 * meridian \return a spherical line datum \note PostgreSQL function
 */
Datum		sphereline_meridian(PG_FUNCTION_ARGS);

/*
 * Swaps begin and end of a line. \return a spherical line datum
 * \note PostgreSQL function
 */
Datum		sphereline_swap_beg_end(PG_FUNCTION_ARGS);

/*
 * Turns the line, but keeps begin and end of the line. \return a
 * spherical line datum \note PostgreSQL function
 */
Datum		sphereline_turn(PG_FUNCTION_ARGS);

/*
 * Returns the begin of a line. \return a spherical point datum
 * \note PostgreSQL function
 */
Datum		sphereline_begin(PG_FUNCTION_ARGS);

/*
 * Returns the end of a line. \return a spherical point datum \note
 * PostgreSQL function
 */
Datum		sphereline_end(PG_FUNCTION_ARGS);

/*
 * Returns the length of a line in radians. \return a float8 datum
 * \note PostgreSQL function
 */
Datum		sphereline_length(PG_FUNCTION_ARGS);

/*
 * Checks whether a line contains a point. \return a bool datum
 * \note PostgreSQL function
 */
Datum		sphereline_cont_point(PG_FUNCTION_ARGS);

/*
 * Checks whether a line doesn't contain a point. \return a bool
 * datum \note PostgreSQL function
 */
Datum		sphereline_cont_point_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a line contains a point. \return a bool datum
 * \note PostgreSQL function
 */
Datum		sphereline_cont_point_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a line doesn't contain a point. \return a bool
 * datum \note PostgreSQL function
 */
Datum		sphereline_cont_point_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle contains a line. \return a bool datum
 * \note PostgreSQL function
 */
Datum		spherecircle_cont_line(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle doesn't contain a line. \return a bool
 * datum \note PostgreSQL function
 */
Datum		spherecircle_cont_line_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle contains a line. \return a bool datum
 * \note PostgreSQL function
 */
Datum		spherecircle_cont_line_com(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle doesn't contain a line. \return a bool
 * datum \note PostgreSQL function
 */
Datum		spherecircle_cont_line_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle and line overlap. \return a bool datum
 * \note PostgreSQL function
 */
Datum		sphereline_overlap_circle(PG_FUNCTION_ARGS);

/*
 * Checks whether circle and line are not overlapping. \return a
 * bool datum \note PostgreSQL function
 */
Datum		sphereline_overlap_circle_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether a circle and line overlap. \return a bool datum
 * \note PostgreSQL function
 */
Datum		sphereline_overlap_circle_com(PG_FUNCTION_ARGS);

/*
 * Checks whether circle and line are not overlapping. \return a
 * bool datum \note PostgreSQL function
 */
Datum		sphereline_overlap_circle_com_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether two lines are equal \return a bool datum \note
 * PostgreSQL function
 */
Datum		sphereline_equal(PG_FUNCTION_ARGS);

/*
 * Checks whether two lines are not equal \return a bool datum \note
 * PostgreSQL function
 */
Datum		sphereline_equal_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether two lines crosses each other. \return a bool datum
 * \note PostgreSQL function
 */
Datum		sphereline_crosses(PG_FUNCTION_ARGS);

/*
 * Checks whether two lines don't cross each other. \return a bool
 * datum \note PostgreSQL function
 */
Datum		sphereline_crosses_neg(PG_FUNCTION_ARGS);

/*
 * Checks whether two lines overlap. \return a bool datum \note
 * PostgreSQL function
 */
Datum		sphereline_overlap(PG_FUNCTION_ARGS);

/*
 * Checks whether two lines are not overlapping. \return a bool
 * datum \note PostgreSQL function
 */
Datum		sphereline_overlap_neg(PG_FUNCTION_ARGS);

/*
 * ! Returns a Euler transformation. A inverse transformation with it puts
 * the line into equator beginning at (0,0) and ending at (0,length). \brief
 * Returns the Euler transformation of a line \return a Euler transformation
 * datum \note PostgreSQL function
 */
Datum		spheretrans_from_line(PG_FUNCTION_ARGS);

/*
 * Transforms a line with an Euler transformation.
 */
Datum		spheretrans_line(PG_FUNCTION_ARGS);

/*
 * Inverse transformation of a line with an Euler transformation.
 */
Datum		spheretrans_line_inverse(PG_FUNCTION_ARGS);

#endif
