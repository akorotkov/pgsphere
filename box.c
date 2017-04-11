#include "box.h"

PG_FUNCTION_INFO_V1(spherebox_in);
PG_FUNCTION_INFO_V1(spherebox_in_from_points);
PG_FUNCTION_INFO_V1(spherebox_sw);
PG_FUNCTION_INFO_V1(spherebox_ne);
PG_FUNCTION_INFO_V1(spherebox_se);
PG_FUNCTION_INFO_V1(spherebox_nw);
PG_FUNCTION_INFO_V1(spherebox_area);
PG_FUNCTION_INFO_V1(spherebox_circ);
PG_FUNCTION_INFO_V1(spherebox_equal);
PG_FUNCTION_INFO_V1(spherebox_equal_neg);
PG_FUNCTION_INFO_V1(spherebox_cont_point);
PG_FUNCTION_INFO_V1(spherebox_cont_point_neg);
PG_FUNCTION_INFO_V1(spherebox_cont_point_com);
PG_FUNCTION_INFO_V1(spherebox_cont_point_com_neg);
PG_FUNCTION_INFO_V1(spherebox_cont_circle);
PG_FUNCTION_INFO_V1(spherebox_cont_circle_neg);
PG_FUNCTION_INFO_V1(spherebox_cont_circle_com);
PG_FUNCTION_INFO_V1(spherebox_cont_circle_com_neg);
PG_FUNCTION_INFO_V1(spherecircle_cont_box);
PG_FUNCTION_INFO_V1(spherecircle_cont_box_neg);
PG_FUNCTION_INFO_V1(spherecircle_cont_box_com);
PG_FUNCTION_INFO_V1(spherecircle_cont_box_com_neg);
PG_FUNCTION_INFO_V1(spherebox_overlap_circle);
PG_FUNCTION_INFO_V1(spherebox_overlap_circle_neg);
PG_FUNCTION_INFO_V1(spherebox_overlap_circle_com);
PG_FUNCTION_INFO_V1(spherebox_overlap_circle_com_neg);
PG_FUNCTION_INFO_V1(spherebox_cont_line);
PG_FUNCTION_INFO_V1(spherebox_cont_line_neg);
PG_FUNCTION_INFO_V1(spherebox_cont_line_com);
PG_FUNCTION_INFO_V1(spherebox_cont_line_com_neg);
PG_FUNCTION_INFO_V1(spherebox_overlap_line);
PG_FUNCTION_INFO_V1(spherebox_overlap_line_neg);
PG_FUNCTION_INFO_V1(spherebox_overlap_line_com);
PG_FUNCTION_INFO_V1(spherebox_overlap_line_com_neg);
PG_FUNCTION_INFO_V1(spherebox_cont_path);
PG_FUNCTION_INFO_V1(spherebox_cont_path_neg);
PG_FUNCTION_INFO_V1(spherebox_cont_eq_path_com);
PG_FUNCTION_INFO_V1(spherebox_cont_path_com);
PG_FUNCTION_INFO_V1(spherebox_cont_path_com_neg);
PG_FUNCTION_INFO_V1(spherebox_overlap_path);
PG_FUNCTION_INFO_V1(spherebox_overlap_path_neg);
PG_FUNCTION_INFO_V1(spherebox_overlap_path_com);
PG_FUNCTION_INFO_V1(spherebox_overlap_path_com_neg);
PG_FUNCTION_INFO_V1(spherebox_cont_poly);
PG_FUNCTION_INFO_V1(spherebox_cont_poly_neg);
PG_FUNCTION_INFO_V1(spherebox_cont_poly_com);
PG_FUNCTION_INFO_V1(spherebox_cont_poly_com_neg);
PG_FUNCTION_INFO_V1(spherepoly_cont_box);
PG_FUNCTION_INFO_V1(spherepoly_cont_box_neg);
PG_FUNCTION_INFO_V1(spherepoly_cont_box_com);
PG_FUNCTION_INFO_V1(spherepoly_cont_box_com_neg);
PG_FUNCTION_INFO_V1(spherebox_overlap_poly);
PG_FUNCTION_INFO_V1(spherebox_overlap_poly_neg);
PG_FUNCTION_INFO_V1(spherebox_overlap_poly_com);
PG_FUNCTION_INFO_V1(spherebox_overlap_poly_com_neg);
PG_FUNCTION_INFO_V1(spherebox_cont_ellipse);
PG_FUNCTION_INFO_V1(spherebox_cont_ellipse_neg);
PG_FUNCTION_INFO_V1(spherebox_cont_ellipse_com);
PG_FUNCTION_INFO_V1(spherebox_cont_ellipse_com_neg);
PG_FUNCTION_INFO_V1(sphereellipse_cont_box);
PG_FUNCTION_INFO_V1(sphereellipse_cont_box_neg);
PG_FUNCTION_INFO_V1(sphereellipse_cont_box_com);
PG_FUNCTION_INFO_V1(sphereellipse_cont_box_com_neg);
PG_FUNCTION_INFO_V1(spherebox_overlap_ellipse);
PG_FUNCTION_INFO_V1(spherebox_overlap_ellipse_neg);
PG_FUNCTION_INFO_V1(spherebox_overlap_ellipse_com);
PG_FUNCTION_INFO_V1(spherebox_overlap_ellipse_com_neg);
PG_FUNCTION_INFO_V1(spherebox_cont_box);
PG_FUNCTION_INFO_V1(spherebox_cont_box_neg);
PG_FUNCTION_INFO_V1(spherebox_cont_box_com);
PG_FUNCTION_INFO_V1(spherebox_cont_box_com_neg);
PG_FUNCTION_INFO_V1(spherebox_overlap_box);
PG_FUNCTION_INFO_V1(spherebox_overlap_box_neg);

