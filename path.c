#include "path.h"

/*
 *  Path functions
 */

PG_FUNCTION_INFO_V1(spherepath_in);
PG_FUNCTION_INFO_V1(spherepath_get_point);
PG_FUNCTION_INFO_V1(spherepath_point);
PG_FUNCTION_INFO_V1(spherepath_equal);
PG_FUNCTION_INFO_V1(spherepath_equal_neg);
PG_FUNCTION_INFO_V1(spherepath_length);
PG_FUNCTION_INFO_V1(spherepath_npts);
PG_FUNCTION_INFO_V1(spherepath_swap);
PG_FUNCTION_INFO_V1(spherepath_cont_point);
PG_FUNCTION_INFO_V1(spherepath_cont_point_neg);
PG_FUNCTION_INFO_V1(spherepath_cont_point_com);
PG_FUNCTION_INFO_V1(spherepath_cont_point_com_neg);
PG_FUNCTION_INFO_V1(spherepath_overlap_line);
PG_FUNCTION_INFO_V1(spherepath_overlap_line_neg);
PG_FUNCTION_INFO_V1(spherepath_overlap_line_com);
PG_FUNCTION_INFO_V1(spherepath_overlap_line_com_neg);
PG_FUNCTION_INFO_V1(spherecircle_cont_path);
PG_FUNCTION_INFO_V1(spherecircle_cont_path_neg);
PG_FUNCTION_INFO_V1(spherecircle_cont_path_com);
PG_FUNCTION_INFO_V1(spherecircle_cont_path_com_neg);
PG_FUNCTION_INFO_V1(spherecircle_overlap_path);
PG_FUNCTION_INFO_V1(spherecircle_overlap_path_neg);
PG_FUNCTION_INFO_V1(spherecircle_overlap_path_com);
PG_FUNCTION_INFO_V1(spherecircle_overlap_path_com_neg);
PG_FUNCTION_INFO_V1(spherepoly_cont_path);
PG_FUNCTION_INFO_V1(spherepoly_cont_path_neg);
PG_FUNCTION_INFO_V1(spherepoly_cont_path_com);
PG_FUNCTION_INFO_V1(spherepoly_cont_path_com_neg);
PG_FUNCTION_INFO_V1(spherepoly_overlap_path);
PG_FUNCTION_INFO_V1(spherepoly_overlap_path_neg);
PG_FUNCTION_INFO_V1(spherepoly_overlap_path_com);
PG_FUNCTION_INFO_V1(spherepoly_overlap_path_com_neg);
PG_FUNCTION_INFO_V1(spherepath_overlap_path);
PG_FUNCTION_INFO_V1(spherepath_overlap_path_neg);
PG_FUNCTION_INFO_V1(sphereellipse_cont_path);
PG_FUNCTION_INFO_V1(sphereellipse_cont_path_neg);
PG_FUNCTION_INFO_V1(sphereellipse_cont_path_com);
PG_FUNCTION_INFO_V1(sphereellipse_cont_path_com_neg);
PG_FUNCTION_INFO_V1(sphereellipse_overlap_path);
PG_FUNCTION_INFO_V1(sphereellipse_overlap_path_neg);
PG_FUNCTION_INFO_V1(sphereellipse_overlap_path_com);
PG_FUNCTION_INFO_V1(sphereellipse_overlap_path_com_neg);
PG_FUNCTION_INFO_V1(spheretrans_path);
PG_FUNCTION_INFO_V1(spheretrans_path_inverse);
PG_FUNCTION_INFO_V1(spherepath_add_point);
PG_FUNCTION_INFO_V1(spherepath_add_points_finalize);


/*
 * Converts an array of spherical points to SPATH.
 *
 * arr   - pointer to the array of spherical points
 * nelem - count of elements
 *
 * Returns pointer to created spherical polygon.
 */
