#include "gist.h"

/*!
  \file
  \brief Functions needed to build a GIST index
*/

#ifndef DOXYGEN_SHOULD_SKIP_THIS

PG_FUNCTION_INFO_V1(pointkey_in);
PG_FUNCTION_INFO_V1(pointkey_out);
PG_FUNCTION_INFO_V1(pointkey_volume);
PG_FUNCTION_INFO_V1(pointkey_area);
PG_FUNCTION_INFO_V1(pointkey_perimeter);
PG_FUNCTION_INFO_V1(spherekey_in);
PG_FUNCTION_INFO_V1(spherekey_out);
PG_FUNCTION_INFO_V1(g_spherekey_decompress);
PG_FUNCTION_INFO_V1(g_scircle_compress);
PG_FUNCTION_INFO_V1(g_spoint_compress);
PG_FUNCTION_INFO_V1(g_spoint2_compress);
PG_FUNCTION_INFO_V1(g_sline_compress);
PG_FUNCTION_INFO_V1(g_spath_compress);
PG_FUNCTION_INFO_V1(g_spoly_compress);
PG_FUNCTION_INFO_V1(g_sellipse_compress);
PG_FUNCTION_INFO_V1(g_sbox_compress);
PG_FUNCTION_INFO_V1(g_spherekey_union);
PG_FUNCTION_INFO_V1(g_spherekey_same);
PG_FUNCTION_INFO_V1(g_spoint2_union);
PG_FUNCTION_INFO_V1(g_spoint2_same);
PG_FUNCTION_INFO_V1(g_spoint_consistent);
PG_FUNCTION_INFO_V1(g_spoint2_consistent);
PG_FUNCTION_INFO_V1(g_scircle_consistent);
PG_FUNCTION_INFO_V1(g_sline_consistent);
PG_FUNCTION_INFO_V1(g_spath_consistent);
PG_FUNCTION_INFO_V1(g_spoly_consistent);
PG_FUNCTION_INFO_V1(g_sellipse_consistent);
PG_FUNCTION_INFO_V1(g_sbox_consistent);
PG_FUNCTION_INFO_V1(g_spherekey_penalty);
PG_FUNCTION_INFO_V1(g_spherekey_picksplit);
PG_FUNCTION_INFO_V1(g_spoint2_penalty);
PG_FUNCTION_INFO_V1(g_spoint2_picksplit);
PG_FUNCTION_INFO_V1(g_spoint2_distance);

#endif


 /*
  * ! \brief Returns the \link	PGS_KEY_REL Relationship \endlink of two keys
  * \param k1 pointer to first key \param k2 pointer to second key \return
  * \link  PGS_KEY_REL Relationship \endlink
  */
uchar
spherekey_interleave(const int32 *k1, const int32 *k2)
{
	uchar		i;
	static char tb;

	/* i represents x,y,z */

	tb = 0;
	for (i = 0; i < 3; i++)
	{
		tb |= ((k2[i] > k1[i + 3]) || (k1[i] > k2[i + 3]));
		if (tb)
			break;
	}
	if (tb)
	{
		return SCKEY_DISJ;
	}
	tb = 1;
	for (i = 0; i < 3; i++)
	{
		tb &= ((k1[i] == k2[i]) && (k1[i + 3] == k2[i + 3]));
		if (!tb)
			break;
	}
	if (tb)
	{
		return SCKEY_SAME;
	}
	tb = 1;
	for (i = 0; i < 3; i++)
	{
		tb &= (k1[i] <= k2[i] && k1[i + 3] >= k2[i + 3]);
		if (!tb)
			break;
	}
	if (tb)
	{
		/* v2 in v1 */
		return SCKEY_IN;
	}
	return SCKEY_OVERLAP;
}

Datum
spherekey_in(PG_FUNCTION_ARGS)
{
	elog(ERROR, "Not implemented!");
	PG_RETURN_POINTER(NULL);
}

Datum
spherekey_out(PG_FUNCTION_ARGS)
{
	static const float8 ks = (float8) MAXCVALUE;
	int32	   *k = (int32 *) PG_GETARG_POINTER(0);
	char	   *buffer = (char *) MALLOC(1024);

	sprintf(
			buffer,
			"(%.9f,%.9f,%.9f),(%.9f,%.9f,%.9f)",
			k[0] / ks,
			k[1] / ks,
			k[2] / ks,
			k[3] / ks,
			k[4] / ks,
			k[5] / ks
		);

	PG_RETURN_CSTRING(buffer);

}

 /*
  * static void checkKey(GiSTSPointKey *k) { if (!IS_LEAF(k)) { int i; for (i
  * = 0; i < 6; i++) { if (k->k[i] < -MAXCVALUE || k->k[i] > MAXCVALUE) {
  * elog(ERROR, "Invalid key!"); } } } }
  */

static bool
get_sizes(GiSTSPointKey *k, float8 sizes[3])
{
	int			i;
	static const float8 ks = (float8) MAXCVALUE;

	if (IS_LEAF(k))
		return false;

	for (i = 0; i < 3; i++)
	{
		sizes[i] = (((uint64) k->k[i + 3] - (uint64) k->k[i]) + 1) / ks;
	}
	return true;
}

Datum
pointkey_volume(PG_FUNCTION_ARGS)
{
	GiSTSPointKey *k = (GiSTSPointKey *) PG_GETARG_POINTER(0);
	float8		sizes[3];

	if (!get_sizes(k, sizes))
		PG_RETURN_FLOAT8(0.0);

	PG_RETURN_FLOAT8(sizes[0] * sizes[1] * sizes[2]);
}

Datum
pointkey_area(PG_FUNCTION_ARGS)
{
	GiSTSPointKey *k = (GiSTSPointKey *) PG_GETARG_POINTER(0);
	float8		sizes[3];

	if (!get_sizes(k, sizes))
		PG_RETURN_FLOAT8(0.0);

	PG_RETURN_FLOAT8(sizes[0] * sizes[1] + sizes[0] * sizes[2] + sizes[1] * sizes[2]);
}

Datum
pointkey_perimeter(PG_FUNCTION_ARGS)
{
	GiSTSPointKey *k = (GiSTSPointKey *) PG_GETARG_POINTER(0);
	float8		sizes[3];

	if (!get_sizes(k, sizes))
		PG_RETURN_FLOAT8(0.0);

	PG_RETURN_FLOAT8(sizes[0] + sizes[1] + sizes[2]);
}

Datum
pointkey_in(PG_FUNCTION_ARGS)
{
	elog(ERROR, "Not implemented!");
	PG_RETURN_POINTER(NULL);
}

Datum
pointkey_out(PG_FUNCTION_ARGS)
{
	static const float8 ks = (float8) MAXCVALUE;
	GiSTSPointKey *k = (GiSTSPointKey *) PG_GETARG_POINTER(0);
	char	   *buffer = (char *) MALLOC(1024);

	if (IS_LEAF(k))
	{
		sprintf(
				buffer,
				"(%.9f,%.9f)",
				k->lng,
				k->lat
			);
	}
	else
	{
		sprintf(
				buffer,
				"(%.9f,%.9f,%.9f),(%.9f,%.9f,%.9f)",
				k->k[0] / ks,
				k->k[1] / ks,
				k->k[2] / ks,
				k->k[3] / ks,
				k->k[4] / ks,
				k->k[5] / ks
			);
	}

	PG_RETURN_CSTRING(buffer);

}

Datum
g_spherekey_decompress(PG_FUNCTION_ARGS)
{
	PG_RETURN_DATUM(PG_GETARG_DATUM(0));
}

/*!
  \brief general compress method for all data types
  \param type \link PGS_DATA_TYPES data type \endlink
  \param genkey function to generate the key value
  \see key.c
*/
#if PG_VERSION_NUM < 80200
#define PGS_COMPRESS( type, genkey, detoast )  do { \
	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0); \
	GISTENTRY  *retval; \
	if (entry->leafkey) \
	{ \
	  retval  =  MALLOC ( sizeof ( GISTENTRY ) ); \
	  if ( DatumGetPointer(entry->key) != NULL ){ \
		int32 * k = ( int32 * ) MALLOC ( KEYSIZE ) ; \
		if( detoast ) \
		{ \
		  genkey ( k , ( type * )  DatumGetPointer( PG_DETOAST_DATUM( entry->key ) ) ) ; \
		} else { \
		  genkey ( k , ( type * )  DatumGetPointer( entry->key ) ) ; \
		} \
		gistentryinit(*retval, PointerGetDatum(k) , \
		  entry->rel, entry->page, \
		  entry->offset, KEYSIZE , FALSE ); \
	  } else { \
		gistentryinit(*retval, (Datum) 0, \
		  entry->rel, entry->page, \
		  entry->offset, 0, FALSE ); \
	  } \
	} else { \
	  retval = entry; \
	} \
	PG_RETURN_POINTER(retval); \
  } while (0) ;
