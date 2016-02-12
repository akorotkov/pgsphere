#ifndef __PGS_KEY_H__
#define __PGS_KEY_H__

#include "types.h"

/* Declarations of key build functions */

#define KEYSIZE 24				/* the key size for one entry */
#define BPCKSIZE (KEYSIZE/6)	/* the key size for one entry per coordinate */

/*
 * The coordinate value has to be between -MAXCVALUE .. MAXCVALUE
 */
#define MAXCVALUE ( (1 << (8 * BPCKSIZE - 2)) - 1 )

typedef struct
{
	int32			vl_len_;
	union
	{
		struct
		{
			float4	lat,
					lng;
		};
		struct
		{
			int32	k[6];
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

/*
 * Returns the union of two keys. Result is placed into 'kunion'.
 */
void	spherekey_union_two(int32 *kunion, const int32 *key);

/*
 * Returns the intersection of two keys. Returns NULL if there is
 * no intersection. Result is placed into 'kinter'.
 */
bool	spherekey_inter_two(int32 *kinter, const int32 *key);

/*
 * Generates the key of a spherical point and returns it. Result is placed
 * into 'k'.
 */
void	spherepoint_gen_key(int32 *k, const SPoint *sp);

/*
 * Generates the circle's key and returns it. Result is placed into 'k'.
 */
void	spherecircle_gen_key(int32 *k, const SCIRCLE *c);

/*
 * Generates the key of a spherical ellipse and returns it. Result is placed
 * into 'k'.
 */
void	sphereellipse_gen_key(int32 *k, const SELLIPSE *e);

/*
 * Generates the key of a spherical line and returns it. Result is placed
 * into 'k'.
 */
void	sphereline_gen_key(int32 *k, const SLine *sl);

/*
 * Generates the key of a polygon and returns it. Result is placed into 'k'.
 */
void	spherepoly_gen_key(int32 *k, const SPOLY *sp);

/*
 * Generates the key of a path and returns it. Result is placed into 'k'.
 */
void	spherepath_gen_key(int32 *k, const SPATH *sp);

/*
 * Generates the key of a box and returns it. Result is placed into 'k'.
 */
void	spherebox_gen_key(int32 *key, const SBOX *box);

/*
 * Returns true if the first key is less than the second key.
 */
Datum	spherekey_lt(PG_FUNCTION_ARGS);

/*
 * Returns true if the first key is less or equal than the second key.
 */
Datum	spherekey_le(PG_FUNCTION_ARGS);

/*
 * Returns true if two keys are equal.
 */
Datum	spherekey_eq(PG_FUNCTION_ARGS);

/*
 * Returns true if two keys are not equal.
 */
Datum	spherekey_eq_neg(PG_FUNCTION_ARGS);

/*
 * Returns true if the first key is greater or equal than the second key.
 */
Datum	spherekey_ge(PG_FUNCTION_ARGS);

/*
 * Returns true if the first key is greater than the second key.
 */
Datum	spherekey_gt(PG_FUNCTION_ARGS);

/*
 * Returns relationship between the two keys.
 * Calls skey_cmp(const int32 *, const int32 *) for two keys.
 */
Datum	spherekey_cmp(PG_FUNCTION_ARGS);

/*
 * Returns relationship between the keys of two spherical points.
 * Calls skey_cmp(const int32 *, const int32 *) for two points.
 */
Datum	spherepoint_cmp(PG_FUNCTION_ARGS);

/*
 * Returns relationship between the keys of two spherical circles.
 * Calls skey_cmp(const int32 *, const int32 *) for two circles.
 */
Datum	spherecircle_cmp(PG_FUNCTION_ARGS);

/*
 * Returns relationship between the keys of two spherical ellipses.
 * Calls skey_cmp(const int32 *, const int32 *) for two ellipses.
 */
Datum	sphereellipse_cmp(PG_FUNCTION_ARGS);

/*
 * Returns relationship between the keys of two spherical lines.
 * Calls skey_cmp(const int32 *, const int32 *) for two lines.
 */
Datum	sphereline_cmp(PG_FUNCTION_ARGS);

/*
 * Returns relationship between the keys of two spherical paths.
 * Calls skey_cmp(const int32 *, const int32 *) for two paths.
 */
Datum	spherepath_cmp(PG_FUNCTION_ARGS);

/*
 * Returns relationship between the keys of two spherical polygons.
 * Calls skey_cmp(const int32 *, const int32 *) for two polygons.
 */
Datum	spherepoly_cmp(PG_FUNCTION_ARGS);

/*
 * Returns relationship between the keys of two spherical boxes.
 * Calls skey_cmp(const int32 *, const int32 *) for two boxes.
 */
Datum	spherebox_cmp(PG_FUNCTION_ARGS);

#endif
