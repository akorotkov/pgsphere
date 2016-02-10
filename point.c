#include "point.h"

/* This file contains definitions for spherical point functions. */

PG_FUNCTION_INFO_V1(spherepoint_in);
PG_FUNCTION_INFO_V1(spherepoint_from_long_lat);
PG_FUNCTION_INFO_V1(spherepoint_distance);
PG_FUNCTION_INFO_V1(spherepoint_long);
PG_FUNCTION_INFO_V1(spherepoint_lat);
PG_FUNCTION_INFO_V1(spherepoint_x);
PG_FUNCTION_INFO_V1(spherepoint_y);
PG_FUNCTION_INFO_V1(spherepoint_z);
PG_FUNCTION_INFO_V1(spherepoint_xyz);
PG_FUNCTION_INFO_V1(spherepoint_equal);

bool
spoint_eq(const SPoint *p1, const SPoint *p2)
{
	Vector3D	a,
				b;

	spoint_vector3d(&a, p1);
	spoint_vector3d(&b, p2);
	return (vector3d_eq(&a, &b));
}

void
spoint_check(SPoint *spoint)
{
	bool lat_is_neg = (spoint->lat < 0) ? true : false;

	if (spoint->lng < 0 || spoint->lng > PID)
		spoint->lng = spoint->lng - floor(spoint->lng / (PID)) * PID;
	if (spoint->lat < -PIH || spoint->lat > PIH)
		spoint->lat = spoint->lat - floor(spoint->lat / (PID)) * PID;
	if (spoint->lng < 0.0)
	{
		spoint->lng += (PID);
	}
	if (spoint->lat > PI)
	{
		spoint->lat -= (2 * PI);
	}
	if (spoint->lat > PIH)
	{
		spoint->lat = (PI - spoint->lat);
		spoint->lng += ((spoint->lng < PI) ? (PI) : (-PI));
	}
	if (spoint->lat < -PIH)
	{
		spoint->lat = (-PI - spoint->lat);
		spoint->lng += ((spoint->lng < PI) ? (PI) : (-PI));
	}
	if (FPeq(spoint->lat, PIH) && lat_is_neg)
		spoint->lat = -PIH;

	if (FPeq(spoint->lng, PID))
	{
		spoint->lng = 0.0;
	}
	if (FPzero(spoint->lng))
	{
		spoint->lng = 0.0;
	}
	if (FPzero(spoint->lat))
	{
		spoint->lat = 0.0;
	}
}

void
vector3d_spoint(SPoint *p, const Vector3D *v)
{
	double rho = sqrt((v->x) * (v->x) + (v->y) * (v->y));

	if (0.0 == rho)
	{
		if (FPzero(v->z))
		{
			p->lat = 0.0;
		}
		else if (v->z > 0)
		{
			p->lat = PIH;
		}
		else if (v->z < 0)
		{
			p->lat = -PIH;
		}
	}
	else
	{
		p->lat = atan(v->z / rho);
	}

	p->lng = atan2(v->y, v->x);
	if (FPzero(p->lng))
	{
		p->lng = 0.0;
	}
	else if (p->lng < 0.0)
	{
		p->lng += PID;
	}
}

void
spoint_vector3d(Vector3D *v, const SPoint *p)
{
	v->x = cos(p->lng) * cos(p->lat);
	v->y = sin(p->lng) * cos(p->lat);
	v->z = sin(p->lat);
}

Datum
spherepoint_in(PG_FUNCTION_ARGS)
{
	SPoint	   *sp = (SPoint *) palloc(sizeof(SPoint));
	char	   *c = PG_GETARG_CSTRING(0);
	double		lng,
				lat;

	void		sphere_yyparse(void);

	init_buffer(c);
	sphere_yyparse();
	if (get_point(&lng, &lat))
	{
		sp->lng = lng;
		sp->lat = lat;
		spoint_check(sp);
	}
	else
	{
		reset_buffer();
		pfree(sp);
		sp = NULL;
		elog(ERROR, "spherepoint_in: parse error");
	}
	reset_buffer();
	PG_RETURN_POINTER(sp);
}


Datum
spherepoint_from_long_lat(PG_FUNCTION_ARGS)
{
	SPoint *p = (SPoint *) palloc(sizeof(SPoint));

	p->lng = PG_GETARG_FLOAT8(0);
	p->lat = PG_GETARG_FLOAT8(1);
	spoint_check(p);
	PG_RETURN_POINTER(p);
}

static double
norm2(double a, double b)
{
	return sqrt(a * a + b * b);
}

float8
spoint_dist(const SPoint *p1, const SPoint *p2)
{
	float8	dl = p1->lng - p2->lng;
	/* use Vincenty's formula for the inverse geodesic problem on the sphere */
	float8	f = atan2(norm2(cos(p2->lat) * sin(dl),
							cos(p1->lat) * sin(p2->lat)
								- sin(p1->lat) * cos(p2->lat) * cos(dl)),
						sin(p1->lat) * sin(p2->lat)
							+ cos(p1->lat) * cos(p2->lat) * cos(dl));
	if (FPzero(f))
	{
		return 0.0;
	}
	else
	{
		return f;
	}
}

Datum
spherepoint_distance(PG_FUNCTION_ARGS)
{
	SPoint	   *p1 = (SPoint *) PG_GETARG_POINTER(0);
	SPoint	   *p2 = (SPoint *) PG_GETARG_POINTER(1);

	PG_RETURN_FLOAT8(spoint_dist(p1, p2));

}

Datum
spherepoint_long(PG_FUNCTION_ARGS)
{
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(0);

	PG_RETURN_FLOAT8(p->lng);
}

Datum
spherepoint_lat(PG_FUNCTION_ARGS)
{
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(0);

	PG_RETURN_FLOAT8(p->lat);
}

Datum
spherepoint_x(PG_FUNCTION_ARGS)
{
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(0);
	Vector3D	v;

	spoint_vector3d(&v, p);
	PG_RETURN_FLOAT8(v.x);
}

Datum
spherepoint_y(PG_FUNCTION_ARGS)
{
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(0);
	Vector3D	v;

	spoint_vector3d(&v, p);
	PG_RETURN_FLOAT8(v.y);
}

Datum
spherepoint_z(PG_FUNCTION_ARGS)
{
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(0);
	Vector3D	v;

	spoint_vector3d(&v, p);
	PG_RETURN_FLOAT8(v.z);
}

Datum
spherepoint_xyz(PG_FUNCTION_ARGS)
{
	SPoint	   *p = (SPoint *) PG_GETARG_POINTER(0);
	Datum		dret[3];
	ArrayType  *result;
	Vector3D	v;

	spoint_vector3d(&v, p);
	dret[0] = Float8GetDatumFast(v.x);
	dret[1] = Float8GetDatumFast(v.y);
	dret[2] = Float8GetDatumFast(v.z);
#ifdef USE_FLOAT8_BYVAL
	result = construct_array(dret, 3, FLOAT8OID, sizeof(float8), true, 'd');
#else
	result = construct_array(dret, 3, FLOAT8OID, sizeof(float8), false, 'd');
#endif
	PG_RETURN_ARRAYTYPE_P(result);
}

Datum
spherepoint_equal(PG_FUNCTION_ARGS)
{
	SPoint	   *p1 = (SPoint *) PG_GETARG_POINTER(0);
	SPoint	   *p2 = (SPoint *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(spoint_eq(p1, p2));
}
