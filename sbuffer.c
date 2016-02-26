#include "pg_sphere.h"
#include "sbuffer.h"

/* Functions to buffer the parser input. */

/* Maximum count of buffered angles. */
#define MAX_BUF_ANGLE	20

/* The type of parsed spherical object. */
unsigned char spheretype;

/* The angle buffer. */
float8	bufangle[MAX_BUF_ANGLE];

/* A simple spherical point. */
typedef struct
{
	double	lng;	/* longitude */
	double	lat;	/* latitude */
} bpoint;

 /* Spherical point buffer. */
struct
{
	int		m;		/* count of buffered points */
	bpoint *p;		/* pointer to array of points */
}		bufpoints;

/* ID of line's length angle. */
int		bufline;

/*
 * First element is the ID of spherical point ( center ).
 * Second element is the ID of radius angle.
 */
int		bufcircle[2];

/* Buffer of ellipse. */
int		bufellipse[5];

/* Buffer of IDs of Euler transformation values. */
int		bufeuler[3];

/* Structure to buffer the axes of Euler transformation. */
struct
{
	unsigned char	phi,	/* first axis */
					theta,	/* second axis */
					psi;	/* third axis */
}		bufeulertype;

/* Current angle ID. */
int		bufapos;

/* Current point ID. */
int		bufspos;

/* Pointer to input buffer. */
char   *parse_buffer;


void
set_spheretype(unsigned char st)
{
	spheretype = st;
}


void
init_buffer(char *buffer)
{
	spheretype = STYPE_UNKNOWN;
	parse_buffer = buffer;

	bufapos = 0;
	bufspos = 0;
	bufeulertype.phi = bufeulertype.psi = EULER_AXIS_Z;
	bufeulertype.theta = EULER_AXIS_X;

	bufpoints.m = 2;
	bufpoints.p = (bpoint *) palloc(bufpoints.m * sizeof(bpoint));

}


void
reset_buffer(void)
{
	sphere_flush_scanner_buffer();
	pfree(bufpoints.p);
	bufpoints.p = NULL;
	bufpoints.m = 0;
	init_buffer(NULL);
}


int
set_angle_sign(int apos, int s)
{
	if (bufangle[apos] > 0 && s < 0)
	{
		bufangle[apos] *= -1;
	}
	if (bufangle[apos] < 0 && s > 0)
	{
		bufangle[apos] *= -1;
	}
	return apos;
}

int
set_angle(unsigned char is_deg, float8 a)
{
	if (is_deg)
	{
		a /= RADIANS;
	}
	bufangle[bufapos] = a;
	bufapos++;
	return (bufapos - 1);
}

int
set_point(int lngpos, int latpos)
{
	if (bufspos >= bufpoints.m)
	{
		bpoint	   *p = bufpoints.p;
		int			i = (bufpoints.m * 2);

		bufpoints.p = (bpoint *) palloc(i * sizeof(bpoint));
		memcpy((void *) bufpoints.p, (void *) p, bufpoints.m * sizeof(bpoint));
		bufpoints.m = i;
		pfree(p);
	}
	bufpoints.p[bufspos].lng = bufangle[lngpos];
	bufpoints.p[bufspos].lat = bufangle[latpos];
	bufspos++;
	lngpos = 0;
	latpos = 0;
	if ((bufapos + 3) > MAX_BUF_ANGLE)
	{
		bufapos = 0;
	}
	return (bufspos - 1);
}

void
set_circle(int spos, int rpos)
{
	bufcircle[0] = spos;
	bufcircle[1] = rpos;
}


void
set_ellipse(int r1, int r2, int sp, int inc)
{
	bufellipse[0] = r1;
	bufellipse[1] = r2;
	bufellipse[2] = sp;
	bufellipse[3] = inc;
}


void
set_line(int length)
{
	bufline = length;
}

