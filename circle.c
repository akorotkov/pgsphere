#include "circle.h"

/* Circle functions */

PG_FUNCTION_INFO_V1(spherecircle_in);
PG_FUNCTION_INFO_V1(spherecircle_equal);
PG_FUNCTION_INFO_V1(spherecircle_equal_neg);
PG_FUNCTION_INFO_V1(spherecircle_distance);
PG_FUNCTION_INFO_V1(spherecircle_point_distance);
PG_FUNCTION_INFO_V1(spherecircle_point_distance_com);
PG_FUNCTION_INFO_V1(spherepoint_in_circle);
PG_FUNCTION_INFO_V1(spherepoint_in_circle_neg);
PG_FUNCTION_INFO_V1(spherepoint_in_circle_com);
PG_FUNCTION_INFO_V1(spherepoint_in_circle_com_neg);
PG_FUNCTION_INFO_V1(spherecircle_in_circle);
PG_FUNCTION_INFO_V1(spherecircle_in_circle_neg);
PG_FUNCTION_INFO_V1(spherecircle_in_circle_com);
PG_FUNCTION_INFO_V1(spherecircle_in_circle_com_neg);
PG_FUNCTION_INFO_V1(spherecircle_overlap);
PG_FUNCTION_INFO_V1(spherecircle_overlap_neg);
PG_FUNCTION_INFO_V1(spherecircle_center);
PG_FUNCTION_INFO_V1(spherecircle_radius);
PG_FUNCTION_INFO_V1(spherepoint_to_circle);
PG_FUNCTION_INFO_V1(spherecircle_by_center);
PG_FUNCTION_INFO_V1(spherecircle_area);
PG_FUNCTION_INFO_V1(spherecircle_circ);
PG_FUNCTION_INFO_V1(spheretrans_circle);
PG_FUNCTION_INFO_V1(spheretrans_circle_inverse);


bool
scircle_eq(const SCIRCLE *c1, const SCIRCLE *c2)
{
	return (spoint_eq(&c1->center, &c2->center) &&
				FPeq(c1->radius, c2->radius));
}

bool
spoint_in_circle(const SPoint *p, const SCIRCLE *c)
{
	float8 dist = spoint_dist(p, &c->center);

	if (FPle(dist, c->radius))
	{
		return true;
	}
	return false;
}

void
euler_scircle_trans(SCIRCLE *out, const SCIRCLE *in, const SEuler *se)
{
	euler_spoint_trans(&out->center, &in->center, se);
	out->radius = in->radius;
}

Datum
spherecircle_in(PG_FUNCTION_ARGS)
{
	SCIRCLE	   *c = (SCIRCLE *) palloc(sizeof(SCIRCLE));
	char	   *s = PG_GETARG_CSTRING(0);
	double		lng,
				lat,
				radius;

	init_buffer(s);
	sphere_yyparse();
	if (get_circle(&lng, &lat, &radius))
	{
		c->center.lng = lng;
		c->center.lat = lat;
		c->radius = radius;
		reset_buffer();

		/*
		 * It's important to allow circles with radius 90 degrees!
		 */
		if (FPgt(c->radius, PIH))
		{
			pfree(c);
			c = NULL;
			elog(ERROR, "spherecircle_in: radius must be not greater than 90 degrees");
		}
		else if (FPeq(c->radius, PIH))
		{
			/* set "exact" 90 degrees */
			c->radius = PIH;
		}
		spoint_check(&c->center);
	}
	else
	{
		reset_buffer();
		pfree(c);
		c = NULL;
		elog(ERROR, "spherecircle_in: parse error");
	}
	PG_RETURN_POINTER(c);
}

