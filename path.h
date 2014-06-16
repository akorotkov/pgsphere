#ifndef __PGS_PATH_H__
#define __PGS_PATH_H__

#include "polygon.h"

/*!
  \file
  \brief Path declarations
*/


/*!
  The definition of spherical path using a list of
  spherical points.
  \brief Spherical path
*/
typedef struct
{
  int32           size;   //!< total size in bytes
  int32           npts;   //!< count of points
  SPoint          p[1];   //!< variable length array of SPoints
} SPATH;


/*!
  \addtogroup PGS_RELATIONSHIPS
  @{
*/
/*! \defgroup PGS_CIRCLE_PATH_REL Path and circle*/
/*!
  \addtogroup PGS_CIRCLE_PATH_REL
  @{
*/
#define PGS_CIRCLE_PATH_AVOID 0    //!< circle avoids path
#define PGS_CIRCLE_CONT_PATH  1    //!< circle contains path
#define PGS_CIRCLE_PATH_OVER  2    //!< circle overlaps path
/*! @} */

/*! \defgroup PGS_POLY_PATH_REL Path and polygon*/
/*!
  \addtogroup PGS_POLY_PATH_REL
  @{
*/
#define PGS_POLY_PATH_AVOID   0    //!< polygon avoids path
#define PGS_POLY_CONT_PATH    1    //!< polygon contains path
#define PGS_POLY_PATH_OVER    2    //!< polygon and path overlap
/*! @} */

/*! \defgroup PGS_ELLIPSE_PATH_REL Path and ellipse*/
/*!
  \addtogroup PGS_ELLIPSE_PATH_REL
  @{
*/
#define PGS_ELLIPSE_PATH_AVOID 0    //!< ellipse avoids path
#define PGS_ELLIPSE_CONT_PATH  1    //!< ellipse contains path
#define PGS_ELLIPSE_PATH_OVER  2    //!< ellipse overlaps path
/*! @} */
/*! @} */

#define PG_GETARG_SPATH( arg ) ( ( SPATH  * ) DatumGetPointer( PG_DETOAST_DATUM( PG_GETARG_DATUM ( arg ) ) ) )

  /*!
    \brief Checks, whether two pathes are equal
    \param p1 pointer to first  path
    \param p2 pointer to second path
    \return true if equal
  */
  bool     spath_eq                   ( const SPATH * p1 , const SPATH * p2 );

  /*!
    \brief Checks, whether a path contains point
    \param sp   pointer to point
    \param path pointer to path
    \return true, if path contains point
  */
  bool spath_cont_point ( const SPATH  * path, const SPoint   * sp );

  /*!
    \brief Returns the i-th line segment of a path
    \param sl   pointer to line segment
    \param path pointer to path
    \param i    number of segment
    \return pointer to line segment, NULL if fails
  */
  SLine * spath_segment ( SLine * sl , const SPATH * path , int32 i );


  /*!
    \brief Input function of path
    \return path datum
    \note PostgreSQL function
  */
  Datum  spherepath_in(PG_FUNCTION_ARGS);

  /*!
    \brief Returns the n-th point of a path
    \return point datum
    \note PostgreSQL function
    \see spherepath_get_point(PG_FUNCTION_ARGS)
  */
  Datum  spherepath_get_point(PG_FUNCTION_ARGS);

  /*!
    This function interpolates between points of path
    \brief Returns the n-th point of a path where n is a float
    \return point datum
    \note PostgreSQL function
    \see spherepath_point(PG_FUNCTION_ARGS)
  */
  Datum  spherepath_point(PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether two pathes are equal
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepath_equal(PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether two pathes aren't equal
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepath_equal_neg(PG_FUNCTION_ARGS);

  /*!
    \brief Returns the length of a path
    \return float8 datum
    \note PostgreSQL function
  */
  Datum  spherepath_length(PG_FUNCTION_ARGS);

  /*!
    \brief Returns the point count of a path
    \return int8 datum
    \note PostgreSQL function
  */
  Datum  spherepath_npts(PG_FUNCTION_ARGS);

  /*!
    \brief Changes the direction of a path
    \return SPATH datum
    \note PostgreSQL function
  */
  Datum  spherepath_swap(PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a path contains point
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepath_cont_point(PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a path doesn't contain point
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepath_cont_point_neg(PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a path contains point
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepath_cont_point_com(PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a path doesn't contain point
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepath_cont_point_com_neg(PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether path and line are overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepath_overlap_line (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether path and line aren't overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepath_overlap_line_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether path and line are overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepath_overlap_line_com (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether path and line aren't overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepath_overlap_line_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a circle contains path
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherecircle_cont_path (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a circle doesn't contains path
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherecircle_cont_path_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a circle contains path
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherecircle_cont_path_com (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a circle doesn't contains path
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherecircle_cont_path_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether circle and path are overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherecircle_overlap_path (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether circle and path aren't overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherecircle_overlap_path_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether circle and path are overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherecircle_overlap_path_com (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether circle and path aren't overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherecircle_overlap_path_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a polygon contains path
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_path (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a polygon doesn't contain path
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_path_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a polygon contains path
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_path_com (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a polygon doesn't contain path
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_cont_path_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a polygon and path are overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_overlap_path (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a polygon and path aren't overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_overlap_path_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a polygon and path are overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_overlap_path_com (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether a polygon and path aren't overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepoly_overlap_path_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether two pathes are overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepath_overlap_path (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether two pathes aren't overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherepath_overlap_path_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether an ellipse contains path
    \return bool datum
    \note PostgreSQL function
  */
  Datum  sphereellipse_cont_path (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether an ellipse doesn't contain path
    \return bool datum
    \note PostgreSQL function
  */
  Datum  sphereellipse_cont_path_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether an ellipse contains path
    \return bool datum
    \note PostgreSQL function
  */
  Datum  sphereellipse_cont_path_com (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether an ellipse doesn't contain path
    \return bool datum
    \note PostgreSQL function
  */
  Datum  sphereellipse_cont_path_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether ellipse and path are overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  sphereellipse_overlap_path (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether ellipse and path arent' overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  sphereellipse_overlap_path_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether ellipse and path are overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  sphereellipse_overlap_path_com (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether ellipse and path arent' overlapping
    \return bool datum
    \note PostgreSQL function
  */
  Datum  sphereellipse_overlap_path_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Does an Euler transformation on a path
    \return path datum
    \note PostgreSQL function
  */
  Datum  spheretrans_path(PG_FUNCTION_ARGS);

  /*!
    \brief Does an inverse Euler transformation on a path
    \return path datum
    \note PostgreSQL function
  */
  Datum  spheretrans_path_inverse(PG_FUNCTION_ARGS);

  /*!
    State transition function for aggregate function spath(spoint).
    Do never call this function outside an aggregate function!
    \brief Adds a point to path 
    \return Path datum
    \note PostgreSQL function
  */
  Datum  spherepath_add_point(PG_FUNCTION_ARGS);

  /*!
    \brief Finalize function for adding spoints to path 
    \return Path datum
    \note PostgreSQL function
  */
  Datum  spherepath_add_points_finalize(PG_FUNCTION_ARGS);

#endif