void
set_euler(int phi, int theta, int psi, char *etype)
{
	int			  i;
	unsigned char t = 0;

	bufeuler[0] = phi;
	bufeuler[1] = theta;
	bufeuler[2] = psi;
	for (i = 0; i < 3; i++)
	{
		switch (etype[i])
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
		}
		switch (i)
		{
			case 0:
				bufeulertype.phi = t;
				break;
			case 1:
				bufeulertype.theta = t;
				break;
			case 2:
				bufeulertype.psi = t;
				break;
		}
	}
}

int
get_point(double *lng, double *lat)
{
	if (spheretype == STYPE_POINT)
	{
		*lng = bufpoints.p[0].lng;
		*lat = bufpoints.p[0].lat;
		return 1;
	}
	else
	{
		return 0;
	}
}

int
get_line(double *phi, double *theta,
		 double *psi, unsigned char *etype, double *length)
{
	int i;

	if (spheretype != STYPE_LINE)
	{
		return 0;
	}

	*phi = bufangle[bufeuler[0]];
	*theta = bufangle[bufeuler[1]];
	*psi = bufangle[bufeuler[2]];
	for (i = 0; i < 3; i++)
	{
		switch (i)
		{
			case 0:
				etype[i] = bufeulertype.phi;
				break;
			case 1:
				etype[i] = bufeulertype.theta;
				break;
			case 2:
				etype[i] = bufeulertype.psi;
				break;
		}
	}
	*length = bufangle[bufline];
	return 1;
}


int
get_euler(double *phi, double *theta,
		  double *psi, unsigned char *etype)
{
	int i;

	if (spheretype != STYPE_EULER)
	{
		return 0;
	}
	*phi = bufangle[bufeuler[0]];
	*theta = bufangle[bufeuler[1]];
	*psi = bufangle[bufeuler[2]];
	for (i = 0; i < 3; i++)
	{
		switch (i)
		{
			case 0:
				etype[i] = bufeulertype.phi;
				break;
			case 1:
				etype[i] = bufeulertype.theta;
				break;
			case 2:
				etype[i] = bufeulertype.psi;
				break;
		}
	}

	return 1;
}

int
get_circle(double *lng, double *lat, double *radius)
{
	if (spheretype == STYPE_CIRCLE)
	{
		*lng = bufpoints.p[bufcircle[0]].lng;
		*lat = bufpoints.p[bufcircle[0]].lat;
		*radius = bufangle[bufcircle[1]];
		return 1;
	}
	else
	{
		return 0;
	}
}

int
get_ellipse(double *lng, double *lat,
			double *r1, double *r2, double *inc)
{
	if (spheretype == STYPE_ELLIPSE)
	{
		*lng = bufpoints.p[bufellipse[2]].lng;
		*lat = bufpoints.p[bufellipse[2]].lat;
		*r1 = bufangle[bufellipse[0]];
		*r2 = bufangle[bufellipse[1]];
		*inc = bufangle[bufellipse[3]];
		return 1;
	}
	else
	{
		return 0;
	}

}

int
get_path_count(void)
{
	return (bufspos);
}

int
get_path_elem(int spos, double *lng, double *lat)
{
	if (spheretype == STYPE_PATH)
	{
		*lng = bufpoints.p[spos].lng;
		*lat = bufpoints.p[spos].lat;
		return 1;
	}
	else
	{
		return 0;
	}
}


int
get_box(double *lng1, double *lat1, double *lng2, double *lat2)
{
	if (spheretype == STYPE_BOX)
	{
		*lng1 = bufpoints.p[0].lng;
		*lat1 = bufpoints.p[0].lat;
		*lng2 = bufpoints.p[1].lng;
		*lat2 = bufpoints.p[1].lat;
		return 1;
	}
	return 0;
}


int
get_buffer(char *buf, int offset)
{
	int slen = strlen(parse_buffer);

	if (!parse_buffer || !(slen > 0))
	{
		return 0;
	}

	if (slen >= offset)
	{
		slen = offset;
	}
	memcpy((void *) buf, (void *) parse_buffer, slen);
	parse_buffer += slen;

	return slen;

}
