/*
 * BRIN SUPPORT for spheric objects:
 *
 * The stored type is the spherekey, as for GiST support,
 * so include some already defined stuffs. We have to define
 * then all the cross-type functions needed by the OpFamilies.
 */

#include "brin.h"
#include "gist.h"
#include <fmgr.h>

/*
 * Functions needed to build a BRIN index
 */
PG_FUNCTION_INFO_V1(spoint_brin_inclusion_add_value);
PG_FUNCTION_INFO_V1(sbox_brin_inclusion_add_value);

/*
 * Functions needed to define supported operators
 */
PG_FUNCTION_INFO_V1(spoint_overlaps_spherekey);
PG_FUNCTION_INFO_V1(spoint_contains_spherekey);
PG_FUNCTION_INFO_V1(spoint_iscontained_spherekey);
PG_FUNCTION_INFO_V1(sbox_overlaps_spherekey);
PG_FUNCTION_INFO_V1(sbox_contains_spherekey);
PG_FUNCTION_INFO_V1(sbox_iscontained_spherekey);
PG_FUNCTION_INFO_V1(spherekey_overlaps_spherekey);
PG_FUNCTION_INFO_V1(spherekey_contains_spherekey);
PG_FUNCTION_INFO_V1(spherekey_iscontained_spherekey);
PG_FUNCTION_INFO_V1(spoint_overlaps_sbox);
PG_FUNCTION_INFO_V1(sbox_iscontained_spoint);

Datum
spoint_brin_inclusion_add_value(PG_FUNCTION_ARGS)
{
	BrinValues *column = (BrinValues *) PG_GETARG_POINTER(1);
	SPoint	   *newval = (SPoint *) DatumGetPointer(PG_GETARG_DATUM(2));
	bool		isnull = PG_GETARG_BOOL(3);
	int32		spointkey[6];
	int32	   *skey = (int32 *) column->bv_values[INCLUSION_UNION];

	/*
	 * If the new value is null, we record that we saw it if it's the first
	 * one; otherwise, there's nothing to do.
	 */
	if (isnull)
	{
		if (column->bv_hasnulls)
			PG_RETURN_BOOL(false);

		column->bv_hasnulls = true;
		PG_RETURN_BOOL(true);
	}

	spherepoint_gen_key(&spointkey, newval);

	/*
	 * If spherekey pointer is NULL, we consider the spoint entry as 'empty'.
	 *
	 * The OpClass support empty entries: we need to set the "contains empty"
	 * flag in the element (unless already set).
	 */
	if (spointkey == NULL)
	{
		if (!DatumGetBool(column->bv_values[INCLUSION_CONTAINS_EMPTY]))
		{
			column->bv_values[INCLUSION_CONTAINS_EMPTY] = BoolGetDatum(true);
			PG_RETURN_BOOL(true);
		}

		PG_RETURN_BOOL(false);
	}

	/* if the recorded value is null, we just need to store the spherekey */
	if (column->bv_allnulls)
	{
		column->bv_values[INCLUSION_UNION] = datumCopy((Datum) spointkey, false,
													   (sizeof(int32) * 6));
		column->bv_values[INCLUSION_UNMERGEABLE] = BoolGetDatum(false);
		column->bv_values[INCLUSION_CONTAINS_EMPTY] = BoolGetDatum(false);
		column->bv_allnulls = false;
		PG_RETURN_BOOL(true);
	}

	/*
	 * Check if the stored spherekey already contains the key of the new value
	 */
	if (spherekey_interleave(skey, spointkey) == SCKEY_IN)
	{
		PG_RETURN_BOOL(false);
	}

	/*
	 * Otherwise, we need to enlarge it to contains the current spoint
	 */
	spherekey_union_two(skey, spointkey);

	PG_RETURN_BOOL(true);
}

