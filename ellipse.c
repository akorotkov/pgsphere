#include "ellipse.h"

/* Ellipse functions */

PG_FUNCTION_INFO_V1(sphereellipse_in);
PG_FUNCTION_INFO_V1(sphereellipse_infunc);
PG_FUNCTION_INFO_V1(sphereellipse_incl);
PG_FUNCTION_INFO_V1(sphereellipse_rad1);
PG_FUNCTION_INFO_V1(sphereellipse_rad2);
PG_FUNCTION_INFO_V1(sphereellipse_center);
PG_FUNCTION_INFO_V1(sphereellipse_trans);
PG_FUNCTION_INFO_V1(sphereellipse_circle);
PG_FUNCTION_INFO_V1(spherepoint_ellipse);
PG_FUNCTION_INFO_V1(spherecircle_ellipse);
PG_FUNCTION_INFO_V1(sphereellipse_equal);
PG_FUNCTION_INFO_V1(sphereellipse_equal_neg);
PG_FUNCTION_INFO_V1(sphereellipse_cont_point);
PG_FUNCTION_INFO_V1(sphereellipse_cont_point_neg);
PG_FUNCTION_INFO_V1(sphereellipse_cont_point_com);
PG_FUNCTION_INFO_V1(sphereellipse_cont_point_com_neg);
PG_FUNCTION_INFO_V1(sphereellipse_cont_line);
PG_FUNCTION_INFO_V1(sphereellipse_cont_line_neg);
PG_FUNCTION_INFO_V1(sphereellipse_cont_line_com);
PG_FUNCTION_INFO_V1(sphereellipse_cont_line_com_neg);
PG_FUNCTION_INFO_V1(sphereellipse_overlap_line);
PG_FUNCTION_INFO_V1(sphereellipse_overlap_line_neg);
PG_FUNCTION_INFO_V1(sphereellipse_overlap_line_com);
PG_FUNCTION_INFO_V1(sphereellipse_overlap_line_com_neg);
PG_FUNCTION_INFO_V1(sphereellipse_cont_circle);
PG_FUNCTION_INFO_V1(sphereellipse_cont_circle_neg);
PG_FUNCTION_INFO_V1(sphereellipse_cont_circle_com);
PG_FUNCTION_INFO_V1(sphereellipse_cont_circle_com_neg);
PG_FUNCTION_INFO_V1(spherecircle_cont_ellipse);
PG_FUNCTION_INFO_V1(spherecircle_cont_ellipse_neg);
PG_FUNCTION_INFO_V1(spherecircle_cont_ellipse_com);
PG_FUNCTION_INFO_V1(spherecircle_cont_ellipse_com_neg);
PG_FUNCTION_INFO_V1(sphereellipse_overlap_circle);
PG_FUNCTION_INFO_V1(sphereellipse_overlap_circle_neg);
PG_FUNCTION_INFO_V1(sphereellipse_overlap_circle_com);
PG_FUNCTION_INFO_V1(sphereellipse_overlap_circle_com_neg);
PG_FUNCTION_INFO_V1(sphereellipse_cont_ellipse);
PG_FUNCTION_INFO_V1(sphereellipse_cont_ellipse_neg);
PG_FUNCTION_INFO_V1(sphereellipse_cont_ellipse_com);
PG_FUNCTION_INFO_V1(sphereellipse_cont_ellipse_com_neg);
PG_FUNCTION_INFO_V1(sphereellipse_overlap_ellipse);
PG_FUNCTION_INFO_V1(sphereellipse_overlap_ellipse_neg);
PG_FUNCTION_INFO_V1(spheretrans_ellipse);
PG_FUNCTION_INFO_V1(spheretrans_ellipse_inv);


/*
 * This function returns the arccos of a value. If variable 'a' is outside
 * the range (-1.00 .. 1.00), the function returns corresponding PI/2 or 3*PI/2.
 */
static float8
my_acos(float8 a)
{
	if (a > 1.0)
		a = 1.0;
	if (a < -1.0)
		a = -1.0;
	return acos(a);
}

/*
 *  Checks the parameter of an ellipse.
 */
static void
sellipse_check(SELLIPSE *e)
{
	SPoint sp;

	sp.lng = e->phi;
	spoint_check(&sp);
	if (PI - sp.lng >= PI_EPS)
		e->phi = sp.lng;
	else
		e->phi = sp.lng - PI;
	sp.lng = 0.0;
	sp.lat = e->theta;
	spoint_check(&sp);
	e->theta = sp.lat;
	sp.lng = e->psi;
	sp.lat = 0.0;
	spoint_check(&sp);
	e->psi = sp.lng;
}

/*
 * Returns the boundary circle of an ellipse.
 */
static void
sellipse_circle(SCIRCLE *sc, const SELLIPSE *e)
{
	SPoint sp;

	sellipse_center(&sp, e);
	memcpy((void *) &sc->center, (void *) &sp, sizeof(SPoint));
	sc->radius = e->rad[0];
}

/*
 * Returns an ellipse from axes, center and inclination. The largest axis
 * length is chosen for large axis.
 */