#else

#define PGS_COMPRESS( type, genkey, detoast )  do { \
	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0); \
	GISTENTRY  *retval; \
	if (entry->leafkey) \
	{ \
	  retval  =  MALLOC ( sizeof ( GISTENTRY ) ); \
	  if ( DatumGetPointer(entry->key) != NULL ){ \
		int32 * k = ( int32 * ) MALLOC ( KEYSIZE ) ; \
		if( detoast ) \
		{ \
		  genkey ( k , ( type * )  DatumGetPointer( PG_DETOAST_DATUM( entry->key ) ) ) ; \
		} else { \
		  genkey ( k , ( type * )  DatumGetPointer( entry->key ) ) ; \
		} \
		gistentryinit(*retval, PointerGetDatum(k) , \
		  entry->rel, entry->page, \
		  entry->offset, FALSE ); \
	  } else { \
		gistentryinit(*retval, (Datum) 0, \
		  entry->rel, entry->page, \
		  entry->offset, FALSE ); \
	  } \
	} else { \
	  retval = entry; \
	} \
	PG_RETURN_POINTER(retval); \
  } while (0) ;
#endif

Datum
g_scircle_compress(PG_FUNCTION_ARGS)
{
	PGS_COMPRESS(SCIRCLE, spherecircle_gen_key, 0)
}

Datum
g_spoint_compress(PG_FUNCTION_ARGS)
{
	PGS_COMPRESS(SPoint, spherepoint_gen_key, 0)
}

Datum
g_sline_compress(PG_FUNCTION_ARGS)
{
	PGS_COMPRESS(SLine, sphereline_gen_key, 0)
}

Datum
g_spath_compress(PG_FUNCTION_ARGS)
{
	PGS_COMPRESS(SPATH, spherepath_gen_key, 1)
}

Datum
g_spoly_compress(PG_FUNCTION_ARGS)
{
	PGS_COMPRESS(SPOLY, spherepoly_gen_key, 1)
}

Datum
g_sellipse_compress(PG_FUNCTION_ARGS)
{
	PGS_COMPRESS(SELLIPSE, sphereellipse_gen_key, 0)
}

Datum
g_sbox_compress(PG_FUNCTION_ARGS)
{
	PGS_COMPRESS(SBOX, spherebox_gen_key, 0)
}

Datum
g_spoint2_compress(PG_FUNCTION_ARGS)
{
	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0);
	GISTENTRY  *retval;

	if (entry->leafkey)
	{
		retval = palloc(sizeof(GISTENTRY));
		if (DatumGetPointer(entry->key) != NULL)
		{
			GiSTSPointKey *key;
			SPoint	   *p = (SPoint *) DatumGetPointer(entry->key);

			ALLOC_LEAF_KEY(key);
			key->lat = p->lat;
			key->lng = p->lng;
			gistentryinit(*retval, PointerGetDatum(key), entry->rel, entry->page,
						  entry->offset, FALSE);
		}
		else
		{
			gistentryinit(*retval, (Datum) 0, entry->rel, entry->page,
						  entry->offset, FALSE);
		}
	}
	else
	{
		retval = entry;
	}
	PG_RETURN_POINTER(retval);
}

Datum
g_spherekey_union(PG_FUNCTION_ARGS)
{
#ifdef GEVHDRSZ
	GistEntryVector *entryvec = (GistEntryVector *) PG_GETARG_POINTER(0);

#else
	bytea	   *entryvec = (bytea *) PG_GETARG_POINTER(0);

#endif
	int		   *sizep = (int *) PG_GETARG_POINTER(1);
	int			numranges,
				i;
	int32	   *ret = (int32 *) MALLOC(KEYSIZE);

#ifdef GEVHDRSZ
	numranges = entryvec->n;
	memcpy((void *) ret, (void *) DatumGetPointer(entryvec->vector[0].key), KEYSIZE);
#else
	numranges = (VARSIZE(entryvec) - VARHDRSZ) / sizeof(GISTENTRY);
	memcpy((void *) ret, (void *) DatumGetPointer(((GISTENTRY *) VARDATA(entryvec))[0].key), KEYSIZE);
#endif

	for (i = 1; i < numranges; i++)
	{
#ifdef GEVHDRSZ
		spherekey_union_two(ret, (int32 *) DatumGetPointer(entryvec->vector[i].key));
#else
		spherekey_union_two(ret, (int32 *) DatumGetPointer(((GISTENTRY *) VARDATA(entryvec))[i].key));
#endif
	}
	*sizep = KEYSIZE;
	PG_RETURN_POINTER(ret);
}

Datum
g_spoint2_union(PG_FUNCTION_ARGS)
{
	GistEntryVector *entryvec = (GistEntryVector *) PG_GETARG_POINTER(0);
	int		   *sizep = (int *) PG_GETARG_POINTER(1);
	int			numranges,
				i;
	GiSTSPointKey *ret;

	ALLOC_INTERNAL_KEY(ret);
	numranges = entryvec->n;

	for (i = 0; i < numranges; i++)
	{
		GiSTSPointKey *key;
		int32	   *p;
		int32		k[6];

		key = (GiSTSPointKey *) DatumGetPointer(entryvec->vector[i].key);

		if (IS_LEAF(key))
		{
			SPoint		point;

			point.lat = key->lat;
			point.lng = key->lng;
			spherepoint_gen_key(k, &point);
			p = k;
		}
		else
		{
			p = key->k;
		}

		if (i == 0)
			memcpy(ret->k, p, KEYSIZE);
		else
			spherekey_union_two(ret->k, p);
		/* checkKey(ret); */
	}
	*sizep = KEYSIZE;
	PG_RETURN_POINTER(ret);
}

Datum
g_spherekey_same(PG_FUNCTION_ARGS)
{
	int32	   *c1 = (int32 *) PG_GETARG_POINTER(0);
	int32	   *c2 = (int32 *) PG_GETARG_POINTER(1);
	bool	   *result = (bool *) PG_GETARG_POINTER(2);
	static int	i;

	*result = TRUE;

	if (c1 && c2)
	{
		for (i = 0; i < 6; i++)
		{
			*result &= (c1[i] == c2[i]);
		}
	}
	else
	{
		*result = (c1 == NULL && c2 == NULL) ? TRUE : FALSE;
	}

	PG_RETURN_POINTER(result);
}

Datum
g_spoint2_same(PG_FUNCTION_ARGS)
{
	GiSTSPointKey *key1 = (GiSTSPointKey *) PG_GETARG_POINTER(0);
	GiSTSPointKey *key2 = (GiSTSPointKey *) PG_GETARG_POINTER(1);
	bool	   *result = (bool *) PG_GETARG_POINTER(2);

	*result = TRUE;
	if (key1 && key2)
	{
		if (VARSIZE(key1) == VARSIZE(key2))
		{
			*result = memcmp(key1, key2, VARSIZE(key1)) ? FALSE : TRUE;
		}
		else
		{
			*result = FALSE;
		}
	}
	else
	{
		*result = (key1 == NULL && key2 == NULL) ? TRUE : FALSE;
	}

	PG_RETURN_POINTER(result);
}


