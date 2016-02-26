#ifndef __PGS_SBUFFER_H__
#define __PGS_SBUFFER_H__

/* Parser buffer declarations */

#define STYPE_UNKNOWN 0	/* unknown type */
#define STYPE_POINT   1	/* input is spherical type */
#define STYPE_CIRCLE  2	/* input is spherical circle */
#define STYPE_LINE	  3	/* input is spherical line */
#define STYPE_EULER   4	/* input is Euler transformation */
#define STYPE_PATH	  5	/* input is spherical path or polygon */
#define STYPE_ELLIPSE 6	/* input is spherical ellipse */
#define STYPE_BOX	  7	/* input is spherical box */

/* PGS_EULER_AXIS Euler axis */
#define EULER_AXIS_X 1	/* x - axis for Euler transformation */
#define EULER_AXIS_Y 2	/* y - axis for Euler transformation */
#define EULER_AXIS_Z 3	/* z - axis for Euler transformation */

int		sphere_yylex();
void	sphere_yyerror(const char *str);
void	sphere_flush_scanner_buffer(void);

/* Sets the data type */
void	set_spheretype(unsigned char st);

/* Initialize the input buffer */
void	init_buffer(char *buffer);

/* Resets the input buffer */
void	reset_buffer(void);

/*
 * Read the "offset" number of bytes from "buf" buffer.
 * Returns the number of read bytes.
 */
int		get_buffer(char *buf, int offset);

/*
 * Input of an angle. When is_deg > 0 then "a" is in degrees,
 * otherwise it's in radians. Returns the unique ID (position) of the angle.
 */
int		set_angle(unsigned char is_deg, double a);

/*
 * Set the sign of an angle. "apos" is the angle. "s" is a sign of the angle
 * ( < 0 .. - , > 0 .. + ). Returns the unique ID (position) of the angle.
 */
int		set_angle_sign(int apos, int s);

/*
 * Creates a spherical point. "lngpos" is the ID of a longitude angle, "latpos"
 * is the ID of a latitude angle. Returns the unique ID (position) of the spherical
 * point.
 */
int		set_point(int lngpos, int latpos);

/*
 * Creates a spherical circle. "spos" is the ID of a spherical point, "rpos"
 * is the ID of a radius angle.
 */
void	set_circle(int spos, int rpos);

/*
 * Sets the length of a spherical line. "length" is the ID of a length angle.
 */
void	set_line(int length);

/*
 * Creates an Euler transformation. "phi" is the ID of a first angle,
 * "theta" is the ID of a second angle, "psi" is the ID of a third angle,
 * "etype" is the three letter code of Euler transformation axes.
 */
void	set_euler(int phi, int theta, int psi, char *etype);

/*
 * Creates a spherical ellipse. "r1" is the ID of a first radius angle,
 * "r2" is the ID of a second radius angle, "sp" is the ID of a spherical
 * point ( center ), "inc" is the ID of an inclination angle.
 */
void	set_ellipse(int r1, int r2, int sp, int inc);

/*
 * Returns the point parameters. "lng" is the pointer to a longitude
 * value, "lat" is the pointer to a latitude value. Returns 0 if user
 * input is a spherical point.
 */
int		get_point(double *lng, double *lat);

/*
 * Returns the circle parameters. "lng" is pointer to a longitude
 * value of its center, "lat" is pointer to the latitude value of the center,
 * "radius" is the pointer to the radius value. Returns 0 if user input
 * is a spherical circle.
 */
int		get_circle(double *lng, double *lat, double *radius);

/*
 * Returns the ellipse parameters. "lng" is the pointer to a longitude value
 * of its center, "lat" is the pointer to a latitude value of the center, "r1"
 * is the pointer to a first radius value, "r2" is the pointer to a second
 * radius value, "inc" is the pointer to an inclination angle. Returns 0 if user
 * input is a spherical ellipse.
 */
int		get_ellipse(double *lng, double *lat, double *r1,
					double *r2, double *inc);

/*
 * Returns the line parameters. "phi" is the pointer to the first angle
 * of Euler transformation, "theta" is the pointer to the second angle of Euler
 * transformation, "psi" is the pointer to the third angle of Euler transformation,
 * "etype" is the pointer to the axes value of Euler transformation, "length" is
 * the pointer to the length value. Returns 0 if user input is a spherical line.
 */
int		get_line(double *phi, double *theta, double *psi,
				 unsigned char *etype, double *length);

/*
 * Returns the Euler transformation parameters. "phi" is the pointer to the
 * first angle of Euler transformation, "theta" is the pointer to the second
 * angle of Euler transformation, "psi" is the pointer to the third angle of Euler
 * transformation, "etype" is the pointer to the axes value of Euler transformation.
 * Returns 0 if user input is an Euler transformation.
 */
int		get_euler(double *phi, double *theta,
				  double *psi, unsigned char *etype);

/*
 * Returns the number of path elements.
 */
int		get_path_count(void);

/*
 * Returns the elements of a path. "spos" is the number of element, "lng" is
 * the ID of longitude angle, "lat" is the ID of a latitude angle. Returns 0
 * if user input is a path or a polygon and "spos" is valid.
 */
int		get_path_elem(int spos, double *lng, double *lat);

/*
 * Returns the elements of a box. "lng1" is the ID of the first longitude
 * angle, "lat1" is the ID of the first latitude angle, "lng2" is the ID of
 * the second longitude angle, "lat2" is the ID of the second latitude angle.
 * Returns 0 if user input is a box.
 */
int		get_box(double *lng1, double *lat1, double *lng2, double *lat2);

#endif
