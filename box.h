#ifndef __PGS_BOX_H__
#define __PGS_BOX_H__

#include "path.h"

/*
 * Box datatype declarations
 */

/*
 * Spherical box structure. The definition of spherical box using two spherical
 * points:south-west and north-east.
 */
typedef struct
{
	SPoint		sw;	/* South-west value of box */
	SPoint		ne; /* North-east value of box */
} SBOX;


/*
 * PGS_RELATIONSHIPS
 */

/* PGS_BOX_CIRCLE_REL Box and circle */
#define PGS_BOX_CIRCLE_AVOID	0	/* box avoids circle */
#define PGS_BOX_CONT_CIRCLE		1	/* box contains circle */
#define PGS_CIRCLE_CONT_BOX		2	/* circle contains box */
#define PGS_BOX_CIRCLE_EQUAL	3	/* circle equals box */
#define PGS_BOX_CIRCLE_OVER		4	/* circle and box are overlapping */

/* PGS_BOX_LINE_REL Box and line */
#define PGS_BOX_LINE_AVOID		0	/* box avoids line */
#define PGS_BOX_CONT_LINE		1	/* box contains line */
#define PGS_BOX_LINE_OVER		2	/* box and line are overlapping */

/* PGS_BOX_PATH_REL Box and path */
#define PGS_BOX_PATH_AVOID		0	/* box avoids path */
#define PGS_BOX_CONT_PATH		1	/* box contains path */
#define PGS_BOX_PATH_OVER		2	/* box and path are overlapping */

/* PGS_BOX_POLY_REL Box and polygon */
#define PGS_BOX_POLY_AVOID		0	/* box avoids polygon */
#define PGS_BOX_CONT_POLY		1	/* box contains polygon */
#define PGS_POLY_CONT_BOX		2	/* polygon contains box */
#define PGS_BOX_POLY_OVER		3	/* polygon and box are overlapping */

/* PGS_BOX_ELLIPSE_REL Box and ellipse */
#define PGS_BOX_ELLIPSE_AVOID	0    /* box avoids ellipse */
#define PGS_BOX_CONT_ELLIPSE	1    /* box contains ellipse */
#define PGS_ELLIPSE_CONT_BOX	2    /* ellipse contains box */
#define PGS_BOX_ELLIPSE_OVER	3    /* ellipse and box are overlapping */

/* PGS_BOX_REL Box and box */
#define PGS_BOX_AVOID			0	  /* box avoids other box */
#define PGS_BOX_CONT			1	  /* box contains other box */
#define PGS_BOX_OVER			2	  /* boxes are overlapping */


 /*
  * Checks, whether two boxes are equal.
  */
bool		sbox_eq(SBOX *b1, SBOX *b2);

 /*
  * Checks, whether point is contained by a box.
  */
bool		sbox_cont_point(const SBOX *b, const SPoint *p);


 /*
  * Input function of box.
  */
Datum		spherebox_in(PG_FUNCTION_ARGS);

 /*
  * Input function of box from two points. The first point is the south-west
  * position, the second the north-east position.
  */
Datum		spherebox_in_from_points(PG_FUNCTION_ARGS);

 /*
  * Returns the south-west edge of box.
  */
Datum		spherebox_sw(PG_FUNCTION_ARGS);

 /*
  * Returns the north-east edge of box.
  */
Datum		spherebox_ne(PG_FUNCTION_ARGS);

 /*
  * Returns the south-east edge of box.
  */
Datum		spherebox_se(PG_FUNCTION_ARGS);

 /*
  * Returns the north-west edge of box.
  */
Datum		spherebox_nw(PG_FUNCTION_ARGS);

 /*
  * Returns the area of a box.
  */
Datum		spherebox_area(PG_FUNCTION_ARGS);

 /*
  * Returns the circumference of a box.
  */
Datum		spherebox_circ(PG_FUNCTION_ARGS);

 /*
  * Checks, whether two boxes are equal.
  */
Datum		spherebox_equal(PG_FUNCTION_ARGS);

 /*
  * Checks, whether two boxes are not equal.
  */
Datum		spherebox_equal_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether point is contained by a box.
  */
Datum		spherebox_cont_point(PG_FUNCTION_ARGS);

 /*
  * Checks, whether point isn't contained by a box.
  */
Datum		spherebox_cont_point_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether point is contained by a box.
  */
Datum		spherebox_cont_point_com(PG_FUNCTION_ARGS);

 /*
  * Checks, whether point isn't contained by a box.
  */
Datum		spherebox_cont_point_com_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box contains a circle.
  */