static SELLIPSE *
sellipse_in(float8 r1, float8 r2, const SPoint *c, float8 inc)
{
	SELLIPSE   *e = (SELLIPSE *) palloc(sizeof(SELLIPSE));

	e->rad[0] = Max(r1, r2);
	e->rad[1] = Min(r1, r2);
	e->phi = inc;
	e->theta = -c->lat;
	e->psi = c->lng;
	if (FPge(e->rad[0], PIH) || FPge(e->rad[1], PIH))
	{
		pfree(e);
		e = NULL;
		elog(ERROR, "sphereellipse_in: radius must be less than 90 degrees");
	}
	else
	{
		sellipse_check(e);
	}
	return e;
}

/*
 * Returns the radius of an ellipse depending on position angle.
 *
 * rada - major axis length
 * radb - minor axis length
 * ang  - position angle in radians
 */
static float8
sellipse_dist(float8 rada, float8 radb, float8 ang)
{
	float8 e;

	e = (1 - Sqr(sin(radb)) / Sqr(sin(rada)));
	return (asin(sin(radb) / sqrt(1 - e * Sqr(cos(ang)))));
}

/*
 * Returns distance between an ellipse and a point.
 */
static float8
sellipse_point_dist(const SELLIPSE *se, const SPoint *sp)
{
	SEuler e;
	SPoint p;
	float8 dist, rad, ang;

	sellipse_trans(&e, se);
	spheretrans_inv(&e);
	euler_spoint_trans(&p, sp, &e);
	dist = my_acos(cos(p.lng) * cos(p.lat));
	if (FPzero(dist))
	{
		return -1.0;
	}
	else
	{
		if (FPeq(dist, PIH))
		{
			ang = p.lat;
		}
		else
		{
			ang = my_acos(tan(p.lng) / tan(dist));
		}
		rad = sellipse_dist(se->rad[0], se->rad[1], ang);
		if (FPzero((dist - rad)))
		{
			return 0.0;
		}
		else if (FPgt(dist, rad))
		{
			return (dist - rad);
		}
		else
		{
			return -1.0;
		}
	}
	return -1.0;
}

/*
 * Performs an Euler transformation of an ellipse.
 */
static void
euler_sellipse_trans(SELLIPSE *out, const SELLIPSE *in, const SEuler *se)
{
	SEuler	et;
	SLine	sl[2];
	SPoint	p[2];

	sellipse_trans(&et, in);
	sl[0].length = PIH;
	sl[0].phi = sl[0].theta = sl[0].psi = 0.0;
	euler_sline_trans(&sl[1], &sl[0], &et);
	euler_sline_trans(&sl[0], &sl[1], se);
	sline_begin(&p[0], &sl[0]);
	sline_end(&p[1], &sl[0]);
	et.psi = p[0].lng;
	et.theta = -p[0].lat;
	et.phi = 0.0;
	et.phi_a = EULER_AXIS_X;
	et.theta_a = EULER_AXIS_Y;
	et.psi_a = EULER_AXIS_Z;
	out->psi = et.psi;
	out->theta = et.theta;
	spheretrans_inv(&et);
	euler_sline_trans(&sl[1], &sl[0], &et);
	sphereline_to_euler(&et, &sl[1]);
	out->phi = et.theta;
	out->rad[0] = in->rad[0];
	out->rad[1] = in->rad[1];
}


/*
 * Returns the relationship between two ellipses as PGS_ELLIPSE_ELLIPSE_REL
 * int8 value.
 */
