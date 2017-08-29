#include "types.h"

/* Output functions */


/* Output modes */
#define OUTPUT_RAD	1	 /* output in radians */
#define OUTPUT_DEG	2	 /* output in degrees */
#define OUTPUT_DMS	3	 /* output in degrees, minutes, seconds */
#define OUTPUT_HMS	4	 /* output in hour, minutes, seconds */

/*.
 * Holds the current output modus.
 * Default is radians.
 */
static unsigned char sphere_output = OUTPUT_RAD;
static short int sphere_output_precision = DBL_DIG;

PG_FUNCTION_INFO_V1(set_sphere_output);
PG_FUNCTION_INFO_V1(spherepoint_out);
PG_FUNCTION_INFO_V1(spherecircle_out);
PG_FUNCTION_INFO_V1(sphereline_out);
PG_FUNCTION_INFO_V1(spheretrans_out);
PG_FUNCTION_INFO_V1(spherepoly_out);
PG_FUNCTION_INFO_V1(spherepath_out);
PG_FUNCTION_INFO_V1(sphereellipse_out);
PG_FUNCTION_INFO_V1(spherebox_out);
PG_FUNCTION_INFO_V1(set_sphere_output_precision);
PG_FUNCTION_INFO_V1(pg_sphere_version);

 /*
  * Sets the output modus.
  */
Datum	set_sphere_output(PG_FUNCTION_ARGS);

 /*
  * Sets the output precision.
  */
Datum	set_sphere_output_precision(PG_FUNCTION_ARGS);

 /*
  * The output function of spherical point.
  */
Datum	spherepoint_out(PG_FUNCTION_ARGS);

 /*
  * The output function of spherical circle.
  */
Datum	spherecircle_out(PG_FUNCTION_ARGS);

 /*
  * The output function of spherical line.
  */
Datum	sphereline_out(PG_FUNCTION_ARGS);

 /*
  * The output function of Euler transformation.
  */
Datum	spheretrans_out(PG_FUNCTION_ARGS);

 /*
  * The output function of spherical polygon.
  */
Datum	spherepoly_out(PG_FUNCTION_ARGS);

 /*
  * The output function of spherical path.
  */
Datum	spherepath_out(PG_FUNCTION_ARGS);

 /*
  * The output function of spherical ellipse.
  */
Datum	sphereellipse_out(PG_FUNCTION_ARGS);

 /*
  * The output function of spherical box.
  */
Datum	spherebox_out(PG_FUNCTION_ARGS);

 /*
  * Returns pg_sphere version.
  */
Datum	pg_sphere_version(PG_FUNCTION_ARGS);


 /*
  * Converts radians to DEG ( degrees, minutes, seconds )
  *
  * rad - input in radians
  * deg - pointer to degrees
  * min - pointer to minutes
  * sec - pointer to seconds
  */
static void
rad_to_dms(double rad, unsigned int *deg, unsigned int *min, double *sec)
{
	double			rsign = rad < 0 ? -1 : 1;
	const double	sec_dig = pow(10, FLT_DIG);

	rad *= (rsign * RADIANS);

	*deg = floor(rad);
	*min = floor(60 * (rad - *deg));
	*sec = rad * 3600 - *min * 60 - *deg * 3600;
	*sec = rint((double) (*sec * sec_dig)) / sec_dig;

	if (*sec >= 60.0)
	{
		*sec -= 60.0;
		(*min)++;
	}
	if (*min >= 60)
	{
		*min -= 60;
		(*deg)++;
	}
}

Datum
set_sphere_output_precision(PG_FUNCTION_ARGS)
{
	short int	c = PG_GETARG_INT16(0);
	char	   *buf = (char *) palloc(20);

	if (c > DBL_DIG)
		c = DBL_DIG;
	if (c < 1)
		c = DBL_DIG;
	sphere_output_precision = c;

	sprintf(buf, "SET %d", c);
	PG_RETURN_CSTRING(buf);
}