/*
 * Checks the box: if the latitude of a south-west corner is larger
 * than that of a north-east corner, swap both positions.
 */
static void
sbox_check(SBOX *box)
{
	if (FPgt(box->sw.lat, box->ne.lat))
	{
		/* swap */
		SPoint sp;

		memcpy((void *) &sp, (void *) &box->sw, sizeof(SPoint));
		memcpy((void *) &box->sw, (void *) &box->ne, sizeof(SPoint));
		memcpy((void *) &box->ne, (void *) &sp, sizeof(SPoint));
	}
	if (FPeq(box->sw.lng, box->ne.lng) && FPne(box->sw.lat, box->ne.lat))
	{
		box->sw.lng = 0.0;
		box->ne.lng = PID;
	}
}

/*
 * Puts the 'center' of a box b' into a point 'c' and returns it.
 */
static void
sbox_center(SPoint *c, const SBOX *b)
{
	c->lat = (b->ne.lat + b->sw.lat) / 2.0;
	c->lng = (b->ne.lng + b->sw.lng) / 2.0;
	if (FPgt(b->sw.lng, b->ne.lng))
		c->lng += PI;
}

/*
 * Relationship between a circle and a box as PGS_BOX_CIRCLE_REL int8 value.
 */
static int8
sbox_circle_pos(const SCIRCLE *sc, const SBOX *sb)
{
	if (FPlt((sc->center.lat + sc->radius), sb->sw.lat))
	{
		return PGS_BOX_CIRCLE_AVOID;
	}
	else if (FPgt((sc->center.lat - sc->radius), sb->ne.lat))
	{
		return PGS_BOX_CIRCLE_AVOID;
	}
	else if (FPzero(sb->sw.lng) && FPeq(sb->ne.lng, PID))
	{
		/* full latitude range */
		const SPoint tmpn = {0.0, PIH};
		const SPoint tmps = {0.0, -PIH};

		if (spoint_eq(&sb->ne, &tmpn) &&
				FPge(sc->center.lat - sc->radius, sb->sw.lat))
		{
			if (spoint_eq(&sc->center, &tmpn) &&
					FPeq(sc->radius, (PIH - sb->sw.lat)))
			{
				return PGS_BOX_CIRCLE_EQUAL;
			}
			else
			{
				return PGS_BOX_CONT_CIRCLE;
			}
		}
		else if (spoint_eq(&sb->sw, &tmps) &&
				 FPle(sc->center.lat + sc->radius, sb->ne.lat))
		{
			if (spoint_eq(&sc->center, &tmps) &&
					FPeq(sc->radius, (PIH + sb->ne.lat)))
			{
				return PGS_BOX_CIRCLE_EQUAL;
			}
			else
			{
				return PGS_BOX_CONT_CIRCLE;
			}
		}
		else if (FPle((sc->center.lat + sc->radius), sb->ne.lat) &&
				 FPge((sc->center.lat - sc->radius), sb->sw.lat)
			)
		{
			return PGS_BOX_CONT_CIRCLE;
		}
		else
		{
			return PGS_BOX_CIRCLE_OVER;
		}
	}
	else
	{
		bool		lat_b_cont_c =
						((sc->center.lat + sc->radius) <= sb->ne.lat) &&
						((sc->center.lat - sc->radius) >= sb->sw.lat);
		bool		bcc = sbox_cont_point(sb, &sc->center);
		bool		ccb = false;
		int8		pw,
					pe;
		SLine		bw,
					be;

		/* west and east boundary */
		SPoint		bc;
		SPoint		p1,
					p2;

		/* center */
		sbox_center(&bc, sb);
		ccb = spoint_in_circle(&bc, sc);

		p1.lat = sb->sw.lat;
		p2.lat = sb->ne.lat;

		/* west */
		p1.lng = p2.lng = sb->sw.lng;
		sline_from_points(&bw, &p1, &p2);
		/* east */
		p1.lng = p2.lng = sb->ne.lng;
		sline_from_points(&be, &p1, &p2);

		/* check E/W boundaries */
		pw = sphereline_circle_pos(&bw, sc);
		pe = sphereline_circle_pos(&be, sc);
		if (pw == PGS_CIRCLE_LINE_AVOID && pe == PGS_CIRCLE_LINE_AVOID)
		{
			if (bcc && lat_b_cont_c)
			{
				return PGS_BOX_CONT_CIRCLE;
			}
			return PGS_BOX_CIRCLE_AVOID;
		}
		if (pw == PGS_CIRCLE_CONT_LINE && pe == PGS_CIRCLE_CONT_LINE)
		{
			if (ccb)
			{
				return PGS_CIRCLE_CONT_BOX;
			}
			return PGS_BOX_CIRCLE_OVER;
		}
		if (bcc && lat_b_cont_c)
		{
			bool	touw = false,
					toue = false;

			if (pw == PGS_CIRCLE_LINE_OVER)
			{
				touw = sline_circle_touch(&bw, sc);
			}
			if (pw == PGS_CIRCLE_LINE_OVER)
			{
				toue = sline_circle_touch(&be, sc);
			}
			if (touw && toue)
			{
				return PGS_BOX_CONT_CIRCLE;
			}
			else if (touw && pe == PGS_CIRCLE_LINE_AVOID)
			{
				return PGS_BOX_CONT_CIRCLE;
			}
			if (toue && pw == PGS_CIRCLE_LINE_AVOID)
			{
				return PGS_BOX_CONT_CIRCLE;
			}
			return PGS_BOX_CIRCLE_OVER;
		}
		return PGS_BOX_CIRCLE_OVER;

	}
	return PGS_BOX_CIRCLE_AVOID;
}

/*
 * Relationship between a line and a box as PGS_BOX_LINE_REL int8 value.
 */