static int8
sellipse_ellipse_pos(const SELLIPSE *se1, const SELLIPSE *se2)
{
	int8 r;

	/* equality */
	if (sellipse_eq(se1, se2))
	{
		return PGS_ELLIPSE_CONT;
	}

	/* se2 is circle or point */
	if (FPeq(se2->rad[0], se2->rad[1]))
	{

		SCIRCLE c;

		sellipse_circle(&c, se2);
		r = sellipse_circle_pos(se1, &c);

		switch (r)
		{
			case PGS_ELLIPSE_CIRCLE_AVOID:
				return PGS_ELLIPSE_AVOID;
			case PGS_CIRCLE_CONT_ELLIPSE:
				return PGS_ELLIPSE_OVER;
			case PGS_ELLIPSE_CONT_CIRCLE:
				return PGS_ELLIPSE_CONT;
			case PGS_ELLIPSE_CIRCLE_OVER:
				return PGS_ELLIPSE_OVER;
			default:
				return PGS_ELLIPSE_AVOID;
		}

	}

	/* se1 is circle or point */
	if (FPeq(se1->rad[0], se1->rad[1]))
	{

		SCIRCLE c;

		sellipse_circle(&c, se1);
		r = sellipse_circle_pos(se2, &c);
		switch (r)
		{
			case PGS_ELLIPSE_CIRCLE_AVOID:
				return PGS_ELLIPSE_AVOID;
			case PGS_CIRCLE_CONT_ELLIPSE:
				return PGS_ELLIPSE_CONT;
			case PGS_ELLIPSE_CONT_CIRCLE:
				return PGS_ELLIPSE_OVER;
			case PGS_ELLIPSE_CIRCLE_OVER:
				return PGS_ELLIPSE_OVER;
			default:
				return PGS_ELLIPSE_AVOID;
		}

	}

	/* se2 is line */
	if (FPzero(se2->rad[1]))
	{
		SLine	l;

		sellipse_line(&l, se2);
		r = sellipse_line_pos(se1, &l);
		switch (r)
		{
			case PGS_ELLIPSE_LINE_AVOID:
				return PGS_ELLIPSE_AVOID;
			case PGS_ELLIPSE_CONT_LINE:
				return PGS_ELLIPSE_CONT;
			case PGS_ELLIPSE_LINE_OVER:
				return PGS_ELLIPSE_OVER;
			default:
				return PGS_ELLIPSE_AVOID;
		}

	}

	/* se1 is line */
	if (FPzero(se1->rad[1]))
	{
		SLine	l;

		sellipse_line(&l, se1);
		r = sellipse_line_pos(se2, &l);
		switch (r)
		{
			case PGS_ELLIPSE_LINE_AVOID:
				return PGS_ELLIPSE_AVOID;
			case PGS_ELLIPSE_CONT_LINE:
				return PGS_ELLIPSE_OVER;
			case PGS_ELLIPSE_LINE_OVER:
				return PGS_ELLIPSE_OVER;
			default:
				return PGS_ELLIPSE_AVOID;
		}

	}

	/* now we have two real ellipses */
	do
	{

		SPoint	p1, p2;
		float8	dist;

		/* check inner and outer circles */
		sellipse_center(&p1, se1);
		sellipse_center(&p2, se2);
		dist = spoint_dist(&p1, &p2);
		if (FPle((se1->rad[0] + se2->rad[0]), dist))
		{
			return PGS_ELLIPSE_AVOID;
		}
		else if (FPle((dist + se1->rad[0]), se2->rad[1]))
		{
			return PGS_ELLIPSE_OVER;
		}
		else if (FPle((dist + se2->rad[0]), se1->rad[1]))
		{
			return PGS_ELLIPSE_CONT;
		}
		else
		{
			SEuler		eul;
			SELLIPSE		etmp, e;
			SPoint		sp[3];
			int			i;
			float8		diff[3];
			float8		elng;
			const int	maxcntr = 100000;
			int			cntr;

			/* transform se1 to north pol */
			sellipse_trans(&eul, se1);
			spheretrans_inv(&eul);
			euler_sellipse_trans(&etmp, se2, &eul);

			eul.phi = PIH;
			eul.theta = PIH;
			eul.psi = 0;
			eul.phi_a = EULER_AXIS_Z;
			eul.theta_a = EULER_AXIS_X;
			eul.psi_a = EULER_AXIS_Z;
			euler_sellipse_trans(&e, &etmp, &eul);

			etmp.rad[0] = se1->rad[0];
			etmp.rad[1] = se1->rad[1];
			etmp.phi = 0.0;
			etmp.theta = -PIH;
			etmp.psi = PIH;


			/* search for minimum distance */
			sp[0].lat = sp[2].lat = PIH - se1->rad[0];
			sellipse_center(&sp[1], &e);

			if (FPeq(sp[1].lat, PIH))
			{
				elng = PIH;
			}
			else
			{
				elng = sp[1].lng;
			}
			if (sin(elng) < 0)
			{
				sp[0].lng = PI;
				sp[1].lng = 3 * PIH;
				sp[2].lng = PID;
			}
			else
			{
				sp[0].lng = 0.0;
				sp[1].lng = PIH;
				sp[2].lng = PI;
			}
			sp[1].lat = PIH - se1->rad[1];

			cntr = 0;
			do
			{
				for (i = 0; i < 3; i++)
				{
					diff[i] = sellipse_point_dist(&e, &sp[i]);

					if (diff[i] < 0.0)
					{
						return PGS_ELLIPSE_OVER;
					}

				}
				if (diff[0] <= diff[1] && diff[1] <= diff[2])
				{
					memcpy((void *) &sp[2], (void *) &sp[1], sizeof(SPoint));
				}
				else if (diff[0] <= diff[2] && diff[2] <= diff[1])
				{
					if (Abs(sp[0].lng - elng) < Abs(sp[2].lng - elng))
					{
						memcpy((void *) &sp[2], (void *) &sp[1], sizeof(SPoint));
					}
					else
					{
						memcpy((void *) &sp[0], (void *) &sp[1], sizeof(SPoint));
					}
				}
				else if (diff[1] <= diff[0] && diff[0] <= diff[2])
				{
					memcpy((void *) &sp[2], (void *) &sp[0], sizeof(SPoint));
					memcpy((void *) &sp[0], (void *) &sp[1], sizeof(SPoint));
				}
				else if (diff[1] <= diff[2] && diff[2] <= diff[0])
				{
					memcpy((void *) &sp[0], (void *) &sp[1], sizeof(SPoint));
				}
				else if (diff[2] <= diff[0] && diff[0] <= diff[1])
				{
					if (Abs(sp[0].lng - elng) < Abs(sp[2].lng - elng))
					{
						memcpy((void *) &sp[2], (void *) &sp[1], sizeof(SPoint));
					}
					else
					{
						memcpy((void *) &sp[0], (void *) &sp[1], sizeof(SPoint));
					}
				}
				else if (diff[2] <= diff[1] && diff[1] <= diff[0])
				{
					memcpy((void *) &sp[0], (void *) &sp[2], sizeof(SPoint));
					memcpy((void *) &sp[2], (void *) &sp[1], sizeof(SPoint));
				}
				if (sp[2].lng < sp[0].lng)
				{
					/* switch here too */
					memcpy((void *) &sp[1], (void *) &sp[0], sizeof(SPoint));
					memcpy((void *) &sp[0], (void *) &sp[2], sizeof(SPoint));
					memcpy((void *) &sp[2], (void *) &sp[1], sizeof(SPoint));
				}
				sp[1].lng = (sp[0].lng + sp[2].lng) / 2.0;
				sp[1].lat = PIH - sellipse_dist(etmp.rad[0], etmp.rad[1], sp[1].lng);
				cntr++;
			} while (cntr < maxcntr && ((sp[2].lng - sp[0].lng) > FLT_EPSILON));
			if (cntr >= maxcntr)
			{
				elog(ERROR, "Bug found in pg_sphere function 'sellipse_ellipse_pos' ! \n Please report it to pg_sphere team.");
			}

			sellipse_center(&sp[1], &e);
			if (sellipse_cont_point(&etmp, &sp[1]))
			{
				return PGS_ELLIPSE_CONT;
			}
			else
			{
				return PGS_ELLIPSE_AVOID;
			}
		}
	} while (0);

	return PGS_ELLIPSE_AVOID;
}

