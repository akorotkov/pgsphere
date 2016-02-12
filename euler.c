#include "euler.h"

/* Euler transformation functions */

PG_FUNCTION_INFO_V1(spheretrans_in);
PG_FUNCTION_INFO_V1(spheretrans_from_float8);
PG_FUNCTION_INFO_V1(spheretrans_from_float8_and_type);
PG_FUNCTION_INFO_V1(spheretrans_equal);
PG_FUNCTION_INFO_V1(spheretrans_not_equal);
PG_FUNCTION_INFO_V1(spheretrans_phi);
PG_FUNCTION_INFO_V1(spheretrans_theta);
PG_FUNCTION_INFO_V1(spheretrans_psi);
PG_FUNCTION_INFO_V1(spheretrans_type);
PG_FUNCTION_INFO_V1(spheretrans_zxz);
PG_FUNCTION_INFO_V1(spheretrans);
PG_FUNCTION_INFO_V1(spheretrans_invert);
PG_FUNCTION_INFO_V1(spheretrans_trans);
PG_FUNCTION_INFO_V1(spheretrans_trans_inv);
PG_FUNCTION_INFO_V1(spheretrans_point);
PG_FUNCTION_INFO_V1(spheretrans_point_inverse);

/*
 * Checks and modifies the Euler transformation.
 */
static void
spheretrans_check(SEuler *e)
{
	SPoint		sp[3];

	sp[0].lat = sp[1].lat = sp[2].lat = 0.0;
	sp[0].lng = e->phi;
	sp[1].lng = e->theta;
	sp[2].lng = e->psi;
	spoint_check(&sp[0]);
	spoint_check(&sp[1]);
	spoint_check(&sp[2]);
	e->phi = sp[0].lng;
	e->theta = sp[1].lng;
	e->psi = sp[2].lng;
}

Datum
spheretrans_in(PG_FUNCTION_ARGS)
{
	SEuler	   *se = (SEuler *) palloc(sizeof(SEuler));
	char	   *c = PG_GETARG_CSTRING(0);
	unsigned char etype[3];
	int			i;

	void		sphere_yyparse(void);

	init_buffer(c);
	sphere_yyparse();

	if (get_euler(&se->phi, &se->theta, &se->psi, etype))
	{

		for (i = 0; i < 3; i++)
		{
			switch (i)
			{
				case 0:
					se->phi_a = etype[i];
					break;
				case 1:
					se->theta_a = etype[i];
					break;
				case 2:
					se->psi_a = etype[i];
					break;
			}
		}
		spheretrans_check(se);
	}
	else
	{
		reset_buffer();
		pfree(se);
		se = NULL;
		elog(ERROR, "spheretrans_in: parse error");
	}
	reset_buffer();
	PG_RETURN_POINTER(se);
}

Datum
spheretrans_from_float8(PG_FUNCTION_ARGS)
{
	SEuler	   *se = (SEuler *) palloc(sizeof(SEuler));

	se->phi = PG_GETARG_FLOAT8(0);
	se->theta = PG_GETARG_FLOAT8(1);
	se->psi = PG_GETARG_FLOAT8(2);
	seuler_set_zxz(se);
	spheretrans_check(se);
	PG_RETURN_POINTER(se);
}

Datum
spheretrans_from_float8_and_type(PG_FUNCTION_ARGS)
{
	SEuler	   *se;
	Datum		d[3];
	int			i;
	char	   *c = PG_GETARG_CSTRING(3);
	unsigned char t = 0;

	d[0] = PG_GETARG_DATUM(0);
	d[1] = PG_GETARG_DATUM(1);
	d[2] = PG_GETARG_DATUM(2);
	se = (SEuler *) DatumGetPointer(
						DirectFunctionCall3(spheretrans_from_float8,
											d[0], d[1], d[2]));

	for (i = 0; i < 3; i++)
	{
		switch (c[i])
		{
			case 'x':
			case 'X':
				t = EULER_AXIS_X;
				break;
			case 'y':
			case 'Y':
				t = EULER_AXIS_Y;
				break;
			case 'z':
			case 'Z':
				t = EULER_AXIS_Z;
				break;
			default:
				t = 0;
		}

		if (t == 0)
		{
			pfree(se);
			elog(ERROR, "invalid axis format");
		}
		switch (i)
		{
			case 0:
				se->phi_a = t;
				break;
			case 1:
				se->theta_a = t;
				break;
			case 2:
				se->psi_a = t;
				break;
		}
	}
	PG_RETURN_POINTER(se);

}

void
seuler_set_zxz(SEuler *se)
{
	se->phi_a = EULER_AXIS_Z;
	se->theta_a = EULER_AXIS_X;
	se->psi_a = EULER_AXIS_Z;
}

bool
strans_eq(const SEuler *e1, const SEuler *e2)
{
	SPoint	in[2], p[4];

	in[0].lng = 0.0;
	in[0].lat = 0.0;
	in[1].lng = PIH;
	in[1].lat = 0.0;

	euler_spoint_trans(&p[0], &in[0], e1);
	euler_spoint_trans(&p[1], &in[1], e1);
	euler_spoint_trans(&p[2], &in[0], e2);
	euler_spoint_trans(&p[3], &in[1], e2);

	return spoint_eq(&p[0], &p[2]) && spoint_eq(&p[1], &p[3]);
}