Datum
set_sphere_output(PG_FUNCTION_ARGS)
{
	char	   *c = PG_GETARG_CSTRING(0);
	char	   *buf = (char *) palloc(20);

	if (strcmp(c, "RAD") == 0)
	{
		sphere_output = OUTPUT_RAD;
	}
	else if (strcmp(c, "DEG") == 0)
	{
		sphere_output = OUTPUT_DEG;
	}
	else if (strcmp(c, "DMS") == 0)
	{
		sphere_output = OUTPUT_DMS;
	}
	else if (strcmp(c, "HMS") == 0)
	{
		sphere_output = OUTPUT_HMS;
	}
	else
	{
		elog(ERROR, "Unknown format");
		pfree(buf);
		PG_RETURN_NULL();
	}
	sprintf(buf, "SET %s", c);
	PG_RETURN_CSTRING(buf);
}

Datum
spherepoint_out(PG_FUNCTION_ARGS)
{
	SPoint		   *sp = (SPoint *) PG_GETARG_POINTER(0);
	char		   *buffer = (char *) palloc(255);
	unsigned int	latdeg,
					latmin,
					lngdeg,
					lngmin;
	double			latsec,
					lngsec;

	latdeg = latmin = lngdeg = lngmin = 0;
	latsec = lngsec = 0.0;

	switch (sphere_output)
	{
		case OUTPUT_DEG:
			sprintf(buffer, "(%.*gd , %.*gd)",
					sphere_output_precision, RADIANS * sp->lng,
					sphere_output_precision, RADIANS * sp->lat);
			break;

		case OUTPUT_DMS:
			rad_to_dms(sp->lng, &lngdeg, &lngmin, &lngsec);
			rad_to_dms(sp->lat, &latdeg, &latmin, &latsec);
			sprintf(buffer,
					"(%3ud %2um %.*gs , %c%2ud %2um %.*gs)",
					lngdeg, lngmin, sphere_output_precision, lngsec,
					(sp->lat < 0) ? ('-') : ('+'),
					latdeg, latmin, sphere_output_precision, latsec);
			break;

		case OUTPUT_HMS:
			rad_to_dms(sp->lng / 15, &lngdeg, &lngmin, &lngsec);
			rad_to_dms(sp->lat, &latdeg, &latmin, &latsec);
			sprintf(buffer,
					"(%3uh %2um %.*gs , %c%2ud %2um %.*gs)",
					lngdeg, lngmin, sphere_output_precision, lngsec,
					(sp->lat < 0) ? ('-') : ('+'),
					latdeg, latmin, sphere_output_precision, latsec);
			break;

		default:
			sprintf(buffer, "(%.*g , %.*g)",
					sphere_output_precision, sp->lng,
					sphere_output_precision, sp->lat);
			break;
	}

	PG_RETURN_CSTRING(buffer);

}

Datum
spherecircle_out(PG_FUNCTION_ARGS)
{
	SCIRCLE    *c = (SCIRCLE *) PG_GETARG_POINTER(0);
	char	   *buffer = (char *) palloc(255);
	char	   *pointstr = DatumGetPointer(
								DirectFunctionCall1(spherepoint_out,
													PointerGetDatum(&c->center)));

	unsigned int rdeg,
				rmin;
	double		rsec;


	rdeg = rmin = 0;
	rsec = 0.0;

	switch (sphere_output)
	{

		case OUTPUT_DEG:
			sprintf(buffer, "<%s , %.*gd>",
					pointstr, sphere_output_precision,
					RADIANS * c->radius);
			break;

		case OUTPUT_HMS:
		case OUTPUT_DMS:
			rad_to_dms(c->radius, &rdeg, &rmin, &rsec);
			sprintf(buffer,
					"<%s , %2ud %2um %.*gs>",
					pointstr,
					rdeg, rmin, sphere_output_precision, rsec);
			break;

		default:
			sprintf(buffer,	"<%s , %.*g>",
					pointstr, sphere_output_precision, c->radius);
			break;
	}

	pfree(pointstr);
	PG_RETURN_CSTRING(buffer);

}

