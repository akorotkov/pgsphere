#ifndef __PGS_POINT_H__
#define __PGS_POINT_H__

#include "vector3d.h"
#include "sbuffer.h"
/*!
  \file
  This file contains declaration for spherical
  point and functions
  \brief spherical point declarations
*/

/*!
  The definition of spherical point.
  \brief Spherical point
*/
  typedef struct {
   float8 lng;  //!< longitude value in radians
   float8 lat;  //!< latitude value in radians
  }  SPoint;

  /*!
    Calculate the distance of two spherical points
    \brief Distance of two spherical points
    \return distance in radians
  */
  float8 spoint_dist ( const SPoint * p1, const SPoint * p2 );


  /*!
    \brief check whether two points are equal
    \param p1 first point
    \param p2 second point
    \return true, if equal
  */
  bool spoint_eq ( const SPoint * p1 , const SPoint * p2 );

  /*!
    Checks the longitude and latitude values and take sure
    the right value ranges
    \brief  validate the spherical point
    \param  spoint pointer to spherical point
    \return pointer to spherical point
  */
  SPoint *  spoint_check (SPoint * spoint);

  /*!
    \brief transforms a 3 dim.vector to a spherical point 
    \param p pointer to spherical point
    \param v pointer to 3 dim. vector
    \return pointer to spherical point
  */
  SPoint   * vector3d_spoint    ( SPoint   * p   , const Vector3D * v );

  /*!
    \brief transforms a spherical point to a 3 dim.vector
    \param v pointer to 3 dim. vector
    \param p pointer to spherical point
    \return pointer to 3 dim. vector
  */
  Vector3D * spoint_vector3d    ( Vector3D * v   , const SPoint   * p );


  /*!
    Take the input and stores it as a spherical point
    \return a spherical point datum
    \note Does check the input too.
   */
  Datum  spherepoint_in(PG_FUNCTION_ARGS);


  /*!
    Create a spherical point from longitude
    and latitude both in radians
    \brief  point created from longitude and latitude
    \return a spherical point datum
    \note PostgreSQL function
   */
  Datum  spherepoint_from_long_lat(PG_FUNCTION_ARGS);


  /*!
    Calculate the distance of two spherical points
    \brief Distance of two spherical points
    \return distance ( float8 ) as datum
    \see spoint_dist ( SPoint *, SPoint * )
    \note PostgreSQL function
  */
  Datum spherepoint_distance(PG_FUNCTION_ARGS);

  /*!
    \brief longitude of spherical point
    \return longitude datum in radians ( float8 )
    \note PostgreSQL function
  */
  Datum  spherepoint_long(PG_FUNCTION_ARGS);

  /*!
    \brief latitude of spherical point
    \return latitude datum in radians ( float8 )
    \note PostgreSQL function
  */
  Datum  spherepoint_lat(PG_FUNCTION_ARGS);

  /*!
    \brief cartesian x-value of spherical point
    \return x-value datum ( float8 )
    \note PostgreSQL function
  */
  Datum  spherepoint_x(PG_FUNCTION_ARGS);

  /*!
    \brief cartesian y-value of spherical point
    \return y-value datum ( float8 )
    \note PostgreSQL function
  */
  Datum  spherepoint_y(PG_FUNCTION_ARGS);

  /*!
    \brief cartesian z-value of spherical point
    \return z-value datum ( float8 )
    \note PostgreSQL function
  */
  Datum  spherepoint_z(PG_FUNCTION_ARGS);

  /*!
    \brief cartesian values of spherical point
    \return array datum ( float8 )
    \note PostgreSQL function
  */
  Datum  spherepoint_xyz(PG_FUNCTION_ARGS);

  /*!
    \brief check whether two points are equal
    \return boolean datum
    \note PostgreSQL function
  */
  Datum  spherepoint_equal(PG_FUNCTION_ARGS);


#endif