static int8
sbox_line_pos(const SLine *sl, const SBOX *sb)
{
	SPoint	p1, p2, pbg, ped;
	SPoint	lc[4];
	int8	pw, pe, lcn, lcs;
	SLine	bw, be;
	float8	minlat,	maxlat;

	sline_begin(&pbg, sl);
	sline_end(&ped, sl);

	if (FPzero(sl->length))
	{
		if (sbox_cont_point(sb, &pbg))
		{
			return PGS_BOX_CONT_LINE;
		}
		else
		{
			return PGS_BOX_LINE_AVOID;
		}
	}
	sline_min_max_lat(sl, &minlat, &maxlat);

	if (FPgt(minlat, sb->ne.lat))
		return PGS_BOX_LINE_AVOID;
	if (FPlt(maxlat, sb->sw.lat))
		return PGS_BOX_LINE_AVOID;

	if (FPzero(sb->sw.lng) && FPeq(sb->ne.lng, PID))
	{
		/* full latitude range */
		if (FPle(sb->sw.lat, minlat) && FPle(maxlat, sb->ne.lat))
		{
			return PGS_BOX_CONT_LINE;
		}
		return PGS_BOX_LINE_OVER;
	}

	/* create east/west boundaries */

	p1.lat = sb->sw.lat;
	p2.lat = sb->ne.lat;

	/* west */
	p1.lng = p2.lng = sb->sw.lng;
	sline_from_points(&bw, &p1, &p2);

	/* east */
	p1.lng = p2.lng = sb->ne.lng;
	sline_from_points(&be, &p1, &p2);


	/* special case: east/west boundaries are connected */
	if ((FPeq(sb->ne.lat, PIH) || FPeq(sb->sw.lat, -PIH)) &&
			FPeq(fabs(sb->sw.lng - sb->ne.lng), PI))
	{
		if (FPeq(sb->ne.lat, PIH))
		{
			/* west */
			p1.lat = sb->sw.lat;
			p2.lat = sb->ne.lat;
			p1.lng = p2.lng = sb->sw.lng;
			sline_from_points(&bw, &p1, &p2);
			bw.length *= 2;
		}
		if (FPeq(sb->ne.lat, PIH))
		{
			/* west */
			p1.lat = sb->ne.lat;
			p2.lat = sb->sw.lat;
			p1.lng = p2.lng = sb->ne.lng;
			sline_from_points(&be, &p1, &p2);
			be.length *= 2;
		}
	}

	pw = sline_sline_pos(&bw, sl);
	pe = sline_sline_pos(&be, sl);

	if (pw == PGS_LINE_EQUAL || pe == PGS_LINE_EQUAL)
	{
		return PGS_BOX_CONT_LINE;
	}
	if (pw == PGS_LINE_CONT_LINE || pe == PGS_LINE_CONT_LINE)
	{
		return PGS_BOX_CONT_LINE;
	}
	if (pw == PGS_LINE_CROSS || pe == PGS_LINE_CROSS)
	{
		if (pw == PGS_LINE_CROSS)
		{
			if (!spoint_at_sline(&pbg, &bw) && !spoint_at_sline(&ped, &bw))
			{
				return PGS_BOX_LINE_OVER;
			}
		}
		if (pe == PGS_LINE_CROSS)
		{
			if (!spoint_at_sline(&pbg, &be) && !spoint_at_sline(&ped, &be))
			{
				return PGS_BOX_LINE_OVER;
			}
		}
	}
	if (pw == PGS_LINE_OVER || pe == PGS_LINE_OVER)
	{
		return PGS_BOX_LINE_OVER;
	}

	/* check latitude */
	lcn = sphereline_latitude_points(sl, sb->ne.lat, &lc[0], &lc[1]);
	if (lcn < 0)
		lcn = 0;
	lcs = sphereline_latitude_points(sl, sb->sw.lat, &lc[lcn], &lc[lcn + 1]);
	if (lcs < 0)
		lcs = 0;
	lcn += lcs;

	pw = sbox_cont_point(sb, &pbg);
	pe = sbox_cont_point(sb, &ped);

	if (pw && pe)
	{
		SPoint	sp;
		int		i;

		for (i = 0; i < lcn; i++)
		{
			if (sbox_cont_point(sb, &lc[i]) &&
					(!spoint_eq(&pbg, &lc[i]) && !spoint_eq(&ped, &lc[i])))
			{
				return PGS_BOX_LINE_OVER;
			}
		}

		/* check center */
		sline_center(&sp, sl);
		if (sbox_cont_point(sb, &sp))
		{
			return PGS_BOX_CONT_LINE;
		}
		else
		{
			return PGS_BOX_LINE_OVER;
		}

	}
	else if (!pw && !pe)
	{
		int		i;

		for (i = 0; i < lcn; i++)
		{
			if (sbox_cont_point(sb, &lc[i]))
			{
				return PGS_BOX_LINE_OVER;
			}
		}
		return PGS_BOX_LINE_AVOID;
	}
	return PGS_BOX_LINE_OVER;
}

/*
 * Returns the relationship between a box and a path as
 * PGS_BOX_PATH_REL int8 value.
 */
static int8
sbox_path_pos(const SPATH *path, const SBOX *box)
{
	int8		pos;
	int32		i;
	SLine		sl;
	int32		n;
	const int8	sb_in = (1 << PGS_BOX_CONT_LINE);
	const int8	sb_ov = (1 << PGS_BOX_LINE_OVER);
	const int8	sb_os = (1 << PGS_BOX_LINE_AVOID);

	n = path->npts - 1;
	pos = 0;

	if (spoint_eq(&box->sw, &box->ne))
	{
		if (spath_cont_point(path, &box->sw))
		{
			return PGS_BOX_PATH_OVER;
		}
		else
		{
			return PGS_BOX_PATH_AVOID;
		}
	}

	for (i = 0; i < n; i++)
	{
		spath_segment(&sl, path, i);
		pos |= (1 << sbox_line_pos(&sl, box));
		if (pos & sb_ov)
		{
			return PGS_BOX_PATH_OVER;
		}
	}

	if (pos == sb_in)
	{
		/* all lines inside box */
		/* box contains path */
		return PGS_BOX_CONT_PATH;
	}
	else if (pos == sb_os)
	{
		/* all lines outside box */
		/* box outside path */
		return PGS_BOX_PATH_AVOID;
	}

	/* box and polygon overlap */
	return PGS_BOX_PATH_OVER;
}

