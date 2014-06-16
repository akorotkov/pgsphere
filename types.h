#ifndef __PGS_TYPES_H__
#define __PGS_TYPES_H__

/*!
  \file
  Include this file if you want to have access to all data
  types.
  \brief data types declarations
*/

/*
  box was the last added data type
*/
#include "box.h"

/*! \defgroup PGS_DATA_TYPES Data type IDs */
/*!
  \addtogroup  PGS_DATA_TYPES
  @{
*/
#define PGS_TYPE_SPoint    1 //!< Spherical point
#define PGS_TYPE_SCIRCLE   2 //!< Spherical circle
#define PGS_TYPE_SELLIPSE  3 //!< Spherical ellipse
#define PGS_TYPE_SLine     4 //!< Spherical line
#define PGS_TYPE_SPATH     5 //!< Spherical path
#define PGS_TYPE_SPOLY     6 //!< Spherical polygon
#define PGS_TYPE_SBOX      7 //!< Spherical box
/* @} */

#endif
