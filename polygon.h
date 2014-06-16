#ifndef __PGS_POLYGON_H__
#define __PGS_POLYGON_H__

#include "ellipse.h"

/*!
  \file
  \brief Polygon declarations
*/


/*!
  The definition of spherical polygon using a list of
  spherical points.
  \brief Spherical polygon
*/
typedef struct
{
  int32           size;   //!< total size in bytes
  int32           npts;   //!< count of points
  SPoint          p[1];   //!< variable length array of SPoints
} SPOLY;


/*!
  \addtogroup PGS_RELATIONSHIPS
  @{
*/
/*! \defgroup PGS_ELLIPSE_POLY_REL Polygon and ellipse*/
/*!
  \addtogroup PGS_ELLIPSE_POLY_REL
  @{
*/
#define PGS_ELLIPSE_POLY_AVOID 0    //!< ellipse avoids polygon
#define PGS_POLY_CONT_ELLIPSE  1    //!< polygon contains ellipse
#define PGS_ELLIPSE_CONT_POLY  2    //!< ellipse contains polygon
#define PGS_ELLIPSE_POLY_OVER  3    //!< ellipse overlaps polygon
/*! @} */

/*! \defgroup PGS_CIRCLE_POLY_REL Polygon and circle*/
/*!
  \addtogroup PGS_CIRCLE_POLY_REL
  @{
*/
#define PGS_CIRCLE_POLY_AVOID 0    //!< circle avoids polygon
#define PGS_POLY_CONT_CIRCLE  1    //!< polygon contains circle
#define PGS_CIRCLE_CONT_POLY  2    //!< circle contains polygon
#define PGS_CIRCLE_POLY_OVER  3    //!< circle overlap polygon 
/*! @} */

/*! \defgroup PGS_LINE_POLY_REL Polygon and line*/
/*!
  \addtogroup PGS_LINE_POLY_REL
  @{
*/
#define PGS_LINE_POLY_AVOID   0    //!< line avoids polygon
#define PGS_POLY_CONT_LINE    1    //!< polygon contains line
#define PGS_LINE_POLY_OVER    2    //!< line overlap polygon 
/*! @} */

/*! \defgroup PGS_POLY_REL Polygon and polygon*/
/*!
  \addtogroup PGS_POLY_REL
  @{
*/
#define PGS_POLY_AVOID        0    //!< polygon avoids other polygon
#define PGS_POLY_CONT         1    //!< polygon contains other polygon
#define PGS_POLY_OVER         2    //!< polygons overlap
/*! @} */
/*! @} */


