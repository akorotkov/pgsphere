#ifndef __PGS_SBUFFER_H__
#define __PGS_SBUFFER_H__

/*!
  \file
  \brief Parser buffer declarations
*/



#define STYPE_UNKNOWN 0 //!< unknown type
#define STYPE_POINT   1 //!< input is spherical type
#define STYPE_CIRCLE  2 //!< input is spherical circle
#define STYPE_LINE    3 //!< input is spherical line
#define STYPE_EULER   4 //!< input is Euler transformation
#define STYPE_PATH    5 //!< input is spherical path or polygon
#define STYPE_ELLIPSE 6 //!< input is spherical ellipse
#define STYPE_BOX     7 //!< input is spherical box

/*! \defgroup PGS_EULER_AXIS Euler axis */
/*!
  \addtogroup PGS_EULER_AXIS
  @{
*/
#define EULER_AXIS_X 1  //!< x - axis for Euler transformation
#define EULER_AXIS_Y 2  //!< y - axis for Euler transformation
#define EULER_AXIS_Z 3  //!< z - axis for Euler transformation
/*! @} */

  int  sphere_yylex();
  void sphere_yyerror( const char *str );
  void sphere_flush_scanner_buffer(void) ;

  /*!
   \brief Sets the data type
   \return type number
  */
  void set_spheretype    ( unsigned char st );

  /*!
   \brief Initialize the input buffer
   \param buffer pointer to input buffer
  */
  void init_buffer       ( char * buffer );

  /*!
   \brief Resets the input buffer
  */
  void reset_buffer      ( void );

  /*!
   \brief Read the input
   \param buf pointer to buffer
   \param offset number of bytes
   \return count of read bytes
  */
  int  get_buffer        ( char * buf , int offset );

  /*!
   \brief input of a angle
   \param is_deg >0 if a in degrees
   \param a value of angle
   \return a unique ID ( position) of angle
  */
  int  set_angle         ( unsigned char is_deg , double a );

  /*!
   \brief set the sign of an angle
   \param apos the angle ID
   \param s sign of angle ( <0 .. - , >0 .. + )
   \return the unique ID ( position) of angle
  */
  int  set_angle_sign    ( int apos   , int s );

  /*!
   \brief Creates a spherical point
   \param lngpos the ID of longitude angle
   \param latpos the ID of latitude angle
   \return the unique ID ( position) of spherical point
  */
  int  set_point         ( int lngpos , int latpos );

  /*!
   \brief Creates a spherical circle
   \param spos the ID of spherical point
   \param rpos the ID of radius angle
  */
  void set_circle        ( int spos , int rpos );

  /*!
   \brief Sets the length of spherical line
   \param length the ID of length angle
  */
  void set_line          ( int length );

  /*!
   \brief Creates an Euler transformation
   \param phi the ID of first angle
   \param theta the ID of second angle
   \param psi the ID of  third angle
   \param etype three letter code of Euler transformation axes
  */
  void set_euler         ( int phi, int theta , int psi , char * etype );

  /*!
   \brief Creates a spherical ellipse
   \param r1 ID of first radius angle
   \param r2 ID of second radius angle
   \param sp ID of spherical point ( center )
   \param inc ID  of inclination angle
  */
  void set_ellipse       ( int r1, int r2, int sp , int inc );

  /*!
   \brief Returns the point parameters
   \param lng pointer to longitude value
   \param lat pointer to latitude value
   \return <>0 , if user input is spherical point
  */
  int  get_point         ( double * lng , double * lat );

  /*!
   \brief Returns the circle parameters
   \param lng pointer to longitude value of center
   \param lat pointer to latitude value of center
   \param radius pointer to radius value
   \return <>0 , if user input is spherical circle
  */
  int  get_circle        ( double * lng , double * lat , double * radius );

  /*!
   \brief Returns the ellipse parameters
   \param lng pointer to longitude value of center
   \param lat pointer to latitude value of center
   \param r1 pointer to first radius value
   \param r2 pointer to second radius value
   \param inc pointer to inclination angle
   \return <>0 , if user input is spherical ellipse
  */
  int  get_ellipse       ( double * lng , double * lat , double * r1,
                                  double * r2, double * inc );
  /*!
   \brief Returns the line parameters
   \param phi   pointer to first angle of Euler transformation
   \param theta pointer to second angle of Euler transformation
   \param psi   pointer to third angle of Euler transformation
   \param etype pointer to axes value of Euler transformation
   \param length pointer to length value
   \return <>0 , if user input is spherical line
  */
  int  get_line          ( double * phi , double * theta , double * psi ,
                                 unsigned char * etype, double * length );
  /*!
   \brief Returns the Euler transformation parameters
   \param phi   pointer to first angle of Euler transformation
   \param theta pointer to second angle of Euler transformation
   \param psi   pointer to third angle of Euler transformation
   \param etype pointer to axes value of Euler transformation
   \return <>0 , if user input is an Euler transformation
  */
  int  get_euler         ( double * phi , double * theta , 
                                 double * psi , unsigned char * etype );
  /*!
   \brief Returns the count of path elements
   \return count of points
  */
  int  get_path_count    ( void );

  /*!
   \brief Returns the elements of path
   \param spos number of element
   \param lng the ID of longitude angle
   \param lat the ID of latitude angle
   \return <>0 , if user input is an path or polygon and spos is valid
  */
  int  get_path_elem     ( int spos, double * lng , double * lat );

  /*!
   \brief Returns the elements of box
   \param lng1 the ID of first longitude angle
   \param lat1 the ID of first latitude angle
   \param lng2 the ID of second longitude angle
   \param lat2 the ID of second latitude angle
   \return <>0 , if user input is a box
  */
  int  get_box ( double * lng1 , double * lat1, double * lng2 , double * lat2 );

#endif