void
sellipse_trans(SEuler *se, const SELLIPSE *e)
{
	se->psi = e->psi;
	se->theta = e->theta;
	se->phi = e->phi;
	se->phi_a = EULER_AXIS_X;
	se->theta_a = EULER_AXIS_Y;
	se->psi_a = EULER_AXIS_Z;
}

/* Returns center of ellipse */
void
sellipse_center(SPoint *sp, const SELLIPSE *e)
{
	sp->lng = e->psi;
	sp->lat = -e->theta;
}

bool
sellipse_line(SLine *sl, const SELLIPSE *e)
{
	if (!FPzero(e->rad[0]))
	{
		SEuler se;
		SLine slt;
		SPoint p[2];

		p[0].lat = p[1].lat = 0.0;
		p[0].lng = -e->rad[0];
		p[1].lng = e->rad[0];
		sline_from_points(&slt, &p[0], &p[1]);
		sellipse_trans(&se, e);
		euler_sline_trans(sl, &slt, &se);
		return true;
	}
	else
	{
		return false;
	}
}

bool
sellipse_eq(const SELLIPSE *e1, const SELLIPSE *e2)
{
	if (FPne(e1->rad[0], e2->rad[0]) || FPne(e1->rad[1], e2->rad[1]))
	{
		return false;
	}
	else if (FPzero(e1->rad[0]))
	{
		/* point */
		SPoint p[2];

		sellipse_center(&p[0], e1);
		sellipse_center(&p[1], e2);
		return spoint_eq(&p[0], &p[1]);
	}
	else if (FPeq(e1->rad[0], e1->rad[1]))
	{
		/* circle */
		SCIRCLE c[2];

		sellipse_circle(&c[0], e1);
		sellipse_circle(&c[1], e2);
		return scircle_eq(&c[0], &c[1]);
	}
	else
	{
		SEuler se[2];

		sellipse_trans(&se[0], e1);
		sellipse_trans(&se[1], e2);
		return strans_eq(&se[0], &se[1]);
	}
	return false;
}

