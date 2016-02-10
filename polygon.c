#include "polygon.h"

/* Polygon functions */


#ifndef DOXYGEN_SHOULD_SKIP_THIS

PG_FUNCTION_INFO_V1(spherepoly_in);
PG_FUNCTION_INFO_V1(spherepoly_equal);
PG_FUNCTION_INFO_V1(spherepoly_equal_neg);
PG_FUNCTION_INFO_V1(spherepoly_circ);
PG_FUNCTION_INFO_V1(spherepoly_npts);
PG_FUNCTION_INFO_V1(spherepoly_area);
PG_FUNCTION_INFO_V1(spherepoly_cont_point);
PG_FUNCTION_INFO_V1(spherepoly_cont_point_neg);
PG_FUNCTION_INFO_V1(spherepoly_cont_point_com);
PG_FUNCTION_INFO_V1(spherepoly_cont_point_com_neg);
PG_FUNCTION_INFO_V1(spherepoly_cont_circle);
PG_FUNCTION_INFO_V1(spherepoly_cont_circle_neg);
PG_FUNCTION_INFO_V1(spherepoly_cont_circle_com);
PG_FUNCTION_INFO_V1(spherepoly_cont_circle_com_neg);
PG_FUNCTION_INFO_V1(spherecircle_cont_poly);
PG_FUNCTION_INFO_V1(spherecircle_cont_poly_neg);
PG_FUNCTION_INFO_V1(spherecircle_cont_poly_com);
PG_FUNCTION_INFO_V1(spherecircle_cont_poly_com_neg);
PG_FUNCTION_INFO_V1(spherepoly_overlap_circle);
PG_FUNCTION_INFO_V1(spherepoly_overlap_circle_neg);
PG_FUNCTION_INFO_V1(spherepoly_overlap_circle_com);
PG_FUNCTION_INFO_V1(spherepoly_overlap_circle_com_neg);
PG_FUNCTION_INFO_V1(spherepoly_cont_line);
PG_FUNCTION_INFO_V1(spherepoly_cont_line_neg);
PG_FUNCTION_INFO_V1(spherepoly_cont_line_com);
PG_FUNCTION_INFO_V1(spherepoly_cont_line_com_neg);
PG_FUNCTION_INFO_V1(spherepoly_overlap_line);
PG_FUNCTION_INFO_V1(spherepoly_overlap_line_neg);
PG_FUNCTION_INFO_V1(spherepoly_overlap_line_com);
PG_FUNCTION_INFO_V1(spherepoly_overlap_line_com_neg);
PG_FUNCTION_INFO_V1(spherepoly_cont_poly);
PG_FUNCTION_INFO_V1(spherepoly_cont_poly_neg);
PG_FUNCTION_INFO_V1(spherepoly_cont_poly_com);
PG_FUNCTION_INFO_V1(spherepoly_cont_poly_com_neg);
PG_FUNCTION_INFO_V1(spherepoly_overlap_poly);
PG_FUNCTION_INFO_V1(spherepoly_overlap_poly_neg);
PG_FUNCTION_INFO_V1(spherepoly_cont_ellipse);
PG_FUNCTION_INFO_V1(spherepoly_cont_ellipse_neg);
PG_FUNCTION_INFO_V1(spherepoly_cont_ellipse_com);
PG_FUNCTION_INFO_V1(spherepoly_cont_ellipse_com_neg);
PG_FUNCTION_INFO_V1(sphereellipse_cont_poly);
PG_FUNCTION_INFO_V1(sphereellipse_cont_poly_neg);
PG_FUNCTION_INFO_V1(sphereellipse_cont_poly_com);
PG_FUNCTION_INFO_V1(sphereellipse_cont_poly_com_neg);
PG_FUNCTION_INFO_V1(spherepoly_overlap_ellipse);
PG_FUNCTION_INFO_V1(spherepoly_overlap_ellipse_neg);
PG_FUNCTION_INFO_V1(spherepoly_overlap_ellipse_com);
PG_FUNCTION_INFO_V1(spherepoly_overlap_ellipse_com_neg);
PG_FUNCTION_INFO_V1(spheretrans_poly);
PG_FUNCTION_INFO_V1(spheretrans_poly_inverse);
PG_FUNCTION_INFO_V1(spherepoly_add_point);
PG_FUNCTION_INFO_V1(spherepoly_add_points_finalize);

#endif


 /*
  * "Center" of a polygon. "v" is the pointer to the center of
  * the polygon, "poly" is the pointer to the polygon.
  * Returns true if crossing.
  */
