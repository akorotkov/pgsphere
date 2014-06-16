#include "types.h"

/*!
  \file
  \brief Output functions
*/


/*! \defgroup PGS_OUTPUT Output modes */
/*!
  \addtogroup PGS_OUTPUT
  @{
*/
#define OUTPUT_RAD  1    //!< output in radians
#define OUTPUT_DEG  2    //!< output in degrees
#define OUTPUT_DMS  3    //!< output in degrees, minutes, seconds
#define OUTPUT_HMS  4    //!< output in hour, minutes, seconds
/* @} */

/*!
  Default is radians.
  \brief holds the current output modus.
*/
static unsigned char sphere_output  =  OUTPUT_RAD  ;
static short int sphere_output_precision = -1;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

  PG_FUNCTION_INFO_V1 (set_sphere_output);
  PG_FUNCTION_INFO_V1 (spherepoint_out  );
  PG_FUNCTION_INFO_V1 (spherecircle_out );
  PG_FUNCTION_INFO_V1 (sphereline_out   );
  PG_FUNCTION_INFO_V1 (spheretrans_out  );
  PG_FUNCTION_INFO_V1 (spherepoly_out   );
  PG_FUNCTION_INFO_V1 (spherepath_out   );
  PG_FUNCTION_INFO_V1 (sphereellipse_out);
  PG_FUNCTION_INFO_V1 (spherebox_out    );
  PG_FUNCTION_INFO_V1 (set_sphere_output_precision);
  PG_FUNCTION_INFO_V1 (pg_sphere_version);