/*!
  \brief general interleave method with query cache
  \param type \link PGS_DATA_TYPES data type \endlink
  \param genkey function to generate the key value
  \param dir for spherekey_interleave what value is the first
		  - 0 : the query key
		  - not 0 : the key entry
  \see key.c gq_cache.c
*/
#define SCK_INTERLEAVE( type , genkey , dir ) do { \
  int32 * q = NULL ; \
  if ( ! gq_cache_get_value ( PGS_TYPE_##type , query, &q ) ){ \
	q = ( int32 *) malloc ( KEYSIZE ); \
	genkey ( q, ( type * ) query ); \
	gq_cache_set_value ( PGS_TYPE_##type , query, q ) ; \
	free ( q ); \
	gq_cache_get_value ( PGS_TYPE_##type , query, &q ) ; \
  } \
  if ( dir ){ \
	i = spherekey_interleave ( ent, q  ); \
  } else { \
	i = spherekey_interleave ( q , ent ); \
  } \
} while (0);


Datum
g_spoint_consistent(PG_FUNCTION_ARGS)
{
	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0);
	void	   *query = (void *) PG_GETARG_POINTER(1);
	StrategyNumber strategy = (StrategyNumber) PG_GETARG_UINT16(2);
	bool		result = FALSE;

	if (DatumGetPointer(entry->key) == NULL || !query)
	{
		PG_RETURN_BOOL(FALSE);
	}
	else
	{

#if PG_VERSION_NUM >= 80400
		bool	   *recheck = (bool *) PG_GETARG_POINTER(4);
#endif
		int32	   *ent = (int32 *) DatumGetPointer(entry->key);
		int			i = SCKEY_DISJ;
#if PG_VERSION_NUM >= 80400
		*recheck = true;
#endif

		switch (strategy)
		{
			case 1:
				SCK_INTERLEAVE(SPoint, spherepoint_gen_key, 1);
				break;
			case 11:
				SCK_INTERLEAVE(SCIRCLE, spherecircle_gen_key, 0);
				break;
			case 12:
				SCK_INTERLEAVE(SLine, sphereline_gen_key, 0);
				break;
			case 13:
				SCK_INTERLEAVE(SPATH, spherepath_gen_key, 0);
				break;
			case 14:
				SCK_INTERLEAVE(SPOLY, spherepoly_gen_key, 0);
				break;
			case 15:
				SCK_INTERLEAVE(SELLIPSE, sphereellipse_gen_key, 0);
				break;
			case 16:
				SCK_INTERLEAVE(SBOX, spherebox_gen_key, 0);
				break;
		}

		if (GIST_LEAF(entry))
		{
			switch (strategy)
			{
				case 1:
					if (i == SCKEY_SAME)
						result = TRUE;
					break;
				default:
					if (i > SCKEY_OVERLAP)
						result = TRUE;
					break;
			}
		}
		else
		{

			switch (strategy)
			{
				case 1:
					if (i > SCKEY_OVERLAP)
						result = TRUE;
					break;
				default:
					if (i > SCKEY_DISJ)
						result = TRUE;
					break;
			}

		}

		PG_RETURN_BOOL(result);

	}
	PG_RETURN_BOOL(FALSE);
}

Datum
g_spoint2_consistent(PG_FUNCTION_ARGS)
{
	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0);
	void	   *query = (void *) PG_GETARG_POINTER(1);
	StrategyNumber strategy = (StrategyNumber) PG_GETARG_UINT16(2);
	bool		result = FALSE;

	if (DatumGetPointer(entry->key) == NULL || !query)
	{
		PG_RETURN_BOOL(FALSE);
	}
	else
	{

#if PG_VERSION_NUM >= 80400
		bool	   *recheck = (bool *) PG_GETARG_POINTER(4);
#endif
		GiSTSPointKey *key = (GiSTSPointKey *) DatumGetPointer(entry->key);
		int			i = SCKEY_DISJ;
#if PG_VERSION_NUM >= 80400
		*recheck = false;
#endif

		if (!IS_LEAF(key))
		{
			int32	   *ent = key->k;

			switch (strategy)
			{
				case 1:
					SCK_INTERLEAVE(SPoint, spherepoint_gen_key, 1);
					break;
				case 11:
					SCK_INTERLEAVE(SCIRCLE, spherecircle_gen_key, 0);
					break;
				case 12:
					SCK_INTERLEAVE(SLine, sphereline_gen_key, 0);
					break;
				case 13:
					SCK_INTERLEAVE(SPATH, spherepath_gen_key, 0);
					break;
				case 14:
					SCK_INTERLEAVE(SPOLY, spherepoly_gen_key, 0);
					break;
				case 15:
					SCK_INTERLEAVE(SELLIPSE, sphereellipse_gen_key, 0);
					break;
				case 16:
					SCK_INTERLEAVE(SBOX, spherebox_gen_key, 0);
					break;
			}
			switch (strategy)
			{
				case 1:
					if (i > SCKEY_OVERLAP)
						result = TRUE;
					break;
				default:
					if (i > SCKEY_DISJ)
						result = TRUE;
					break;
			}
		}
		else
		{
			SPoint		point;

			point.lat = key->lat;
			point.lng = key->lng;
			switch (strategy)
			{
				case 1:
					result = spoint_eq(&point, (SPoint *) query);
					break;
				case 11:
					result = spoint_in_circle(&point, (SCIRCLE *) query);
					break;
				case 12:
					result = spoint_at_sline(&point, (SLine *) query);
					break;
				case 13:
					result = spath_cont_point((SPATH *) query, &point);
					break;
				case 14:
					result = spoly_contains_point((SPOLY *) query, &point);
					break;
				case 15:
					result = sellipse_cont_point((SELLIPSE *) query, &point);
					break;
				case 16:
					result = sbox_cont_point((SBOX *) query, &point);
					break;
			}
		}
		PG_RETURN_BOOL(result);
	}
	PG_RETURN_BOOL(FALSE);
}

Datum
g_spoint2_distance(PG_FUNCTION_ARGS)
{
	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0);
	SPoint	   *query = (SPoint *) PG_GETARG_POINTER(1);

	/* StrategyNumber strategy = (StrategyNumber) PG_GETARG_UINT16(2); */
	GiSTSPointKey *key = (GiSTSPointKey *) DatumGetPointer(entry->key);

	if (IS_LEAF(key))
	{
		SPoint		point;

		point.lat = key->lat;
		point.lng = key->lng;
		PG_RETURN_FLOAT8(spoint_dist(&point, query));
	}
	else
	{
		Vector3D	v;
		float8		sum = 0.0,
					x_min,
					x_max,
					y_min,
					y_max,
					z_min,
					z_max;

		spoint_vector3d(&v, query);

		x_min = (float8) key->k[0] / (float8) MAXCVALUE;
		x_max = (float8) (key->k[3] + 1) / (float8) MAXCVALUE;
		if (v.x < x_min)
			sum += sqr(v.x - x_min);
		else if (v.x > x_max)
			sum += sqr(v.x - x_max);

		y_min = (float8) key->k[1] / (float8) MAXCVALUE;
		y_max = (float8) (key->k[4] + 1) / (float8) MAXCVALUE;
		if (v.y < y_min)
			sum += sqr(v.y - y_min);
		else if (v.y > y_max)
			sum += sqr(v.y - y_max);

		z_min = (float8) key->k[2] / (float8) MAXCVALUE;
		z_max = (float8) (key->k[5] + 1) / (float8) MAXCVALUE;
		if (v.z < z_min)
			sum += sqr(v.z - z_min);
		else if (v.z > z_max)
			sum += sqr(v.z - z_max);

		PG_RETURN_FLOAT8(sqrt(sum));
	}
}

Datum
g_scircle_consistent(PG_FUNCTION_ARGS)
{
	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0);
	void	   *query = (void *) PG_GETARG_POINTER(1);
	StrategyNumber strategy = (StrategyNumber) PG_GETARG_UINT16(2);
	bool		result = FALSE;

	if (DatumGetPointer(entry->key) == NULL || !query)
	{
		PG_RETURN_BOOL(FALSE);
	}
	else
	{

#if PG_VERSION_NUM >= 80400
		bool	   *recheck = (bool *) PG_GETARG_POINTER(4);
#endif
		int32	   *ent = (int32 *) DatumGetPointer(entry->key);
		int			i = SCKEY_DISJ;
#if PG_VERSION_NUM >= 80400
		*recheck = true;
#endif

		switch (strategy)
		{
			case 1:
				SCK_INTERLEAVE(SCIRCLE, spherecircle_gen_key, 1);
				break;
			case 11:
				SCK_INTERLEAVE(SCIRCLE, spherecircle_gen_key, 0);
				break;
			case 12:
				SCK_INTERLEAVE(SPOLY, spherepoly_gen_key, 0);
				break;
			case 13:
				SCK_INTERLEAVE(SELLIPSE, sphereellipse_gen_key, 0);
				break;
			case 14:
				SCK_INTERLEAVE(SBOX, spherebox_gen_key, 0);
				break;
			case 21:
				SCK_INTERLEAVE(SPoint, spherepoint_gen_key, 1);
				break;
			case 22:
				SCK_INTERLEAVE(SCIRCLE, spherecircle_gen_key, 1);
				break;
			case 23:
				SCK_INTERLEAVE(SLine, sphereline_gen_key, 1);
				break;
			case 24:
				SCK_INTERLEAVE(SPATH, spherepath_gen_key, 1);
				break;
			case 25:
				SCK_INTERLEAVE(SPOLY, spherepoly_gen_key, 1);
				break;
			case 26:
				SCK_INTERLEAVE(SELLIPSE, sphereellipse_gen_key, 1);
				break;
			case 27:
				SCK_INTERLEAVE(SBOX, spherebox_gen_key, 1);
				break;
			case 31:
				SCK_INTERLEAVE(SCIRCLE, spherecircle_gen_key, 0);
				break;
			case 32:
				SCK_INTERLEAVE(SLine, sphereline_gen_key, 0);
				break;
			case 33:
				SCK_INTERLEAVE(SPATH, spherepath_gen_key, 0);
				break;
			case 34:
				SCK_INTERLEAVE(SPOLY, spherepoly_gen_key, 0);
				break;
			case 35:
				SCK_INTERLEAVE(SELLIPSE, sphereellipse_gen_key, 0);
				break;
			case 36:
				SCK_INTERLEAVE(SBOX, spherebox_gen_key, 0);
				break;
		}

		if (GIST_LEAF(entry))
		{

			switch (strategy)
			{
				case 1:
					if (i == SCKEY_SAME)
						result = TRUE;
					break;
				default:
					if (i > SCKEY_DISJ)
						result = TRUE;
					break;
			}
		}
		else
		{
			switch (strategy)
			{
				case 1:
					if (i > SCKEY_OVERLAP)
						result = TRUE;
					break;
				default:
					if (i > SCKEY_DISJ)
						result = TRUE;
					break;
			}
		}
		PG_RETURN_BOOL(result);
	}
	PG_RETURN_BOOL(FALSE);
}



