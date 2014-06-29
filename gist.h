#ifndef __PGS_GIST_H__
#define __PGS_GIST_H__

#include "key.h"

/*!
  \file
  \brief GIST index declarations
*/

/* An alias for unsigned char */
typedef unsigned char uchar;

 /* ! \defgroup PGS_KEY_REL Key relationships */

 /*
  * ! \addtogroup PGS_KEY_REL @{
  */
#define SCKEY_DISJ	  0 //!< two keys are disjunct
#define SCKEY_OVERLAP 1 //!< two keys are overlapping
#define SCKEY_IN	  2 //!< first key contains second key
#define SCKEY_SAME	  3 //!< keys are equal
 /* @} */

uchar		spherekey_interleave(const int32 *k1, const int32 *k2);

 /*
  * ! \brief returns the key of cached query \param pgstype \link
  * PGS_DATA_TYPES type \endlink of query \param query pointer to current
  * query \param key pointer to adress of cached key \return true if , cached
  * query is equal to current query
  */
bool		gq_cache_get_value(unsigned pgstype, const void *query, int32 **key);

 /*
  * ! \brief copy current query , type and its key value to cache \param
  * pgstype \link PGS_DATA_TYPES type \endlink of query \param query pointer
  * to query \param key pointer to key \return nothing
  */
void		gq_cache_set_value(unsigned pgstype, const void *query, const int32 *key);


 /*
  * ! Just a dummy. But PostgreSQL need this function to create a data type.
  * \brief Input function of key value \return NULL datum and raises an error
  * \note PostgreSQL function
  */
Datum		spherekey_in(PG_FUNCTION_ARGS);

 /*
  * ! Just a dummy. But PostgreSQL need this function to create a data type.
  * \brief Output function of key value \return NULL datum and raises an error
  * \note PostgreSQL function
  */
Datum		spherekey_out(PG_FUNCTION_ARGS);

 /*
  * ! This function does nothing. \brief GIST's decompress method \return the
  * key datum \note PostgreSQL function
  */
Datum		g_spherekey_decompress(PG_FUNCTION_ARGS);

 /*
  * ! Creates the key value from spherical circle. \brief GIST's compress
  * method for circle \return GIST entry datum \note PostgreSQL function
  */
Datum		g_scircle_compress(PG_FUNCTION_ARGS);

 /*
  * ! Creates the key value from spherical point. \brief GIST's compress
  * method for point \return GIST entry datum \note PostgreSQL function
  */
Datum		g_spoint_compress(PG_FUNCTION_ARGS);

 /*
  * ! Creates the key value from spherical line. \brief GIST's compress method
  * for line \return GIST entry datum \note PostgreSQL function
  */
Datum		g_sline_compress(PG_FUNCTION_ARGS);

 /*
  * ! Creates the key value from spherical path. \brief GIST's compress method
  * for path \return GIST entry datum \note PostgreSQL function
  */
Datum		g_spath_compress(PG_FUNCTION_ARGS);

 /*
  * ! Creates the key value from spherical polygon. \brief GIST's compress
  * method for polygon \return GIST entry datum \note PostgreSQL function
  */
Datum		g_spoly_compress(PG_FUNCTION_ARGS);


 /*
  * ! Creates the key value from spherical ellipse. \brief GIST's compress
  * method for ellipse \return GIST entry datum \note PostgreSQL function
  */
Datum		g_sellipse_compress(PG_FUNCTION_ARGS);

 /*
  * ! Creates the key value from spherical box. \brief GIST's compress method
  * for box \return GIST entry datum \note PostgreSQL function
  */
Datum		g_sbox_compress(PG_FUNCTION_ARGS);


 /*
  * ! The GiST Union method for boxes. Returns the minimal bounding box that
  * encloses all the entries in entryvec. \brief Unions two GIST entries.
  * \return GIST entry datum \note PostgreSQL function
  */
Datum		g_spherekey_union(PG_FUNCTION_ARGS);


 /*
  * ! \brief GIST's equality method \return bool datum, true if equal \note
  * PostgreSQL function
  */
Datum		g_spherekey_same(PG_FUNCTION_ARGS);

 /*
  * ! \brief GIST's consistence method for point \return bool datum, true if
  * consistent \note PostgreSQL function
  */
Datum		g_spoint_consistent(PG_FUNCTION_ARGS);

 /*
  * ! \brief GIST's consistence method for circle \return bool datum, true if
  * consistent \note PostgreSQL function
  */
Datum		g_scircle_consistent(PG_FUNCTION_ARGS);

 /*
  * ! \brief GIST's consistence method for line \return bool datum, true if
  * consistent \note PostgreSQL function
  */
Datum		g_sline_consistent(PG_FUNCTION_ARGS);

 /*
  * ! \brief GIST's consistence method for path \return bool datum, true if
  * consistent \note PostgreSQL function
  */
Datum		g_spath_consistent(PG_FUNCTION_ARGS);

 /*
  * ! \brief GIST's consistence method for polygon \return bool datum, true if
  * consistent \note PostgreSQL function
  */
Datum		g_spoly_consistent(PG_FUNCTION_ARGS);

 /*
  * ! \brief GIST's consistence method for ellipse \return bool datum, true if
  * consistent \note PostgreSQL function
  */
Datum		g_sellipse_consistent(PG_FUNCTION_ARGS);

 /*
  * ! \brief GIST's consistence method for box \return bool datum, true if
  * consistent \note PostgreSQL function
  */
Datum		g_sbox_consistent(PG_FUNCTION_ARGS);

 /*
  * ! \brief GIST's penalty method \return penalty value ( float datum ) \note
  * PostgreSQL function
  */
Datum		g_spherekey_penalty(PG_FUNCTION_ARGS);


 /*
  * ! This method is using the new linear algorithm for R-Trees. See 'New
  * Linear Node Splitting Algorithm for R-tree', C.H.Ang and T.C.Tan . \brief
  * GIST's picksplit method \return GIST_SPLITVEC datum \note PostgreSQL
  * function
  */
Datum		g_spherekey_picksplit(PG_FUNCTION_ARGS);

Datum		pointkey_in(PG_FUNCTION_ARGS);
Datum		pointkey_out(PG_FUNCTION_ARGS);
Datum		pointkey_volume(PG_FUNCTION_ARGS);
Datum		pointkey_area(PG_FUNCTION_ARGS);
Datum		pointkey_perimeter(PG_FUNCTION_ARGS);
Datum		g_spoint2_compress(PG_FUNCTION_ARGS);
Datum		g_spoint2_union(PG_FUNCTION_ARGS);
Datum		g_spoint2_same(PG_FUNCTION_ARGS);
Datum		g_spoint2_consistent(PG_FUNCTION_ARGS);
Datum		g_spoint2_penalty(PG_FUNCTION_ARGS);
Datum		g_spoint2_picksplit(PG_FUNCTION_ARGS);
Datum		g_spoint2_distance(PG_FUNCTION_ARGS);

#endif
