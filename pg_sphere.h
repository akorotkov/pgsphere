#ifndef __PGS_PGSPHERE_H__
#define __PGS_PGSPHERE_H__

/*!
  \file
  \brief Base declarations and includes
*/


/*! 
\page index

 <h2>pgSphere</h2>
 <p>
   pgSphere is an extra module for PostgreSQL which adds spherical data types. It provides:
 </p>
 <ul>
   <li> input and output of data</li>
   <li> containing, overlapping, and other operators</li>
   <li> various input and converting functions and operators
   <li> circumference and area of an object
   <li> spherical transformation
   <li> indexing of spherical data types
   <li> several input and output formats 
 </ul>
 <p>
  Hence, you can do a fast search and analysis for objects with spherical
  attributes as used in geographical, astronomical, or other applications
  using PostgreSQL. For instance, you can manage data of geographical
  objects around the world and astronomical data like star and other
  catalogs conveniently using an SQL interface.
 </p>
 <p>
  The aim of pgSphere is to
  provide uniform access to spherical data. Because PostgreSQL itself
  supports a lot of software interfaces, you can now use the same database
  with different utilities and applications.
 </p>
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>

#define PI  3.141592653589793116            //!< pi
#define PIH 1.570796326794896558            //!< pi/2
#define PID 6.283185307179586232            //!< 2*pi
#define RADIANS 57.29577951308232311024     //!< 180/pi

#define sqr(a)   ( ( a ) * ( a ) )          //!< the square functionas macro
#define max(a,b) ( (a>b)?(a):(b) )          //!< maximum of two values
#define min(a,b) ( (a<b)?(a):(b) )          //!< minimum of two values
#define pgs_abs(a) ((a<0)?(-a):(a))         //!< absolute value

#include "postgres.h"
#include "fmgr.h"
#include "utils/geo_decls.h"
#include "utils/array.h"
#include "utils/elog.h"
#include "utils/builtins.h"
#include "catalog/pg_type.h"
#include "access/skey.h"
#include "access/gist.h"
#include "access/itup.h"

/* PGSQL up to 8.1 use access/rtree.h for defining StrategyNumbers */
#ifndef RTLeftStrategyNumber
#include "access/rtree.h"
#endif

#ifdef EPSILON
#undef EPSILON
#endif
#define EPSILON  1.0E-09                   //!< Precision of floating point values

#define FREE     pfree                     //!< An alias for pfree
#define MALLOC   palloc                    //!< An alias for palloc

typedef unsigned char uchar;               //!< An alias for unsigned char


#endif