static SPATH *
spherepath_from_array(SPoint *arr, int32 nelem)
{
	SPATH *path = NULL;

	if (nelem < 2)
	{
		elog(ERROR, "spherepath_from_array: more than one point needed");
		return NULL;
	}
	else
	{

		int32	i;
		float8	scheck;
		int32	size;

		for (i = 0; i < nelem; i++)
		{
			spoint_check(&arr[i]);
		}

		/* check duplicate points */
		i = 0;
		while (i < (nelem - 1))
		{
			if (nelem < 2)
				break;
			if (spoint_eq(&arr[i], &arr[i + 1]))
			{
				if (i < (nelem - 2))
				{
					memmove((void *) &arr[i + 1],
							(void *) &arr[i + 2],
							(nelem - i - 2) * sizeof(SPoint));
				}
				nelem--;
				continue;
			}
			i++;
		}
		if (nelem < 2)
		{
			elog(ERROR, "spherepath_from_array: more than one point needed");
			return NULL;
		}

		size = offsetof(SPATH, p[0]) +sizeof(path->p[0]) * nelem;
		path = (SPATH *) palloc(size);
		SET_VARSIZE(path, size);
		path->npts = nelem;
		for (i = 0; i < nelem; i++)
		{
			if (i > 0)
			{
				scheck = spoint_dist(&arr[i - 1], &arr[i]);
				if (FPeq(scheck, PI))
				{
					elog(ERROR, "spherepath_from_array: a path segment length must be not equal 180 degrees.");
					return NULL;
				}
			}
			memcpy((void *) &path->p[i], (void *) &arr[i], sizeof(SPoint));
		}

	}

	return (path);

}

/*
 * Performs an Euler transformation on a path.
 *
 * out - pointer to the result path
 * in  - pointer to the input path
 * se  - pointer to the Euler transformation
 *
 * Returns the pointer to the result path.
 */
static void
euler_spath_trans(SPATH *out, const SPATH *in, const SEuler *se)
{
	int32 i;

	out->size = in->size;
	out->npts = in->npts;
	for (i = 0; i < in->npts; i++)
		euler_spoint_trans(&out->p[i], &in->p[i], se);
}

/*
 * Returns the relationship between a path and a circle as
 * PGS_CIRCLE_PATH_REL int8 value.
 *
 * path - pointer to the path
 * circ - pointer to the circle
 */
static int8
path_circle_pos(const SPATH *path, const SCIRCLE *circ)
{
	int8		pos;
	int32		i;
	SLine		sl;
	int32		n;
	const int8	sc_in = (1 << PGS_CIRCLE_CONT_LINE);
	const int8	sc_ov = (1 << PGS_CIRCLE_LINE_OVER);
	const int8	sc_os = (1 << PGS_CIRCLE_LINE_AVOID);

	n = path->npts - 1;
	pos = 0;

	if (FPzero(circ->radius))
	{
		bool		pcp = spath_cont_point(path, &circ->center);

		if (pcp)
		{
			return PGS_CIRCLE_PATH_OVER;
		}
		else
		{
			return PGS_CIRCLE_PATH_AVOID;
		}
	}

	for (i = 0; i < n; i++)
	{
		spath_segment(&sl, path, i);
		pos |= (1 << sphereline_circle_pos(&sl, circ));
		if (pos & sc_ov)
		{
			return PGS_CIRCLE_PATH_OVER;
		}
	}

	if (pos == sc_in)
	{
		/* all lines inside circle */
		/* circle contains path */
		return PGS_CIRCLE_CONT_PATH;
	}
	else if (pos == sc_os)
	{
		/* all lines outside circle */
		/* circle outside path */
		return PGS_CIRCLE_PATH_AVOID;
	}

	/* circle and path overlap */
	return PGS_CIRCLE_PATH_OVER;
}


/*
 * Checks whether a path and a line are overlapping.
 *
 * line - pointer to the line
 * path - pointer to the path
 *
 * Returns true if overlapping.
 */