static void
spherepoly_center(Vector3D *v, const SPOLY *poly)
{
	int32		i;
	Vector3D	v1,
				v2;

	v1.x = 2.0;
	v1.y = 2.0;
	v1.z = 2.0;
	v2.x = -2.0;
	v2.y = -2.0;
	v2.z = -2.0;

	for (i = 0; i < poly->npts; i++)
	{
		spoint_vector3d(v, &poly->p[i]);
		v1.x = Min(v->x, v1.x);
		v1.y = Min(v->y, v1.y);
		v1.z = Min(v->z, v1.z);
		v2.x = Max(v->x, v2.x);
		v2.y = Max(v->y, v2.y);
		v2.z = Max(v->z, v2.z);
	}

	v->x = (v1.x + v2.x) / 2.0;
	v->y = (v1.y + v2.y) / 2.0;
	v->z = (v1.z + v2.z) / 2.0;
}


 /*
  * Checks crossing of line segments. "poly" is the pointer to a polygon.
  * Returns true if crossing.
  */
static bool
spherepoly_check(const SPOLY *poly)
{
	int32		i,
				k;
	SLine		sli,
				slk;
	Vector3D	v;
	SPoint		p;
	SEuler		se;
	int8		pos;

	spherepoly_center(&v, poly);
	/* If 0-vector */
	if (FPzero(v.x) && FPzero(v.y) && FPzero(v.z))
	{
		return false;
	}

	for (i = 0; i < poly->npts; i++)
	{
		spoly_segment(&sli, poly, i);
		for (k = (i + 1); k < poly->npts; k++)
		{
			spoly_segment(&slk, poly, k);
			pos = sline_sline_pos(&sli, &slk);
			if (!(pos == PGS_LINE_CONNECT || pos == PGS_LINE_AVOID))
			{
				return false;
			}
		}
	}

	vector3d_spoint(&p, &v);

	se.phi_a = EULER_AXIS_Z;
	se.theta_a = EULER_AXIS_X;
	se.psi_a = EULER_AXIS_Z;
	se.phi = -PIH - p.lng;
	se.theta = p.lat - PIH;
	se.psi = 0.0;

	for (i = 0; i < poly->npts; i++)
	{
		euler_spoint_trans(&p, &poly->p[i], &se);
		/* less _and_ equal are important !! */
		/* Do not change it! */
		if (FPle(p.lat, 0.0))
		{
			return false;
		}
	}
	return true;
}


 /*
  * Converts an array of spherical points to SPOLY. "arr" is the pointer
  * to the array of spherical point,s "nelem" is the number of the
  * elements. Returns the pointer to the created spherical polygon.
  */
static SPOLY *
spherepoly_from_array(SPoint *arr, int32 nelem)
{
	SPOLY *poly = NULL;

	if (nelem < 3)
	{
		elog(ERROR, "spherepoly_from_array: more than two points needed");
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
			if (nelem < 3)
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
		if (spoint_eq(&arr[0], &arr[nelem - 1]))
		{
			nelem--;
		}
		if (nelem < 3)
		{
			elog(ERROR, "spherepoly_from_array: more than two points needed");
			return NULL;
		}

		size = offsetof(SPOLY, p[0]) +sizeof(SPoint) * nelem;
		poly = (SPOLY *) palloc(size);
		SET_VARSIZE(poly, size);
		poly->npts = nelem;
		for (i = 0; i < nelem; i++)
		{
			if (i == 0)
			{
				scheck = spoint_dist(&arr[nelem - 1], &arr[0]);
			}
			else
			{
				scheck = spoint_dist(&arr[i - 1], &arr[i]);
			}
			if (FPeq(scheck, PI))
			{
				elog(ERROR, "spherepoly_from_array: a polygon segment length must be not equal 180 degrees.");
				return NULL;
			}
			memcpy((void *) &poly->p[i],
				   (void *) &arr[i],
				   sizeof(SPoint));
		}

	}

	if (!spherepoly_check(poly))
	{
		elog(ERROR, "spherepoly_from_array: a line segment overlaps or polygon too large");
		pfree(poly);
		return NULL;
	}

	return poly;

}


 /*
  * Performs a transform of a polygon using an Euler transformation.
  * "se" is the pointer to the Euler transformation, "in" is the pointer
  * to the polygon, "out" is the pointer to the transformed polygon.
  */
static void
euler_spoly_trans(SPOLY *out, const SPOLY *in, const SEuler *se)
{
	int32		i;

	out->size = in->size;
	out->npts = in->npts;
	for (i = 0; i < in->npts; i++)
		euler_spoint_trans(&out->p[i], &in->p[i], se);
}


 /*
  * Returns the relationship between polygon and circle as an int8 value.
  * "circ" is the pointer to the circle, "poly" is the pointer to the
  * polygon.
  */
