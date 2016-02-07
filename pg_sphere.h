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

#define PI  3.14159265358979323846          //!< pi
#define PIH 1.57079632679489661923          //!< pi/2
#define PID 6.2831853071795864769           //!< 2*pi
#define RADIANS 57.295779513082320877       //!< 180/pi
#define PI_EPS 4.4408920985006261617e-16 /* 2 ** -51 */

#define Sqr(a)	 ( ( a ) * ( a ) )			/* square function as macro */

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

#ifdef EPSILON
#undef EPSILON
#endif
#define EPSILON  1.0E-09				   //!< Precision of floating point values

void		sphere_yyparse(void);

#endif
