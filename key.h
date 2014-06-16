#ifndef __PGS_KEY_H__
#define __PGS_KEY_H__

#include "types.h"

/*!
  \file
  \brief Declarations of key build functions
*/


#define KEYSIZE 24                         //!< the key size for one entry
#define BPCKSIZE (KEYSIZE/6)               //!< the key size for one entry per coordinate

/*!
  The coordinate value has to be between -MAXCVALUE .. MAXCVALUE
*/
#define MAXCVALUE ( ( 1 << ( 8*BPCKSIZE - 2 ) ) - 1 )

typedef struct
{
	int32		vl_len_;
	union
	{
		struct
		{
			float4 lat, lng;
		};
		struct
		{
			int32 k[6];
		};
	};
} GiSTSPointKey;

#define INTERNAL_KEY_SIZE (VARHDRSZ + sizeof(int32) * 6)
#define LEAF_KEY_SIZE (VARHDRSZ + sizeof(float4) * 2)
#define IS_LEAF(key) (VARSIZE(key) == LEAF_KEY_SIZE)
#define ALLOC_LEAF_KEY(key) do { \
	key = (GiSTSPointKey *)palloc0(LEAF_KEY_SIZE); \
	SET_VARSIZE(key, LEAF_KEY_SIZE); \
} while (0) ;
#define ALLOC_INTERNAL_KEY(key) do { \
	key = (GiSTSPointKey *)palloc0(INTERNAL_KEY_SIZE); \
	SET_VARSIZE(key, INTERNAL_KEY_SIZE); \
} while (0) ;

  /*!
    \brief Union the both keys and returns it.
    \param kunion pointer to first key ( = united key )
    \param key second ( unmodified ) key
    \return pointer to result key
  */
  int32 * spherekey_union_two ( int32 * kunion , const int32 * key );
  

  /*!
    \brief Intersect the both keys and returns it.
    \param kinter pointer to first key ( = intersected key )
    \param key second ( unmodified ) key
    \return pointer to result key or NULL if there is not intersection
  */
  int32 * spherekey_inter_two ( int32 * kinter , const int32 * key );


  /*!
    \brief generate key value of spherical point
    \param k  pointer to key
    \param sp spherical point
    \return pointer to key
  */
  int32 * spherepoint_gen_key (  int32 * k , const SPoint * sp );

  /*!
    \brief generates circle's key
    \param k  pointer to key
    \param c  pointer to circle
    \return pointer to key
  */
  int32 * spherecircle_gen_key ( int32 * k, const SCIRCLE * c );

  /*!
    \brief Returns the key of a spherical ellipse
    \param k   the pointer to the key
    \param e  the pointer to a ellipse
    \return pointer to key
  */
  int32    *  sphereellipse_gen_key    ( int32 * k, const SELLIPSE * e );

  /*!
    \brief Returns the key of a spherical line
    \param k   the pointer to the key
    \param sl  the pointer to a line
    \return pointer to key
  */
  int32 * sphereline_gen_key ( int32 * k  , const SLine * sl  );

  /*!
    \brief Creates the key of polygon
    \param sp pointer to polygon
    \param key pointer to key
    \return pointer to key
  */
  int32 * spherepoly_gen_key          ( int32 * key , const SPOLY * sp );

  /*!
    \brief Creates the key of path
    \param sp pointer to path
    \param k pointer to key
    \return pointer to key
  */
  int32  * spherepath_gen_key         ( int32 * k    , const SPATH * sp );

  /*!
    \brief Creates the key of path
    \param box pointer to path
    \param key pointer to key
    \return pointer to key
  */
  int32 * spherebox_gen_key ( int32 * key , const SBOX * box );


  /*!
    \brief Returns true, if first key is less than second key
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherekey_lt(PG_FUNCTION_ARGS);

  /*!
    \brief Returns true, if first key is less or equal than second key
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherekey_le(PG_FUNCTION_ARGS);

  /*!
    \brief Returns true, if first keys are equal
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherekey_eq(PG_FUNCTION_ARGS);

  /*!
    \brief Returns true, if first keys are not equal
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherekey_eq_neg(PG_FUNCTION_ARGS);

  /*!
    \brief Returns true, if first key is greater or equal than second key
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherekey_ge(PG_FUNCTION_ARGS);

  /*!
    \brief Returns true, if first key is greater than second key
    \return bool datum
    \note PostgreSQL function
  */
  Datum  spherekey_gt(PG_FUNCTION_ARGS);

  /*!
    \brief calls skey_cmp( const int32 *, const int32 * ) for two keys
    \return relationship
    \note PostgreSQL function
    \see skey_cmp( const int32 *, const int32 * )
  */
  Datum  spherekey_cmp(PG_FUNCTION_ARGS);

  /*!
    \brief calls skey_cmp( const int32 *, const int32 * ) for two points
    \return relationship
    \note PostgreSQL function
    \see skey_cmp( const int32 *, const int32 * )
  */
  Datum  spherepoint_cmp(PG_FUNCTION_ARGS);

  /*!
    \brief calls skey_cmp( const int32 *, const int32 * ) for two circles
    \return relationship
    \note PostgreSQL function
    \see skey_cmp( const int32 *, const int32 * )
  */
  Datum  spherecircle_cmp(PG_FUNCTION_ARGS);

  /*!
    \brief calls skey_cmp( const int32 *, const int32 * ) for two ellipses
    \return relationship
    \note PostgreSQL function
    \see skey_cmp( const int32 *, const int32 * )
  */
  Datum  sphereellipse_cmp(PG_FUNCTION_ARGS);

  /*!
    \brief calls skey_cmp( const int32 *, const int32 * ) for two lines
    \return relationship
    \note PostgreSQL function
    \see skey_cmp( const int32 *, const int32 * )
  */
  Datum  sphereline_cmp(PG_FUNCTION_ARGS);

  /*!
    \brief calls skey_cmp( const int32 *, const int32 * ) for two pathes
    \return relationship
    \note PostgreSQL function
    \see skey_cmp( const int32 *, const int32 * )
  */
  Datum  spherepath_cmp(PG_FUNCTION_ARGS);

  /*!
    \brief calls skey_cmp( const int32 *, const int32 * ) for two polygons
    \return relationship
    \note PostgreSQL function
    \see skey_cmp( const int32 *, const int32 * )
  */
  Datum  spherepoly_cmp(PG_FUNCTION_ARGS);

  /*!
    \brief calls skey_cmp( const int32 *, const int32 * ) for two boxes
    \return relationship
    \note PostgreSQL function
    \see skey_cmp( const int32 *, const int32 * )
  */
  Datum  spherebox_cmp(PG_FUNCTION_ARGS);

#endif