static int8
poly_circle_pos(const SPOLY *poly, const SCIRCLE *circ)
{
	int8		pos = 0;
	int32		i;
	SLine		sl;
	bool		pcp;
	const int8	sc_in = (1 << PGS_CIRCLE_CONT_LINE);
	const int8	sc_ov = (1 << PGS_CIRCLE_LINE_OVER);
	const int8	sc_os = (1 << PGS_CIRCLE_LINE_AVOID);

	pcp = spoly_contains_point(poly, &circ->center);

	if (FPzero(circ->radius))
	{
		if (pcp)
		{
			return PGS_POLY_CONT_CIRCLE;
		}
		else
		{
			return PGS_CIRCLE_POLY_AVOID;
		}
	}

	for (i = 0; i < poly->npts; i++)
	{

		spoly_segment(&sl, poly, i);
		pos |= (1 << sphereline_circle_pos(&sl, circ));
		if (((pos & sc_in) && (pos & sc_os)) || (pos & sc_ov))
		{
			return PGS_CIRCLE_POLY_OVER;
			/* overlaps */
		}

	}

	if ((pos & sc_in) == pos)
	{
		/* all lines inside circle */
		/* circle contains polygon */
		return PGS_CIRCLE_CONT_POLY;
	}
	else if ((pos & sc_os) == pos)
	{
		/* all lines outside circle */
		if (pcp)
		{
			/* polygon contains circle */
			return PGS_POLY_CONT_CIRCLE;
		}
		else
		{
			/* circle outside polygon */
			return PGS_CIRCLE_POLY_AVOID;
		}

	}
	/* circle and polygon overlap */
	return PGS_CIRCLE_POLY_OVER;
}


 /*
  * Returns the relationship between a polygon and an ellipse
  * as an int8 value. "ell" is the pointer to the ellipse,
  * "poly" is the pointer to the polygon.
  */
static int8
poly_ellipse_pos(const SPOLY *poly, const SELLIPSE *ell)
{
	int8		pos = 0;
	int32		i;
	SLine		sl;
	bool		pcp;
	SPoint		cen;
	const int8	sc_in = (1 << PGS_ELLIPSE_CONT_LINE);
	const int8	sc_ov = (1 << PGS_ELLIPSE_LINE_OVER);
	const int8	sc_os = (1 << PGS_ELLIPSE_LINE_AVOID);

	sellipse_center(&cen, ell);
	pcp = spoly_contains_point(poly, &cen);

	if (FPzero(ell->rad[0]))
	{
		if (pcp)
		{
			return PGS_POLY_CONT_ELLIPSE;
		}
		else
		{
			return PGS_ELLIPSE_POLY_AVOID;
		}
	}

	if (FPzero(ell->rad[1]))
	{
		SLine		l;
		int8		res;

		sellipse_line(&l, ell);
		res = poly_line_pos(poly, &l);
		if (res == PGS_LINE_POLY_AVOID)
		{
			return PGS_ELLIPSE_POLY_AVOID;
		}
		else if (res == PGS_POLY_CONT_LINE)
		{
			return PGS_POLY_CONT_ELLIPSE;
		}
		else
		{
			return PGS_ELLIPSE_POLY_OVER;
		}
	}

	for (i = 0; i < poly->npts; i++)
	{
		spoly_segment(&sl, poly, i);
		pos |= (1 << sellipse_line_pos(ell, &sl));
		if (((pos & sc_in) && (pos & sc_os)) || (pos & sc_ov))
		{
			return PGS_ELLIPSE_POLY_OVER;
			/* overlaps */
		}
	}

	if ((pos & sc_in) == pos)
	{
		/* all lines inside ellipse */
		/* ellipse contains polygon */
		return PGS_ELLIPSE_CONT_POLY;
	}
	else if ((pos & sc_os) == pos)
	{
		/* all lines outside ellipse */
		if (pcp)
		{
			/* polygon contains ellipse */
			return PGS_POLY_CONT_ELLIPSE;
		}
		else
		{
			/* ellipse outside polygon */
			return PGS_ELLIPSE_POLY_AVOID;
		}

	}

	/* ellipse and polygon overlap */
	return PGS_ELLIPSE_POLY_OVER;
}


 /*
  * Returns the relationship between two polygons as an int8 value.
  * "p1" is the pointer to the first polygon, "p2" is the pointer
  * to the second polygon. If "recheck" is true, swaps p1 and p2.
  */
static int8
poly_poly_pos(const SPOLY *p1, const SPOLY *p2, bool recheck)
{
	int32		i;
	SLine		sl;
	int8		pos = 0,
				res = 0;
	const int8	sp_os = (1 << PGS_LINE_POLY_AVOID);
	const int8	sp_ct = (1 << PGS_POLY_CONT_LINE);
	const int8	sp_ov = (1 << PGS_LINE_POLY_OVER);

	for (i = 0; i < p2->npts; i++)
	{

		spoly_segment(&sl, p2, i);
		pos = (1 << poly_line_pos(p1, &sl));
		if (pos == sp_ov)
		{
			return PGS_POLY_OVER;
			/* overlap */
		}
		res |= pos;
	}

	if (res == sp_os)
	{
		if (!recheck)
		{
			pos = poly_poly_pos(p2, p1, true);
		}
		if (pos == PGS_POLY_CONT)
		{
			return PGS_POLY_OVER;
		}
		else
		{
			return PGS_POLY_AVOID;
		}
	}
	if (res == sp_ct)
	{
		return PGS_POLY_CONT;
	}
	return PGS_POLY_OVER;
}