Datum
sphereellipse_out(PG_FUNCTION_ARGS)
{
	SELLIPSE   *e = (SELLIPSE *) PG_GETARG_POINTER(0);
	char	   *buffer = (char *) palloc(255);
	char	   *pointstr;
	unsigned int rdeg[3],
				rmin[3];
	double		rsec[3];
	SPoint		sp;


	sp.lng = e->psi;
	sp.lat = -e->theta;
	pointstr = DatumGetPointer(DirectFunctionCall1(spherepoint_out,
												   PointerGetDatum(&sp)));

	switch (sphere_output)
	{

		case OUTPUT_DEG:
			sprintf(buffer,
					"<{ %.*gd , %.*gd }, %s , %.*gd>",
					sphere_output_precision, RADIANS * (e->rad[0]),
					sphere_output_precision, RADIANS * (e->rad[1]),
					pointstr,
					sphere_output_precision, RADIANS * (e->phi));
			break;

		case OUTPUT_HMS:
		case OUTPUT_DMS:
			rad_to_dms(e->rad[0], &rdeg[0], &rmin[0], &rsec[0]);
			rad_to_dms(e->rad[1], &rdeg[1], &rmin[1], &rsec[1]);
			rad_to_dms(e->phi, &rdeg[2], &rmin[2], &rsec[2]);
			sprintf(buffer,
					"<{ %2ud %2um %.*gs , %2ud %2um %.*gs }, %s , %2ud %2um %.*gs>",
					rdeg[0], rmin[0], sphere_output_precision, rsec[0],
					rdeg[1], rmin[1], sphere_output_precision, rsec[1],
					pointstr,
					rdeg[2], rmin[2], sphere_output_precision, rsec[2]);
			break;

		default:
			sprintf(
				buffer,
				"<{ %.*g , %.*g }, %s , %.*g>",
				sphere_output_precision, e->rad[0],
				sphere_output_precision, e->rad[1],
				pointstr,
				sphere_output_precision, e->phi);
			break;
	}

	pfree(pointstr);
	PG_RETURN_CSTRING(buffer);
}

Datum
sphereline_out(PG_FUNCTION_ARGS)
{
	SLine		   *sl = (SLine *) PG_GETARG_POINTER(0);
	char		   *out = (char *) palloc(255);
	char		   *tstr = NULL;
	SEuler			se;

	unsigned int	rdeg,
					rmin;
	double			rsec;

	rdeg = rmin = 0;
	rsec = 0.0;

	seuler_set_zxz(&se);
	se.phi = sl->phi;
	se.theta = sl->theta;
	se.psi = sl->psi;
	tstr = DatumGetPointer(DirectFunctionCall1(spheretrans_out,
											   PointerGetDatum(&se)));

	switch (sphere_output)
	{
		case OUTPUT_DEG:
			sprintf(out,
					"( %s ), %.*gd",
					tstr, sphere_output_precision, RADIANS * sl->length
				);
			break;

		case OUTPUT_HMS:
		case OUTPUT_DMS:
			rad_to_dms(sl->length, &rdeg, &rmin, &rsec);
			sprintf(out,
					"( %s ), %2ud %2um %.*gs",
					tstr, rdeg, rmin, sphere_output_precision, rsec);
			break;

		default:
			sprintf(out,
					"( %s ), %.*g",
					tstr, sphere_output_precision, sl->length
				);
			break;
	}

	PG_RETURN_CSTRING(out);
}