Datum
sbox_brin_inclusion_add_value(PG_FUNCTION_ARGS)
{
	BrinValues *column = (BrinValues *) PG_GETARG_POINTER(1);
	SBOX	   *newval = (SBOX *) DatumGetPointer(PG_GETARG_DATUM(2));
	bool		isnull = PG_GETARG_BOOL(3);
	int32		sboxkey[6];
	int32	   *skey = (int32 *) column->bv_values[INCLUSION_UNION];

	/*
	 * If the new value is null, we record that we saw it if it's the first
	 * one; otherwise, there's nothing to do.
	 */
	if (isnull)
	{
		if (column->bv_hasnulls)
			PG_RETURN_BOOL(false);

		column->bv_hasnulls = true;
		PG_RETURN_BOOL(true);
	}

	spherebox_gen_key(&sboxkey, newval);

	/*
	 * If spherekey pointer is NULL, we consider the spoint entry as 'empty'.
	 *
	 * The OpClass support empty entries: we need to set the "contains empty"
	 * flag in the element (unless already set).
	 */
	if (sboxkey == NULL)
	{
		if (!DatumGetBool(column->bv_values[INCLUSION_CONTAINS_EMPTY]))
		{
			column->bv_values[INCLUSION_CONTAINS_EMPTY] = BoolGetDatum(true);
			PG_RETURN_BOOL(true);
		}

		PG_RETURN_BOOL(false);
	}

	/* if the recorded value is null, we just need to store the spherekey */
	if (column->bv_allnulls)
	{
		column->bv_values[INCLUSION_UNION] = datumCopy((Datum) sboxkey, false,
													   (sizeof(int32) * 6));
		column->bv_values[INCLUSION_UNMERGEABLE] = BoolGetDatum(false);
		column->bv_values[INCLUSION_CONTAINS_EMPTY] = BoolGetDatum(false);
		column->bv_allnulls = false;
		PG_RETURN_BOOL(true);
	}

	/*
	 * Check if the stored spherekey already contains the key of the new value
	 */
	if (spherekey_interleave(skey, sboxkey) == SCKEY_IN)
	{
		PG_RETURN_BOOL(false);
	}

	/*
	 * Otherwise, we need to enlarge it to contains the current spoint
	 */
	spherekey_union_two(skey, sboxkey);

	PG_RETURN_BOOL(true);
}

/*  */
/*   Define operators procedures below */
/*  */

Datum
spoint_overlaps_spherekey(PG_FUNCTION_ARGS)
{
	int32		k1[6];
	SPoint	   *p1 = (SPoint *) PG_GETARG_POINTER(0);
	int32	   *k2 = (int32 *) PG_GETARG_POINTER(1);

	spherepoint_gen_key(&k1, p1);
	if (spherekey_interleave(k1, k2) == SCKEY_OVERLAP)
	{
		PG_RETURN_BOOL(true);
	}

	PG_RETURN_BOOL(false);
}

Datum
spoint_contains_spherekey(PG_FUNCTION_ARGS)
{
	int32		k1[6];
	SPoint	   *p1 = (SPoint *) PG_GETARG_POINTER(0);
	int32	   *k2 = (int32 *) PG_GETARG_POINTER(1);

	spherepoint_gen_key(&k1, p1);
	if (spherekey_interleave(k1, k2) == SCKEY_IN)
	{
		PG_RETURN_BOOL(true);
	}

	PG_RETURN_BOOL(false);
}

Datum
spoint_iscontained_spherekey(PG_FUNCTION_ARGS)
{
	int32		k1[6];
	SPoint	   *p1 = (SPoint *) PG_GETARG_POINTER(0);
	int32	   *k2 = (int32 *) PG_GETARG_POINTER(1);

	spherepoint_gen_key(&k1, p1);
	if (spherekey_interleave(k2, k1) == SCKEY_IN)
	{
		PG_RETURN_BOOL(true);
	}

	PG_RETURN_BOOL(false);
}