Datum
spheretrans_equal(PG_FUNCTION_ARGS)
{
	SEuler	   *e1 = (SEuler *) PG_GETARG_POINTER(0);
	SEuler	   *e2 = (SEuler *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(strans_eq(e1, e2));
}

Datum
spheretrans_not_equal(PG_FUNCTION_ARGS)
{
	SEuler	   *e1 = (SEuler *) PG_GETARG_POINTER(0);
	SEuler	   *e2 = (SEuler *) PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(!strans_eq(e1, e2));
}

Datum
spheretrans_phi(PG_FUNCTION_ARGS)
{
	SEuler	   *se = (SEuler *) PG_GETARG_POINTER(0);

	PG_RETURN_POINTER(&se->phi);
}

Datum
spheretrans_theta(PG_FUNCTION_ARGS)
{
	SEuler	   *se = (SEuler *) PG_GETARG_POINTER(0);

	PG_RETURN_POINTER(&se->theta);
}

Datum
spheretrans_psi(PG_FUNCTION_ARGS)
{
	SEuler	   *se = (SEuler *) PG_GETARG_POINTER(0);

	PG_RETURN_POINTER(&se->psi);
}

Datum
spheretrans_type(PG_FUNCTION_ARGS)
{
	SEuler	   *se = (SEuler *) PG_GETARG_POINTER(0);
	BpChar	   *result = (BpChar *) palloc(3 + VARHDRSZ);
	char		ret[4];
	int			i;
	unsigned char t = 0;

	for (i = 0; i < 3; i++)
	{
		switch (i)
		{
			case 0:
				t = se->phi_a;
				break;
			case 1:
				t = se->theta_a;
				break;
			case 2:
				t = se->psi_a;
				break;
		}
		switch (t)
		{
			case EULER_AXIS_X:
				ret[i] = 'X';
				break;
			case EULER_AXIS_Y:
				ret[i] = 'Y';
				break;
			case EULER_AXIS_Z:
				ret[i] = 'Z';
				break;
		}
	}
	ret[3] = '\0';
	SET_VARSIZE(result, 3 + VARHDRSZ);
	memcpy((void *) VARDATA(result), (void *) &ret[0], 3);

	PG_RETURN_BPCHAR_P(result);
}

void
spheretrans_inv(SEuler *se)
{
	float8				lng[3];
	const unsigned char	c = se->phi_a;

	lng[2] = -se->phi;
	lng[1] = -se->theta;
	lng[0] = -se->psi;
	se->phi = lng[0];
	se->theta = lng[1];
	se->psi = lng[2];
	se->phi_a = se->psi_a;
	se->psi_a = c;
}

void
spheretrans_inverse(SEuler *se_out, const SEuler *se_in)
{
	memcpy((void *) se_out, (void *) se_in, sizeof(SEuler));
	spheretrans_inv(se_out);
}

void
strans_zxz(SEuler *ret, const SEuler *se)
{
	if (se->phi_a == EULER_AXIS_Z &&
		se->theta_a == EULER_AXIS_X &&
		se->psi_a == EULER_AXIS_Z)
	{
		memcpy((void *) ret, (void *) se, sizeof(SEuler));
	}
	else
	{
		SEuler	tmp;

		tmp.psi = 0.0;
		tmp.theta = 0.0;
		tmp.phi = 0.0;
		seuler_set_zxz(&tmp);
		seuler_trans_zxz(ret, se, &tmp);
	}
}

Datum
spheretrans_zxz(PG_FUNCTION_ARGS)
{
	SEuler	   *si = (SEuler *) PG_GETARG_POINTER(0);
	SEuler	   *ret = (SEuler *) palloc(sizeof(SEuler));

	strans_zxz(ret, si);
	PG_RETURN_POINTER(ret);
}

Datum
spheretrans(PG_FUNCTION_ARGS)
{
	Datum		d = PG_GETARG_DATUM(0);

	PG_RETURN_DATUM(d);
}

Datum
spheretrans_invert(PG_FUNCTION_ARGS)
{
	SEuler	   *se = (SEuler *) PG_GETARG_POINTER(0);
	SEuler	   *ret = (SEuler *) palloc(sizeof(SEuler));

	spheretrans_inverse(ret, se);
	PG_RETURN_POINTER(ret);
}

void
seuler_trans_zxz(SEuler *out, const SEuler *in, const SEuler *se)
{
	SPoint	sp[4];

	sp[0].lng = 0.0;
	sp[0].lat = 0.0;
	sp[1].lng = PIH;
	sp[1].lat = 0.0;
	euler_spoint_trans(&sp[2], &sp[0], in);
	euler_spoint_trans(&sp[3], &sp[1], in);
	euler_spoint_trans(&sp[0], &sp[2], se);
	euler_spoint_trans(&sp[1], &sp[3], se);
	spherevector_to_euler(out, &sp[0], &sp[1]);
}

Datum
spheretrans_trans(PG_FUNCTION_ARGS)
{
	SEuler	   *se1 = (SEuler *) PG_GETARG_POINTER(0);
	SEuler	   *se2 = (SEuler *) PG_GETARG_POINTER(1);
	SEuler	   *out = (SEuler *) palloc(sizeof(SEuler));

	seuler_trans_zxz(out, se1, se2);
	PG_RETURN_POINTER(out);
}

Datum
spheretrans_trans_inv(PG_FUNCTION_ARGS)
{
	SEuler	   *se1 = (SEuler *) PG_GETARG_POINTER(0);
	SEuler	   *se2 = (SEuler *) PG_GETARG_POINTER(1);
	SEuler	   *out = (SEuler *) palloc(sizeof(SEuler));
	SEuler		tmp;

	spheretrans_inverse(&tmp, se2);
	seuler_trans_zxz(out, se1, &tmp);
	spheretrans_check(out);
	PG_RETURN_POINTER(out);
}

void
euler_spoint_trans(SPoint *out, const SPoint *in, const SEuler *se)
{
	Vector3D	v, o;

	spoint_vector3d(&v, in);
	euler_vector_trans(&o, &v, se);
	vector3d_spoint(out, &o);
}

Datum
spheretrans_point(PG_FUNCTION_ARGS)
{
	SPoint	   *sp = (SPoint *) PG_GETARG_POINTER(0);
	SEuler	   *se = (SEuler *) PG_GETARG_POINTER(1);
	SPoint	   *out = (SPoint *) palloc(sizeof(SPoint));

	euler_spoint_trans(out, sp, se);
	PG_RETURN_POINTER(out);
}

Datum
spheretrans_point_inverse(PG_FUNCTION_ARGS)
{
	Datum		sp = PG_GETARG_DATUM(0);
	SEuler	   *se = (SEuler *) PG_GETARG_POINTER(1);
	SEuler		tmp;
	Datum		ret;

	spheretrans_inverse(&tmp, se);
	ret = DirectFunctionCall2(spheretrans_point,
							  sp, PointerGetDatum(&tmp));
	PG_RETURN_DATUM(ret);
}

 /*
  * Transforms a spherical vector from 'spb' to 'spe' into an inverse Euler
  * transformation. Returns true if the transformation was successful.
  */
static bool
spherevector_to_euler_inv(SEuler *se, const SPoint *spb, const SPoint *spe)
{
	if (spoint_eq(spb, spe))
	{
		return false;
	}
	else
	{
		Vector3D	vbeg, vend, vtmp;
		SPoint		spt[2];
		SEuler		set;

		spoint_vector3d(&vbeg, spb);
		spoint_vector3d(&vend, spe);
		vector3d_cross(&vtmp, &vbeg, &vend);
		vector3d_spoint(&spt[0], &vtmp);
		set.phi = -spt[0].lng - PIH;
		set.theta = spt[0].lat - PIH;
		set.psi = 0.0;
		seuler_set_zxz(&set);
		euler_spoint_trans(&spt[1], spb, &set);
		set.psi = -spt[1].lng;
		memcpy((void *) se, (void *) &set, sizeof(SEuler));
	}

	return true;
}

bool
spherevector_to_euler(SEuler *se, const SPoint *spb, const SPoint *spe)
{
	bool	ret;

	ret = spherevector_to_euler_inv(se, spb, spe);
	if (ret)
	{
		spheretrans_inv(se);
	}
	return ret;
}

void
euler_vector_trans(Vector3D *out, const Vector3D *in, const SEuler *se)
{
	int				i;
	unsigned char	t;
	const double   *a;
	double 			u[3], vr[3], sa, ca;

	t = 0;
	a = NULL;
	u[0] = in->x;
	u[1] = in->y;
	u[2] = in->z;

	for (i = 0; i < 3; i++)
	{

		switch (i)
		{
			case 0:
				a = &se->phi;
				t = se->phi_a;
				break;
			case 1:
				a = &se->theta;
				t = se->theta_a;
				break;
			case 2:
				a = &se->psi;
				t = se->psi_a;
				break;
		}

		if (FPzero(*a))
		{
			continue;
		}

		sa = sin(*a);
		ca = cos(*a);

		switch (t)
		{

			case EULER_AXIS_X:
				vr[0] = u[0];
				vr[1] = ca * u[1] - sa * u[2];
				vr[2] = sa * u[1] + ca * u[2];
				break;
			case EULER_AXIS_Y:
				vr[0] = ca * u[0] + sa * u[2];
				vr[1] = u[1];
				vr[2] = ca * u[2] - sa * u[0];
				break;
			case EULER_AXIS_Z:
				vr[0] = ca * u[0] - sa * u[1];
				vr[1] = sa * u[0] + ca * u[1];
				vr[2] = u[2];
				break;

		}
		memcpy((void *) &u[0], (void *) &vr[0], sizeof(u));

	}
	out->x = u[0];
	out->y = u[1];
	out->z = u[2];
}