Datum
g_sline_consistent(PG_FUNCTION_ARGS)
{
	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0);
	void	   *query = (void *) PG_GETARG_POINTER(1);
	StrategyNumber strategy = (StrategyNumber) PG_GETARG_UINT16(2);
	bool		result = FALSE;

	if (DatumGetPointer(entry->key) == NULL || !query)
	{
		PG_RETURN_BOOL(FALSE);
	}
	else
	{

#if PG_VERSION_NUM >= 80400
		bool	   *recheck = (bool *) PG_GETARG_POINTER(4);
#endif
		int32	   *ent = (int32 *) DatumGetPointer(entry->key);
		int			i = SCKEY_DISJ;
#if PG_VERSION_NUM >= 80400
		*recheck = true;
#endif

		switch (strategy)
		{
			case 1:
			case 2:
				SCK_INTERLEAVE(SLine, sphereline_gen_key, 1);
				break;
			case 11:
				SCK_INTERLEAVE(SCIRCLE, spherecircle_gen_key, 0);
				break;
			case 12:
				SCK_INTERLEAVE(SPOLY, spherepoly_gen_key, 0);
				break;
			case 13:
				SCK_INTERLEAVE(SELLIPSE, sphereellipse_gen_key, 0);
				break;
			case 14:
				SCK_INTERLEAVE(SBOX, spherebox_gen_key, 0);
				break;
			case 21:
				SCK_INTERLEAVE(SPoint, spherepoint_gen_key, 1);
				break;
			case 31:
				SCK_INTERLEAVE(SCIRCLE, spherecircle_gen_key, 1);
				break;
			case 32:
				SCK_INTERLEAVE(SLine, sphereline_gen_key, 1);
				break;
			case 33:
				SCK_INTERLEAVE(SPATH, spherepath_gen_key, 1);
				break;
			case 34:
				SCK_INTERLEAVE(SPOLY, spherepoly_gen_key, 1);
				break;
			case 35:
				SCK_INTERLEAVE(SELLIPSE, sphereellipse_gen_key, 1);
				break;
			case 36:
				SCK_INTERLEAVE(SBOX, spherebox_gen_key, 1);
				break;

		}

		if (GIST_LEAF(entry))
		{
			switch (strategy)
			{
				case 1:
					if (i == SCKEY_SAME)
						result = TRUE;
					break;
				default:
					if (i > SCKEY_DISJ)
						result = TRUE;
					break;
			}
		}
		else
		{
			switch (strategy)
			{
				case 1:
					if (i > SCKEY_OVERLAP)
						result = TRUE;
					break;
				default:
					if (i > SCKEY_DISJ)
						result = TRUE;
					break;
			}
		}
		PG_RETURN_BOOL(result);
	}
	PG_RETURN_BOOL(FALSE);
}



Datum
g_spath_consistent(PG_FUNCTION_ARGS)
{
	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0);
	void	   *query = (void *) PG_GETARG_POINTER(1);
	StrategyNumber strategy = (StrategyNumber) PG_GETARG_UINT16(2);
	bool		result = FALSE;

	if (DatumGetPointer(entry->key) == NULL || !query)
	{
		PG_RETURN_BOOL(FALSE);
	}
	else
	{

#if PG_VERSION_NUM >= 80400
		bool	   *recheck = (bool *) PG_GETARG_POINTER(4);
#endif
		int32	   *ent = (int32 *) DatumGetPointer(entry->key);
		int			i = SCKEY_DISJ;
#if PG_VERSION_NUM >= 80400
		*recheck = true;
#endif

		switch (strategy)
		{
			case 1:
				SCK_INTERLEAVE(SPATH, spherepath_gen_key, 1);
				break;
			case 11:
				SCK_INTERLEAVE(SCIRCLE, spherecircle_gen_key, 0);
				break;
			case 12:
				SCK_INTERLEAVE(SPOLY, spherepoly_gen_key, 0);
				break;
			case 13:
				SCK_INTERLEAVE(SELLIPSE, sphereellipse_gen_key, 0);
				break;
			case 14:
				SCK_INTERLEAVE(SBOX, spherebox_gen_key, 0);
				break;
			case 21:
				SCK_INTERLEAVE(SPoint, spherepoint_gen_key, 1);
				break;
			case 31:
				SCK_INTERLEAVE(SCIRCLE, spherecircle_gen_key, 1);
				break;
			case 32:
				SCK_INTERLEAVE(SLine, sphereline_gen_key, 1);
				break;
			case 33:
				SCK_INTERLEAVE(SPATH, spherepath_gen_key, 1);
				break;
			case 34:
				SCK_INTERLEAVE(SPOLY, spherepoly_gen_key, 1);
				break;
			case 35:
				SCK_INTERLEAVE(SELLIPSE, sphereellipse_gen_key, 1);
				break;
			case 36:
				SCK_INTERLEAVE(SBOX, spherebox_gen_key, 1);
				break;

		}

		if (GIST_LEAF(entry))
		{
			switch (strategy)
			{
				case 1:
					if (i == SCKEY_SAME)
						result = TRUE;
					break;
				default:
					if (i > SCKEY_DISJ)
						result = TRUE;
					break;
			}
		}
		else
		{
			switch (strategy)
			{
				case 1:
					if (i > SCKEY_OVERLAP)
						result = TRUE;
					break;
				default:
					if (i > SCKEY_DISJ)
						result = TRUE;
					break;
			}
		}
		PG_RETURN_BOOL(result);
	}
	PG_RETURN_BOOL(FALSE);
}


Datum
g_spoly_consistent(PG_FUNCTION_ARGS)
{
	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0);
	void	   *query = (void *) PG_GETARG_POINTER(1);
	StrategyNumber strategy = (StrategyNumber) PG_GETARG_UINT16(2);
	bool		result = FALSE;

	if (DatumGetPointer(entry->key) == NULL || !query)
	{
		PG_RETURN_BOOL(FALSE);
	}
	else
	{

#if PG_VERSION_NUM >= 80400
		bool	   *recheck = (bool *) PG_GETARG_POINTER(4);
#endif
		int32	   *ent = (int32 *) DatumGetPointer(entry->key);
		int			i = SCKEY_DISJ;
#if PG_VERSION_NUM >= 80400
		*recheck = true;
#endif

		switch (strategy)
		{
			case 1:
				SCK_INTERLEAVE(SPATH, spherepath_gen_key, 1);
				break;
			case 11:
				SCK_INTERLEAVE(SCIRCLE, spherecircle_gen_key, 0);
				break;
			case 12:
				SCK_INTERLEAVE(SPOLY, spherepoly_gen_key, 0);
				break;
			case 13:
				SCK_INTERLEAVE(SELLIPSE, sphereellipse_gen_key, 0);
				break;
			case 14:
				SCK_INTERLEAVE(SBOX, spherebox_gen_key, 0);
				break;
			case 21:
				SCK_INTERLEAVE(SPoint, spherepoint_gen_key, 1);
				break;
			case 22:
				SCK_INTERLEAVE(SCIRCLE, spherecircle_gen_key, 1);
				break;
			case 23:
				SCK_INTERLEAVE(SLine, sphereline_gen_key, 1);
				break;
			case 24:
				SCK_INTERLEAVE(SPATH, spherepath_gen_key, 1);
				break;
			case 25:
				SCK_INTERLEAVE(SPOLY, spherepoly_gen_key, 1);
				break;
			case 26:
				SCK_INTERLEAVE(SELLIPSE, sphereellipse_gen_key, 1);
				break;
			case 27:
				SCK_INTERLEAVE(SBOX, spherebox_gen_key, 1);
				break;
			case 31:
				SCK_INTERLEAVE(SCIRCLE, spherecircle_gen_key, 0);
				break;
			case 32:
				SCK_INTERLEAVE(SLine, sphereline_gen_key, 0);
				break;
			case 33:
				SCK_INTERLEAVE(SPATH, spherepath_gen_key, 0);
				break;
			case 34:
				SCK_INTERLEAVE(SPOLY, spherepoly_gen_key, 0);
				break;
			case 35:
				SCK_INTERLEAVE(SELLIPSE, sphereellipse_gen_key, 0);
				break;
			case 36:
				SCK_INTERLEAVE(SBOX, spherebox_gen_key, 0);
				break;
		}

		if (GIST_LEAF(entry))
		{
			switch (strategy)
			{
				case 1:
					if (i == SCKEY_SAME)
						result = TRUE;
					break;
				default:
					if (i > SCKEY_DISJ)
						result = TRUE;
					break;
			}
		}
		else
		{
			switch (strategy)
			{
				case 1:
					if (i > SCKEY_OVERLAP)
						result = TRUE;
					break;
				default:
					if (i > SCKEY_DISJ)
						result = TRUE;
					break;
			}
		}
		PG_RETURN_BOOL(result);
	}
	PG_RETURN_BOOL(FALSE);
}


