#ifndef __PGS_CIRCLE_H__
#define __PGS_CIRCLE_H__

#include "euler.h"

  /*! \file
    \brief Spherical circle declarations
  */

  /*!
    \brief Spherical circle.
  */
  typedef struct {
    SPoint center; //!< the center of circle
    float8 radius; //!< the circle radius in radians
  } SCIRCLE;

  /*!
    \brief Checks whether two circles are equal.
    \param c1 pointer to first circle
    \param c2 pointer to second circle
    \return true, if equal
  */
  bool scircle_eq ( const SCIRCLE * c1 , const SCIRCLE * c2 );

  /*!
    \brief checks whether circle contains point
    \param p  pointer to point 
    \param c  pointer to circle
    \return true, if circle contains point
  */
  bool  spoint_in_circle  ( const SPoint * p, const SCIRCLE * c );

  /*!
    \brief transforms a circle using Euler transformation
    \param out pointer to transformed circle
    \param in  pointer to circle
    \param se  pointer to Euler transformation
    \return pointer to transformed circle
  */
  SCIRCLE   * euler_scircle_trans  ( SCIRCLE * out , const SCIRCLE  * in , const SEuler * se );

  /*!
    Takes the input and stores it as spherical
    circle.
    \brief a circle input function
    \return a spherical circle datum
    \note PostgreSQL function
  */
  Datum  spherecircle_in                 (PG_FUNCTION_ARGS);

  /*!
    Checks whether two circles are equal.
    \brief equality of two circles
    \return boolean datum
    \note PostgreSQL function
  */
  Datum  spherecircle_equal              (PG_FUNCTION_ARGS);

  /*!
    Checks whether two circles are not equal.
    \brief Checks whether two circles are not equal
    \return boolean datum
    \note PostgreSQL function
  */
  Datum  spherecircle_equal_neg          (PG_FUNCTION_ARGS);

  /*!
    Calculate the distance of two circles.
    If overlapping, this function returns 0.0.
    \brief distance of two circles
    \return float8 datum
    \note PostgreSQL function
  */
  Datum  spherecircle_distance           (PG_FUNCTION_ARGS);

  /*!
    Calculate the distance of circle and point.
    If circle contains point, this function returns 0.0.
    \brief distance of circle and point
    \return float8 datum
    \note PostgreSQL function
    \see  spherecircle_point_distance_com(PG_FUNCTION_ARGS)
  */
  Datum  spherecircle_point_distance     (PG_FUNCTION_ARGS);

  /*!
    Calculate the distance of point and circle.
    If circle contains point, this function returns 0.0.
    \brief distance of point and circle
    \return float8 datum
    \note PostgreSQL function
    \see  spherecircle_point_distance(PG_FUNCTION_ARGS)
  */
  Datum  spherecircle_point_distance_com (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether circle contains point
    \return boolean datum
    \note PostgreSQL function
  */
  Datum  spherepoint_in_circle           (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether circle doesn't contain point
    \return boolean datum
    \note PostgreSQL function
  */
  Datum  spherepoint_in_circle_neg       (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether circle contains point
    \return boolean datum
    \note PostgreSQL function
  */
  Datum  spherepoint_in_circle_com       (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether circle doesn't contain point
    \return boolean datum
    \note PostgreSQL function
  */
  Datum  spherepoint_in_circle_com_neg   (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether circle is contained by other circle
    \return boolean datum
    \note PostgreSQL function
  */
  Datum  spherecircle_in_circle          (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether circle is not contained by other circle
    \return boolean datum
    \note PostgreSQL function
  */
  Datum  spherecircle_in_circle_neg      (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether circle contains other circle
    \return boolean datum
    \note PostgreSQL function
  */
  Datum  spherecircle_in_circle_com      (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether circle does not contain other circle
    \return boolean datum
    \note PostgreSQL function
  */
  Datum  spherecircle_in_circle_com_neg      (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether two circle overlap
    \return boolean datum
    \note PostgreSQL function
  */
  Datum  spherecircle_overlap            (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether two circle overlap
    \return boolean datum
    \note PostgreSQL function
  */
  Datum  spherecircle_overlap_neg        (PG_FUNCTION_ARGS);

  /*!
    \brief returns the center of circle
    \return spherical point datum
    \note PostgreSQL function
  */
  Datum  spherecircle_center             (PG_FUNCTION_ARGS);

  /*!
    \brief returns the radius of circle
    \return float8 datum
    \note PostgreSQL function
  */
  Datum  spherecircle_radius             (PG_FUNCTION_ARGS);

  /*!
    \brief converts a point to a circle
    \return spherical circle datum
    \note PostgreSQL function
  */
  Datum  spherepoint_to_circle           (PG_FUNCTION_ARGS);

  /*!
    \brief Creates a circle from center and radius
    \return spherical circle datum
    \note PostgreSQL function
  */
  Datum  spherecircle_by_center           (PG_FUNCTION_ARGS);

  /*!
    Calculates the area of a circle in square
    radians
    \brief calculate the area of a circle
    \return float8 datum
    \note PostgreSQL function
  */
  Datum  spherecircle_area               (PG_FUNCTION_ARGS);

  /*!
    Calculates the circumference of a circle in
    radians.
    \brief calculate the circumference of a circle
    \return float8 datum
    \note PostgreSQL function
  */
  Datum  spherecircle_circ               (PG_FUNCTION_ARGS);

  /*!
    Transforms a circle using Euler transformation
    \brief transforms a circle
    \return spherical circle datum
    \note PostgreSQL function
  */
  Datum  spheretrans_circle              (PG_FUNCTION_ARGS);

  /*!
    Invers transformation of a circle 
    using Euler transformation
    \brief inverse transformation of a circle
    \return spherical circle datum
    \note PostgreSQL function
  */
  Datum  spheretrans_circle_inverse      (PG_FUNCTION_ARGS);



#endif