Datum		spherebox_cont_circle(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box doesn't contain a circle.
  */
Datum		spherebox_cont_circle_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box contains a circle.
  */
Datum		spherebox_cont_circle_com(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box doesn't contain a circle.
  */
Datum		spherebox_cont_circle_com_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether circle contains a box.
  */
Datum		spherecircle_cont_box(PG_FUNCTION_ARGS);

 /*
  * Checks, whether circle doesn't contain a box.
  */
Datum		spherecircle_cont_box_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether circle contains a box.
  */
Datum		spherecircle_cont_box_com(PG_FUNCTION_ARGS);

 /*
  * Checks, whether circle doesn't contain a box.
  */
Datum		spherecircle_cont_box_com_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether circle and box are overlapping.
  */
Datum		spherebox_overlap_circle(PG_FUNCTION_ARGS);

 /*
  * Checks, whether circle and box aren't overlapping.
  */
Datum		spherebox_overlap_circle_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether circle and box are overlapping.
  */
Datum		spherebox_overlap_circle_com(PG_FUNCTION_ARGS);

 /*
  * Checks, whether circle and box aren't overlapping.
  */
Datum		spherebox_overlap_circle_com_neg(PG_FUNCTION_ARGS);


 /*
  * Checks, whether box contains line.
  */
Datum		spherebox_cont_line(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box doesn't contain line.
  */
Datum		spherebox_cont_line_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box contains line.
  */
Datum		spherebox_cont_line_com(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box doesn't contain line.
  */
Datum		spherebox_cont_line_com_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box and line are overlapping.
  */
Datum		spherebox_overlap_line(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box and line aren't overlapping.
  */
Datum		spherebox_overlap_line_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box and line are overlapping.
  */
Datum		spherebox_overlap_line_com(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box and line aren't overlapping.
  */
Datum		spherebox_overlap_line_com_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box contains path.
  */
Datum		spherebox_cont_path(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box doesn't contain path.
  */
Datum		spherebox_cont_path_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box contains path.
  */
Datum		spherebox_cont_path_com(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box doesn't contain path.
  */
Datum		spherebox_cont_path_com_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box and path are overlapping.
  */
Datum		spherebox_overlap_path(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box and path aren't overlapping.
  */
Datum		spherebox_overlap_path_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box and path are overlapping.
  */
Datum		spherebox_overlap_path_com(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box and path aren't overlapping.
  */
Datum		spherebox_overlap_path_com_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box contains a polygon.
  */
Datum		spherebox_cont_poly(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box doesn't contain a polygon.
  */
Datum		spherebox_cont_poly_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box contains a polygon.
  */
Datum		spherebox_cont_poly_com(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box doesn't contain a polygon.
  */
Datum		spherebox_cont_poly_com_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether polygon contains a box.
  */
Datum		spherepoly_cont_box(PG_FUNCTION_ARGS);

 /*
  * Checks, whether polygon doesn't contain a box.
  */
Datum		spherepoly_cont_box_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether polygon contains a box.
  */
Datum		spherepoly_cont_box_com(PG_FUNCTION_ARGS);

 /*
  * Checks, whether polygon doesn't contain a box.
  */
Datum		spherepoly_cont_box_com_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether polygon and box are overlapping.
  */
Datum		spherebox_overlap_poly(PG_FUNCTION_ARGS);

 /*
  * Checks, whether polygon and box aren't overlapping.
  */
Datum		spherebox_overlap_poly_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether polygon and box are overlapping.
  */
Datum		spherebox_overlap_poly_com(PG_FUNCTION_ARGS);

 /*
  * Checks, whether polygon and box aren't overlapping.
  */
Datum		spherebox_overlap_poly_com_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box contains a ellipse.
  */
Datum		spherebox_cont_ellipse(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box doesn't contain a ellipse.
  */
Datum		spherebox_cont_ellipse_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box contains a ellipse.
  */
Datum		spherebox_cont_ellipse_com(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box doesn't contain a ellipse.
  */
Datum		spherebox_cont_ellipse_com_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether ellipse contains a box.
  */
Datum		sphereellipse_cont_box(PG_FUNCTION_ARGS);

 /*
  * Checks, whether ellipse doesn't contain a box.
  */
Datum		sphereellipse_cont_box_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether ellipse contains a box.
  */
Datum		sphereellipse_cont_box_com(PG_FUNCTION_ARGS);

 /*
  * Checks, whether ellipse doesn't contain a box.
  */
Datum		sphereellipse_cont_box_com_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether ellipse and box are overlapping.
  */
Datum		spherebox_overlap_ellipse(PG_FUNCTION_ARGS);

 /*
  * Checks, whether ellipse and box aren't overlapping.
  */
Datum		spherebox_overlap_ellipse_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether ellipse and box are overlapping.
  */
Datum		spherebox_overlap_ellipse_com(PG_FUNCTION_ARGS);

 /*
  * Checks, whether ellipse and box aren't overlapping.
  */
Datum		spherebox_overlap_ellipse_com_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether a box contains another box.
  */
Datum		spherebox_cont_box(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box doesn't contain another box.
  */
Datum		spherebox_cont_box_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box contains another box.
  */
Datum		spherebox_cont_box_com(PG_FUNCTION_ARGS);

 /*
  * Checks, whether box doesn't contain another box.
  */
Datum		spherebox_cont_box_com_neg(PG_FUNCTION_ARGS);

 /*
  * Checks, whether boxes are overlapping.
  */
Datum		spherebox_overlap_box(PG_FUNCTION_ARGS);

 /*
  * Checks, whether boxes aren't overlapping.
  */
Datum		spherebox_overlap_box_neg(PG_FUNCTION_ARGS);

#endif