bool
sellipse_cont_point(const SELLIPSE *se, const SPoint *sp)
{
	SPoint		c;
	float8		dist;

	sellipse_center(&c, se);
	dist = spoint_dist(sp, &c);

	if (FPgt(dist, se->rad[0]))
	{
		return false;
	}
	if (FPle(dist, se->rad[1]))
	{
		return true;
	}
	if (FPzero(se->rad[1]))
	{
		SLine		l;

		sellipse_line(&l, se);
		return spoint_at_sline(sp, &l);
	}
	else
	{
		SEuler		et;
		SPoint		p;
		float8		a,
					e;

		sellipse_trans(&et, se);
		spheretrans_inv(&et);
		euler_spoint_trans(&p, sp, &et);
		if (FPeq(dist, PIH))
		{
			e = p.lat;
		}
		else
		{
			e = my_acos(tan(p.lng) / tan(dist));
		}
		a = sellipse_dist(se->rad[0], se->rad[1], e);
		if (FPge(a, dist))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}


int8
sellipse_line_pos(const SELLIPSE *se, const SLine *sl)
{
	/* line is point */
	if (FPzero(sl->length))
	{
		SPoint		p;

		sline_begin(&p, sl);
		if (sellipse_cont_point(se, &p))
		{
			return PGS_ELLIPSE_CONT_LINE;
		}
		else
		{
			return PGS_ELLIPSE_LINE_AVOID;
		}
	}

	/* ellipse is point */
	if (FPzero(se->rad[0]))
	{
		SPoint		p;

		sellipse_center(&p, se);
		if (spoint_at_sline(&p, sl))
		{
			return PGS_ELLIPSE_LINE_OVER;
		}
		else
		{
			return PGS_ELLIPSE_LINE_AVOID;
		}
	}

	/* ellipse is line */
	if (FPzero(se->rad[1]))
	{
		SLine l;
		int8 res;

		sellipse_line(&l, se);
		res = sline_sline_pos(&l, sl);
		if (res == PGS_LINE_AVOID)
		{
			return PGS_ELLIPSE_LINE_AVOID;
		}
		else if (res == PGS_LINE_CONT_LINE || res == PGS_LINE_EQUAL)
		{
			return PGS_ELLIPSE_CONT_LINE;
		}
		else
		{
			return PGS_ELLIPSE_LINE_OVER;
		}
	}

	/* ellipse is circle */
	if (FPeq(se->rad[0], se->rad[1]))
	{
		SCIRCLE		c;
		int8		res;

		sellipse_circle(&c, se);
		res = sphereline_circle_pos(sl, &c);
		if (res == PGS_CIRCLE_LINE_AVOID)
		{
			return PGS_ELLIPSE_LINE_AVOID;
		}
		else if (res == PGS_CIRCLE_CONT_LINE)
		{
			return PGS_ELLIPSE_CONT_LINE;
		}
		else
		{
			return PGS_ELLIPSE_LINE_OVER;
		}
	}

	/* begin or end of line inside ellipse */
	{
		bool		bb,
					be;
		SPoint		p;

		sline_begin(&p, sl);
		bb = sellipse_cont_point(se, &p);
		sline_end(&p, sl);
		be = sellipse_cont_point(se, &p);
		if (bb || be)
		{
			if (bb && be)
			{
				return PGS_ELLIPSE_CONT_LINE;
			}
			if (!(bb && be))
			{
				return PGS_ELLIPSE_LINE_OVER;
			}
		}

	}

	/* compare with bounding circle */
	{

		SCIRCLE		c;
		int8		res;

		sellipse_circle(&c, se);
		res = sphereline_circle_pos(sl, &c);
		if (res == PGS_CIRCLE_LINE_AVOID)
		{
			return PGS_ELLIPSE_LINE_AVOID;
		}
	}

	/* compare in detail */
	{
		SEuler		e;
		SPoint		c;
		SELLIPSE	set;

		sphereline_to_euler(&e, sl);
		spheretrans_inv(&e);
		euler_sellipse_trans(&set, se, &e);
		sellipse_center(&c, &set);

		if (sin(c.lng + se->rad[0]) < 0.0)
		{
			return PGS_ELLIPSE_LINE_AVOID;
		}
		if (sin(c.lng - se->rad[0] - sl->length) < 0.0)
		{
			return PGS_ELLIPSE_LINE_AVOID;
		}
		if ((c.lat >= 0) && (se->rad[0] - c.lat) > 0.0)
		{
			return PGS_ELLIPSE_LINE_AVOID;
		}
		if ((c.lat < 0) && (se->rad[0] + c.lat) > 0.0)
		{
			return PGS_ELLIPSE_LINE_AVOID;
		}
		else
		{

			SPoint		cn;
			float8		eps,
						dist,
						sinr;
			float8		d[3];
			int			i;
			SPoint		lp[3];
			SPoint		lpt[3];

			sellipse_trans(&e, &set);
			spheretrans_inv(&e);
			lp[0].lng = 0.0;
			lp[1].lng = sl->length / 2;
			lp[2].lng = sl->length;
			lp[0].lat = lp[1].lat = lp[2].lat = 0.0;
			cn.lng = 0.0;
			cn.lat = 0.0;
			eps = (1 - Sqr(sin(se->rad[1])) / Sqr(sin(se->rad[0])));
			sinr = sin(se->rad[1]);

			while (FPgt(lp[2].lng, lp[0].lng))
			{

				for (i = 0; i < 3; i++)
				{
					euler_spoint_trans(&lpt[i], &lp[i], &e);
					dist = spoint_dist(&lpt[i], &cn);
					if (FPeq(dist, PIH))
					{
						d[i] = lpt[i].lat;
					}
					else
					{
						d[i] = tan(lpt[i].lng) / tan(dist);
					}
					d[i] = asin(sinr / sqrt(1 - eps * Sqr(d[i])));
					if (FPge(d[i], dist))
					{
						return PGS_ELLIPSE_LINE_OVER;
					}
				}
				/* get the best values */
				for (i = 0; i < 3; i++)
				{
					if (d[i] <= d[(i + 1) % 3] && d[i] <= d[(i + 2) % 3])
					{
						lpt[0].lng = lp[i].lng;
						if (d[(i + 1) % 3] <= d[(i + 2) % 3])
						{
							lpt[1].lng = lp[(i + 1) % 3].lng;
						}
						else
						{
							lpt[1].lng = lp[(i + 2) % 3].lng;
						}
						if (lpt[0].lng > lpt[1].lng)
						{
							dist = lpt[0].lng;
							lpt[0].lng = lpt[1].lng;
							lpt[1].lng = dist;
						}
						lp[0].lng = lpt[0].lng;
						lp[1].lng = (lpt[0].lng + lpt[1].lng) / 2;
						lp[2].lng = lpt[1].lng;
					}
				}

			}

		}

	}
	return PGS_ELLIPSE_LINE_AVOID;
}


int8
sellipse_circle_pos(const SELLIPSE *se, const SCIRCLE *sc)
{
	/* circle is point */
	if (FPzero(sc->radius))
	{
		if (sellipse_cont_point(se, &sc->center))
		{
			return PGS_ELLIPSE_CONT_CIRCLE;
		}
		else
		{
			return PGS_ELLIPSE_CIRCLE_AVOID;
		}
	}

	/* ellipse is circle */
	if (FPeq(se->rad[0], se->rad[1]))
	{
		SCIRCLE	tc;
		float8	dist;

		sellipse_circle(&tc, se);
		if (scircle_eq(&tc, sc))
		{
			return PGS_ELLIPSE_CIRCLE_EQUAL;
		}
		dist = spoint_dist(&tc.center, &sc->center);
		if (FPle((dist + sc->radius), tc.radius))
		{
			return PGS_ELLIPSE_CONT_CIRCLE;
		}
		if (FPle((dist + tc.radius), sc->radius))
		{
			return PGS_CIRCLE_CONT_ELLIPSE;
		}
		if (FPgt((sc->radius + tc.radius), dist))
		{
			return PGS_ELLIPSE_CIRCLE_OVER;
		}
		else
		{
			return PGS_ELLIPSE_CIRCLE_AVOID;
		}
	}

	/* ellipse is line */
	if (FPzero(se->rad[1]))
	{
		SLine	l;
		int8	res;

		sellipse_line(&l, se);
		res = sphereline_circle_pos(&l, sc);
		if (res == PGS_CIRCLE_LINE_AVOID)
		{
			return PGS_ELLIPSE_CIRCLE_AVOID;
		}
		else if (res == PGS_CIRCLE_CONT_LINE)
		{
			return PGS_CIRCLE_CONT_ELLIPSE;
		}
		else
		{
			return PGS_ELLIPSE_CIRCLE_OVER;
		}

	}
	else
	{
		/*
		 * now ellipse is a real ellipse and
		 * circle is a real circle
		 */

		float8	dist;
		SPoint	c;

		sellipse_center(&c, se);
		dist = spoint_dist(&sc->center, &c);

		if (FPzero(dist))
		{
			if (FPle(sc->radius, se->rad[1]))
			{
				return PGS_ELLIPSE_CONT_CIRCLE;
			}
			else if (FPge(sc->radius, se->rad[0]))
			{
				return PGS_CIRCLE_CONT_ELLIPSE;
			}
			else
			{
				return PGS_ELLIPSE_CIRCLE_OVER;
			}

		}
		else
		{

			SEuler	et;
			SPoint	p;
			float8	a, e;

			sellipse_trans(&et, se);
			spheretrans_inv(&et);
			euler_spoint_trans(&p, &sc->center, &et);
			if (FPeq(dist, PIH))
			{
				e = p.lat;
			}
			else
			{
				e = my_acos(tan(p.lng) / tan(dist));
			}
			a = sellipse_dist(se->rad[0], se->rad[1], e);
			if (FPle((dist + sc->radius), a))
			{
				return PGS_ELLIPSE_CONT_CIRCLE;
			}
			else if (FPle((dist + a), sc->radius))
			{
				return PGS_CIRCLE_CONT_ELLIPSE;
			}
			else if (FPgt((a + sc->radius), dist))
			{
				return PGS_ELLIPSE_CIRCLE_OVER;
			}
			else
			{
				return PGS_ELLIPSE_CIRCLE_AVOID;
			}
		}
	}
	return PGS_ELLIPSE_CIRCLE_AVOID;
}


Datum
sphereellipse_in(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = NULL;
	char	   *s = PG_GETARG_CSTRING(0);
	SPoint		p;
	double		r1,
				r2,
				inc;

	void		sphere_yyparse(void);

	init_buffer(s);
	sphere_yyparse();
	if (get_ellipse(&p.lng, &p.lat, &r1, &r2, &inc))
	{
		e = sellipse_in(r1, r2, &p, inc);
		reset_buffer();
	}
	PG_RETURN_POINTER(e);
}

Datum
sphereellipse_infunc(PG_FUNCTION_ARGS)
{
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(0);
	float8		r1 = PG_GETARG_FLOAT8(1);
	float8		r2 = PG_GETARG_FLOAT8(2);
	float8		inc = PG_GETARG_FLOAT8(3);
	SELLIPSE   *e = sellipse_in(r1, r2, p, inc);

	PG_RETURN_POINTER(e);
}

Datum
sphereellipse_incl(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);

	PG_RETURN_FLOAT8(e->phi);
}