#define PG_GETARG_SPOLY( arg ) ( ( SPOLY  * ) DatumGetPointer( PG_DETOAST_DATUM( PG_GETARG_DATUM ( arg ) ) ) )

  /*!
    \brief Checks, whether two polygons are equal
    \param p1 pointer to first  polygon
    \param p2 pointer to second polygon
    \param dir true, if check with reverse polygon p2
    \return true, if polygons are equal
  */
  bool    spoly_eq ( const SPOLY * p1 , const SPOLY * p2 , bool dir );

  /*!
    \brief Returns the i-th line segment of a polygon
    \param sl   pointer to line segment
    \param poly pointer to polygon
    \param i    number of segment 
    \return pointer to line segment, NULL if fails
  */
  SLine * spoly_segment ( SLine * sl , const SPOLY * poly , int32 i );

  /*!
    \brief Checks, whether polygon contains point
    \param sp pointer to point
    \param pg pointer to polygon
    \return true if polygon contains point
  */
  bool spoly_contains_point ( const SPOLY * pg , const SPoint * sp );

  /*!
    \brief Returns the relationship between polygon and line
    \param line pointer to line
    \param poly pointer to polygon
    \return relationship as a \link PGS_LINE_POLY_REL int8 value \endlink (\ref PGS_POLY_LINE_REL )
  */
  int8    poly_line_pos ( const SPOLY * poly, const SLine * line );

  /*!
    \brief input of spherical polygon
    \return polygon datum
    \note PostgreSQL function
  */
  Datum  spherepoly_in(PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether two polygons are equal
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_equal(PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether two polygons are not equal
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_equal_neg(PG_FUNCTION_ARGS);

  /*!
    \brief Circumstance of a polygon
    \return circumference in radians (float8 datum)
    \note PostgreSQL function
  */
  Datum  spherepoly_circ(PG_FUNCTION_ARGS);

  /*!
    \brief Count of points (edges) of polygon
    \return int8 datum
    \note PostgreSQL function
  */
  Datum  spherepoly_npts(PG_FUNCTION_ARGS);

  /*!
    \brief Returns area of a polygon
    \return float8 datum
    \note PostgreSQL function
  */
  Datum  spherepoly_area(PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon contains point
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_point (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon doesn't contain point
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_point_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon contains point
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_point_com (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon doesn't contain point
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_point_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon contains circle
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_circle (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon doesn't contain circle
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_circle_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon contains circle
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_circle_com (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon doesn't contain circle
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_circle_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether circle contains polygon
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherecircle_cont_poly (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether circle doesn't contain polygon
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherecircle_cont_poly_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether circle contains polygon
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherecircle_cont_poly_com (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether circle doesn't contain polygon
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherecircle_cont_poly_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon and circle are overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_overlap_circle (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon and circle aren't  overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_overlap_circle_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon and circle are overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_overlap_circle_com (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon and circle aren't  overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_overlap_circle_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon contains line
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_line (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon doesn't contain line
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_line_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon contains line
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_line_com (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon doesn't contain line
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_line_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon and line are overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_overlap_line (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon and line aren't overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_overlap_line_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon and line are overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_overlap_line_com (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon and line aren't overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_overlap_line_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a polygon contains a other polygon
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_poly (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a polygon doesn't contain a other polygon
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_poly_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a polygon contains a other polygon
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_poly_com (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a polygon doesn't contain a other polygon
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_poly_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether two polygons are overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_overlap_poly (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether two polygons are not overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_overlap_poly_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a polygon contains an ellipse
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_ellipse (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a polygon doesn't contain an ellipse
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_ellipse_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a polygon contains an ellipse
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_ellipse_com (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a polygon doesn't contain an ellipse
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_ellipse_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether an ellipse contains polygon
    \return bool datum
    \note PostgreSQL function
  */
  Datum  sphereellipse_cont_poly (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether an ellipse doesn't contain polygon
    \return bool datum
    \note PostgreSQL function
  */
  Datum  sphereellipse_cont_poly_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether an ellipse contains polygon
    \return bool datum
    \note PostgreSQL function
  */
  Datum  sphereellipse_cont_poly_com (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether an ellipse doesn't contain polygon
    \return bool datum
    \note PostgreSQL function
  */
  Datum  sphereellipse_cont_poly_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon and ellipse are overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_overlap_ellipse (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon and ellipse aren't overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_overlap_ellipse_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon and ellipse are overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_overlap_ellipse_com (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether polygon and ellipse aren't overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_overlap_ellipse_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Does transform a polygon using Euler transformation
    \return Polygon datum
    \note PostgreSQL function
  */
  Datum  spheretrans_poly(PG_FUNCTION_ARGS);

  /*!
    \brief Does inverse transform a polygon using Euler transformation
    \return Polygon datum
    \note PostgreSQL function
  */
  Datum  spheretrans_poly_inverse(PG_FUNCTION_ARGS);

  /*!
    State transition function for aggregate function spoly(spoint).
    Do never call this function outside an aggregate function!
    \brief Adds a point to polygon 
    \return Polygon datum
    \note PostgreSQL function
  */
  Datum  spherepoly_add_point(PG_FUNCTION_ARGS);

  /*!
    \brief Finalize function for adding spoints to polygon 
    \return Polygon datum
    \note PostgreSQL function
  */
  Datum  spherepoly_add_points_finalize(PG_FUNCTION_ARGS);

#endif