/*
 * Returns the relationship between a polygon and a box as
 * PGS_BOX_POLY_REL int8 value.
 */
static int8
sbox_poly_pos(const SPOLY *poly, const SBOX *box)
{
	int8		pos = 0;
	int32		i;
	SLine		sl;
	SPoint		sp;
	bool		pcp;
	const int8	sb_in = (1 << PGS_BOX_CONT_LINE);
	const int8	sb_ov = (1 << PGS_BOX_LINE_OVER);
	const int8	sb_os = (1 << PGS_BOX_LINE_AVOID);

	sbox_center(&sp, box);
	pcp = spoly_contains_point(poly, &sp);

	if (spoint_eq(&box->sw, &box->ne))
	{
		if (pcp)
		{
			return PGS_POLY_CONT_BOX;
		}
		else
		{
			return PGS_BOX_POLY_AVOID;
		}
	}

	for (i = 0; i < poly->npts; i++)
	{
		spoly_segment(&sl, poly, i);
		pos |= (1 << sbox_line_pos(&sl, box));
		if (((pos & sb_in) && (pos & sb_os)) || (pos & sb_ov))
		{
			/* overlaps */
			return PGS_BOX_POLY_OVER;
		}
	}

	if ((pos & sb_in) == pos)
	{
		/* all lines inside box; box contains polygon */
		return PGS_BOX_CONT_POLY;
	}
	else if ((pos & sb_os) == pos)
	{
		/* all lines outside box */
		if (pcp)
		{
			/* polygon contains box */
			return PGS_POLY_CONT_BOX;
		}
		else
		{
			/* box outside polygon */
			return PGS_BOX_POLY_AVOID;
		}
	}
	/* box and polygon overlap */
	return PGS_BOX_POLY_OVER;
}


/*
 * Relationship between an ellipse and a box as PGS_BOX_ELLIPSE_REL int8 value.
 */
static int8
sbox_ellipse_pos(const SELLIPSE *ell, const SBOX *box)
{
	SCIRCLE		sco,
				sci;
	SPoint		ec;
	int8		pw,
				pe,
				po,
				pi;
	SLine		bw,
				be;

	if (spoint_eq(&box->sw, &box->ne))
	{
		bool	scp = sellipse_cont_point(ell, &box->sw);

		if (scp)
		{
			return PGS_ELLIPSE_CONT_BOX;
		}
		else
		{
			return PGS_BOX_ELLIPSE_AVOID;
		}
	}

	/* init circles */
	sco.center.lng = sci.center.lng = 0.0;
	if (box->sw.lat >= 0.0 && box->ne.lat >= 0.0)
	{
		sco.center.lat = sci.center.lat = PIH;
		sco.radius = PIH - box->sw.lat;
		sci.radius = PIH - box->ne.lat;
		if (FPlt(sco.radius, PIH))
			sco.radius += EPSILON;
	}
	else if (box->sw.lat <= 0.0 && box->ne.lat <= 0.0)
	{
		sco.center.lat = sci.center.lat = -PIH;
		sco.radius = PIH + box->sw.lat;
		sci.radius = PIH + box->ne.lat;
		if (FPlt(sco.radius, PIH))
			sco.radius += EPSILON;
	}
	else
	{
		sco.center.lat = -PIH;

		/* south */
		sci.center.lat = PIH;
		/* north */
		sco.radius = PIH + box->sw.lat;
		sci.radius = PIH - box->ne.lat;
		if (FPgt(sco.radius, 0.0))
			sco.radius -= EPSILON;
	}
	if (FPgt(sci.radius, 0.0))
		sci.radius -= EPSILON;


	po = sellipse_circle_pos(ell, &sco);
	pi = sellipse_circle_pos(ell, &sci);

	/* check by latitude */
	if (pi == PGS_CIRCLE_CONT_ELLIPSE || pi == PGS_ELLIPSE_CIRCLE_EQUAL)
	{
		return PGS_BOX_ELLIPSE_AVOID;
	}
	if (FPeq(sco.center.lat, sci.center.lat))
	{
		if (po == PGS_ELLIPSE_CIRCLE_AVOID)
		{
			return PGS_BOX_ELLIPSE_AVOID;
		}
		if (FPzero(box->sw.lng) && FPeq(box->ne.lng, PID))
		{
			/* full latitude range */
			if ((po == PGS_CIRCLE_CONT_ELLIPSE
						|| po == PGS_ELLIPSE_CIRCLE_EQUAL) &&
					pi == PGS_ELLIPSE_CIRCLE_AVOID)
			{
				return PGS_BOX_CONT_ELLIPSE;
			}
			else
			{
				return PGS_BOX_ELLIPSE_OVER;
			}
		}
	}
	else
	{
		/* equator modus */
		if (po == PGS_CIRCLE_CONT_ELLIPSE || po == PGS_ELLIPSE_CIRCLE_EQUAL)
		{
			return PGS_BOX_ELLIPSE_AVOID;
		}
		if (FPzero(box->sw.lng) && FPeq(box->ne.lng, PID))
		{
			/* full latitude range */
			if (po == PGS_ELLIPSE_CIRCLE_AVOID &&
				pi == PGS_ELLIPSE_CIRCLE_AVOID)
			{
				return PGS_BOX_CONT_ELLIPSE;
			}
			else
			{
				return PGS_BOX_ELLIPSE_OVER;
			}
		}
	}

	sellipse_center(&ec, ell);
	if (FPgt(box->sw.lng, 0.0))
	{
		sline_meridian(&bw, box->sw.lng - EPSILON);
	}
	else
	{
		sline_meridian(&bw, box->sw.lng);
	}
	sline_meridian(&be, box->ne.lng + EPSILON);
	pw = sellipse_line_pos(ell, &bw);
	pe = sellipse_line_pos(ell, &be);

	/* check meridians */
	if (pw == PGS_ELLIPSE_LINE_AVOID &&
		pe == PGS_ELLIPSE_LINE_AVOID)
	{
		/* center is between west and east meridians */
		if ((FPgt(box->sw.lng, box->ne.lng) &&
					(FPle(ec.lng, box->ne.lng) || FPgt(ec.lng, box->sw.lng))) ||
			(FPle(box->sw.lng, box->ne.lng) &&
					(FPge(ec.lng, box->sw.lng) && FPle(ec.lng, box->ne.lng))))
		{
			if (FPeq(sco.center.lat, sci.center.lat))
			{
				if ((po == PGS_CIRCLE_CONT_ELLIPSE
							|| po == PGS_ELLIPSE_CIRCLE_EQUAL) &&
						pi == PGS_ELLIPSE_CIRCLE_AVOID)
				{
					return PGS_BOX_CONT_ELLIPSE;
				}
				else
				{
					return PGS_BOX_ELLIPSE_OVER;
				}
			}
			else
			{
				/* equator modus */
				if (po == PGS_ELLIPSE_CIRCLE_AVOID &&
					pi == PGS_ELLIPSE_CIRCLE_AVOID)
				{
					return PGS_BOX_CONT_ELLIPSE;
				}
				else
				{
					return PGS_BOX_ELLIPSE_OVER;
				}
			}
		}
		return PGS_BOX_ELLIPSE_AVOID;

	}
	else
	{
		SPoint	p1, p2;

		/* create east/west boundaries */
		p1.lat = box->sw.lat;
		p2.lat = box->ne.lat;
		/* west */
		p1.lng = p2.lng = box->sw.lng;
		sline_from_points(&bw, &p1, &p2);
		/* east */
		p1.lng = p2.lng = box->ne.lng;
		sline_from_points(&be, &p1, &p2);
		pw = sellipse_line_pos(ell, &bw);
		pe = sellipse_line_pos(ell, &be);
		sbox_center(&ec, box);

		/* ellipse contains box */
		if (pw == PGS_ELLIPSE_CONT_LINE &&
			pe == PGS_ELLIPSE_CONT_LINE &&
			sellipse_cont_point(ell, &ec))
		{
			return PGS_ELLIPSE_CONT_BOX;
		}

	}
	return PGS_BOX_LINE_OVER;

}