#endif

  /*!
   \brief set the output modus
   \return the set modus as varchar
   \note PostgreSQL function
  */
  Datum  set_sphere_output         (PG_FUNCTION_ARGS);

  /*!
   \brief set the output precision
   \return the set number of decimal digits as int
   \note PostgreSQL function
  */
  Datum  set_sphere_output_precision (PG_FUNCTION_ARGS);

  /*!
    \brief the output function of spherical point
    \return cstring
    \note PostgreSQL function
  */
  Datum  spherepoint_out           (PG_FUNCTION_ARGS);

  /*!
    \brief the output function of spherical circle
    \return cstring
    \note PostgreSQL function
  */
  Datum  spherecircle_out          (PG_FUNCTION_ARGS);

  /*!
    \brief the output function of spherical line
    \return cstring
    \note PostgreSQL function
  */
  Datum  sphereline_out            (PG_FUNCTION_ARGS);

  /*!
    \brief the output function of Euler transformation
    \return cstring
    \note PostgreSQL function
  */
  Datum  spheretrans_out           (PG_FUNCTION_ARGS);

  /*!
    \brief the output function of spherical polygon
    \return cstring
    \note PostgreSQL function
  */
  Datum  spherepoly_out            (PG_FUNCTION_ARGS);

  /*!
    \brief the output function of spherical path
    \return cstring
    \note PostgreSQL function
  */
  Datum  spherepath_out            (PG_FUNCTION_ARGS);

  /*!
    \brief the output function of spherical ellipse
    \return cstring
    \note PostgreSQL function
  */
  Datum  sphereellipse_out         (PG_FUNCTION_ARGS);

  /*!
    \brief the output function of spherical box
    \return cstring
    \note PostgreSQL function
  */
  Datum  spherebox_out             (PG_FUNCTION_ARGS);

  /*!
   \brief output of version
   \return cstring
   \note PostgreSQL function
  */
  Datum  pg_sphere_version         (PG_FUNCTION_ARGS);


  /*!
    \brief Converts radians to DEG ( degrees, minutes, seconds )
    \param rad input in radians
    \param deg pointer to degrees
    \param min pointer to minutes
    \param sec pointer to seconds
    \return nothing
    \note PostgreSQL function
  */
  static void rad_to_dms ( double rad, unsigned int * deg, unsigned int * min, double * sec )
  {
    char rsign  = ( rad < 0 )?( -1 ):( 1 );
    const double sec_dig = pow ( 10, FLT_DIG ) ;

    rad        *= ( rsign * RADIANS );

    *deg  = floor ( rad );
    *min  = floor ( 60 * ( rad - *deg ) );
    *sec  = rad * 3600 - *min * 60 - *deg * 3600 ;
    *sec  = rint ( ( double ) ( *sec * sec_dig ) ) / sec_dig;

    if ( *sec >= 60.0 ){
      *sec -= 60.0 ;
      (*min)++;
    }
    if ( *min >= 60 ){
      *min -= 60 ;
      (*deg)++;
    }
  }

  Datum set_sphere_output_precision(PG_FUNCTION_ARGS)
  {
    short int  c  = PG_GETARG_INT16(0);
    char    * buf = ( char * ) MALLOC ( 20 );

    if ( c > DBL_DIG ) c=-1;
    if ( c < -1 ) c=-1;
    sphere_output_precision=c;

    sprintf(buf,"SET %d",c);
    PG_RETURN_CSTRING ( buf ) ;
  }

  Datum set_sphere_output(PG_FUNCTION_ARGS)
  {
    char    *  c  = PG_GETARG_CSTRING(0);
    char    * buf = ( char * ) MALLOC ( 20 );

    if ( strcmp ( c, "RAD" ) == 0 ){
      sphere_output = OUTPUT_RAD;
    } else if ( strcmp ( c, "DEG" ) == 0 ){
      sphere_output = OUTPUT_DEG;
    } else if ( strcmp ( c, "DMS" ) == 0 ){
      sphere_output = OUTPUT_DMS;
    } else if ( strcmp ( c, "HMS" ) == 0 ){
      sphere_output = OUTPUT_HMS;
    } else {
      elog ( ERROR , "Unknown format" );
      FREE ( buf );
      PG_RETURN_NULL();
    }
    sprintf(buf,"SET %s",c);
    PG_RETURN_CSTRING ( buf ) ;
  }

  Datum spherepoint_out(PG_FUNCTION_ARGS)
  {

    SPoint * sp   =  ( SPoint * ) PG_GETARG_POINTER ( 0 ) ;
    char * buffer = ( char * ) MALLOC ( 255 ) ;
    unsigned int latdeg , latmin, lngdeg, lngmin;
    double latsec, lngsec;
    short int sopd=sphere_output_precision;
    short int sopl=( sopd>0 )? sopd+3 : sopd+2;
    
    latdeg = latmin = lngdeg = lngmin = 0;
    latsec = lngsec = 0.0;

    switch ( sphere_output ){

      case OUTPUT_DEG : if(sphere_output_precision==-1) {
                          sprintf ( buffer , "(%.*gd , %.*gd)", 
                            DBL_DIG, RADIANS*sp->lng, DBL_DIG, RADIANS*sp->lat );
                        } else {
                          sprintf ( buffer , "(%*.*fd , %*.*fd)", 
                            sopd+8, sopd+4, RADIANS*sp->lng,
                            sopd+8, sopd+4, RADIANS*sp->lat );
                        }
                        break;
      case OUTPUT_DMS : rad_to_dms ( sp->lng , &lngdeg, &lngmin, &lngsec );
                        rad_to_dms ( sp->lat , &latdeg, &latmin, &latsec );
                        if(sphere_output_precision==-1) {
                          sprintf (
                            buffer ,
                            "(%3ud %2um %.*gs , %c%2ud %2um %.*gs)",
                            lngdeg, lngmin, DBL_DIG, lngsec,
                            ( sp->lat<0 )?('-'):('+'),
                            latdeg, latmin, DBL_DIG, latsec 
                          );
                        } else {
                          sprintf (
                            buffer ,
                            "(%03ud %02um %0*.*fs , %c%02ud %02um %0*.*fs)",
                            lngdeg, lngmin, sopl, sopd, lngsec,
                            ( sp->lat<0 )?('-'):('+'),
                            latdeg, latmin, sopl, sopd, latsec 
                          );
                        }
                        break;

      case OUTPUT_HMS : rad_to_dms ( sp->lng / 15 , &lngdeg, &lngmin, &lngsec );
                        rad_to_dms ( sp->lat , &latdeg, &latmin, &latsec );
                        if(sphere_output_precision==-1) {
                          sprintf ( 
                            buffer ,
                            "(%3uh %2um %.*gs , %c%2ud %2um %.*gs)",
                            lngdeg, lngmin, DBL_DIG, lngsec,
                            ( sp->lat<0 )?('-'):('+'),
                            latdeg, latmin, DBL_DIG, latsec 
                          );
                        } else {
                          sprintf (
                            buffer ,
                            "(%02uh %02um %0*.*fs , %c%02ud %02um %0*.*fs)",
                            lngdeg, lngmin, (sopd==0)?sopl+2:sopl+1, sopd+1, lngsec,
                            ( sp->lat<0 )?('-'):('+'),
                            latdeg, latmin, sopl, sopd, latsec 
                          );
                        }
                        break;

      default         : if(sphere_output_precision==-1) {
                          sprintf ( buffer , "(%.*g , %.*g)", DBL_DIG, sp->lng, DBL_DIG, sp->lat );
                        } else {
                          sprintf ( buffer , "(%*.*f , %*.*f)", sopd+9, sopd+6, sp->lng, sopd+9, sopd+6, sp->lat );
                        }
                        break;
    }

    PG_RETURN_CSTRING ( buffer );

  }

  Datum spherecircle_out(PG_FUNCTION_ARGS)
  {
    SCIRCLE  *    c =  ( SCIRCLE  * ) PG_GETARG_POINTER ( 0 ) ;
    char * buffer   =  ( char * ) MALLOC (255);
    char * pointstr = DatumGetPointer( DirectFunctionCall1 ( spherepoint_out , PointerGetDatum(&c->center) ) ) ;

    unsigned int rdeg , rmin;
    double rsec;

    short int sopd=sphere_output_precision;
    short int sopl=( sopd>0 )? sopd+3 : sopd+2;

    rdeg = rmin = 0;
    rsec = 0.0;

    switch ( sphere_output ){

      case OUTPUT_DEG : if(sphere_output_precision==-1) {
                          sprintf ( buffer , "<%s , %.*gd>", pointstr, DBL_DIG, RADIANS*c->radius );
                        } else {
                          sprintf ( buffer , "<%s , %*.*fd>", pointstr, sopd+8, sopd+4, RADIANS*c->radius );
                        }
                        break;
      case OUTPUT_HMS :
      case OUTPUT_DMS : rad_to_dms ( c->radius , &rdeg, &rmin, &rsec );
                        if(sphere_output_precision==-1) {
                          sprintf ( 
                            buffer ,
                            "<%s , %2ud %2um %.*gs>",
                            pointstr,
                            rdeg, rmin, DBL_DIG, rsec
                          );
                        } else {
                          sprintf ( 
                            buffer ,
                            "<%s , %02ud %02um %0*.*fs>",
                            pointstr,
                            rdeg, rmin, sopl, sopd, rsec
                          );
                        }
                        break;
      default         : if(sphere_output_precision==-1) {
                          sprintf ( buffer , "<%s , %.*g>", pointstr, DBL_DIG, c->radius );
                        } else {
                          sprintf ( buffer , "<%s , %*.*f>", pointstr, sopd+9, sopd+6, c->radius );
                        }
                        break;
    }

    FREE ( pointstr );
    PG_RETURN_CSTRING ( buffer );

  }


  Datum sphereellipse_out(PG_FUNCTION_ARGS)
  {
    SELLIPSE    * e =  ( SELLIPSE  * ) PG_GETARG_POINTER ( 0 ) ;
    char * buffer   =  ( char * ) MALLOC (255);
    char * pointstr ;
    unsigned int rdeg[3] , rmin[3];
    double rsec[3];
    SPoint sp;
    
    short int sopd=sphere_output_precision;
    short int sopl=( sopd>0 )? sopd+3 : sopd+2;

    sp.lng   =   e->psi  ;
    sp.lat   = - e->theta;
    pointstr = DatumGetPointer( DirectFunctionCall1 ( spherepoint_out , PointerGetDatum(&sp) ) );


    switch ( sphere_output ){

      case OUTPUT_DEG : if(sphere_output_precision==-1) {
                          sprintf ( buffer , "<{ %.*gd , %.*gd }, %s , %.*gd>", 
                            DBL_DIG, RADIANS*(e->rad[0]), DBL_DIG, RADIANS*(e->rad[1]),
                            pointstr, DBL_DIG, RADIANS*(e->phi) );
                        } else {
                          sprintf ( buffer , "<{ %*.*fd , %*.*fd }, %s , %*.*fd>", 
                            sopd+8, sopd+4, RADIANS*(e->rad[0]),
                            sopd+8, sopd+4, RADIANS*(e->rad[1]),
                            pointstr, sopd+8, sopd+4, RADIANS*(e->phi) );
                        }
                        break;
      case OUTPUT_HMS :
      case OUTPUT_DMS : rad_to_dms ( e->rad[0] , &rdeg[0], &rmin[0], &rsec[0] );
                        rad_to_dms ( e->rad[1] , &rdeg[1], &rmin[1], &rsec[1] );
                        rad_to_dms ( e->phi    , &rdeg[2], &rmin[2], &rsec[2] );
                        if(sphere_output_precision==-1) {
                          sprintf ( buffer ,
                            "<{ %2ud %2um %.*gs , %2ud %2um %.*gs }, %s , %2ud %2um %.*gs>",
                            rdeg[0], rmin[0], DBL_DIG, rsec[0],
                            rdeg[1], rmin[1], DBL_DIG, rsec[1],
                            pointstr,
                            rdeg[2], rmin[2], DBL_DIG, rsec[2] );
                        } else {
                          sprintf ( buffer ,
                            "<{ %02ud %02um %*.*fs , %02ud %02um %*.*fs }, %s , %02ud %02um %*.*fs>",
                            rdeg[0], rmin[0], sopl, sopd, rsec[0],
                            rdeg[1], rmin[1], sopl, sopd, rsec[1],
                            pointstr,
                            rdeg[2], rmin[2], sopl, sopd, rsec[2] );
                        }
                        break;
      default         : if(sphere_output_precision==-1) {
                          sprintf ( buffer , "<{ %.*g , %.*g }, %s , %.*g>",
                            DBL_DIG, e->rad[0], DBL_DIG, e->rad[1],
                            pointstr, DBL_DIG, e->phi );
                        } else {
                          sprintf ( buffer , "<{ %*.*f , %*.*f }, %s , %*.*f>",
                            sopd+8, sopd+6, e->rad[0],
                            sopd+8, sopd+6, e->rad[1],
                            pointstr, sopd+8, sopd+6, e->phi );
                        }
                        break;
    }

    FREE ( pointstr );
    PG_RETURN_CSTRING ( buffer );
  }

  Datum sphereline_out(PG_FUNCTION_ARGS)
  {
    SLine    * sl   =  ( SLine  * ) PG_GETARG_POINTER ( 0 ) ;
    char     * out  =  ( char * ) MALLOC (255) ;
    char     * tstr =  NULL;
    SEuler     se ;

    unsigned int rdeg , rmin;
    double rsec;

    short int sopd=sphere_output_precision;
    short int sopl=( sopd>0 )? sopd+3 : sopd+2;

    rdeg = rmin = 0;
    rsec = 0.0;
    
    seuler_set_zxz ( &se );
    se.phi   = sl->phi;
    se.theta = sl->theta;
    se.psi   = sl->psi;
    tstr     = DatumGetPointer ( DirectFunctionCall1 ( 
                       spheretrans_out,
                       PointerGetDatum ( &se ) ) );

    switch ( sphere_output ){

      case OUTPUT_DEG : if(sphere_output_precision==-1) {
                          sprintf ( out , "( %s ), %.*gd", tstr, DBL_DIG, RADIANS*sl->length );
                        } else {
                          sprintf ( out , "( %s ), %*.*fd", tstr, sopd+8, sopd+4, RADIANS*sl->length );
                        }
                        break;
      case OUTPUT_HMS :
      case OUTPUT_DMS : rad_to_dms ( sl->length , &rdeg, &rmin, &rsec );
                        if(sphere_output_precision==-1) {
                          sprintf ( 
                            out ,
                            "( %s ), %2ud %2um %.*gs",
                            tstr, rdeg, rmin, DBL_DIG, rsec
                          );
                        } else {
                          sprintf ( 
                            out ,
                            "( %s ), %02ud %02um %0*.*fs",
                            tstr, rdeg, rmin, sopl, sopd, rsec
                          );
                        }
                        break;
      default         : if(sphere_output_precision==-1) {
                          sprintf ( out , "( %s ), %.*g", tstr, DBL_DIG, sl->length );
                        } else {
                          sprintf ( out , "( %s ), %*.*f", tstr, sopd+8, sopd+6, sl->length );
                        }
                        break;
    }

    PG_RETURN_CSTRING ( out );
  }


  Datum spheretrans_out(PG_FUNCTION_ARGS)
  {
    SEuler  *    se =  ( SEuler  * ) PG_GETARG_POINTER ( 0 ) ;
    char * buffer   =  ( char * ) MALLOC (255);
    char  buf[100];
    char  etype[4];
    SPoint  val[3];
    unsigned char i, t = 0;
    unsigned int rdeg , rmin;
    double rsec;

    short int sopd=sphere_output_precision;
    short int sopl=( sopd>0 )? sopd+3 : sopd+2;

    val[0].lat = val[1].lat = val[2].lat = 0.0;
    val[0].lng = se->phi;
    val[1].lng = se->theta;
    val[2].lng = se->psi;

    spoint_check ( &val[0] );
    spoint_check ( &val[1] );
    spoint_check ( &val[2] );
    
    buffer[0] ='\0';
    for ( i=0; i<3; i++){

      rdeg = rmin = 0;
      rsec = 0.0;
      switch ( sphere_output ){

        case OUTPUT_DEG : if(sphere_output_precision==-1) {
                            sprintf ( &buf[0] , "%.*gd", DBL_DIG, RADIANS*val[i].lng );
                          } else {
                            sprintf ( &buf[0] , "%*.*fd", sopd+8, sopd+4, RADIANS*val[i].lng );
                          }
                          break;
        case OUTPUT_HMS :
        case OUTPUT_DMS : rad_to_dms ( val[i].lng , &rdeg, &rmin, &rsec );
                          if(sphere_output_precision==-1) {
                            sprintf ( 
                              &buf[0] ,
                              "%2ud %2um %.*gs",
                              rdeg, rmin, DBL_DIG, rsec
                            );
                          } else {
                            sprintf ( 
                              &buf[0] ,
                              "%02ud %02um %0*.*fs",
                              rdeg, rmin, sopl, sopd, rsec
                            );
                          }
                          break;
        default         : if(sphere_output_precision==-1) {
                            sprintf ( &buf[0] , "%.*g", DBL_DIG, val[i].lng );
                          } else {
                            sprintf ( &buf[0] , "%*.*f", sopd+9, sopd+6, val[i].lng );
                          }
                          break;
      }
      strcat( &buf[0], ", ");
      strcat ( buffer, &buf[0] );
    }
    for ( i=0; i<3; i++ ){
      switch ( i ){
        case 0: t = se->phi_a  ; break;
        case 1: t = se->theta_a; break;
        case 2: t = se->psi_a  ; break;
      }
      switch ( t ){
        case EULER_AXIS_X : etype[i]='X'; break;
        case EULER_AXIS_Y : etype[i]='Y'; break;
        case EULER_AXIS_Z : etype[i]='Z'; break;
      }
    }
    etype[3] = '\0';
    strcat( buffer , etype );

    PG_RETURN_CSTRING ( buffer );
  }


  Datum spherepath_out(PG_FUNCTION_ARGS)
  {
    SPATH * path = PG_GETARG_SPATH( 0 ) ;
    int32  i ;
    char * out   =  ( char * ) MALLOC ( 128 * path->npts );
    char * tmp;

    strcpy(out,"{");
    for ( i = 0; i<path->npts; i++ ){
      if ( i>0 ){
      	strcat(out,",");
      }
      tmp = DatumGetPointer ( DirectFunctionCall1( spherepoint_out , PointerGetDatum( &path->p[i] ) ) );
      strcat(out,tmp);
      FREE ( tmp );
    }
    strcat(out,"}");
    PG_RETURN_CSTRING ( out );
  }


  Datum spherepoly_out(PG_FUNCTION_ARGS)
  {
    SPOLY * poly = PG_GETARG_SPOLY( 0 );
    int32  i ;
    char * out   =  ( char * ) MALLOC ( 128 * poly->npts );
    char * tmp;

    strcpy(out,"{");
    for ( i = 0; i<poly->npts; i++ ){
      if ( i>0 ){
      	strcat(out,",");
      }
      tmp = DatumGetPointer ( DirectFunctionCall1( spherepoint_out , PointerGetDatum( &poly->p[i] ) ) );
      strcat(out,tmp);
      FREE ( tmp );
    }
    strcat(out,"}");
    PG_RETURN_CSTRING ( out );
  }


  Datum spherebox_out(PG_FUNCTION_ARGS)
  {
    SBOX  * box      =  ( SBOX * ) PG_GETARG_POINTER ( 0 ) ;
    char  * buffer   =  ( char * ) MALLOC (255);
    char  * str1     =  DatumGetPointer( DirectFunctionCall1 ( spherepoint_out , PointerGetDatum(&box->sw) ) ) ;
    char  * str2     =  DatumGetPointer( DirectFunctionCall1 ( spherepoint_out , PointerGetDatum(&box->ne) ) ) ;

    sprintf ( buffer, "(%s, %s)", str1, str2 );
    FREE ( str1 );
    FREE ( str2 );
    PG_RETURN_CSTRING ( buffer );

  }


  Datum pg_sphere_version(PG_FUNCTION_ARGS)
  {
    char  * buffer   =  ( char * ) MALLOC (20);
    sprintf ( buffer, "1.1.1pre2");
    PG_RETURN_CSTRING ( buffer );
  }