Datum
sphereellipse_rad1(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);

	PG_RETURN_FLOAT8(e->rad[0]);
}

Datum
sphereellipse_rad2(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);

	PG_RETURN_FLOAT8(e->rad[1]);
}

Datum
sphereellipse_center(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);
	SPoint	   *p = (SPoint *) palloc(sizeof(SPoint));

	sellipse_center(p, e);
	PG_RETURN_POINTER(p);
}

Datum
sphereellipse_trans(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);
	SEuler	   *t = (SEuler *) palloc(sizeof(SEuler));

	sellipse_trans(t, e);
	PG_RETURN_POINTER(t);
}

Datum
sphereellipse_circle(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);
	SCIRCLE    *c = (SCIRCLE *) palloc(sizeof(SCIRCLE));

	sellipse_circle(c, e);
	PG_RETURN_POINTER(c);
}

Datum
spherepoint_ellipse(PG_FUNCTION_ARGS)
{
	SPoint	   *c = (SPoint *) PG_GETARG_POINTER(0);
	SELLIPSE   *e = sellipse_in(0.0, 0.0, c, 0.0);

	if (e)
	{
		PG_RETURN_POINTER(e);
	}
	PG_RETURN_NULL();
}

Datum
spherecircle_ellipse(PG_FUNCTION_ARGS)
{
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(0);
	SELLIPSE   *e = sellipse_in(c->radius, c->radius, &c->center, 0.0);

	if (e)
	{
		PG_RETURN_POINTER(e);
	}
	PG_RETURN_NULL();
}

