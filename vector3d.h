#ifndef __PGS_VECTOR3D_H__
#define __PGS_VECTOR3D_H__

#include "pg_sphere.h"

/*!
  \file
  \brief Vector declarations
*/


/*!
  The definition of a three dimensional
  vector.
  \brief three-dimensional vector
*/
 typedef struct {
    float8    x;         //!< x value ( -1.0 .. 1.0 )
    float8    y;         //!< y value ( -1.0 .. 1.0 )
    float8    z;         //!< z value ( -1.0 .. 1.0 ) 
 } Vector3D;


/*!
  \brief calculate the cross product of two vectors
  \param v1  pointer to first vector
  \param v2  pointer to second vector
  \param out pointer to result vector
  \return pointer to result vector
*/
Vector3D * vector3d_cross     ( Vector3D * out , const Vector3D * v1 , const Vector3D * v2 );

/*!
  \brief checks equalness of two vectors
  \param a pointer to first vector
  \param b pointer to second vector
  \return true, if equal
*/
bool       vector3d_eq        ( const Vector3D * a   , const Vector3D * b  );


/*!
  \brief calculate the scalar product of two vectors
  \param v1  pointer to first vector
  \param v2  pointer to second vector
  \return scalar product
*/
float8 vector3d_scalar ( Vector3D * v1 , Vector3D * v2 );

/*!
  \brief calculate the length of a vector
  \param v pointer to vector
  \return length
*/
float8 vector3d_length ( const Vector3D * v );

#endif