Datum
spheretrans_out(PG_FUNCTION_ARGS)
{
	SEuler	   *se = (SEuler *) PG_GETARG_POINTER(0);
	char	   *buffer = (char *) palloc(255);
	char		buf[100];
	char		etype[4];
	SPoint		val[3];
	unsigned char i,
				t = 0;
	unsigned int rdeg,
				rmin;
	double		rsec;

	val[0].lat = val[1].lat = val[2].lat = 0.0;
	val[0].lng = se->phi;
	val[1].lng = se->theta;
	val[2].lng = se->psi;

	spoint_check(&val[0]);
	spoint_check(&val[1]);
	spoint_check(&val[2]);

	buffer[0] = '\0';
	for (i = 0; i < 3; i++)
	{

		rdeg = rmin = 0;
		rsec = 0.0;
		switch (sphere_output)
		{

			case OUTPUT_DEG:
				sprintf(&buf[0],
						"%.*gd",
						sphere_output_precision, RADIANS * val[i].lng);
				break;

			case OUTPUT_HMS:
			case OUTPUT_DMS:
				rad_to_dms(val[i].lng, &rdeg, &rmin, &rsec);
				sprintf(&buf[0],
						"%2ud %2um %.*gs",
						rdeg, rmin, sphere_output_precision, rsec);
				break;

			default:
				sprintf(&buf[0], "%.*g", sphere_output_precision, val[i].lng);
				break;
		}
		strcat(&buf[0], ", ");
		strcat(buffer, &buf[0]);
	}
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
				etype[i] = 'X';
				break;
			case EULER_AXIS_Y:
				etype[i] = 'Y';
				break;
			case EULER_AXIS_Z:
				etype[i] = 'Z';
				break;
		}
	}
	etype[3] = '\0';
	strcat(buffer, etype);

	PG_RETURN_CSTRING(buffer);
}

Datum
spherepath_out(PG_FUNCTION_ARGS)
{
	SPATH	   *path = PG_GETARG_SPATH(0);
	int32		i;
	char	   *out = (char *) palloc(128 * path->npts);
	char	   *tmp;

	strcpy(out, "{");
	for (i = 0; i < path->npts; i++)
	{
		if (i > 0)
		{
			strcat(out, ",");
		}
		tmp = DatumGetPointer(DirectFunctionCall1(spherepoint_out,
												  PointerGetDatum(&path->p[i])));
		strcat(out, tmp);
		pfree(tmp);
	}
	strcat(out, "}");
	PG_RETURN_CSTRING(out);
}

Datum
spherepoly_out(PG_FUNCTION_ARGS)
{
	SPOLY	   *poly = PG_GETARG_SPOLY(0);
	int32		i;
	char	   *out = (char *) palloc(128 * poly->npts);
	char	   *tmp;

	strcpy(out, "{");
	for (i = 0; i < poly->npts; i++)
	{
		if (i > 0)
		{
			strcat(out, ",");
		}
		tmp = DatumGetPointer(DirectFunctionCall1(spherepoint_out,
												  PointerGetDatum(&poly->p[i])));
		strcat(out, tmp);
		pfree(tmp);
	}
	strcat(out, "}");
	PG_RETURN_CSTRING(out);
}

Datum
spherebox_out(PG_FUNCTION_ARGS)
{
	SBOX	   *box = (SBOX *) PG_GETARG_POINTER(0);
	char	   *buffer = (char *) palloc(255);
	char	   *str1 = DatumGetPointer(
							DirectFunctionCall1(spherepoint_out,
												PointerGetDatum(&box->sw)));
	char	   *str2 = DatumGetPointer(
							DirectFunctionCall1(spherepoint_out,
												PointerGetDatum(&box->ne)));

	sprintf(buffer, "(%s, %s)", str1, str2);
	pfree(str1);
	pfree(str2);
	PG_RETURN_CSTRING(buffer);
}

Datum
pg_sphere_version(PG_FUNCTION_ARGS)
{
	char	   *buffer = (char *) palloc(20);
	sprintf(buffer, "1.1.5");
	PG_RETURN_CSTRING(buffer);
}