bool
spoly_eq(const SPOLY *p1, const SPOLY *p2, bool dir)
{
	bool ret = false;

	if (p1->npts == p2->npts)
	{

		int32		i,
					k,
					cntr,
					shift;

		for (shift = 0; shift < p1->npts; shift++)
		{
			cntr = 0;
			for (i = 0; i < p1->npts; i++)
			{
				k = (dir) ? (p1->npts - i - 1) : (i);
				k += shift;
				k = (k < p1->npts) ? (k) : (k - p1->npts);
				if (spoint_eq(&p1->p[i], &p2->p[k]))
				{
					cntr++;
				}
			}
			if (cntr == p1->npts)
			{
				ret = true;
				break;
			}
		}

		/* Try other direction if not equal */
		if (!dir && !ret)
		{
			ret = spoly_eq(p1, p2, true);
		}

	}

	return ret;
}

bool
spoly_segment(SLine *sl, const SPOLY *poly, int32 i)
{
	if (i >= 0 && i < poly->npts)
	{
		if (i == (poly->npts - 1))
			sline_from_points(sl, &poly->p[i], &poly->p[0]);
		else
			sline_from_points(sl, &poly->p[i], &poly->p[i + 1]);
		return true;
	}
	else
	{
		return false;
	}
}

bool
spoly_contains_point(const SPOLY *pg, const SPoint *sp)
{
	int32		i;
	SLine		sl;
	bool		res = false;
	float8		scp;
	Vector3D	vc,
				vp;

	/* First check if point is outside polygon (behind) */
	spherepoly_center(&vc, pg);
	spoint_vector3d(&vp, sp);
	scp = vector3d_scalar(&vp, &vc);
	if (FPle(scp, 0.0))
	{
		return false;
	}

	/* Check whether point is edge */
	for (i = 0; i < pg->npts; i++)
	{
		if (spoint_eq(&pg->p[i], sp))
		{
			return true;
		}
	}

	/* Check whether point is on a line segment */
	for (i = 0; i < pg->npts; i++)
	{
		spoly_segment(&sl, pg, i);
		if (spoint_at_sline(sp, &sl))
		{
			return true;
		}
	}

	do
	{
		SEuler		se,
					te;
		SPoint		p,
					lp[2];
		bool		a1,
					a2,
					eqa;
		int32		cntr = 0;
		SPOLY	   *tmp = (SPOLY *) palloc(VARSIZE(pg));

		/*
		 * Make a transformation, so the point is (0,0)
		 */

		se.phi_a = EULER_AXIS_Z;
		se.theta_a = EULER_AXIS_X;
		se.psi_a = EULER_AXIS_Z;
		se.phi = PIH - sp->lng;
		se.theta = -sp->lat;
		se.psi = -PIH;

		euler_spoly_trans(tmp, pg, &se);

		p.lng = 0.0;
		p.lat = 0.0;

		/* Check whether an edge is on equator. */
		/* If yes, rotate randomized around 0,0 */

		cntr = 0;
		do
		{
			eqa = false;
			for (i = 0; i < pg->npts; i++)
			{
				if (FPzero(tmp->p[i].lat))
				{
					if (FPeq(cos(tmp->p[i].lng), -1.0))
					{
						return false;
					}
					else
					{
						eqa = true;
						break;
					}
				}
			}
			if (eqa)
			{
				SPOLY	   *ttt = (SPOLY *) palloc(VARSIZE(pg));

				srand(cntr);
				se.phi_a = se.theta_a = se.psi_a = EULER_AXIS_X;
				se.phi = ((double) rand() / RAND_MAX) * PID;
				se.theta = 0.0;
				se.psi = 0.0;
				euler_spoly_trans(ttt, tmp, &se);
				memcpy((void *) tmp, (void *) ttt, VARSIZE(pg));
				pfree(ttt);
			}
			if (cntr > 10000)
			{
				elog(WARNING, "Bug found in spoly_contains_point");
				elog(ERROR, "Please report it to pg_sphere team!");
				return false;
			}
			cntr++;
		} while (eqa);

		/* Count line segment crossing "equator" */

		cntr = 0;
		for (i = 0; i < pg->npts; i++)
		{

			/* create a single line from segment */
			spoly_segment(&sl, tmp, i);

			sline_begin(&lp[0], &sl);
			sline_end(&lp[1], &sl);

			a1 = (FPgt(lp[0].lat, 0.0) && FPlt(lp[1].lat, 0.0));
			a2 = (FPlt(lp[0].lat, 0.0) && FPgt(lp[1].lat, 0.0));

			if (a1 || a2)
			{
				/* if crossing */
				sphereline_to_euler_inv(&te, &sl);
				if (a2)
				{
					/* crossing ascending */
					p.lng = PID - te.phi;
				}
				else
				{
					p.lng = PI - te.phi;
				}
				spoint_check(&p);
				if (p.lng < PI)
				{
					/* crossing between 0 and 180 deg */
					cntr++;
				}
			}
		}

		pfree(tmp);
		if (cntr % 2)
		{
			res = true;
		}

	} while (0);

	return res;
}

 /*
  * Returns the relationship between polygon and line. "line" is
  * the pointer to line, "poly" is the pointer to polygon.
  */