static bool
path_line_overlap(const SPATH *path, const SLine *line)
{
	int32	i;
	SLine	sl;
	int32	n;

	n = path->npts - 1;

	for (i = 0; i < n; i++)
	{
		spath_segment(&sl, path, i);
		if (sline_sline_pos(&sl, line) != PGS_LINE_AVOID)
		{
			return true;
		}
	}
	return false;
}


/*
 * Returns the relationship between a path and a circle as
 * PGS_ELLIPSE_PATH_REL int8 value.
 *
 * path - pointer to the path
 * ell  - pointer to the ellipse
 */
static int8
path_ellipse_pos(const SPATH *path, const SELLIPSE *ell)
{
	int8		pos;
	int32		i;
	SLine		sl;
	int32		n;
	const int8	sc_in = (1 << PGS_ELLIPSE_CONT_LINE);
	const int8	sc_ov = (1 << PGS_ELLIPSE_LINE_OVER);
	const int8	sc_os = (1 << PGS_ELLIPSE_LINE_AVOID);

	pos = 0;
	n = path->npts - 1;

	if (FPzero(ell->rad[0]))
	{
		bool	pcp;
		SPoint	cen;

		sellipse_center(&cen, ell);
		pcp = spath_cont_point(path, &cen);
		if (pcp)
		{
			return PGS_ELLIPSE_PATH_OVER;
		}
		else
		{
			return PGS_ELLIPSE_PATH_AVOID;
		}
	}

	if (FPzero(ell->rad[1]))
	{
		SLine	l;

		sellipse_line(&l, ell);
		/* TODO implement ellipse contains path if ellipse is a line */
		if (path_line_overlap(path, &l))
		{
			return PGS_ELLIPSE_PATH_OVER;
		}
		else
		{
			return PGS_ELLIPSE_PATH_AVOID;
		}
	}

	for (i = 0; i < n; i++)
	{
		spath_segment(&sl, path, i);
		pos |= (1 << sellipse_line_pos(ell, &sl));
		if (pos & sc_ov)
		{
			return PGS_ELLIPSE_PATH_OVER;
		}
	}

	if (pos == sc_in)
	{
		/* all lines inside ellipse */
		/* ellipse contains path */
		return PGS_ELLIPSE_CONT_PATH;
	}
	else if (pos == sc_os)
	{
		/* all lines outside ellipse */
		/* ellipse outside path */
		return PGS_ELLIPSE_PATH_AVOID;
	}

	/* ellipse and path overlap */
	return PGS_ELLIPSE_PATH_OVER;
}


/*
 * Checks whether two pathes are overlapping.
 *
 * path1 - pointer to the first path
 * path2 - pointer to the second path
 *
 * Returns true if overlapping.
 */
static bool
path_overlap(const SPATH *path1, const SPATH *path2)
{
	int32	i;
	SLine	sl;

	for (i = 0; i < path1->npts; i++)
	{
		spath_segment(&sl, path1, i);
		if (path_line_overlap(path2, &sl))
		{
			/* overlap */
			return true;
		}
	}
	return false;
}


/*
 * Returns the relationship between a path and a polygon as
 * PGS_POLY_PATH_REL int8 value.
 *
 * path - pointer to the path
 * poly - pointer to the polygon
 */
static int8
path_poly_pos(const SPATH *path, const SPOLY *poly)
{
	int32		i;
	SLine		sl;
	int8		pos,
				res;
	int32		n;
	const int8	sp_os = (1 << PGS_LINE_POLY_AVOID);
	const int8	sp_ct = (1 << PGS_POLY_CONT_LINE);
	const int8	sp_ov = (1 << PGS_LINE_POLY_OVER);

	n = path->npts - 1;
	pos = res = 0;

	for (i = 0; i < n; i++)
	{

		spath_segment(&sl, path, i);
		pos = (1 << poly_line_pos(poly, &sl));
		if (pos == sp_ov)
		{
			return PGS_POLY_PATH_OVER; /* overlap */
		}
		res |= pos;
	}

	if (res == sp_os)
	{
		return PGS_POLY_PATH_AVOID;
	}
	if (res == sp_ct)
	{
		return PGS_POLY_CONT_PATH;
	}
	return PGS_POLY_OVER;
}


 /*
  * Returns the i-th point of a path.
  *
  * sp   - pointer to the result point
  * path - pointer to the path
  * i    - number of the point
  *
  * Returns pointer to result point.
  *
  * See spath_point(SPoint * , SPATH *, float8)
  */