/*
 * Relationship between two boxes as PGS_BOX_REL int8 value.
 */
static int8
sbox_box_pos(const SBOX *b1, const SBOX *b2, bool recheck)
{
	SPoint	p1, p2, bc;
	int8	pw, pe;
	SLine	bw, be;
	bool	scp;

	if (spoint_eq(&b2->sw, &b2->ne))
	{
		scp = sbox_cont_point(b1, &b2->sw);
		if (scp)
		{
			return PGS_BOX_CONT;
		}
		else
		{
			return PGS_BOX_AVOID;
		}
	}

	if (FPzero(b1->sw.lng) && FPeq(b1->ne.lng, PID))
	{
		/* full latitude range */
		if (FPge(b2->sw.lat, b1->sw.lat) && FPle(b2->ne.lat, b1->ne.lat))
		{
			return PGS_BOX_CONT;
		}
		else if (FPgt(b2->sw.lat, b1->ne.lat) || FPlt(b2->ne.lat, b1->sw.lat))
		{
			return PGS_BOX_AVOID;
		}
		return PGS_BOX_OVER;
	}

	/* create east/west boundaries from b2 */
	p1.lat = b2->sw.lat;
	p2.lat = b2->ne.lat;

	/* west */
	p1.lng = p2.lng = b2->sw.lng;
	sline_from_points(&bw, &p1, &p2);

	/* east */
	p1.lng = p2.lng = b2->ne.lng;
	sline_from_points(&be, &p1, &p2);

	pe = sbox_line_pos(&be, b1);
	pw = sbox_line_pos(&bw, b1);

	sbox_center(&bc, b2);
	scp = sbox_cont_point(b1, &bc);

	if (scp && pe == PGS_BOX_CONT_LINE && pw == PGS_BOX_CONT_LINE)
	{
		return PGS_BOX_CONT;
	}
	if (pe > PGS_BOX_LINE_AVOID || pw > PGS_BOX_LINE_AVOID)
	{
		return PGS_BOX_OVER;
	}

	if (!recheck)
	{
		pe = sbox_box_pos(b2, b1, true);
		if (pe == PGS_BOX_CONT)
		{
			return PGS_BOX_OVER;
		}
	}
	return PGS_BOX_AVOID;
}

bool
sbox_eq(SBOX *b1, SBOX *b2)
{
	return (spoint_eq(&b1->sw, &b2->sw) && spoint_eq(&b1->ne, &b2->ne));
}

bool
sbox_cont_point(const SBOX *b, const SPoint *p)
{
	if ((FPeq(p->lat, b->ne.lat) && FPeq(p->lat, PIH)) ||
		(FPeq(p->lat, b->sw.lat) && FPeq(p->lat, -PIH)))
	{
		return true;
	}

	if (FPlt(p->lat, b->sw.lat) || FPgt(p->lat, b->ne.lat))
	{
		return false;
	}
	if (FPgt(b->sw.lng, b->ne.lng))
	{
		if (FPlt(p->lng, b->sw.lng) && FPgt(p->lng, b->ne.lng))
			return false;
	}
	else
	{
		if (FPlt(p->lng, b->sw.lng) || FPgt(p->lng, b->ne.lng))
			return false;
	}
	return true;
}