int8
poly_line_pos(const SPOLY *poly, const SLine *line)
{
	int32		i;
	SLine		sl;
	SPoint		slbeg,
				slend;
	int8		p1,
				p2,
				pos,
				res;
	const int8	sl_os = (1 << PGS_LINE_AVOID);
	const int8	sl_cl = (1 << PGS_LINE_CONT_LINE);
	const int8	sl_cr = (1 << PGS_LINE_CROSS);
	const int8	sl_cn = (1 << PGS_LINE_CONNECT);
	const int8	sl_ov = (1 << PGS_LINE_OVER);
	const int8	sl_eq = (1 << PGS_LINE_EQUAL);

	pos = 0;
	res = 0;

	sline_begin(&slbeg, line);
	sline_end(&slend, line);

	p1 = spoly_contains_point(poly, &slbeg);
	p2 = spoly_contains_point(poly, &slend);

	for (i = 0; i < poly->npts; i++)
	{
		spoly_segment(&sl, poly, i);
		pos = (1 << sline_sline_pos(&sl, line));
		if (pos == sl_eq)
		{
			pos = sl_cl;
			/* is contain */
		}
		if (pos == sl_ov)
		{
			return PGS_LINE_POLY_OVER;
			/* overlap */
		}
		/* Recheck line crossing */
		if (pos == sl_cr)
		{
			bool	bal,
					eal;

			bal = spoint_at_sline(&slbeg, &sl);
			eal = spoint_at_sline(&slend, &sl);
			if (!bal && !eal)
			{
				return PGS_LINE_POLY_OVER;
				/* overlap */
			}
			if ((bal && p2) || (eal && p1))
			{
				pos = sl_cl;
				/* is contain */
			}
			else
			{
				return PGS_LINE_POLY_OVER;
				/* overlap */
			}
		}
		res |= pos;
	}
	if ((res & sl_cl) && ((res - sl_cl - sl_os - sl_cn - 1) < 0))
	{
		return PGS_POLY_CONT_LINE;
	}
	else if (p1 && p2 && ((res - sl_os - sl_cn - 1) < 0))
	{
		return PGS_POLY_CONT_LINE;
	}
	else if (!p1 && !p2 && ((res - sl_os - 1) < 0))
	{
		return PGS_LINE_POLY_AVOID;
	}
	return PGS_LINE_POLY_OVER;
}


Datum
spherepoly_in(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly;
	char	   *c = PG_GETARG_CSTRING(0);
	int32		i,
				nelem;

	void		sphere_yyparse(void);

	init_buffer(c);
	sphere_yyparse();

	nelem = get_path_count();
	if (nelem > 2)
	{
		SPoint		arr[nelem];

		for (i = 0; i < nelem; i++)
		{
			get_path_elem(i, &arr[i].lng, &arr[i].lat);
		}
		poly = spherepoly_from_array(&arr[0], nelem);
	}
	else
	{
		reset_buffer();
		elog(ERROR, "spherepoly_in: more than two points needed");
		PG_RETURN_NULL();
	}
	reset_buffer();

	PG_RETURN_POINTER(poly);
}

Datum
spherepoly_equal(PG_FUNCTION_ARGS)
{
	SPOLY	   *p1 = PG_GETARG_SPOLY(0);
	SPOLY	   *p2 = PG_GETARG_SPOLY(1);

	PG_RETURN_BOOL(spoly_eq(p1, p2, false));
}

Datum
spherepoly_equal_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *p1 = PG_GETARG_SPOLY(0);
	SPOLY	   *p2 = PG_GETARG_SPOLY(1);

	PG_RETURN_BOOL(!spoly_eq(p1, p2, false));
}

Datum
spherepoly_circ(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	int32		i;
	SLine		l;
	float8		sum = 0.0;

	for (i = 0; i < poly->npts; i++)
	{
		spoly_segment(&l, poly, i);
		sum += l.length;
	}
	PG_RETURN_FLOAT8(sum);
}

Datum
spherepoly_npts(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);

	PG_RETURN_INT32(poly->npts);
}