Datum
sbox_overlaps_spherekey(PG_FUNCTION_ARGS)
{
	int32		k1[6];
	SBOX	   *p1 = (SBOX *) PG_GETARG_POINTER(0);
	int32	   *k2 = (int32 *) PG_GETARG_POINTER(1);

	spherebox_gen_key(&k1, p1);
	if (spherekey_interleave(k1, k2) == SCKEY_OVERLAP)
	{
		PG_RETURN_BOOL(true);
	}

	PG_RETURN_BOOL(false);
}

Datum
sbox_contains_spherekey(PG_FUNCTION_ARGS)
{
	int32		k1[6];
	SBOX	   *p1 = (SBOX *) PG_GETARG_POINTER(0);
	int32	   *k2 = (int32 *) PG_GETARG_POINTER(1);

	spherebox_gen_key(&k1, p1);
	if (spherekey_interleave(k1, k2) == SCKEY_IN)
	{
		PG_RETURN_BOOL(true);
	}

	PG_RETURN_BOOL(false);
}

Datum
sbox_iscontained_spherekey(PG_FUNCTION_ARGS)
{
	int32		k1[6];
	SBOX	   *p1 = (SBOX *) PG_GETARG_POINTER(0);
	int32	   *k2 = (int32 *) PG_GETARG_POINTER(1);

	spherebox_gen_key(&k1, p1);
	if (spherekey_interleave(k2, k1) == SCKEY_IN)
	{
		PG_RETURN_BOOL(true);
	}

	PG_RETURN_BOOL(false);
}

Datum
spherekey_overlaps_spherekey(PG_FUNCTION_ARGS)
{
	int32	   *k1 = (int32 *) PG_GETARG_POINTER(0);
	int32	   *k2 = (int32 *) PG_GETARG_POINTER(1);

	if (spherekey_interleave(k1, k2) == SCKEY_OVERLAP)
	{
		PG_RETURN_BOOL(true);
	}

	PG_RETURN_BOOL(false);
}

Datum
spherekey_contains_spherekey(PG_FUNCTION_ARGS)
{
	int32	   *k1 = (int32 *) PG_GETARG_POINTER(0);
	int32	   *k2 = (int32 *) PG_GETARG_POINTER(1);

	if (spherekey_interleave(k1, k2) == SCKEY_IN)
	{
		PG_RETURN_BOOL(true);
	}

	PG_RETURN_BOOL(false);
}

Datum
spherekey_iscontained_spherekey(PG_FUNCTION_ARGS)
{
	int32	   *k1 = (int32 *) PG_GETARG_POINTER(0);
	int32	   *k2 = (int32 *) PG_GETARG_POINTER(1);

	if (spherekey_interleave(k2, k1) == SCKEY_IN)
	{
		PG_RETURN_BOOL(true);
	}

	PG_RETURN_BOOL(false);
}

Datum
spoint_overlaps_sbox(PG_FUNCTION_ARGS)
{
	int32		k1[6];
	SPoint	   *p1 = (SPoint *) PG_GETARG_POINTER(0);
	int32		k2[6];
	SBOX	   *p2 = (SBOX *) PG_GETARG_POINTER(1);

	spherepoint_gen_key(&k1, p1);
	spherebox_gen_key(&k2, p2);

	if (spherekey_interleave(k1, k2) == SCKEY_OVERLAP)
	{
		PG_RETURN_BOOL(true);
	}

	PG_RETURN_BOOL(false);
}

Datum
sbox_iscontained_spoint(PG_FUNCTION_ARGS)
{
	int32		k1[6];
	SBOX	   *p1 = (SBOX *) PG_GETARG_POINTER(0);
	int32		k2[6];
	SPoint	   *p2 = (SPoint *) PG_GETARG_POINTER(1);

	spherebox_gen_key(&k1, p1);
	spherepoint_gen_key(&k2, p2);

	if (spherekey_interleave(k1, k2) == SCKEY_IN)
	{
		PG_RETURN_BOOL(true);
	}

	PG_RETURN_BOOL(false);
}