static bool
spath_get_point(SPoint *sp, const SPATH *path, int32 i)
{
	if (i >= 0 && i < path->npts)
	{
		memcpy((void *) sp, (void *) &path->p[i], sizeof(SPoint));
		return true;
	}
	return false;
}

 /*
  * This function interpolates between points. Returns the f-th point
  * of a path.
  *
  * sp   - pointer to the result point
  * path - pointer to the path
  * f    - 'number' of the point
  *
  * Returns pointer to result point.
  *
  * See spherepath_point(PG_FUNCTION_ARGS)
  */
static bool
spath_point(SPoint *sp, const SPATH *path, float8 f)
{
	SLine		sl;
	int32		i;

	i = (int32) floor(f);

	if (spath_segment(&sl, path, i))
	{
		SEuler	se;
		SPoint	tp;

		sphereline_to_euler(&se, &sl);

		tp.lng = sl.length * (f - (float8) i);
		tp.lat = 0.0;
		euler_spoint_trans(sp, &tp, &se);
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * Checks whether two pathes are equal.
 *
 * p1 - pointer to the first path
 * p2 - pointer to the second path
 */
bool
spath_eq(const SPATH *p1, const SPATH *p2)
{
	if (p1->npts == p2->npts)
	{
		int32	i;
		bool	ret;

		ret = true;

		for (i = 0; i < p1->npts; i++)
		{
			if (!spoint_eq(&p1->p[i], &p2->p[i]))
			{
				ret = false;
				break;
			}
		}
		return ret;
	}
	return false;
}

bool
spath_cont_point(const SPATH *path, const SPoint *sp)
{
	int32	n;
	bool	ret;
	SLine	sl;
	int32	i;

	n = path->npts - 1;
	ret = false;

	for (i = 0; i < n; i++)
	{
		spath_segment(&sl, path, i);
		if (spoint_at_sline(sp, &sl))
		{
			ret = true;
			break;
		}
	}

	return ret;
}

bool
spath_segment(SLine *sl, const SPATH *path, int32 i)
{
	if (i >= 0 && i < (path->npts - 1))
	{
		sline_from_points(sl, &path->p[i], &path->p[i + 1]);
		return true;
	}
	return false;
}

Datum
spherepath_in(PG_FUNCTION_ARGS)
{
	SPATH	   *path;
	char	   *c = PG_GETARG_CSTRING(0);
	int32		i, nelem;
	void		sphere_yyparse(void);

	init_buffer(c);
	sphere_yyparse();

	nelem = get_path_count();
	if (nelem > 1)
	{
		SPoint		arr[nelem];

		for (i = 0; i < nelem; i++)
		{
			get_path_elem(i, &arr[i].lng, &arr[i].lat);
		}
		path = spherepath_from_array(&arr[0], nelem);
	}
	else
	{
		reset_buffer();
		elog(ERROR, "spherepath_in: more than one point needed");
		PG_RETURN_NULL();
	}
	reset_buffer();

	PG_RETURN_POINTER(path);
}


Datum
spherepath_get_point(PG_FUNCTION_ARGS)
{
	int32		i;
	SPATH	   *path = PG_GETARG_SPATH(0);
	SPoint	   *sp = (SPoint *) palloc(sizeof(SPoint));

	i = PG_GETARG_INT32(1);
	if (spath_get_point(sp, path, i - 1))
	{
		PG_RETURN_POINTER(sp);
	}
	pfree(sp);
	PG_RETURN_NULL();
}

Datum
spherepath_point(PG_FUNCTION_ARGS)
{
	float8		i;
	SPATH	   *path = PG_GETARG_SPATH(0);
	SPoint	   *sp = (SPoint *) palloc(sizeof(SPoint));

	i = PG_GETARG_FLOAT8(1);

	if (spath_point(sp, path, i - 1))
	{
		PG_RETURN_POINTER(sp);
	}
	pfree(sp);
	PG_RETURN_NULL();
}

Datum
spherepath_equal(PG_FUNCTION_ARGS)
{
	SPATH	   *p1 = PG_GETARG_SPATH(0);
	SPATH	   *p2 = PG_GETARG_SPATH(1);

	PG_RETURN_BOOL(spath_eq(p1, p2));
}

Datum
spherepath_equal_neg(PG_FUNCTION_ARGS)
{
	SPATH	   *p1 = PG_GETARG_SPATH(0);
	SPATH	   *p2 = PG_GETARG_SPATH(1);

	PG_RETURN_BOOL(!spath_eq(p1, p2));
}

Datum
spherepath_length(PG_FUNCTION_ARGS)
{
	SPATH	   *path = PG_GETARG_SPATH(0);
	int32		i;
	SLine		l;
	float8		sum;
	int32		n;

	n = path->npts - 1;
	sum = 0.0;

	for (i = 0; i < n; i++)
	{
		spath_segment(&l, path, i);
		sum += l.length;
	}
	PG_RETURN_FLOAT8(sum);
}

Datum
spherepath_npts(PG_FUNCTION_ARGS)
{
	SPATH	   *path = PG_GETARG_SPATH(0);

	PG_RETURN_INT32(path->npts);
}

Datum
spherepath_swap(PG_FUNCTION_ARGS)
{
	SPATH	   *path = PG_GETARG_SPATH(0);
	int32		i;
	int32		n;
	SPATH	   *ret = (SPATH *) palloc(VARSIZE(path));

	n = path->npts - 1;

	for (i = 0; i < n; i++)
	{
		memcpy((void *) &ret->p[i], (void *) &path->p[n - i], sizeof(SPoint));
	}
	ret->size = path->size;
	ret->npts = path->npts;
	PG_RETURN_POINTER(ret);
}

Datum
spherepath_cont_point(PG_FUNCTION_ARGS)
{
	SPATH	   *path = PG_GETARG_SPATH(0);
	SPoint	   *sp = (SPoint *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(spath_cont_point(path, sp));
}

Datum
spherepath_cont_point_neg(PG_FUNCTION_ARGS)
{
	SPATH	   *path = PG_GETARG_SPATH(0);
	SPoint	   *sp = (SPoint *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(!spath_cont_point(path, sp));
}

Datum
spherepath_cont_point_com(PG_FUNCTION_ARGS)
{
	SPATH	   *path = PG_GETARG_SPATH(1);
	SPoint	   *sp = (SPoint *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(spath_cont_point(path, sp));
}

Datum
spherepath_cont_point_com_neg(PG_FUNCTION_ARGS)
{
	SPATH	   *path = PG_GETARG_SPATH(1);
	SPoint	   *sp = (SPoint *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(!spath_cont_point(path, sp));
}

Datum
spherepath_overlap_line(PG_FUNCTION_ARGS)
{
	SPATH	   *path = PG_GETARG_SPATH(0);
	SLine	   *line = (SLine *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(path_line_overlap(path, line));
}

Datum
spherepath_overlap_line_neg(PG_FUNCTION_ARGS)
{
	SPATH	   *path = PG_GETARG_SPATH(0);
	SLine	   *line = (SLine *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(!path_line_overlap(path, line));
}

Datum
spherepath_overlap_line_com(PG_FUNCTION_ARGS)
{
	SPATH	   *path = PG_GETARG_SPATH(1);
	SLine	   *line = (SLine *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(path_line_overlap(path, line));
}

Datum
spherepath_overlap_line_com_neg(PG_FUNCTION_ARGS)
{
	SPATH	   *path = PG_GETARG_SPATH(1);
	SLine	   *line = (SLine *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(!path_line_overlap(path, line));
}

Datum
spherecircle_cont_path(PG_FUNCTION_ARGS)
{
	SCIRCLE    *circ = (SCIRCLE *) PG_GETARG_POINTER(0);
	SPATH	   *path = PG_GETARG_SPATH(1);

	PG_RETURN_BOOL(path_circle_pos(path, circ) == PGS_CIRCLE_CONT_PATH);
}

Datum
spherecircle_cont_path_neg(PG_FUNCTION_ARGS)
{
	SCIRCLE    *circ = (SCIRCLE *) PG_GETARG_POINTER(0);
	SPATH	   *path = PG_GETARG_SPATH(1);

	PG_RETURN_BOOL(path_circle_pos(path, circ) != PGS_CIRCLE_CONT_PATH);
}

Datum
spherecircle_cont_path_com(PG_FUNCTION_ARGS)
{
	SCIRCLE    *circ = (SCIRCLE *) PG_GETARG_POINTER(1);
	SPATH	   *path = PG_GETARG_SPATH(0);

	PG_RETURN_BOOL(path_circle_pos(path, circ) == PGS_CIRCLE_CONT_PATH);
}

Datum
spherecircle_cont_path_com_neg(PG_FUNCTION_ARGS)
{
	SCIRCLE    *circ = (SCIRCLE *) PG_GETARG_POINTER(1);
	SPATH	   *path = PG_GETARG_SPATH(0);

	PG_RETURN_BOOL(path_circle_pos(path, circ) != PGS_CIRCLE_CONT_PATH);
}

Datum
spherecircle_overlap_path(PG_FUNCTION_ARGS)
{
	SCIRCLE    *circ = (SCIRCLE *) PG_GETARG_POINTER(0);
	SPATH	   *path = PG_GETARG_SPATH(1);

	PG_RETURN_BOOL(path_circle_pos(path, circ) > PGS_CIRCLE_PATH_AVOID);
}

Datum
spherecircle_overlap_path_neg(PG_FUNCTION_ARGS)
{
	SCIRCLE    *circ = (SCIRCLE *) PG_GETARG_POINTER(0);
	SPATH	   *path = PG_GETARG_SPATH(1);

	PG_RETURN_BOOL(path_circle_pos(path, circ) == PGS_CIRCLE_PATH_AVOID);
}

Datum
spherecircle_overlap_path_com(PG_FUNCTION_ARGS)
{
	SCIRCLE    *circ = (SCIRCLE *) PG_GETARG_POINTER(1);
	SPATH	   *path = PG_GETARG_SPATH(0);

	PG_RETURN_BOOL(path_circle_pos(path, circ) > PGS_CIRCLE_PATH_AVOID);
}

Datum
spherecircle_overlap_path_com_neg(PG_FUNCTION_ARGS)
{
	SCIRCLE    *circ = (SCIRCLE *) PG_GETARG_POINTER(1);
	SPATH	   *path = PG_GETARG_SPATH(0);

	PG_RETURN_BOOL(path_circle_pos(path, circ) == PGS_CIRCLE_PATH_AVOID);
}

Datum
spherepoly_cont_path(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	SPATH	   *path = PG_GETARG_SPATH(1);

	PG_RETURN_BOOL(path_poly_pos(path, poly) == PGS_POLY_CONT_PATH);
}

Datum
spherepoly_cont_path_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	SPATH	   *path = PG_GETARG_SPATH(1);

	PG_RETURN_BOOL(path_poly_pos(path, poly) != PGS_POLY_CONT_PATH);
}

Datum
spherepoly_cont_path_com(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(1);
	SPATH	   *path = PG_GETARG_SPATH(0);

	PG_RETURN_BOOL(path_poly_pos(path, poly) == PGS_POLY_CONT_PATH);
}

Datum
spherepoly_cont_path_com_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(1);
	SPATH	   *path = PG_GETARG_SPATH(0);

	PG_RETURN_BOOL(path_poly_pos(path, poly) != PGS_POLY_CONT_PATH);
}

Datum
spherepoly_overlap_path(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	SPATH	   *path = PG_GETARG_SPATH(1);

	PG_RETURN_BOOL(path_poly_pos(path, poly) != PGS_POLY_PATH_AVOID);
}

Datum
spherepoly_overlap_path_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	SPATH	   *path = PG_GETARG_SPATH(1);

	PG_RETURN_BOOL(path_poly_pos(path, poly) == PGS_POLY_PATH_AVOID);
}

Datum
spherepoly_overlap_path_com(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(1);
	SPATH	   *path = PG_GETARG_SPATH(0);

	PG_RETURN_BOOL(path_poly_pos(path, poly) != PGS_POLY_PATH_AVOID);
}

Datum
spherepoly_overlap_path_com_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(1);
	SPATH	   *path = PG_GETARG_SPATH(0);

	PG_RETURN_BOOL(path_poly_pos(path, poly) == PGS_POLY_PATH_AVOID);
}

Datum
spherepath_overlap_path(PG_FUNCTION_ARGS)
{
	SPATH	   *p1 = PG_GETARG_SPATH(0);
	SPATH	   *p2 = PG_GETARG_SPATH(1);

	PG_RETURN_BOOL(path_overlap(p1, p2));
}

Datum
spherepath_overlap_path_neg(PG_FUNCTION_ARGS)
{
	SPATH	   *p1 = PG_GETARG_SPATH(0);
	SPATH	   *p2 = PG_GETARG_SPATH(1);

	PG_RETURN_BOOL(!path_overlap(p1, p2));
}

Datum
sphereellipse_cont_path(PG_FUNCTION_ARGS)
{
	SELLIPSE   *ell = (SELLIPSE *) PG_GETARG_POINTER(0);
	SPATH	   *path = PG_GETARG_SPATH(1);

	PG_RETURN_BOOL(path_ellipse_pos(path, ell) == PGS_ELLIPSE_CONT_PATH);
}

Datum
sphereellipse_cont_path_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *ell = (SELLIPSE *) PG_GETARG_POINTER(0);
	SPATH	   *path = PG_GETARG_SPATH(1);

	PG_RETURN_BOOL(path_ellipse_pos(path, ell) != PGS_ELLIPSE_CONT_PATH);
}

Datum
sphereellipse_cont_path_com(PG_FUNCTION_ARGS)
{
	SELLIPSE   *ell = (SELLIPSE *) PG_GETARG_POINTER(1);
	SPATH	   *path = PG_GETARG_SPATH(0);

	PG_RETURN_BOOL(path_ellipse_pos(path, ell) == PGS_ELLIPSE_CONT_PATH);
}

Datum
sphereellipse_cont_path_com_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *ell = (SELLIPSE *) PG_GETARG_POINTER(1);
	SPATH	   *path = PG_GETARG_SPATH(0);

	PG_RETURN_BOOL(path_ellipse_pos(path, ell) != PGS_ELLIPSE_CONT_PATH);
}

Datum
sphereellipse_overlap_path(PG_FUNCTION_ARGS)
{
	SELLIPSE   *ell = (SELLIPSE *) PG_GETARG_POINTER(0);
	SPATH	   *path = PG_GETARG_SPATH(1);

	PG_RETURN_BOOL(path_ellipse_pos(path, ell) != PGS_ELLIPSE_PATH_AVOID);
}

Datum
sphereellipse_overlap_path_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *ell = (SELLIPSE *) PG_GETARG_POINTER(0);
	SPATH	   *path = PG_GETARG_SPATH(1);

	PG_RETURN_BOOL(path_ellipse_pos(path, ell) == PGS_ELLIPSE_PATH_AVOID);
}

Datum
sphereellipse_overlap_path_com(PG_FUNCTION_ARGS)
{
	SELLIPSE   *ell = (SELLIPSE *) PG_GETARG_POINTER(1);
	SPATH	   *path = PG_GETARG_SPATH(0);

	PG_RETURN_BOOL(path_ellipse_pos(path, ell) != PGS_ELLIPSE_PATH_AVOID);
}

Datum
sphereellipse_overlap_path_com_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *ell = (SELLIPSE *) PG_GETARG_POINTER(1);
	SPATH	   *path = PG_GETARG_SPATH(0);

	PG_RETURN_BOOL(path_ellipse_pos(path, ell) == PGS_ELLIPSE_PATH_AVOID);
}


Datum
spheretrans_path(PG_FUNCTION_ARGS)
{
	SPATH	   *sp = PG_GETARG_SPATH(0);
	SEuler	   *se = (SEuler *) PG_GETARG_POINTER(1);
	SPATH	   *out = (SPATH *) palloc(VARSIZE(sp));

	euler_spath_trans(out, sp, se);
	PG_RETURN_POINTER(out);
}

Datum
spheretrans_path_inverse(PG_FUNCTION_ARGS)
{
	Datum		sp = PG_GETARG_DATUM(0);
	SEuler	   *se = (SEuler *) PG_GETARG_POINTER(1);
	SEuler		tmp;
	Datum		ret;

	spheretrans_inverse(&tmp, se);
	ret = DirectFunctionCall2(
							  spheretrans_path,
							  sp, PointerGetDatum(&tmp));
	PG_RETURN_DATUM(ret);
}

Datum
spherepath_add_point(PG_FUNCTION_ARGS)
{
	SPATH	   *path = (SPATH *) PG_GETARG_POINTER(0);
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(1);
	int32		size = 0;
	SPATH	   *path_new = NULL;

	if (p == NULL)
	{
		PG_RETURN_POINTER(path);
	}
	if (path == NULL)
	{
		size = offsetof(SPATH, p[0]) + sizeof(SPoint);
		path = (SPATH *) palloc(size);
		memcpy((void *) &path->p[0], (void *) p, sizeof(SPoint));
		SET_VARSIZE(path, size);
		path->npts = 1;
		PG_RETURN_POINTER(path);
	}

	path = PG_GETARG_SPATH(0);

	/* skip if equal */
	if (spoint_eq(p, &path->p[path->npts - 1]))
	{
		PG_RETURN_POINTER(path);
	}

	/* Skip if distance is equal 180deg */
	if (FPeq(spoint_dist(p, &path->p[path->npts - 1]), PI))
	{
		elog(NOTICE, "spath(spoint): Skip point, distance of previous point is 180deg");
	}

	size = offsetof(SPATH, p[0]) + sizeof(SPoint) * (path->npts + 1);
	path_new = palloc(size);
	memcpy((void *) path_new, (void *) path, VARSIZE(path));
	path_new->npts++;

	SET_VARSIZE(path_new, size);

	memcpy((void *) &path_new->p[path->npts], (void *) p, sizeof(SPoint));
	PG_RETURN_POINTER(path_new);
}

Datum
spherepath_add_points_finalize(PG_FUNCTION_ARGS)
{
	SPATH	   *path = (SPATH *) PG_GETARG_POINTER(0);

	if (path == NULL)
	{
		PG_RETURN_NULL();
	}

	path = PG_GETARG_SPATH(0);

	if (path->npts < 2)
	{
		elog(NOTICE, "spath(spoint): At least 2 points required");
		pfree(path);
		PG_RETURN_NULL();
	}
	PG_RETURN_POINTER(path);
}