Datum
spherepoly_area(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	int32		i;
	SPoint		s[poly->npts + 2];
	SPoint		stmp[2];
	SEuler		se;
	float8		sum = 0.0;

	memcpy((void *) &s[1],
		   (void *) &poly->p[0],
		   poly->npts * sizeof(SPoint));
	memcpy((void *) &s[0], (void *) &s[poly->npts], sizeof(SPoint));
	memcpy((void *) &s[poly->npts + 1], (void *) &s[1], sizeof(SPoint));

	se.psi = 0;
	se.phi_a = EULER_AXIS_Z;
	se.theta_a = EULER_AXIS_X;
	se.psi_a = EULER_AXIS_Z;

	for (i = 1; i <= poly->npts; i++)
	{

		se.phi = -PIH - s[i].lng;
		se.theta = s[i].lat - PIH;
		euler_spoint_trans(&stmp[0], &s[i - 1], &se);
		euler_spoint_trans(&stmp[1], &s[i + 1], &se);

		stmp[1].lng -= stmp[0].lng;
		if (FPlt(stmp[1].lng, 0.0))
		{
			stmp[1].lng += PID;
		}
		sum += stmp[1].lng;

	}

	sum -= (PI * (poly->npts - 2));
	if (FPge(sum, PID))
	{
		sum = 2 * PID - sum;
	}

	if (FPzero(sum))
	{
		sum = 0.0;
	}

	PG_RETURN_FLOAT8(sum);
}