Datum
spherebox_in(PG_FUNCTION_ARGS)
{
	SBOX	   *box = (SBOX *) palloc(sizeof(SBOX));
	char	   *c = PG_GETARG_CSTRING(0);

	void		sphere_yyparse(void);

	init_buffer(c);
	sphere_yyparse();

	if (!get_box(&box->sw.lng, &box->sw.lat, &box->ne.lng, &box->ne.lat))
	{
		reset_buffer();
		pfree(box);
		elog(ERROR, "spherebox_in: wrong data type");
		PG_RETURN_NULL();

	}
	spoint_check(&box->sw);
	spoint_check(&box->ne);
	sbox_check(box);
	reset_buffer();

	PG_RETURN_POINTER(box);
}

Datum
spherebox_in_from_points(PG_FUNCTION_ARGS)
{
	SBOX	   *box = (SBOX *) palloc(sizeof(SBOX));
	SPoint	   *p1 = (SPoint *) PG_GETARG_POINTER(0);
	SPoint	   *p2 = (SPoint *) PG_GETARG_POINTER(1);

	memcpy((void *) &box->sw, (void *) p1, sizeof(SPoint));
	memcpy((void *) &box->ne, (void *) p2, sizeof(SPoint));
	sbox_check(box);
	PG_RETURN_POINTER(box);
}

Datum
spherebox_sw(PG_FUNCTION_ARGS)
{
	SPoint	   *p = (SPoint *) palloc(sizeof(SPoint));
	SBOX	   *box = (SBOX *) PG_GETARG_POINTER(0);

	memcpy((void *) p, (void *) &box->sw, sizeof(SPoint));
	PG_RETURN_POINTER(p);
}

Datum
spherebox_ne(PG_FUNCTION_ARGS)
{
	SPoint	   *p = (SPoint *) palloc(sizeof(SPoint));
	SBOX	   *box = (SBOX *) PG_GETARG_POINTER(0);

	memcpy((void *) p, (void *) &box->ne, sizeof(SPoint));
	PG_RETURN_POINTER(p);
}

Datum
spherebox_se(PG_FUNCTION_ARGS)
{
	SPoint	   *p = (SPoint *) palloc(sizeof(SPoint));
	SBOX	   *box = (SBOX *) PG_GETARG_POINTER(0);

	p->lng = box->ne.lng;
	p->lat = box->sw.lat;
	PG_RETURN_POINTER(p);
}

Datum
spherebox_nw(PG_FUNCTION_ARGS)
{
	SPoint	   *p = (SPoint *) palloc(sizeof(SPoint));
	SBOX	   *box = (SBOX *) PG_GETARG_POINTER(0);

	p->lng = box->sw.lng;
	p->lat = box->ne.lat;
	PG_RETURN_POINTER(p);
}

Datum
spherebox_area(PG_FUNCTION_ARGS)
{
	SBOX	   *box = (SBOX *) PG_GETARG_POINTER(0);
	float8		a;

	if (FPgt(box->sw.lng, box->ne.lng))
	{
		a = PID + box->ne.lng - box->sw.lng;
	}
	else
	{
		a = box->ne.lng - box->sw.lng;
	}
	a *= (sin(box->ne.lat) - sin(box->sw.lat));
	PG_RETURN_FLOAT8(a);
}

Datum
spherebox_circ(PG_FUNCTION_ARGS)
{
	SBOX	   *box = (SBOX *) PG_GETARG_POINTER(0);
	float8		a;

	if (FPgt(box->sw.lng, box->ne.lng))
	{
		a = PID + box->ne.lng - box->sw.lng;
	}
	else
	{
		a = box->ne.lng - box->sw.lng;
	}
	a = (a * cos(box->ne.lat) + a * cos(box->sw.lat));
	a += 2 * (box->ne.lat - box->sw.lat);
	PG_RETURN_FLOAT8(a);
}

Datum
spherebox_equal(PG_FUNCTION_ARGS)
{
	SBOX	   *b1 = (SBOX *) PG_GETARG_POINTER(0);
	SBOX	   *b2 = (SBOX *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(sbox_eq(b1, b2));
}

Datum
spherebox_equal_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b1 = (SBOX *) PG_GETARG_POINTER(0);
	SBOX	   *b2 = (SBOX *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(!sbox_eq(b1, b2));
}

Datum
spherebox_cont_point(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(sbox_cont_point(b, p));
}

Datum
spherebox_cont_point_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(!sbox_cont_point(b, p));
}

Datum
spherebox_cont_point_com(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(sbox_cont_point(b, p));
}

Datum
spherebox_cont_point_com_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(!sbox_cont_point(b, p));
}

Datum
spherebox_cont_circle(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(1);
	int			pos = sbox_circle_pos(c, b);

	PG_RETURN_BOOL(pos == PGS_BOX_CONT_CIRCLE || pos == PGS_BOX_CIRCLE_EQUAL);
}

Datum
spherebox_cont_circle_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(1);
	int			pos = sbox_circle_pos(c, b);

	PG_RETURN_BOOL(pos != PGS_BOX_CONT_CIRCLE && pos != PGS_BOX_CIRCLE_EQUAL);
}

Datum
spherebox_cont_circle_com(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(0);
	int			pos = sbox_circle_pos(c, b);

	PG_RETURN_BOOL(pos == PGS_BOX_CONT_CIRCLE || pos == PGS_BOX_CIRCLE_EQUAL);
}