Datum
g_sellipse_consistent(PG_FUNCTION_ARGS)
{
	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0);
	void	   *query = (void *) PG_GETARG_POINTER(1);
	StrategyNumber strategy = (StrategyNumber) PG_GETARG_UINT16(2);
	bool		result = FALSE;

	if (DatumGetPointer(entry->key) == NULL || !query)
	{
		PG_RETURN_BOOL(FALSE);
	}
	else
	{

#if PG_VERSION_NUM >= 80400
		bool	   *recheck = (bool *) PG_GETARG_POINTER(4);
#endif
		int32	   *ent = (int32 *) DatumGetPointer(entry->key);
		int			i = SCKEY_DISJ;
#if PG_VERSION_NUM >= 80400
		*recheck = true;
#endif

		switch (strategy)
		{
			case 1:
				SCK_INTERLEAVE(SELLIPSE, sphereellipse_gen_key, 1);
				break;
			case 11:
				SCK_INTERLEAVE(SCIRCLE, spherecircle_gen_key, 0);
				break;
			case 12:
				SCK_INTERLEAVE(SPOLY, spherepoly_gen_key, 0);
				break;
			case 13:
				SCK_INTERLEAVE(SELLIPSE, sphereellipse_gen_key, 0);
				break;
			case 14:
				SCK_INTERLEAVE(SBOX, spherebox_gen_key, 0);
				break;
			case 21:
				SCK_INTERLEAVE(SPoint, spherepoint_gen_key, 1);
				break;
			case 22:
				SCK_INTERLEAVE(SCIRCLE, spherecircle_gen_key, 1);
				break;
			case 23:
				SCK_INTERLEAVE(SLine, sphereline_gen_key, 1);
				break;
			case 24:
				SCK_INTERLEAVE(SPATH, spherepath_gen_key, 1);
				break;
			case 25:
				SCK_INTERLEAVE(SPOLY, spherepoly_gen_key, 1);
				break;
			case 26:
				SCK_INTERLEAVE(SELLIPSE, sphereellipse_gen_key, 1);
				break;
			case 27:
				SCK_INTERLEAVE(SBOX, spherebox_gen_key, 1);
				break;
			case 31:
				SCK_INTERLEAVE(SCIRCLE, spherecircle_gen_key, 0);
				break;
			case 32:
				SCK_INTERLEAVE(SLine, sphereline_gen_key, 0);
				break;
			case 33:
				SCK_INTERLEAVE(SPATH, spherepath_gen_key, 0);
				break;
			case 34:
				SCK_INTERLEAVE(SPOLY, spherepoly_gen_key, 0);
				break;
			case 35:
				SCK_INTERLEAVE(SELLIPSE, sphereellipse_gen_key, 0);
				break;
			case 36:
				SCK_INTERLEAVE(SBOX, spherebox_gen_key, 0);
				break;
		}

		if (GIST_LEAF(entry))
		{
			switch (strategy)
			{
				case 1:
					if (i == SCKEY_SAME)
						result = TRUE;
					break;
				default:
					if (i > SCKEY_DISJ)
						result = TRUE;
					break;
			}
		}
		else
		{
			switch (strategy)
			{
				case 1:
					if (i > SCKEY_OVERLAP)
						result = TRUE;
					break;
				default:
					if (i > SCKEY_DISJ)
						result = TRUE;
					break;
			}
		}
		PG_RETURN_BOOL(result);
	}
	PG_RETURN_BOOL(FALSE);
}


Datum
g_sbox_consistent(PG_FUNCTION_ARGS)
{
	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0);
	void	   *query = (void *) PG_GETARG_POINTER(1);
	StrategyNumber strategy = (StrategyNumber) PG_GETARG_UINT16(2);
	bool		result = FALSE;

	if (DatumGetPointer(entry->key) == NULL || !query)
	{
		PG_RETURN_BOOL(FALSE);
	}
	else
	{

#if PG_VERSION_NUM >= 80400
		bool	   *recheck = (bool *) PG_GETARG_POINTER(4);
#endif
		int32	   *ent = (int32 *) DatumGetPointer(entry->key);
		int			i = SCKEY_DISJ;
#if PG_VERSION_NUM >= 80400
		*recheck = true;
#endif

		switch (strategy)
		{
			case 1:
				SCK_INTERLEAVE(SBOX, spherebox_gen_key, 1);
				break;
			case 11:
				SCK_INTERLEAVE(SCIRCLE, spherecircle_gen_key, 0);
				break;
			case 12:
				SCK_INTERLEAVE(SPOLY, spherepoly_gen_key, 0);
				break;
			case 13:
				SCK_INTERLEAVE(SELLIPSE, sphereellipse_gen_key, 0);
				break;
			case 14:
				SCK_INTERLEAVE(SBOX, spherebox_gen_key, 0);
				break;
			case 21:
				SCK_INTERLEAVE(SPoint, spherepoint_gen_key, 1);
				break;
			case 22:
				SCK_INTERLEAVE(SCIRCLE, spherecircle_gen_key, 1);
				break;
			case 23:
				SCK_INTERLEAVE(SLine, sphereline_gen_key, 1);
				break;
			case 24:
				SCK_INTERLEAVE(SPATH, spherepath_gen_key, 1);
				break;
			case 25:
				SCK_INTERLEAVE(SPOLY, spherepoly_gen_key, 1);
				break;
			case 26:
				SCK_INTERLEAVE(SELLIPSE, sphereellipse_gen_key, 1);
				break;
			case 27:
				SCK_INTERLEAVE(SBOX, spherebox_gen_key, 1);
				break;
			case 31:
				SCK_INTERLEAVE(SCIRCLE, spherecircle_gen_key, 0);
				break;
			case 32:
				SCK_INTERLEAVE(SLine, sphereline_gen_key, 0);
				break;
			case 33:
				SCK_INTERLEAVE(SPATH, spherepath_gen_key, 0);
				break;
			case 34:
				SCK_INTERLEAVE(SPOLY, spherepoly_gen_key, 0);
				break;
			case 35:
				SCK_INTERLEAVE(SELLIPSE, sphereellipse_gen_key, 0);
				break;
			case 36:
				SCK_INTERLEAVE(SBOX, spherebox_gen_key, 0);
				break;
		}

		if (GIST_LEAF(entry))
		{
			switch (strategy)
			{
				case 1:
					if (i == SCKEY_SAME)
						result = TRUE;
					break;
				default:
					if (i > SCKEY_DISJ)
						result = TRUE;
					break;
			}
		}
		else
		{
			switch (strategy)
			{
				case 1:
					if (i > SCKEY_OVERLAP)
						result = TRUE;
					break;
				default:
					if (i > SCKEY_DISJ)
						result = TRUE;
					break;
			}
		}
		PG_RETURN_BOOL(result);
	}
	PG_RETURN_BOOL(FALSE);
}


typedef int32 coord_t;

typedef struct
{
	coord_t		coord[3];
} Point3D;


typedef struct
{
	Point3D		low;
	Point3D		high;
} Box3D;

/*static void
checkBox3D(Box3D *box)
{
	  int i;
	  for (i = 0; i < 3; i++)
	  {
		  if (box->low.coord[i] < -MAXCVALUE || box->low.coord[i] > MAXCVALUE)
		  {
			  elog(ERROR, "Invalid key!");
		  }
		  if (box->high.coord[i] < -MAXCVALUE || box->high.coord[i] > MAXCVALUE)
		  {
			  elog(ERROR, "Invalid key!");
		  }
	  }
}*/

static void
adjustBox3D(Box3D *b, Box3D *addon)
{
	int			i;

	for (i = 0; i < 3; i++)
	{
		if (b->high.coord[i] < addon->high.coord[i])
			b->high.coord[i] = addon->high.coord[i];
		if (b->low.coord[i] > addon->low.coord[i])
			b->low.coord[i] = addon->low.coord[i];
	}
}

static inline double
sizeBox3D(Box3D *b)
{
	return (double) ((int64) b->high.coord[0] - (int64) b->low.coord[0]) / MAXCVALUE
		* (double) ((int64) b->high.coord[1] - (int64) b->low.coord[1]) / MAXCVALUE
		* (double) ((int64) b->high.coord[2] - (int64) b->low.coord[2]) / MAXCVALUE;
}