Datum
spherepoly_cont_point(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	SPoint	   *sp = (SPoint *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(spoly_contains_point(poly, sp));
}

Datum
spherepoly_cont_point_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	SPoint	   *sp = (SPoint *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(!spoly_contains_point(poly, sp));
}

Datum
spherepoly_cont_point_com(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(1);
	SPoint	   *sp = (SPoint *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(spoly_contains_point(poly, sp));
}

Datum
spherepoly_cont_point_com_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(1);
	SPoint	   *sp = (SPoint *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(!spoly_contains_point(poly, sp));
}

Datum
spherepoly_cont_circle(PG_FUNCTION_ARGS)
{
	SCIRCLE    *circ = (SCIRCLE *) PG_GETARG_POINTER(1);
	SPOLY	   *poly = PG_GETARG_SPOLY(0);

	PG_RETURN_BOOL(poly_circle_pos(poly, circ) == PGS_POLY_CONT_CIRCLE);
}

Datum
spherepoly_cont_circle_neg(PG_FUNCTION_ARGS)
{
	SCIRCLE    *circ = (SCIRCLE *) PG_GETARG_POINTER(1);
	SPOLY	   *poly = PG_GETARG_SPOLY(0);

	PG_RETURN_BOOL(poly_circle_pos(poly, circ) != PGS_POLY_CONT_CIRCLE);
}

Datum
spherepoly_cont_circle_com(PG_FUNCTION_ARGS)
{
	SCIRCLE    *circ = (SCIRCLE *) PG_GETARG_POINTER(0);
	SPOLY	   *poly = PG_GETARG_SPOLY(1);

	PG_RETURN_BOOL(poly_circle_pos(poly, circ) == PGS_POLY_CONT_CIRCLE);
}

Datum
spherepoly_cont_circle_com_neg(PG_FUNCTION_ARGS)
{
	SCIRCLE    *circ = (SCIRCLE *) PG_GETARG_POINTER(0);
	SPOLY	   *poly = PG_GETARG_SPOLY(1);

	PG_RETURN_BOOL(poly_circle_pos(poly, circ) != PGS_POLY_CONT_CIRCLE);
}

Datum
spherecircle_cont_poly(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(1);
	SCIRCLE    *circ = (SCIRCLE *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(poly_circle_pos(poly, circ) == PGS_CIRCLE_CONT_POLY);
}

Datum
spherecircle_cont_poly_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(1);
	SCIRCLE    *circ = (SCIRCLE *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(poly_circle_pos(poly, circ) != PGS_CIRCLE_CONT_POLY);
}

Datum
spherecircle_cont_poly_com(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	SCIRCLE    *circ = (SCIRCLE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(poly_circle_pos(poly, circ) == PGS_CIRCLE_CONT_POLY);
}

Datum
spherecircle_cont_poly_com_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	SCIRCLE    *circ = (SCIRCLE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(poly_circle_pos(poly, circ) != PGS_CIRCLE_CONT_POLY);
}

Datum
spherepoly_overlap_circle(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	SCIRCLE    *circ = (SCIRCLE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(poly_circle_pos(poly, circ) > PGS_CIRCLE_POLY_AVOID);
}

Datum
spherepoly_overlap_circle_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	SCIRCLE    *circ = (SCIRCLE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(poly_circle_pos(poly, circ) == PGS_CIRCLE_POLY_AVOID);
}

Datum
spherepoly_overlap_circle_com(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(1);
	SCIRCLE    *circ = (SCIRCLE *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(poly_circle_pos(poly, circ) > PGS_CIRCLE_POLY_AVOID);
}

Datum
spherepoly_overlap_circle_com_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(1);
	SCIRCLE    *circ = (SCIRCLE *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(poly_circle_pos(poly, circ) == PGS_CIRCLE_POLY_AVOID);
}

Datum
spherepoly_cont_line(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	SLine	   *line = (SLine *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(poly_line_pos(poly, line) == PGS_POLY_CONT_LINE);
}

Datum
spherepoly_cont_line_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	SLine	   *line = (SLine *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(poly_line_pos(poly, line) != PGS_POLY_CONT_LINE);
}

Datum
spherepoly_cont_line_com(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(1);
	SLine	   *line = (SLine *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(poly_line_pos(poly, line) == PGS_POLY_CONT_LINE);
}

Datum
spherepoly_cont_line_com_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(1);
	SLine	   *line = (SLine *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(poly_line_pos(poly, line) != PGS_POLY_CONT_LINE);
}

Datum
spherepoly_overlap_line(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	SLine	   *line = (SLine *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(poly_line_pos(poly, line) > PGS_LINE_POLY_AVOID);
}

Datum
spherepoly_overlap_line_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	SLine	   *line = (SLine *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(poly_line_pos(poly, line) == PGS_LINE_POLY_AVOID);
}

Datum
spherepoly_overlap_line_com(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(1);
	SLine	   *line = (SLine *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(poly_line_pos(poly, line) > PGS_LINE_POLY_AVOID);
}

Datum
spherepoly_overlap_line_com_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(1);
	SLine	   *line = (SLine *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(poly_line_pos(poly, line) == PGS_LINE_POLY_AVOID);
}


Datum
spherepoly_cont_poly(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly1 = PG_GETARG_SPOLY(0);
	SPOLY	   *poly2 = PG_GETARG_SPOLY(1);

	PG_RETURN_BOOL(poly_poly_pos(poly1, poly2, false) == PGS_POLY_CONT);
}

Datum
spherepoly_cont_poly_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly1 = PG_GETARG_SPOLY(0);
	SPOLY	   *poly2 = PG_GETARG_SPOLY(1);

	PG_RETURN_BOOL(poly_poly_pos(poly1, poly2, false) != PGS_POLY_CONT);
}

Datum
spherepoly_cont_poly_com(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly1 = PG_GETARG_SPOLY(1);
	SPOLY	   *poly2 = PG_GETARG_SPOLY(0);

	PG_RETURN_BOOL(poly_poly_pos(poly1, poly2, false) == PGS_POLY_CONT);
}

Datum
spherepoly_cont_poly_com_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly1 = PG_GETARG_SPOLY(1);
	SPOLY	   *poly2 = PG_GETARG_SPOLY(0);

	PG_RETURN_BOOL(poly_poly_pos(poly1, poly2, false) != PGS_POLY_CONT);
}

Datum
spherepoly_overlap_poly(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly1 = PG_GETARG_SPOLY(0);
	SPOLY	   *poly2 = PG_GETARG_SPOLY(1);

	PG_RETURN_BOOL(poly_poly_pos(poly1, poly2, false) > PGS_POLY_AVOID);
}

Datum
spherepoly_overlap_poly_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly1 = PG_GETARG_SPOLY(0);
	SPOLY	   *poly2 = PG_GETARG_SPOLY(1);

	PG_RETURN_BOOL(poly_poly_pos(poly1, poly2, false) == PGS_POLY_AVOID);
}

Datum
spherepoly_cont_ellipse(PG_FUNCTION_ARGS)
{
	SELLIPSE   *ell = (SELLIPSE *) PG_GETARG_POINTER(1);
	SPOLY	   *poly = PG_GETARG_SPOLY(0);

	PG_RETURN_BOOL(poly_ellipse_pos(poly, ell) == PGS_POLY_CONT_ELLIPSE);
}

Datum
spherepoly_cont_ellipse_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *ell = (SELLIPSE *) PG_GETARG_POINTER(1);
	SPOLY	   *poly = PG_GETARG_SPOLY(0);

	PG_RETURN_BOOL(poly_ellipse_pos(poly, ell) != PGS_POLY_CONT_ELLIPSE);
}

Datum
spherepoly_cont_ellipse_com(PG_FUNCTION_ARGS)
{
	SELLIPSE   *ell = (SELLIPSE *) PG_GETARG_POINTER(0);
	SPOLY	   *poly = PG_GETARG_SPOLY(1);

	PG_RETURN_BOOL(poly_ellipse_pos(poly, ell) == PGS_POLY_CONT_ELLIPSE);
}

Datum
spherepoly_cont_ellipse_com_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *ell = (SELLIPSE *) PG_GETARG_POINTER(0);
	SPOLY	   *poly = PG_GETARG_SPOLY(1);

	PG_RETURN_BOOL(poly_ellipse_pos(poly, ell) != PGS_POLY_CONT_ELLIPSE);
}

Datum
sphereellipse_cont_poly(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(1);
	SELLIPSE   *ell = (SELLIPSE *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(poly_ellipse_pos(poly, ell) == PGS_ELLIPSE_CONT_POLY);
}

Datum
sphereellipse_cont_poly_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(1);
	SELLIPSE   *ell = (SELLIPSE *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(poly_ellipse_pos(poly, ell) != PGS_ELLIPSE_CONT_POLY);
}

Datum
sphereellipse_cont_poly_com(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	SELLIPSE   *ell = (SELLIPSE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(poly_ellipse_pos(poly, ell) == PGS_ELLIPSE_CONT_POLY);
}

Datum
sphereellipse_cont_poly_com_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	SELLIPSE   *ell = (SELLIPSE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(poly_ellipse_pos(poly, ell) != PGS_ELLIPSE_CONT_POLY);
}

Datum
spherepoly_overlap_ellipse(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	SELLIPSE   *ell = (SELLIPSE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(poly_ellipse_pos(poly, ell) > PGS_ELLIPSE_POLY_AVOID);
}

Datum
spherepoly_overlap_ellipse_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	SELLIPSE   *ell = (SELLIPSE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(poly_ellipse_pos(poly, ell) == PGS_ELLIPSE_POLY_AVOID);
}

Datum
spherepoly_overlap_ellipse_com(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(1);
	SELLIPSE   *ell = (SELLIPSE *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(poly_ellipse_pos(poly, ell) > PGS_ELLIPSE_POLY_AVOID);
}

Datum
spherepoly_overlap_ellipse_com_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(1);
	SELLIPSE   *ell = (SELLIPSE *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(poly_ellipse_pos(poly, ell) == PGS_ELLIPSE_POLY_AVOID);
}

Datum
spheretrans_poly(PG_FUNCTION_ARGS)
{
	SPOLY	   *sp = PG_GETARG_SPOLY(0);
	SEuler	   *se = (SEuler *) PG_GETARG_POINTER(1);
	SPOLY	   *out = (SPOLY *) palloc(VARSIZE(sp));

	euler_spoly_trans(out, sp, se);
	PG_RETURN_POINTER(out);
}

Datum
spheretrans_poly_inverse(PG_FUNCTION_ARGS)
{
	Datum		sp = PG_GETARG_DATUM(0);
	SEuler	   *se = (SEuler *) PG_GETARG_POINTER(1);
	SEuler		tmp;
	Datum		ret;

	spheretrans_inverse(&tmp, se);
	ret = DirectFunctionCall2(
							  spheretrans_poly,
							  sp, PointerGetDatum(&tmp));
	PG_RETURN_DATUM(ret);
}

Datum
spherepoly_add_point(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = (SPOLY *) PG_GETARG_POINTER(0);
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(1);
	int32		size = 0;
	SPOLY	   *poly_new = NULL;

	if (p == NULL)
	{
		PG_RETURN_POINTER(poly);
	}
	if (poly == NULL)
	{
		size = offsetof(SPOLY, p[0]) +sizeof(SPoint);
		poly = (SPOLY *) palloc(size);
		memcpy((void *) &poly->p[0], (void *) p, sizeof(SPoint));
		SET_VARSIZE(poly, size);
		poly->npts = 1;
		PG_RETURN_POINTER(poly);
	}

	poly = PG_GETARG_SPOLY(0);

	/* skip if equal */
	if (spoint_eq(p, &poly->p[poly->npts - 1]))
	{
		PG_RETURN_POINTER(poly);
	}

	/* Skip if distance is equal 180deg */
	if (FPeq(spoint_dist(p, &poly->p[poly->npts - 1]), PI))
	{
		elog(NOTICE, "spoly(spoint): Skip point, distance of previous point is 180deg");
	}

	size = offsetof(SPOLY, p[0]) +sizeof(SPoint) * (poly->npts + 1);
	poly_new = palloc(size);
	memcpy((void *) poly_new, (void *) poly, VARSIZE(poly));
	poly_new->npts++;
	SET_VARSIZE(poly_new, size);

	memcpy((void *) &poly_new->p[poly->npts], (void *) p, sizeof(SPoint));
	PG_RETURN_POINTER(poly_new);
}


Datum
spherepoly_add_points_finalize(PG_FUNCTION_ARGS)
{
	SPOLY *poly = (SPOLY *) PG_GETARG_POINTER(0);

	if (poly == NULL)
	{
		PG_RETURN_NULL();
	}

	poly = PG_GETARG_SPOLY(0);

	if (poly->npts < 3)
	{
		elog(NOTICE, "spoly(spoint): At least 3 points required");
		pfree(poly);
		PG_RETURN_NULL();
	}
	/* Skip if distance is equal to 180deg */
	if (FPeq(spoint_dist(&poly->p[0], &poly->p[poly->npts - 1]), PI))
	{
		elog(NOTICE, "spoly(spoint): Cannot close polygon. Distance between first and last point is 180deg");
		pfree(poly);
		PG_RETURN_NULL();
	}

	if (!spherepoly_check(poly))
	{
		elog(NOTICE, "spoly(spoint): a line segment overlaps or polygon too large");
		pfree(poly);
		PG_RETURN_NULL();
	}
	PG_RETURN_POINTER(poly);
}
