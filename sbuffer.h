#ifndef __PGS_SBUFFER_H__
#define __PGS_SBUFFER_H__

/*
 * Parser buffer declarations
 */

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

int			sphere_yylex();
void		sphere_yyerror(const char *str);
void		sphere_flush_scanner_buffer(void);

/*
 * Sets the data type
 */
void		set_spheretype(unsigned char st);

/*
 * Initialize the input buffer
 */
void		init_buffer(char *buffer);

/*
 * Resets the input buffer
 */
void		reset_buffer(void);

/*
 * Read the "offset" number of bytes from "buf" buffer. Returns count of read
 * bytes.
 */
int			get_buffer(char *buf, int offset);

/*
 * Input of a angle. When is_deg > 0 then "a" is in degrees otherwise it's in
 * radians. Returns an unique ID (position) of angle.
 */
int			set_angle(unsigned char is_deg, double a);

/*
 * Set the sign of an angle. "apos" is the angle. "s" is sign of angle
 * ( < 0 .. - , > 0 .. + ). Returns the unique ID (position) of angle.
 */
int			set_angle_sign(int apos, int s);

/*
 * Creates a spherical point. "lngpos" is the ID of longitude angle, "latpos"
 * is the ID of latitude angle. Returns the unique ID (position) of spherical
 * point.
 */
int			set_point(int lngpos, int latpos);

/*
 * Creates a spherical circle. "spos" is the ID of spherical point. "rpos"
 * is the ID of radius angle.
 */
void		set_circle(int spos, int rpos);

/*
 * Sets the length of spherical line \param length the ID of length
 * angle
 */
void		set_line(int length);

/*
 * Creates an Euler transformation \param phi the ID of first angle
 * \param theta the ID of second angle \param psi the ID of  third angle
 * \param etype three letter code of Euler transformation axes
 */
void		set_euler(int phi, int theta, int psi, char *etype);

/*
 * Creates a spherical ellipse \param r1 ID of first radius angle
 * \param r2 ID of second radius angle \param sp ID of spherical point (
 * center ) \param inc ID	of inclination angle
 */
void		set_ellipse(int r1, int r2, int sp, int inc);

/*
 * Returns the point parameters \param lng pointer to longitude
 * value \param lat pointer to latitude value \return <>0 , if user input is
 * spherical point
 */
int			get_point(double *lng, double *lat);

/*
 * Returns the circle parameters \param lng pointer to longitude
 * value of center \param lat pointer to latitude value of center \param
 * radius pointer to radius value \return <>0 , if user input is spherical
 * circle
 */
int			get_circle(double *lng, double *lat, double *radius);

/*
 * Returns the ellipse parameters \param lng pointer to longitude
 * value of center \param lat pointer to latitude value of center \param r1
 * pointer to first radius value \param r2 pointer to second radius value
 * \param inc pointer to inclination angle \return <>0 , if user input is
 * spherical ellipse
 */
int			get_ellipse(double *lng, double *lat, double *r1,
													double *r2, double *inc);

/*
 * Returns the line parameters \param phi   pointer to first angle
 * of Euler transformation \param theta pointer to second angle of Euler
 * transformation \param psi	pointer to third angle of Euler transformation
 * \param etype pointer to axes value of Euler transformation \param length
 * pointer to length value \return <>0 , if user input is spherical line
 */
int			get_line(double *phi, double *theta, double *psi,
										unsigned char *etype, double *length);

/*
 * Returns the Euler transformation parameters \param phi   pointer
 * to first angle of Euler transformation \param theta pointer to second
 * angle of Euler transformation \param psi   pointer to third angle of Euler
 * transformation \param etype pointer to axes value of Euler transformation
 * \return <>0 , if user input is an Euler transformation
 */
int			get_euler(double *phi, double *theta,
											double *psi, unsigned char *etype);

/*
 * Returns the count of path elements \return count of points
 */
int			get_path_count(void);

/*
 * Returns the elements of path \param spos number of element \param
 * lng the ID of longitude angle \param lat the ID of latitude angle \return
 * <>0 , if user input is an path or polygon and spos is valid
 */
int			get_path_elem(int spos, double *lng, double *lat);

/*
 * Returns the elements of box \param lng1 the ID of first longitude
 * angle \param lat1 the ID of first latitude angle \param lng2 the ID of
 * second longitude angle \param lat2 the ID of second latitude angle \return
 * <>0 , if user input is a box
 */
int			get_box(double *lng1, double *lat1, double *lng2, double *lat2);

#endif