static inline double
unionSizeBox3D(Box3D *a, Box3D *b)
{
	return (double) ((int64) Max(a->high.coord[0], b->high.coord[0]) - (int64) Min(a->low.coord[0], b->low.coord[0])) / MAXCVALUE
		* (double) ((int64) Max(a->high.coord[1], b->high.coord[1]) - (int64) Min(a->low.coord[1], b->low.coord[1])) / MAXCVALUE
		* (double) ((int64) Max(a->high.coord[2], b->high.coord[2]) - (int64) Min(a->low.coord[2], b->low.coord[2])) / MAXCVALUE;
}

/*
 * Trivial split: half of entries will be placed on one page
 * and another half - to another
 */
static void
fallbackSplit(Box3D *boxes, OffsetNumber maxoff, GIST_SPLITVEC *v)
{
	OffsetNumber i;
	Box3D	   *unionL = NULL,
			   *unionR = NULL;
	int			nbytes;

	nbytes = (maxoff + 2) * sizeof(OffsetNumber);
	v->spl_left = (OffsetNumber *) palloc(nbytes);
	v->spl_right = (OffsetNumber *) palloc(nbytes);
	v->spl_nleft = v->spl_nright = 0;

	for (i = FirstOffsetNumber; i <= maxoff; i = OffsetNumberNext(i))
	{
		Box3D	   *cur = &boxes[i];

		if (i <= (maxoff - FirstOffsetNumber + 1) / 2)
		{
			v->spl_left[v->spl_nleft] = i;
			if (unionL == NULL)
			{
				unionL = (Box3D *) palloc(sizeof(Box3D));
				*unionL = *cur;
			}
			else
				adjustBox3D(unionL, cur);

			v->spl_nleft++;
		}
		else
		{
			v->spl_right[v->spl_nright] = i;
			if (unionR == NULL)
			{
				unionR = (Box3D *) palloc(sizeof(Box3D));
				*unionR = *cur;
			}
			else
				adjustBox3D(unionR, cur);

			v->spl_nright++;
		}
	}

	if (v->spl_ldatum_exists)
		adjustBox3D(unionL, (Box3D *) DatumGetPointer(v->spl_ldatum));
	v->spl_ldatum = PointerGetDatum(unionL);

	if (v->spl_rdatum_exists)
		adjustBox3D(unionR, (Box3D *) DatumGetPointer(v->spl_rdatum));
	v->spl_rdatum = PointerGetDatum(unionR);

	v->spl_ldatum_exists = v->spl_rdatum_exists = false;
}

/*
 * Represents information about an entry that can be placed to either group
 * without affecting overlap over selected axis ("common entry").
 */
typedef struct
{
	/* Index of entry in the initial array */
	int			index;
	/* Delta between penalties of entry insertion into different groups */
	double		delta;
} CommonEntry;

/*
 * Context for g_box_consider_split. Contains information about currently
 * selected split and some general information.
 */
typedef struct
{
	int			entriesCount;	/* total number of entries being split */
	Box3D		boundingBox;	/* minimum bounding box across all entries */

	/* Information about currently selected split follows */

	bool		first;			/* true if no split was selected yet */

	coord_t		leftUpper;		/* upper bound of left interval */
	coord_t		rightLower;		/* lower bound of right interval */

	float4		ratio;
	float4		overlap;
	int			dim;			/* axis of this split */
	double		range;			/* width of general MBR projection to the
								 * selected axis */
} ConsiderSplitContext;

/*
 * Interval represents projection of box to axis.
 */
typedef struct
{
	coord_t		lower,
				upper;
} SplitInterval;

/*
 * Interval comparison function by lower bound of the interval;
 */
static inline int
interval_cmp_lower(const void *i1, const void *i2)
{
	coord_t		lower1 = ((const SplitInterval *) i1)->lower,
				lower2 = ((const SplitInterval *) i2)->lower;

	if (lower1 < lower2)
		return -1;
	else if (lower1 > lower2)
		return 1;
	else
		return 0;
}

/*
 * Interval comparison function by upper bound of the interval;
 */
static inline int
interval_cmp_upper(const void *i1, const void *i2)
{
	coord_t		upper1 = ((const SplitInterval *) i1)->upper,
				upper2 = ((const SplitInterval *) i2)->upper;

	if (upper1 < upper2)
		return -1;
	else if (upper1 > upper2)
		return 1;
	else
		return 0;
}

/*
 * Replace negative value with zero.
 */
static inline float
non_negative(float val)
{
	if (val >= 0.0f)
		return val;
	else
		return 0.0f;
}

/* Minimum accepted ratio of split */
#define LIMIT_RATIO 0.3

/*
 * Consider replacement of currently selected split with the better one.
 */
static inline void
g_box_consider_split(ConsiderSplitContext *context, int dimNum,
					 coord_t rightLower, int minLeftCount,
					 coord_t leftUpper, int maxLeftCount)
{
	int			leftCount,
				rightCount;
	float4		ratio,
				overlap;
	double		range;

	/*
	 * Calculate entries distribution ratio assuming most uniform distribution
	 * of common entries.
	 */
	if (minLeftCount >= (context->entriesCount + 1) / 2)
	{
		leftCount = minLeftCount;
	}
	else
	{
		if (maxLeftCount <= context->entriesCount / 2)
			leftCount = maxLeftCount;
		else
			leftCount = context->entriesCount / 2;
	}
	rightCount = context->entriesCount - leftCount;

	/*
	 * Ratio of split - quotient between size of lesser group and total
	 * entries count.
	 */
	ratio = ((float4) Min(leftCount, rightCount)) /
		((float4) context->entriesCount);

	if (ratio > LIMIT_RATIO)
	{
		bool		selectthis = false;

		/*
		 * The ratio is acceptable, so compare current split with previously
		 * selected one. Between splits of one dimension we search for minimal
		 * overlap (allowing negative values) and minimal ration (between same
		 * overlaps. We switch dimension if find less overlap (non-negative)
		 * or less range with same overlap.
		 */
		range = (float8) context->boundingBox.high.coord[dimNum] - (float8) context->boundingBox.low.coord[dimNum];
		overlap = ((float8) leftUpper - (float8) rightLower) / range;

		/* If there is no previous selection, select this */
		if (context->first)
			selectthis = true;
		else if (context->dim == dimNum)
		{
			/*
			 * Within the same dimension, choose the new split if it has a
			 * smaller overlap, or same overlap but better ratio.
			 */
			if (overlap < context->overlap ||
				(overlap == context->overlap && ratio > context->ratio))
				selectthis = true;
		}
		else
		{
			/*
			 * Across dimensions, choose the new split if it has a smaller
			 * *non-negative* overlap, or same *non-negative* overlap but
			 * bigger range. This condition differs from the one described in
			 * the article. On the datasets where leaf MBRs don't overlap
			 * themselves, non-overlapping splits (i.e. splits which have zero
			 * *non-negative* overlap) are frequently possible. In this case
			 * splits tends to be along one dimension, because most distant
			 * non-overlapping splits (i.e. having lowest negative overlap)
			 * appears to be in the same dimension as in the previous split.
			 * Therefore MBRs appear to be very prolonged along another
			 * dimension, which leads to bad search performance. Using range
			 * as the second split criteria makes MBRs more quadratic. Using
			 * *non-negative* overlap instead of overlap as the first split
			 * criteria gives to range criteria a chance to matter, because
			 * non-overlapping splits are equivalent in this criteria.
			 */
			if (non_negative(overlap) < non_negative(context->overlap) ||
				(range > context->range &&
				 non_negative(overlap) <= non_negative(context->overlap)))
				selectthis = true;
		}

		if (selectthis)
		{
			/* save information about selected split */
			context->first = false;
			context->ratio = ratio;
			context->range = range;
			context->overlap = overlap;
			context->rightLower = rightLower;
			context->leftUpper = leftUpper;
			context->dim = dimNum;
		}
	}
}

/*
 * Compare common entries by their deltas.
 */
static int
common_entry_cmp(const void *i1, const void *i2)
{
	double		delta1 = ((const CommonEntry *) i1)->delta,
				delta2 = ((const CommonEntry *) i2)->delta;

	if (delta1 < delta2)
		return -1;
	else if (delta1 > delta2)
		return 1;
	else
		return 0;
}