Datum
spherecircle_equal(PG_FUNCTION_ARGS)
{
	SCIRCLE	   *c1 = (SCIRCLE *) PG_GETARG_POINTER(0);
	SCIRCLE	   *c2 = (SCIRCLE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(scircle_eq(c1, c2));
}

Datum
spherecircle_equal_neg(PG_FUNCTION_ARGS)
{
	SCIRCLE	   *c1 = (SCIRCLE *) PG_GETARG_POINTER(0);
	SCIRCLE	   *c2 = (SCIRCLE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(!scircle_eq(c1, c2));
}

Datum
spherecircle_distance(PG_FUNCTION_ARGS)
{
	SCIRCLE	   *c1 = (SCIRCLE *) PG_GETARG_POINTER(0);
	SCIRCLE	   *c2 = (SCIRCLE *) PG_GETARG_POINTER(1);
	float8		dist = spoint_dist(&c1->center, &c2->center);

	dist -= (c1->radius + c2->radius);
	if (dist < 0.0)
	{
		dist = 0.0;
	}
	PG_RETURN_FLOAT8(dist);
}

Datum
spherecircle_point_distance(PG_FUNCTION_ARGS)
{
	SCIRCLE	   *c = (SCIRCLE *) PG_GETARG_POINTER(0);
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(1);
	float8		dist = spoint_dist(&c->center, p);

	dist = dist - c->radius;
	if (dist < 0.0)
	{
		dist = 0.0;
	}
	PG_RETURN_FLOAT8(dist);
}

Datum
spherecircle_point_distance_com(PG_FUNCTION_ARGS)
{
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(0);
	SCIRCLE	   *c = (SCIRCLE *) PG_GETARG_POINTER(1);
	float8		dist = spoint_dist(&c->center, p);

	dist = dist - c->radius;
	if (dist < 0.0)
	{
		dist = 0.0;
	}
	PG_RETURN_FLOAT8(dist);
}

Datum
spherepoint_in_circle(PG_FUNCTION_ARGS)
{
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(0);
	SCIRCLE	   *c = (SCIRCLE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(spoint_in_circle(p, c));
}

Datum
spherepoint_in_circle_neg(PG_FUNCTION_ARGS)
{
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(0);
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(!spoint_in_circle(p, c));
}

Datum
spherepoint_in_circle_com(PG_FUNCTION_ARGS)
{
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(1);
	SCIRCLE	   *c = (SCIRCLE *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(spoint_in_circle(p, c));
}

Datum
spherepoint_in_circle_com_neg(PG_FUNCTION_ARGS)
{
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(1);
	SCIRCLE	   *c = (SCIRCLE *) PG_GETARG_POINTER(0);

	PG_RETURN_BOOL(!spoint_in_circle(p, c));
}

Datum
spherecircle_in_circle(PG_FUNCTION_ARGS)
{
	SCIRCLE	   *c1 = (SCIRCLE *) PG_GETARG_POINTER(0);
	SCIRCLE	   *c2 = (SCIRCLE *) PG_GETARG_POINTER(1);
	float8		dist = spoint_dist(&c1->center, &c2->center);

	if (scircle_eq(c1, c2))
	{
		PG_RETURN_BOOL(true);
	}
	else if (FPle((dist + c1->radius), c2->radius))
	{
		PG_RETURN_BOOL(true);
	}
	else
	{
		PG_RETURN_BOOL(false);
	}
}

Datum
spherecircle_in_circle_neg(PG_FUNCTION_ARGS)
{
	SCIRCLE	   *c1 = (SCIRCLE *) PG_GETARG_POINTER(0);
	SCIRCLE	   *c2 = (SCIRCLE *) PG_GETARG_POINTER(1);
	float8		dist = spoint_dist(&c1->center, &c2->center);

	if (scircle_eq(c1, c2))
	{
		PG_RETURN_BOOL(false);
	}
	else if (FPgt((dist + c1->radius), c2->radius))
	{
		PG_RETURN_BOOL(true);
	}
	else
	{
		PG_RETURN_BOOL(false);
	}
}

Datum
spherecircle_in_circle_com(PG_FUNCTION_ARGS)
{
	SCIRCLE	   *c1 = (SCIRCLE *) PG_GETARG_POINTER(1);
	SCIRCLE	   *c2 = (SCIRCLE *) PG_GETARG_POINTER(0);
	float8		dist = spoint_dist(&c1->center, &c2->center);

	if (scircle_eq(c1, c2))
	{
		PG_RETURN_BOOL(true);
	}
	else if (FPle((dist + c1->radius), c2->radius))
	{
		PG_RETURN_BOOL(true);
	}
	else
	{
		PG_RETURN_BOOL(false);
	}
}

Datum
spherecircle_in_circle_com_neg(PG_FUNCTION_ARGS)
{
	SCIRCLE	   *c1 = (SCIRCLE *) PG_GETARG_POINTER(1);
	SCIRCLE	   *c2 = (SCIRCLE *) PG_GETARG_POINTER(0);
	float8		dist = spoint_dist(&c1->center, &c2->center);

	if (scircle_eq(c1, c2))
	{
		PG_RETURN_BOOL(false);
	}
	else if (FPgt((dist + c1->radius), c2->radius))
	{
		PG_RETURN_BOOL(true);
	}
	else
	{
		PG_RETURN_BOOL(false);
	}
}

Datum
spherecircle_overlap(PG_FUNCTION_ARGS)
{
	SCIRCLE	   *c1 = (SCIRCLE *) PG_GETARG_POINTER(0);
	SCIRCLE	   *c2 = (SCIRCLE *) PG_GETARG_POINTER(1);
	float8		dist = spoint_dist(&c1->center, &c2->center);

	if (scircle_eq(c1, c2))
	{
		PG_RETURN_BOOL(true);
	}
	else if (FPlt((c1->radius + c2->radius), dist))
	{
		PG_RETURN_BOOL(false);
	}
	else
	{
		PG_RETURN_BOOL(true);
	}
}

Datum
spherecircle_overlap_neg(PG_FUNCTION_ARGS)
{
	SCIRCLE	   *c1 = (SCIRCLE *) PG_GETARG_POINTER(0);
	SCIRCLE	   *c2 = (SCIRCLE *) PG_GETARG_POINTER(1);
	float8		dist = spoint_dist(&c1->center, &c2->center);

	if (scircle_eq(c1, c2))
	{
		PG_RETURN_BOOL(false);
	}
	else if (FPge((c1->radius + c2->radius), dist))
	{
		PG_RETURN_BOOL(false);
	}
	else
	{
		PG_RETURN_BOOL(true);
	}
}

Datum
spherecircle_center(PG_FUNCTION_ARGS)
{
	SCIRCLE	   *c = (SCIRCLE *) PG_GETARG_POINTER(0);
	SPoint	   *p = (SPoint *) palloc(sizeof(SPoint));

	memcpy((void *) p, (void *) &c->center, sizeof(SPoint));
	PG_RETURN_POINTER(p);
}

Datum
spherecircle_radius(PG_FUNCTION_ARGS)
{
	SCIRCLE	   *c = (SCIRCLE *) PG_GETARG_POINTER(0);

	PG_RETURN_FLOAT8(c->radius);
}

Datum
spherepoint_to_circle(PG_FUNCTION_ARGS)
{
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(0);
	SCIRCLE	   *c = (SCIRCLE *) palloc(sizeof(SCIRCLE));

	memcpy((void *) &c->center, (void *) p, sizeof(SPoint));
	c->radius = 0;
	PG_RETURN_POINTER(c);
}

Datum
spherecircle_by_center(PG_FUNCTION_ARGS)
{
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(0);
	float8		rad = PG_GETARG_FLOAT8(1);
	SCIRCLE	   *c;

	if (FPgt(rad, PIH) || FPlt(rad, 0.0))
	{
		elog(ERROR, "radius must be not greater than 90 degrees or less than 0");
		PG_RETURN_NULL();
	}
	c = (SCIRCLE *) palloc(sizeof(SCIRCLE));
	memcpy((void *) &c->center, (void *) p, sizeof(SPoint));
	c->radius = rad;
	PG_RETURN_POINTER(c);
}

Datum
spherecircle_area(PG_FUNCTION_ARGS)
{
	SCIRCLE	   *c = (SCIRCLE *) PG_GETARG_POINTER(0);

	PG_RETURN_FLOAT8(PID * (1 - cos(c->radius)));
}

Datum
spherecircle_circ(PG_FUNCTION_ARGS)
{
	SCIRCLE	   *c = (SCIRCLE *) PG_GETARG_POINTER(0);

	PG_RETURN_FLOAT8(PID * (sin(c->radius)));
}

Datum
spheretrans_circle(PG_FUNCTION_ARGS)
{
	SCIRCLE	   *sc = (SCIRCLE *) PG_GETARG_POINTER(0);
	SEuler	   *se = (SEuler *) PG_GETARG_POINTER(1);
	SCIRCLE	   *out = (SCIRCLE *) palloc(sizeof(SCIRCLE));

	euler_scircle_trans(out, sc, se);
	PG_RETURN_POINTER(out);
}

Datum
spheretrans_circle_inverse(PG_FUNCTION_ARGS)
{
	Datum		sc = PG_GETARG_DATUM(0);
	SEuler	   *se = (SEuler *) PG_GETARG_POINTER(1);
	SEuler		tmp;
	Datum		ret;

	spheretrans_inverse(&tmp, se);
	ret = DirectFunctionCall2(spheretrans_circle,
							  sc, PointerGetDatum(&tmp));
	PG_RETURN_DATUM(ret);
}