Datum
sphereellipse_equal(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e1 = (SELLIPSE *) PG_GETARG_POINTER(0);
	SELLIPSE   *e2 = (SELLIPSE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(sellipse_eq(e1, e2));
}

Datum
sphereellipse_equal_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e1 = (SELLIPSE *) PG_GETARG_POINTER(0);
	SELLIPSE   *e2 = (SELLIPSE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(!sellipse_eq(e1, e2));
}

Datum
sphereellipse_cont_point(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(sellipse_cont_point(e, p));
}

Datum
sphereellipse_cont_point_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(!sellipse_cont_point(e, p));
}

Datum
sphereellipse_cont_point_com(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(1);
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(sellipse_cont_point(e, p));
}

Datum
sphereellipse_cont_point_com_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(1);
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(!sellipse_cont_point(e, p));
}

Datum
sphereellipse_cont_line(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);
	SLine	   *l = (SLine *) PG_GETARG_POINTER(1);
	int8		b = sellipse_line_pos(e, l);

	PG_RETURN_BOOL(b == PGS_ELLIPSE_CONT_LINE);
}

Datum
sphereellipse_cont_line_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);
	SLine	   *l = (SLine *) PG_GETARG_POINTER(1);
	int8		b = sellipse_line_pos(e, l);

	PG_RETURN_BOOL(b != PGS_ELLIPSE_CONT_LINE);
}

Datum
sphereellipse_cont_line_com(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(1);
	SLine	   *l = (SLine *) PG_GETARG_POINTER(0);
	int8		b = sellipse_line_pos(e, l);

	PG_RETURN_BOOL(b == PGS_ELLIPSE_CONT_LINE);
}

Datum
sphereellipse_cont_line_com_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(1);
	SLine	   *l = (SLine *) PG_GETARG_POINTER(0);
	int8		b = sellipse_line_pos(e, l);

	PG_RETURN_BOOL(b != PGS_ELLIPSE_CONT_LINE);
}

Datum
sphereellipse_overlap_line(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);
	SLine	   *l = (SLine *) PG_GETARG_POINTER(1);
	int8		b = sellipse_line_pos(e, l);

	PG_RETURN_BOOL(b > PGS_ELLIPSE_LINE_AVOID);
}

Datum
sphereellipse_overlap_line_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);
	SLine	   *l = (SLine *) PG_GETARG_POINTER(1);
	int8		b = sellipse_line_pos(e, l);

	PG_RETURN_BOOL(b == PGS_ELLIPSE_LINE_AVOID);
}

Datum
sphereellipse_overlap_line_com(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(1);
	SLine	   *l = (SLine *) PG_GETARG_POINTER(0);
	int8		b = sellipse_line_pos(e, l);

	PG_RETURN_BOOL(b > PGS_ELLIPSE_LINE_AVOID);
}

Datum
sphereellipse_overlap_line_com_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(1);
	SLine	   *l = (SLine *) PG_GETARG_POINTER(0);
	int8		b = sellipse_line_pos(e, l);

	PG_RETURN_BOOL(b == PGS_ELLIPSE_LINE_AVOID);
}


Datum
sphereellipse_cont_circle(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(1);
	int			pos = sellipse_circle_pos(e, c);

	PG_RETURN_BOOL(pos == PGS_ELLIPSE_CONT_CIRCLE || pos == PGS_ELLIPSE_CIRCLE_EQUAL);
}

Datum
sphereellipse_cont_circle_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(1);
	int			pos = sellipse_circle_pos(e, c);

	PG_RETURN_BOOL(pos != PGS_ELLIPSE_CONT_CIRCLE && pos != PGS_ELLIPSE_CIRCLE_EQUAL);
}