/*
 * --------------------------------------------------------------------------
 * Double sorting split algorithm. This is used for both boxes and points.
 *
 * The algorithm finds split of boxes by considering splits along each axis.
 * Each entry is first projected as an interval on the X-axis, and different
 * ways to split the intervals into two groups are considered, trying to
 * minimize the overlap of the groups. Then the same is repeated for the
 * Y-axis, and the overall best split is chosen. The quality of a split is
 * determined by overlap along that axis and some other criteria (see
 * g_box_consider_split).
 *
 * After that, all the entries are divided into three groups:
 *
 * 1) Entries which should be placed to the left group
 * 2) Entries which should be placed to the right group
 * 3) "Common entries" which can be placed to any of groups without affecting
 *	  of overlap along selected axis.
 *
 * The common entries are distributed by minimizing penalty.
 *
 * For details see:
 * "A new double sorting-based node splitting algorithm for R-tree", A. Korotkov
 * http://syrcose.ispras.ru/2011/files/SYRCoSE2011_Proceedings.pdf#page=36
 * --------------------------------------------------------------------------
 */
static void
do_picksplit(Box3D *boxes, OffsetNumber maxoff, GIST_SPLITVEC *v)
{
	OffsetNumber i;
	ConsiderSplitContext context;
	Box3D	   *box,
			   *leftBox,
			   *rightBox;
	int			dim,
				commonEntriesCount;
	SplitInterval *intervalsLower,
			   *intervalsUpper;
	CommonEntry *commonEntries;
	int			nentries;
	double		leftBoxSize,
				rightBoxSize;

	memset(&context, 0, sizeof(ConsiderSplitContext));

	nentries = context.entriesCount = maxoff - FirstOffsetNumber + 1;

	/* Allocate arrays for intervals along axes */
	intervalsLower = (SplitInterval *) palloc(nentries * sizeof(SplitInterval));
	intervalsUpper = (SplitInterval *) palloc(nentries * sizeof(SplitInterval));

	/*
	 * Calculate the overall minimum bounding box over all the entries.
	 */
	for (i = FirstOffsetNumber; i <= maxoff; i = OffsetNumberNext(i))
	{
		box = &boxes[i];
		if (i == FirstOffsetNumber)
			context.boundingBox = *box;
		else
			adjustBox3D(&context.boundingBox, box);
	}

	/*
	 * Iterate over axes for optimal split searching.
	 */
	context.first = true;		/* nothing selected yet */
	for (dim = 0; dim < 3; dim++)
	{
		coord_t		leftUpper,
					rightLower;
		int			i1,
					i2;

		/* Project each entry as an interval on the selected axis. */
		for (i = FirstOffsetNumber; i <= maxoff; i = OffsetNumberNext(i))
		{
			box = &boxes[i];
			intervalsLower[i - FirstOffsetNumber].lower = box->low.coord[dim];
			intervalsLower[i - FirstOffsetNumber].upper = box->high.coord[dim];
		}

		/*
		 * Make two arrays of intervals: one sorted by lower bound and another
		 * sorted by upper bound.
		 */
		memcpy(intervalsUpper, intervalsLower,
			   sizeof(SplitInterval) * nentries);
		qsort(intervalsLower, nentries, sizeof(SplitInterval),
			  interval_cmp_lower);
		qsort(intervalsUpper, nentries, sizeof(SplitInterval),
			  interval_cmp_upper);

		/*----
		 * The goal is to form a left and right interval, so that every entry
		 * interval is contained by either left or right interval (or both).
		 *
		 * For example, with the intervals (0,1), (1,3), (2,3), (2,4):
		 *
		 * 0 1 2 3 4
		 * +-+
		 *	 +---+
		 *	   +-+
		 *	   +---+
		 *
		 * The left and right intervals are of the form (0,a) and (b,4).
		 * We first consider splits where b is the lower bound of an entry.
		 * We iterate through all entries, and for each b, calculate the
		 * smallest possible a. Then we consider splits where a is the
		 * uppper bound of an entry, and for each a, calculate the greatest
		 * possible b.
		 *
		 * In the above example, the first loop would consider splits:
		 * b=0: (0,1)-(0,4)
		 * b=1: (0,1)-(1,4)
		 * b=2: (0,3)-(2,4)
		 *
		 * And the second loop:
		 * a=1: (0,1)-(1,4)
		 * a=3: (0,3)-(2,4)
		 * a=4: (0,4)-(2,4)
		 */

		/*
		 * Iterate over lower bound of right group, finding smallest possible
		 * upper bound of left group.
		 */
		i1 = 0;
		i2 = 0;
		rightLower = intervalsLower[i1].lower;
		leftUpper = intervalsUpper[i2].lower;
		while (true)
		{
			/*
			 * Find next lower bound of right group.
			 */
			while (i1 < nentries && rightLower == intervalsLower[i1].lower)
			{
				leftUpper = Max(leftUpper, intervalsLower[i1].upper);
				i1++;
			}
			if (i1 >= nentries)
				break;
			rightLower = intervalsLower[i1].lower;

			/*
			 * Find count of intervals which anyway should be placed to the
			 * left group.
			 */
			while (i2 < nentries && intervalsUpper[i2].upper <= leftUpper)
				i2++;

			/*
			 * Consider found split.
			 */
			g_box_consider_split(&context, dim, rightLower, i1, leftUpper, i2);
		}

		/*
		 * Iterate over upper bound of left group finding greates possible
		 * lower bound of right group.
		 */
		i1 = nentries - 1;
		i2 = nentries - 1;
		rightLower = intervalsLower[i1].upper;
		leftUpper = intervalsUpper[i2].upper;
		while (true)
		{
			/*
			 * Find next upper bound of left group.
			 */
			while (i2 >= 0 && leftUpper == intervalsUpper[i2].upper)
			{
				rightLower = Min(rightLower, intervalsUpper[i2].lower);
				i2--;
			}
			if (i2 < 0)
				break;
			leftUpper = intervalsUpper[i2].upper;

			/*
			 * Find count of intervals which anyway should be placed to the
			 * right group.
			 */
			while (i1 >= 0 && intervalsLower[i1].lower >= rightLower)
				i1--;

			/*
			 * Consider found split.
			 */
			g_box_consider_split(&context, dim,
								 rightLower, i1 + 1, leftUpper, i2 + 1);
		}
	}

	/*
	 * If we failed to find any acceptable splits, use trivial split.
	 */
	if (context.first)
	{
		fallbackSplit(boxes, maxoff, v);
		return;
	}

	/*
	 * Ok, we have now selected the split across one axis.
	 *
	 * While considering the splits, we already determined that there will be
	 * enough entries in both groups to reach the desired ratio, but we did
	 * not memorize which entries go to which group. So determine that now.
	 */

	/* Allocate vectors for results */
	v->spl_left = (OffsetNumber *) palloc(nentries * sizeof(OffsetNumber));
	v->spl_right = (OffsetNumber *) palloc(nentries * sizeof(OffsetNumber));
	v->spl_nleft = 0;
	v->spl_nright = 0;

	/* Allocate bounding boxes of left and right groups */
	leftBox = palloc0(sizeof(Box3D));
	rightBox = palloc0(sizeof(Box3D));

	leftBoxSize = sizeBox3D(leftBox);
	rightBoxSize = sizeBox3D(rightBox);

	/*
	 * Allocate an array for "common entries" - entries which can be placed to
	 * either group without affecting overlap along selected axis.
	 */
	commonEntriesCount = 0;
	commonEntries = (CommonEntry *) palloc(nentries * sizeof(CommonEntry));

	/* Helper macros to place an entry in the left or right group */
#define PLACE_LEFT(box, off)					\
	do {										\
		if (v->spl_nleft > 0)					\
			adjustBox3D(leftBox, box);			\
		else									\
			*leftBox = *(box);					\
		v->spl_left[v->spl_nleft++] = off;		\
	} while(0)

#define PLACE_RIGHT(box, off)					\
	do {										\
		if (v->spl_nright > 0)					\
			adjustBox3D(rightBox, box);			\
		else									\
			*rightBox = *(box);					\
		v->spl_right[v->spl_nright++] = off;	\
	} while(0)

	/*
	 * Distribute entries which can be distributed unambiguously, and collect
	 * common entries.
	 */
	for (i = FirstOffsetNumber; i <= maxoff; i = OffsetNumberNext(i))
	{
		coord_t		lower,
					upper;

		/*
		 * Get upper and lower bounds along selected axis.
		 */
		box = &boxes[i];
		lower = box->low.coord[context.dim];
		upper = box->high.coord[context.dim];

		if (upper <= context.leftUpper)
		{
			/* Fits to the left group */
			if (lower >= context.rightLower)
			{
				/* Fits also to the right group, so "common entry" */
				commonEntries[commonEntriesCount++].index = i;
			}
			else
			{
				/* Doesn't fit to the right group, so join to the left group */
				PLACE_LEFT(box, i);
				/* checkBox3D(leftBox); */
			}
		}
		else
		{
			/*
			 * Each entry should fit on either left or right group. Since this
			 * entry didn't fit on the left group, it better fit in the right
			 * group.
			 */
			Assert(lower >= context.rightLower);

			/* Doesn't fit to the left group, so join to the right group */
			PLACE_RIGHT(box, i);
			/* checkBox3D(rightBox); */
		}
	}

	/*
	 * Distribute "common entries", if any.
	 */
	if (commonEntriesCount > 0)
	{
		/*
		 * Calculate minimum number of entries that must be placed in both
		 * groups, to reach LIMIT_RATIO.
		 */
		int			m = ceil(LIMIT_RATIO * (double) nentries);

		/*
		 * Calculate delta between penalties of join "common entries" to
		 * different groups.
		 */
		for (i = 0; i < commonEntriesCount; i++)
		{
			box = &boxes[i];
			commonEntries[i].delta = Abs((unionSizeBox3D(leftBox, box) - leftBoxSize) -
							 (unionSizeBox3D(rightBox, box) - rightBoxSize));
		}

		/*
		 * Sort "common entries" by calculated deltas in order to distribute
		 * the most ambiguous entries first.
		 */
		qsort(commonEntries, commonEntriesCount, sizeof(CommonEntry), common_entry_cmp);

		/*
		 * Distribute "common entries" between groups.
		 */
		for (i = 0; i < commonEntriesCount; i++)
		{
			box = &boxes[commonEntries[i].index];

			/*
			 * Check if we have to place this entry in either group to achieve
			 * LIMIT_RATIO.
			 */
			if (v->spl_nleft + (commonEntriesCount - i) <= m)
			{
				PLACE_LEFT(box, commonEntries[i].index);
				/* checkBox3D(leftBox); */
			}
			else if (v->spl_nright + (commonEntriesCount - i) <= m)
			{
				PLACE_RIGHT(box, commonEntries[i].index);
				/* checkBox3D(rightBox); */
			}
			else
			{
				/* Otherwise select the group by minimal penalty */
				if (unionSizeBox3D(leftBox, box) - leftBoxSize < unionSizeBox3D(rightBox, box) - rightBoxSize)
				{
					PLACE_LEFT(box, commonEntries[i].index);
					/* checkBox3D(leftBox); */
				}
				else
				{
					PLACE_RIGHT(box, commonEntries[i].index);
					/* checkBox3D(rightBox); */
				}
			}
		}
	}

	/*
	 * checkBox3D(leftBox); checkBox3D(rightBox);
	 */

	v->spl_ldatum = PointerGetDatum(leftBox);
	v->spl_rdatum = PointerGetDatum(rightBox);
}