Datum
spherebox_cont_circle_com_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(0);
	int			pos = sbox_circle_pos(c, b);

	PG_RETURN_BOOL(pos != PGS_BOX_CONT_CIRCLE && pos != PGS_BOX_CIRCLE_EQUAL);
}

Datum
spherecircle_cont_box(PG_FUNCTION_ARGS)
{
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(0);
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	int			pos = sbox_circle_pos(c, b);

	PG_RETURN_BOOL(pos == PGS_CIRCLE_CONT_BOX || pos == PGS_BOX_CIRCLE_EQUAL);
}

Datum
spherecircle_cont_box_neg(PG_FUNCTION_ARGS)
{
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(0);
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	int			pos = sbox_circle_pos(c, b);

	PG_RETURN_BOOL(pos != PGS_CIRCLE_CONT_BOX && pos != PGS_BOX_CIRCLE_EQUAL);
}

Datum
spherecircle_cont_box_com(PG_FUNCTION_ARGS)
{
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(1);
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	int			pos = sbox_circle_pos(c, b);

	PG_RETURN_BOOL(pos == PGS_CIRCLE_CONT_BOX || pos == PGS_BOX_CIRCLE_EQUAL);
}

Datum
spherecircle_cont_box_com_neg(PG_FUNCTION_ARGS)
{
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(1);
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	int			pos = sbox_circle_pos(c, b);

	PG_RETURN_BOOL(pos != PGS_CIRCLE_CONT_BOX && pos != PGS_BOX_CIRCLE_EQUAL);
}

Datum
spherebox_overlap_circle(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(sbox_circle_pos(c, b) > PGS_BOX_CIRCLE_AVOID);
}

Datum
spherebox_overlap_circle_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(!(sbox_circle_pos(c, b) > PGS_BOX_CIRCLE_AVOID));
}

Datum
spherebox_overlap_circle_com(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(sbox_circle_pos(c, b) > PGS_BOX_CIRCLE_AVOID);
}

Datum
spherebox_overlap_circle_com_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(!(sbox_circle_pos(c, b) > PGS_BOX_CIRCLE_AVOID));
}

Datum
spherebox_cont_line(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SLine	   *l = (SLine *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(sbox_line_pos(l, b) == PGS_BOX_CONT_LINE);
}

Datum
spherebox_cont_line_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SLine	   *l = (SLine *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(!(sbox_line_pos(l, b) == PGS_BOX_CONT_LINE));
}

Datum
spherebox_cont_line_com(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SLine	   *l = (SLine *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(sbox_line_pos(l, b) == PGS_BOX_CONT_LINE);
}

Datum
spherebox_cont_line_com_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SLine	   *l = (SLine *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(!(sbox_line_pos(l, b) == PGS_BOX_CONT_LINE));
}

Datum
spherebox_overlap_line(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SLine	   *l = (SLine *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(sbox_line_pos(l, b) > PGS_BOX_LINE_AVOID);
}

Datum
spherebox_overlap_line_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SLine	   *l = (SLine *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(!(sbox_line_pos(l, b) > PGS_BOX_LINE_AVOID));
}

Datum
spherebox_overlap_line_com(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SLine	   *l = (SLine *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(sbox_line_pos(l, b) > PGS_BOX_LINE_AVOID);
}

Datum
spherebox_overlap_line_com_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SLine	   *l = (SLine *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(!(sbox_line_pos(l, b) > PGS_BOX_LINE_AVOID));
}

Datum
spherebox_cont_path(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SPATH	   *p = PG_GETARG_SPATH(1);

	PG_RETURN_BOOL(sbox_path_pos(p, b) == PGS_BOX_CONT_PATH);
}

Datum
spherebox_cont_path_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SPATH	   *p = PG_GETARG_SPATH(1);

	PG_RETURN_BOOL(!(sbox_path_pos(p, b) == PGS_BOX_CONT_PATH));
}

Datum
spherebox_cont_path_com(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SPATH	   *p = PG_GETARG_SPATH(0);

	PG_RETURN_BOOL(sbox_path_pos(p, b) == PGS_BOX_CONT_PATH);
}

Datum
spherebox_cont_path_com_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SPATH	   *p = PG_GETARG_SPATH(0);

	PG_RETURN_BOOL(!(sbox_path_pos(p, b) == PGS_BOX_CONT_PATH));
}

Datum
spherebox_overlap_path(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SPATH	   *p = PG_GETARG_SPATH(1);

	PG_RETURN_BOOL(sbox_path_pos(p, b) > PGS_BOX_PATH_AVOID);
}

Datum
spherebox_overlap_path_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SPATH	   *p = PG_GETARG_SPATH(1);

	PG_RETURN_BOOL(!(sbox_path_pos(p, b) > PGS_BOX_PATH_AVOID));
}

Datum
spherebox_overlap_path_com(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SPATH	   *p = PG_GETARG_SPATH(0);

	PG_RETURN_BOOL(sbox_path_pos(p, b) > PGS_BOX_PATH_AVOID);
}

Datum
spherebox_overlap_path_com_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SPATH	   *p = PG_GETARG_SPATH(0);

	PG_RETURN_BOOL(!(sbox_path_pos(p, b) > PGS_BOX_PATH_AVOID));
}

Datum
spherebox_cont_poly(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SPOLY	   *p = PG_GETARG_SPOLY(1);

	PG_RETURN_BOOL(sbox_poly_pos(p, b) == PGS_BOX_CONT_POLY);
}

Datum
spherebox_cont_poly_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SPOLY	   *p = PG_GETARG_SPOLY(1);

	PG_RETURN_BOOL(!(sbox_poly_pos(p, b) == PGS_BOX_CONT_POLY));
}

Datum
spherebox_cont_poly_com(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SPOLY	   *p = PG_GETARG_SPOLY(0);

	PG_RETURN_BOOL(sbox_poly_pos(p, b) == PGS_BOX_CONT_POLY);
}