Datum
sphereellipse_cont_circle_com(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(1);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(0);
	int			pos = sellipse_circle_pos(e, c);

	PG_RETURN_BOOL(pos == PGS_ELLIPSE_CONT_CIRCLE || pos == PGS_ELLIPSE_CIRCLE_EQUAL);
}

Datum
sphereellipse_cont_circle_com_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(1);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(0);
	int			pos = sellipse_circle_pos(e, c);

	PG_RETURN_BOOL(pos != PGS_ELLIPSE_CONT_CIRCLE && pos != PGS_ELLIPSE_CIRCLE_EQUAL);
}

Datum
spherecircle_cont_ellipse(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(1);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(0);
	int			pos = sellipse_circle_pos(e, c);

	PG_RETURN_BOOL(pos == PGS_CIRCLE_CONT_ELLIPSE || pos == PGS_ELLIPSE_CIRCLE_EQUAL);
}

Datum
spherecircle_cont_ellipse_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(1);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(0);
	int			pos = sellipse_circle_pos(e, c);

	PG_RETURN_BOOL(pos != PGS_CIRCLE_CONT_ELLIPSE && pos != PGS_ELLIPSE_CIRCLE_EQUAL);
}

Datum
spherecircle_cont_ellipse_com(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(1);
	int			pos = sellipse_circle_pos(e, c);

	PG_RETURN_BOOL(pos == PGS_CIRCLE_CONT_ELLIPSE || pos == PGS_ELLIPSE_CIRCLE_EQUAL);
}

Datum
spherecircle_cont_ellipse_com_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(1);
	int			pos = sellipse_circle_pos(e, c);

	PG_RETURN_BOOL(pos != PGS_CIRCLE_CONT_ELLIPSE && pos != PGS_ELLIPSE_CIRCLE_EQUAL);
}

Datum
sphereellipse_overlap_circle(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(sellipse_circle_pos(e, c) > PGS_ELLIPSE_CIRCLE_AVOID);
}

Datum
sphereellipse_overlap_circle_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(sellipse_circle_pos(e, c) == PGS_ELLIPSE_CIRCLE_AVOID);
}

Datum
sphereellipse_overlap_circle_com(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(1);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(sellipse_circle_pos(e, c) > PGS_ELLIPSE_CIRCLE_AVOID);
}

Datum
sphereellipse_overlap_circle_com_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(1);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(sellipse_circle_pos(e, c) == PGS_ELLIPSE_CIRCLE_AVOID);
}

Datum
sphereellipse_cont_ellipse(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e1 = (SELLIPSE *) PG_GETARG_POINTER(0);
	SELLIPSE   *e2 = (SELLIPSE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(sellipse_ellipse_pos(e1, e2) == PGS_ELLIPSE_CONT);
}

Datum
sphereellipse_cont_ellipse_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e1 = (SELLIPSE *) PG_GETARG_POINTER(0);
	SELLIPSE   *e2 = (SELLIPSE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(sellipse_ellipse_pos(e1, e2) != PGS_ELLIPSE_CONT);
}

Datum
sphereellipse_cont_ellipse_com(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e1 = (SELLIPSE *) PG_GETARG_POINTER(1);
	SELLIPSE   *e2 = (SELLIPSE *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(sellipse_ellipse_pos(e1, e2) == PGS_ELLIPSE_CONT);
}

Datum
sphereellipse_cont_ellipse_com_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e1 = (SELLIPSE *) PG_GETARG_POINTER(1);
	SELLIPSE   *e2 = (SELLIPSE *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(sellipse_ellipse_pos(e1, e2) != PGS_ELLIPSE_CONT);
}

Datum
sphereellipse_overlap_ellipse(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e1 = (SELLIPSE *) PG_GETARG_POINTER(0);
	SELLIPSE   *e2 = (SELLIPSE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(sellipse_ellipse_pos(e1, e2) > PGS_ELLIPSE_AVOID);
}

Datum
sphereellipse_overlap_ellipse_neg(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e1 = (SELLIPSE *) PG_GETARG_POINTER(0);
	SELLIPSE   *e2 = (SELLIPSE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(sellipse_ellipse_pos(e1, e2) == PGS_ELLIPSE_AVOID);
}

Datum
spheretrans_ellipse(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);
	SEuler	   *se = (SEuler *) PG_GETARG_POINTER(1);
	SELLIPSE   *out = (SELLIPSE *) palloc(sizeof(SELLIPSE));

	euler_sellipse_trans(out, e, se);
	sellipse_check(out);
	PG_RETURN_POINTER(out);
}

Datum
spheretrans_ellipse_inv(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);
	SEuler	   *se = (SEuler *) PG_GETARG_POINTER(1);
	SELLIPSE   *out = (SELLIPSE *) palloc(sizeof(SELLIPSE));
	SEuler		tmp;

	spheretrans_inverse(&tmp, se);
	euler_sellipse_trans(out, e, &tmp);
	sellipse_check(out);
	PG_RETURN_POINTER(out);
}