Datum
g_spherekey_picksplit(PG_FUNCTION_ARGS)
{
	GistEntryVector *entryvec = (GistEntryVector *) PG_GETARG_POINTER(0);
	GIST_SPLITVEC *v = (GIST_SPLITVEC *) PG_GETARG_POINTER(1);
	OffsetNumber i,
				maxoff;
	Box3D	   *boxes;

	maxoff = entryvec->n - 1;
	boxes = (Box3D *) palloc(sizeof(Box3D) * entryvec->n);
	for (i = FirstOffsetNumber; i <= maxoff; i = OffsetNumberNext(i))
		boxes[i] = *((Box3D *) DatumGetPointer(entryvec->vector[i].key));

	do_picksplit(boxes, maxoff, v);

	PG_RETURN_POINTER(v);
}

Datum
g_spoint2_picksplit(PG_FUNCTION_ARGS)
{
	GistEntryVector *entryvec = (GistEntryVector *) PG_GETARG_POINTER(0);
	GIST_SPLITVEC *v = (GIST_SPLITVEC *) PG_GETARG_POINTER(1);
	OffsetNumber i,
				maxoff;
	Box3D	   *boxes;
	GiSTSPointKey *leftKey,
			   *rightKey;

	maxoff = entryvec->n - 1;
	boxes = (Box3D *) palloc(sizeof(Box3D) * entryvec->n);
	for (i = FirstOffsetNumber; i <= maxoff; i = OffsetNumberNext(i))
	{
		GiSTSPointKey *key = (GiSTSPointKey *) DatumGetPointer(entryvec->vector[i].key);

		/* checkKey(key); */
		if (IS_LEAF(key))
		{
			SPoint		point;

			point.lat = key->lat;
			point.lng = key->lng;
			spherepoint_gen_key((int32 *) &boxes[i], &point);
		}
		else
		{
			boxes[i] = *((Box3D *) key->k);
		}
		/* checkBox3D(&boxes[i]); */
	}

	do_picksplit(boxes, maxoff, v);

	ALLOC_INTERNAL_KEY(leftKey);
	ALLOC_INTERNAL_KEY(rightKey);
	memcpy(leftKey->k, DatumGetPointer(v->spl_ldatum), KEYSIZE);
	memcpy(rightKey->k, DatumGetPointer(v->spl_rdatum), KEYSIZE);
	v->spl_ldatum = PointerGetDatum(leftKey);
	v->spl_rdatum = PointerGetDatum(rightKey);

	/* checkKey(leftKey); */
	/* checkKey(rightKey); */

	PG_RETURN_POINTER(v);
}

 /*
  * The GiST Penalty method for boxes. We have to make panalty as fast as
  * possible ( offen called ! )
  */
Datum
g_spherekey_penalty(PG_FUNCTION_ARGS)
{
	GISTENTRY  *origentry = (GISTENTRY *) PG_GETARG_POINTER(0);
	GISTENTRY  *newentry = (GISTENTRY *) PG_GETARG_POINTER(1);
	float	   *result = (float *) PG_GETARG_POINTER(2);
	Box3D	   *o = (Box3D *) DatumGetPointer(origentry->key);

	if (newentry != NULL)
	{
		Box3D	   *n = (Box3D *) DatumGetPointer(newentry->key);

		*result = (float) (((uint64) (Max(o->high.coord[0], n->high.coord[0]) - Min(o->low.coord[0], n->low.coord[0])) >> 10)
						   * ((uint64) (Max(o->high.coord[1], n->high.coord[1]) - Min(o->low.coord[1], n->low.coord[1])) >> 10)
						   * ((uint64) (Max(o->high.coord[2], n->high.coord[2]) - Min(o->low.coord[2], n->low.coord[2])) >> 10)
					  - ((uint64) (o->high.coord[0] - o->low.coord[0]) >> 10)
					  * ((uint64) (o->high.coord[1] - o->low.coord[1]) >> 10)
					* ((uint64) (o->high.coord[2] - o->low.coord[2]) >> 10));
		PG_RETURN_POINTER(result);
	}
	else
	{
		PG_RETURN_POINTER(NULL);
	}
}

/*
* The GiST Penalty method for spherical points.
* We have to make panalty as fast as possible (offen called !)
*/
Datum
g_spoint2_penalty(PG_FUNCTION_ARGS)
{
	GISTENTRY  *origentry = (GISTENTRY *) PG_GETARG_POINTER(0);
	GISTENTRY  *newentry = (GISTENTRY *) PG_GETARG_POINTER(1);
	float	   *result = (float *) PG_GETARG_POINTER(2);
	GiSTSPointKey *origkey = (GiSTSPointKey *) DatumGetPointer(origentry->key);
	GiSTSPointKey *newkey = (GiSTSPointKey *) DatumGetPointer(newentry->key);
	Box3D	   *o,
			   *n;
	int32		k[6],
				ok[6];

	if (IS_LEAF(origkey))
	{
		SPoint		point;

		point.lat = origkey->lat;
		point.lng = origkey->lng;
		spherepoint_gen_key(ok, &point);
		o = (Box3D *) ok;
	}
	else
	{
		o = (Box3D *) origkey->k;
	}

	if (newentry == NULL)
		PG_RETURN_NULL();

	if (IS_LEAF(newkey))
	{
		int32	   *ptr;
		SPoint		point;

		point.lat = newkey->lat;
		point.lng = newkey->lng;
		if (!gq_cache_get_value(PGS_TYPE_SPoint, &point, &ptr))
		{
			spherepoint_gen_key(k, &point);
			gq_cache_set_value(PGS_TYPE_SPoint, &point, k);
			n = (Box3D *) k;
		}
		else
		{
			n = (Box3D *) ptr;
		}
	}
	else
	{
		n = (Box3D *) newkey->k;
	}

	*result =
		(
		 (float) ((int64) Max(o->high.coord[0], n->high.coord[0])
				  - (int64) Min(o->low.coord[0], n->low.coord[0]))) * ((float) ((int64) Max(o->high.coord[1], n->high.coord[1]) - (int64) Min(o->low.coord[1], n->low.coord[1])))
		* ((float) ((int64) Max(o->high.coord[2], n->high.coord[2]) - (int64) Min(o->low.coord[2], n->low.coord[2])))
		- ((float) ((int64) o->high.coord[0] - (int64) o->low.coord[0]))
		* ((float) ((int64) o->high.coord[1] - (int64) o->low.coord[1]))
		* ((float) ((int64) o->high.coord[2] - (int64) o->low.coord[2]));
	PG_RETURN_POINTER(result);
}