Datum
spherebox_cont_poly_com_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SPOLY	   *p = PG_GETARG_SPOLY(0);

	PG_RETURN_BOOL(!(sbox_poly_pos(p, b) == PGS_BOX_CONT_POLY));
}

Datum
spherepoly_cont_box(PG_FUNCTION_ARGS)
{
	SPOLY	   *p = PG_GETARG_SPOLY(0);
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(sbox_poly_pos(p, b) == PGS_POLY_CONT_BOX);
}

Datum
spherepoly_cont_box_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *p = PG_GETARG_SPOLY(0);
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(!(sbox_poly_pos(p, b) == PGS_POLY_CONT_BOX));
}

Datum
spherepoly_cont_box_com(PG_FUNCTION_ARGS)
{
	SPOLY	   *p = PG_GETARG_SPOLY(1);
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(sbox_poly_pos(p, b) == PGS_POLY_CONT_BOX);
}

Datum
spherepoly_cont_box_com_neg(PG_FUNCTION_ARGS)
{
	SPOLY	   *p = PG_GETARG_SPOLY(1);
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(!(sbox_poly_pos(p, b) == PGS_POLY_CONT_BOX));
}

Datum
spherebox_overlap_poly(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SPOLY	   *p = PG_GETARG_SPOLY(1);

	PG_RETURN_BOOL(sbox_poly_pos(p, b) > PGS_BOX_POLY_AVOID);
}

Datum
spherebox_overlap_poly_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SPOLY	   *p = PG_GETARG_SPOLY(1);

	PG_RETURN_BOOL(!(sbox_poly_pos(p, b) > PGS_BOX_POLY_AVOID));
}

Datum
spherebox_overlap_poly_com(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SPOLY	   *p = PG_GETARG_SPOLY(0);

	PG_RETURN_BOOL(sbox_poly_pos(p, b) > PGS_BOX_POLY_AVOID);
}

Datum
spherebox_overlap_poly_com_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SPOLY	   *p = PG_GETARG_SPOLY(0);

	PG_RETURN_BOOL(!(sbox_poly_pos(p, b) > PGS_BOX_POLY_AVOID));
}

Datum
spherebox_cont_ellipse(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(sbox_ellipse_pos(e, b) == PGS_BOX_CONT_ELLIPSE);
}

Datum
spherebox_cont_ellipse_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(!(sbox_ellipse_pos(e, b) == PGS_BOX_CONT_ELLIPSE));
}

Datum
spherebox_cont_ellipse_com(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(sbox_ellipse_pos(e, b) == PGS_BOX_CONT_ELLIPSE);
}

Datum
spherebox_cont_ellipse_com_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(!(sbox_ellipse_pos(e, b) == PGS_BOX_CONT_ELLIPSE));
}

Datum
sphereellipse_cont_box(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(sbox_ellipse_pos(e, b) == PGS_ELLIPSE_CONT_BOX);
}

Datum
sphereellipse_cont_box_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(!(sbox_ellipse_pos(e, b) == PGS_ELLIPSE_CONT_BOX));
}

Datum
sphereellipse_cont_box_com(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(1);
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(sbox_ellipse_pos(e, b) == PGS_ELLIPSE_CONT_BOX);
}

Datum
sphereellipse_cont_box_com_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(1);
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(!(sbox_ellipse_pos(e, b) == PGS_ELLIPSE_CONT_BOX));
}

Datum
spherebox_overlap_ellipse(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(sbox_ellipse_pos(e, b) > PGS_BOX_ELLIPSE_AVOID);
}

Datum
spherebox_overlap_ellipse_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(0);
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(!(sbox_ellipse_pos(e, b) > PGS_BOX_ELLIPSE_AVOID));
}

Datum
spherebox_overlap_ellipse_com(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(sbox_ellipse_pos(e, b) > PGS_BOX_ELLIPSE_AVOID);
}

Datum
spherebox_overlap_ellipse_com_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *b = (SBOX *) PG_GETARG_POINTER(1);
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(!(sbox_ellipse_pos(e, b) > PGS_BOX_ELLIPSE_AVOID));
}

Datum
spherebox_cont_box(PG_FUNCTION_ARGS)
{
	SBOX	   *box1 = (SBOX *) PG_GETARG_POINTER(0);
	SBOX	   *box2 = (SBOX *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(sbox_box_pos(box1, box2, false) == PGS_BOX_CONT);
}

Datum
spherebox_cont_box_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *box1 = (SBOX *) PG_GETARG_POINTER(0);
	SBOX	   *box2 = (SBOX *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(!(sbox_box_pos(box1, box2, false) == PGS_BOX_CONT));
}

Datum
spherebox_cont_box_com(PG_FUNCTION_ARGS)
{
	SBOX	   *box1 = (SBOX *) PG_GETARG_POINTER(1);
	SBOX	   *box2 = (SBOX *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(sbox_box_pos(box1, box2, false) == PGS_BOX_CONT);
}

Datum
spherebox_cont_box_com_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *box1 = (SBOX *) PG_GETARG_POINTER(1);
	SBOX	   *box2 = (SBOX *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(!(sbox_box_pos(box1, box2, false) == PGS_BOX_CONT));
}

Datum
spherebox_overlap_box(PG_FUNCTION_ARGS)
{
	SBOX	   *box1 = (SBOX *) PG_GETARG_POINTER(0);
	SBOX	   *box2 = (SBOX *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(sbox_box_pos(box1, box2, false) > PGS_BOX_AVOID);
}

Datum
spherebox_overlap_box_neg(PG_FUNCTION_ARGS)
{
	SBOX	   *box1 = (SBOX *) PG_GETARG_POINTER(0);
	SBOX	   *box2 = (SBOX *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(sbox_box_pos(box1, box2, false) == PGS_BOX_AVOID);
}
