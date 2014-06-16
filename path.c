#include "path.h"   

/*!
  \file
  \brief Path functions
*/


#ifndef DOXYGEN_SHOULD_SKIP_THIS

  PG_FUNCTION_INFO_V1(spherepath_in);
  PG_FUNCTION_INFO_V1(spherepath_get_point);
  PG_FUNCTION_INFO_V1(spherepath_point);
  PG_FUNCTION_INFO_V1(spherepath_equal);
  PG_FUNCTION_INFO_V1(spherepath_equal_neg);
  PG_FUNCTION_INFO_V1(spherepath_length);
  PG_FUNCTION_INFO_V1(spherepath_npts);
  PG_FUNCTION_INFO_V1(spherepath_swap);
  PG_FUNCTION_INFO_V1(spherepath_cont_point);
  PG_FUNCTION_INFO_V1(spherepath_cont_point_neg);
  PG_FUNCTION_INFO_V1(spherepath_cont_point_com);
  PG_FUNCTION_INFO_V1(spherepath_cont_point_com_neg);
  PG_FUNCTION_INFO_V1(spherepath_overlap_line );
  PG_FUNCTION_INFO_V1(spherepath_overlap_line_neg );
  PG_FUNCTION_INFO_V1(spherepath_overlap_line_com );
  PG_FUNCTION_INFO_V1(spherepath_overlap_line_com_neg );
  PG_FUNCTION_INFO_V1(spherecircle_cont_path );
  PG_FUNCTION_INFO_V1(spherecircle_cont_path_neg );
  PG_FUNCTION_INFO_V1(spherecircle_cont_path_com );
  PG_FUNCTION_INFO_V1(spherecircle_cont_path_com_neg );
  PG_FUNCTION_INFO_V1(spherecircle_overlap_path );
  PG_FUNCTION_INFO_V1(spherecircle_overlap_path_neg );
  PG_FUNCTION_INFO_V1(spherecircle_overlap_path_com );
  PG_FUNCTION_INFO_V1(spherecircle_overlap_path_com_neg );
  PG_FUNCTION_INFO_V1(spherepoly_cont_path );
  PG_FUNCTION_INFO_V1(spherepoly_cont_path_neg );
  PG_FUNCTION_INFO_V1(spherepoly_cont_path_com );
  PG_FUNCTION_INFO_V1(spherepoly_cont_path_com_neg );
  PG_FUNCTION_INFO_V1(spherepoly_overlap_path );
  PG_FUNCTION_INFO_V1(spherepoly_overlap_path_neg );
  PG_FUNCTION_INFO_V1(spherepoly_overlap_path_com );
  PG_FUNCTION_INFO_V1(spherepoly_overlap_path_com_neg );
  PG_FUNCTION_INFO_V1(spherepath_overlap_path );
  PG_FUNCTION_INFO_V1(spherepath_overlap_path_neg );
  PG_FUNCTION_INFO_V1(sphereellipse_cont_path );
  PG_FUNCTION_INFO_V1(sphereellipse_cont_path_neg );
  PG_FUNCTION_INFO_V1(sphereellipse_cont_path_com );
  PG_FUNCTION_INFO_V1(sphereellipse_cont_path_com_neg );
  PG_FUNCTION_INFO_V1(sphereellipse_overlap_path );
  PG_FUNCTION_INFO_V1(sphereellipse_overlap_path_neg );
  PG_FUNCTION_INFO_V1(sphereellipse_overlap_path_com );
  PG_FUNCTION_INFO_V1(sphereellipse_overlap_path_com_neg );
  PG_FUNCTION_INFO_V1(spheretrans_path);
  PG_FUNCTION_INFO_V1(spheretrans_path_inverse);
  PG_FUNCTION_INFO_V1(spherepath_add_point);
  PG_FUNCTION_INFO_V1(spherepath_add_points_finalize);


#endif


  /*!
    \brief Converts an array of spherical points to SPATH
    \param arr pointer to array of spherical points
    \param nelem count of elements
    \return pointer to created spherical polygon
  */
  static SPATH * spherepath_from_array ( SPoint * arr, int32 nelem )
  {

    SPATH  * path = NULL;

    if ( nelem < 2 ){
      elog ( ERROR , "spherepath_from_array: more than one point needed" );
      return NULL;
    } else {

      static int32  i;
      static float8 scheck ;
      int32      size;

      for ( i=0; i<nelem ; i++ ){
        spoint_check ( &arr[i] );
      }

      // check duplicate points
      i = 0;
      while ( i<(nelem-1) ){
        if ( nelem < 2 ) break;
        if ( spoint_eq (&arr[i],&arr[i+1]) ){
          if ( i<(nelem-2) ){
            memmove ((void*) &arr[i+1], (void*) &arr[i+2], (nelem-i-2) * sizeof( SPoint ) );
          }
          nelem--;
          continue;
        }
        i++;
      }
      if ( nelem < 2 ){
        elog ( ERROR , "spherepath_from_array: more than one point needed" );
        return NULL;
      }

      size       = offsetof(SPATH, p[0]) + sizeof(path->p[0]) * nelem;
      path       = (SPATH *) MALLOC ( size ) ;
#if PG_VERSION_NUM < 80300
      path->size = size;
#else
      SET_VARSIZE(path, size);
#endif
      path->npts = nelem;
      for ( i=0; i<nelem ; i++ ){
        if ( i>0 ){
          scheck = spoint_dist ( &arr[i-1], &arr[i] );
          if (FPeq(scheck,PI)){
            elog ( ERROR , "spherepath_from_array: a path segment length must be not equal 180 degrees." );
            return NULL;
          }
        }
        memcpy( (void*) &path->p[i], (void*) &arr[i], sizeof( SPoint ) );
      }

    }

    return ( path );

  }


  /*!
    \brief Does an Euler transformation on a path
    \param out pointer to result path
    \param in  pointer to input path
    \param se  pointer to Euler transformation
    \return pointer to result path
  */
  static SPATH  * euler_spath_trans ( SPATH * out , const SPATH  * in , const SEuler * se )
  {
    int32 i;
    
    out->size = in->size;
    out->npts = in->npts;
    for ( i=0; i<in->npts ; i++ ){
      euler_spoint_trans ( &out->p[i] , &in->p[i] , se );
    }
    return out ;
  }




  /*!
    \brief Returns the relationship between path and circle
    \param path pointer to path
    \param circ pointer to circle
    \return relationship as a \link PGS_CIRCLE_PATH_REL int8 value \endlink (\ref PGS_CIRCLE_PATH_REL )
  */
  static int8  path_circle_pos ( const SPATH * path, const SCIRCLE * circ )
  {
     static int8    pos;
     static int32     i;
     static SLine    sl;
     static int32     n;
     static const int8 sc_in = ( 1 << PGS_CIRCLE_CONT_LINE  );
     static const int8 sc_ov = ( 1 << PGS_CIRCLE_LINE_OVER  );
     static const int8 sc_os = ( 1 << PGS_CIRCLE_LINE_AVOID );

     n   = path->npts - 1;
     pos = 0;

     if ( FPzero( circ->radius ) ){
       bool pcp = spath_cont_point ( path, &circ->center );
       if ( pcp ){
         return PGS_CIRCLE_PATH_OVER;
       } else {
         return PGS_CIRCLE_PATH_AVOID;
       }
     }

     for ( i=0; i<n; i++ ){
        spath_segment ( &sl , path , i );
     	pos |= ( 1 << sphereline_circle_pos ( &sl , circ ) ) ;
     	if ( pos & sc_ov ){
          return PGS_CIRCLE_PATH_OVER;
     	}
     }

     if ( pos == sc_in ){                   // all lines inside  circle
        // circle contains path
        return PGS_CIRCLE_CONT_PATH; 
     } else if ( pos == sc_os ){            // all lines outside circle 
        // circle outside path
        return PGS_CIRCLE_PATH_AVOID;
     }

     // circle and path overlap
     return PGS_CIRCLE_PATH_OVER;
  }


  /*!
    \brief Checks, whether path and line are overlapping
    \param line pointer to a line
    \param path pointer to a path
    \return true, if overlapping
  */
  static  bool  path_line_overlap ( const SPATH * path, const SLine * line )
  {
     static int32  i ;
     static SLine sl ;
     static int32  n ;

     n = path->npts - 1;

     for ( i=0 ; i<n; i++ ){
        spath_segment ( &sl , path , i );
        if ( sline_sline_pos ( &sl, line  ) != PGS_LINE_AVOID ){
          return TRUE;
        }
     }
     return FALSE;
  }


  /*!
    \brief Returns the relationship between path and circle
    \param path pointer to path
    \param ell  pointer to ellipse
    \return relationship as a \link PGS_ELLIPSE_PATH_REL int8 value \endlink (\ref PGS_ELLIPSE_PATH_REL )
  */
  static int8  path_ellipse_pos ( const SPATH * path, const SELLIPSE * ell )
  {
     static int8    pos ;
     static int32     i ;
     static SLine    sl ;
     static int32     n ;
     static const int8 sc_in = ( 1 << PGS_ELLIPSE_CONT_LINE  );
     static const int8 sc_ov = ( 1 << PGS_ELLIPSE_LINE_OVER  );
     static const int8 sc_os = ( 1 << PGS_ELLIPSE_LINE_AVOID );

     pos = 0;
     n = path->npts - 1;

     if ( FPzero( ell->rad[0] ) ){
       static bool    pcp;
       static SPoint  cen;
       sellipse_center( &cen, ell );
       pcp = spath_cont_point ( path, &cen );
       if ( pcp ){
         return PGS_ELLIPSE_PATH_OVER;
       } else {
         return PGS_ELLIPSE_PATH_AVOID;
       }
     }

     if ( FPzero( ell->rad[1] ) ){ 
       static SLine l;
       sellipse_line( &l, ell );
/*!
\todo implement ellipse contains path if ellipse is a line
*/
       if ( path_line_overlap ( path, &l ) ){
         return PGS_ELLIPSE_PATH_OVER ;
       } else {
         return PGS_ELLIPSE_PATH_AVOID;
       }
     }

     for ( i=0; i<n; i++ ){
        spath_segment ( &sl , path , i );
     	pos |= ( 1 << sellipse_line_pos ( ell , &sl ) ) ;
     	if ( pos & sc_ov ){
          return PGS_ELLIPSE_PATH_OVER;
     	}
     }

     if ( pos == sc_in ){                   // all lines inside  ellipse
        // ellipse contains path
        return PGS_ELLIPSE_CONT_PATH; 
     } else if ( pos == sc_os ){            // all lines outside ellipse 
        // ellipse outside path
        return PGS_ELLIPSE_PATH_AVOID;
     }

     // ellipse and path overlap
     return PGS_ELLIPSE_PATH_OVER;
  }


  /*!
    \brief Checks, whether two pathes are overlapping
    \param path1 pointer to first path
    \param path2 pointer to second path
    \return true, if overlapping
  */
  static bool path_overlap ( const SPATH * path1, const SPATH * path2 )
  {
     static int32     i ;
     static SLine    sl ;
     for ( i=0 ; i<path1->npts; i++ ){
        spath_segment ( &sl , path1 , i );
        if ( path_line_overlap ( path2 , &sl ) ){
          return TRUE; // overlap
        }
     }
     return  FALSE;
  }  


  /*!
    \brief Returns the relationship between path and polygon
    \param path pointer to path
    \param poly pointer to polygon
    \return relationship as a \link PGS_POLY_PATH_REL int8 value \endlink (\ref PGS_POLY_PATH_REL )
  */
  static int8  path_poly_pos ( const SPATH * path, const SPOLY * poly )
  {
     static int32     i ;
     static SLine    sl ;
     static int8 pos, res;
     static int32      n ;
     static const int8 sp_os = ( 1 << PGS_LINE_POLY_AVOID );
     static const int8 sp_ct = ( 1 << PGS_POLY_CONT_LINE  );
     static const int8 sp_ov = ( 1 << PGS_LINE_POLY_OVER  );

     n   = path->npts - 1;
     pos = res = 0;

     for ( i=0 ; i<n; i++ ){

        spath_segment ( &sl , path , i );
        pos = ( 1 << poly_line_pos ( poly , &sl ) ) ;
        if ( pos == sp_ov ){
          return PGS_POLY_PATH_OVER; // overlap
        }
        res |= pos;
     }

     if ( res == sp_os ) {
       return PGS_POLY_PATH_AVOID;
     }
     if ( res == sp_ct ){
       return PGS_POLY_CONT_PATH;
     }
     return  PGS_POLY_OVER;
  }  


  /*!
    \brief Returns the i-th point of a path
    \param sp   pointer to result point
    \param path pointer to path
    \param i    number of point
    \return pointer to result point
    \see spath_point ( SPoint * , SPATH *, float8 )
  */
  static SPoint * spath_get_point ( SPoint * sp , const SPATH * path , int32 i )
  {
    if ( i >= 0 && i < path->npts ){
      memcpy ( (void*) sp , (void*) &path->p[i]  , sizeof ( SPoint ) );
      return sp;
    }
    return NULL;
  }

  /*!
    This function interpolates between points.
    \brief Returns the f-th point of a path
    \param sp   pointer to result point
    \param path pointer to path
    \param f    "number" of point
    \return pointer to result point
    \see spherepath_point(PG_FUNCTION_ARGS)
  */
  static SPoint * spath_point ( SPoint * sp , const SPATH * path , float8 f )
  {
      static SLine sl;
      SLine     * slp;
      static int32  i;
      
      i = (int32) floor(f) ;

      slp = spath_segment ( &sl , path , i );
      if ( ! slp ){
        return NULL;
      } else {
        static SEuler se;
        static SPoint tp;
        
        sphereline_to_euler ( &se, &sl ) ;
        
        tp.lng = sl.length * ( f - (float8) i );
        tp.lat = 0.0;
        euler_spoint_trans(sp, &tp, &se );
        return sp;
      }
      return NULL;
  }



  /*!
    \brief Checks whether two pathes are equal
    \param p1  pointer to first path
    \param p2  pointer to secondpath
    \return true, if equal
  */
  bool spath_eq ( const SPATH * p1, const SPATH * p2 )
  {
    if ( p1->npts == p2->npts ){

      static  int32   i;
      static  bool  ret;

      ret = TRUE;

      for ( i=0; i<p1->npts; i++ ){
        if ( ! spoint_eq ( &p1->p[i], &p2->p[i]) ){
          ret = FALSE;
          break;
        }
      }
      return ( ret );
    }
    return ( FALSE );
  }

  bool spath_cont_point ( const SPATH  * path, const SPoint   * sp )
  {
    static int32  n;
    static bool ret;
    static SLine sl;
    static int32  i;
    n   = path->npts - 1;
    ret = FALSE;

    for ( i=0; i<n; i++ ){
      spath_segment ( &sl , path , i );
      if ( spoint_at_sline( sp, &sl ) ){
        ret = TRUE;
        break;
      }
    }

    return ( ret );
  }

  SLine * spath_segment ( SLine * sl , const SPATH * path , int32 i )
  {
    if ( i >= 0 && i < ( path->npts - 1 ) ){
      sline_from_points ( sl, &path->p[i], &path->p[i+1] );
      return sl;
    }
    return NULL;
  }


  Datum  spherepath_in(PG_FUNCTION_ARGS)
  {
    SPATH * path ;
    char  * c  = PG_GETARG_CSTRING(0);
    static int32  i, nelem;

    void sphere_yyparse( void );
    init_buffer ( c );
    sphere_yyparse() ;

    nelem = get_path_count( ) ;
    if ( nelem > 1 ){
      SPoint arr[nelem];
      for ( i = 0; i<nelem ; i++ ){
         get_path_elem ( i , &arr[i].lng , &arr[i].lat );
      }
      path  = spherepath_from_array ( &arr[0], nelem );
    } else {
      reset_buffer();
      elog ( ERROR , "spherepath_in: more than one point needed" );
      PG_RETURN_NULL();
    }
    reset_buffer();

    PG_RETURN_POINTER( path );
  }


  Datum  spherepath_get_point(PG_FUNCTION_ARGS)
  {
    static int32 i;
    SPATH  * path = PG_GETARG_SPATH( 0 ) ;
    SPoint   * sp = ( SPoint * ) MALLOC ( sizeof ( SPoint ) );
    i = PG_GETARG_INT32 ( 1 ) ;
    if ( spath_get_point ( sp , path , i-1 ) ){
    	PG_RETURN_POINTER ( sp );
    }
    FREE( sp );
    PG_RETURN_NULL( );
  }

  Datum  spherepath_point(PG_FUNCTION_ARGS)
  {
    static float8 i;
    SPATH  * path = PG_GETARG_SPATH( 0 ) ;
    SPoint   * sp = ( SPoint * ) MALLOC ( sizeof ( SPoint ) );
    i = PG_GETARG_FLOAT8 ( 1 ) ;

    if ( spath_point ( sp , path , i-1 ) ){
    	PG_RETURN_POINTER ( sp );
    }
    FREE( sp );
    PG_RETURN_NULL( );
  }

  Datum  spherepath_equal(PG_FUNCTION_ARGS)
  {
    SPATH  * p1 = PG_GETARG_SPATH( 0 ) ;
    SPATH  * p2 = PG_GETARG_SPATH( 1 ) ;
    PG_RETURN_BOOL ( spath_eq ( p1, p2 ) );
  }

  Datum  spherepath_equal_neg(PG_FUNCTION_ARGS)
  {
    SPATH  * p1 = PG_GETARG_SPATH( 0 ) ;
    SPATH  * p2 = PG_GETARG_SPATH( 1 ) ;
    PG_RETURN_BOOL ( !spath_eq ( p1, p2 ) );
  }

  Datum  spherepath_length(PG_FUNCTION_ARGS)
  {
    SPATH  * path = PG_GETARG_SPATH( 0 ) ;
    static int32 i;
    static SLine l;
    static float8 sum;
    static int32  n;
    n = path->npts - 1;
    sum = 0.0;
    
    for ( i=0; i<n; i++ ){
       sum += ( spath_segment ( &l , path , i ) )->length ;
    }
    PG_RETURN_FLOAT8 ( sum );
  }

  Datum  spherepath_npts(PG_FUNCTION_ARGS)
  {
    SPATH * path = PG_GETARG_SPATH( 0 ) ;
    PG_RETURN_INT32 ( path->npts );
  }

  Datum  spherepath_swap(PG_FUNCTION_ARGS)
  {
    SPATH  * path = PG_GETARG_SPATH( 0 ) ;
    static int32  i;
    static int32  n;
    SPATH * ret    = (SPATH *) MALLOC ( VARSIZE(path) );
    n = path->npts - 1;
    
    for ( i=0; i<n; i++ ){
      memcpy( (void*) &ret->p[i], (void*) &path->p[n-i], sizeof(SPoint) );
    }
    ret->size = path->size;
    ret->npts = path->npts;
    PG_RETURN_POINTER ( ret );
  }

  Datum  spherepath_cont_point(PG_FUNCTION_ARGS)
  {
    SPATH  * path = PG_GETARG_SPATH( 0 ) ;
    SPoint   * sp = ( SPoint * ) PG_GETARG_POINTER ( 1 ) ;
    PG_RETURN_BOOL ( spath_cont_point ( path, sp ) );
  }

  Datum  spherepath_cont_point_neg(PG_FUNCTION_ARGS)
  {
    SPATH  * path = PG_GETARG_SPATH( 0 ) ;
    SPoint   * sp = ( SPoint * ) PG_GETARG_POINTER ( 1 ) ;
    PG_RETURN_BOOL ( !spath_cont_point ( path, sp ) );
  }

  Datum  spherepath_cont_point_com(PG_FUNCTION_ARGS)
  {
    SPATH  * path = PG_GETARG_SPATH( 1 ) ;
    SPoint   * sp = ( SPoint * ) PG_GETARG_POINTER ( 0 ) ;
    PG_RETURN_BOOL ( spath_cont_point ( path, sp ) );
  }

  Datum  spherepath_cont_point_com_neg(PG_FUNCTION_ARGS)
  {
    SPATH  * path = PG_GETARG_SPATH( 1 ) ;
    SPoint   * sp = ( SPoint * ) PG_GETARG_POINTER ( 0 ) ;
    PG_RETURN_BOOL ( !spath_cont_point ( path, sp ) );
  }

  Datum spherepath_overlap_line (PG_FUNCTION_ARGS)
  {
    SPATH   * path = PG_GETARG_SPATH( 0 ) ;
    SLine   * line = ( SLine * ) PG_GETARG_POINTER ( 1 ) ;
    PG_RETURN_BOOL ( path_line_overlap ( path, line ) );
  }

  Datum spherepath_overlap_line_neg (PG_FUNCTION_ARGS)
  {
    SPATH   * path = PG_GETARG_SPATH( 0 ) ;
    SLine   * line = ( SLine * ) PG_GETARG_POINTER ( 1 ) ;
    PG_RETURN_BOOL ( !path_line_overlap ( path, line ) );
  }

  Datum spherepath_overlap_line_com (PG_FUNCTION_ARGS)
  {
    SPATH   * path = PG_GETARG_SPATH( 1 ) ;
    SLine   * line = ( SLine * ) PG_GETARG_POINTER ( 0 ) ;
    PG_RETURN_BOOL ( path_line_overlap ( path, line ) );
  }

  Datum spherepath_overlap_line_com_neg (PG_FUNCTION_ARGS)
  {
    SPATH   * path = PG_GETARG_SPATH( 1 ) ;
    SLine   * line = ( SLine * ) PG_GETARG_POINTER ( 0 ) ;
    PG_RETURN_BOOL ( !path_line_overlap ( path, line ) );
  }

  Datum spherecircle_cont_path (PG_FUNCTION_ARGS)
  {
    SCIRCLE * circ = ( SCIRCLE  * ) PG_GETARG_POINTER ( 0 ) ;
    SPATH   * path = PG_GETARG_SPATH( 1 ) ;
    PG_RETURN_BOOL ( path_circle_pos ( path, circ ) == PGS_CIRCLE_CONT_PATH );
  }

  Datum spherecircle_cont_path_neg (PG_FUNCTION_ARGS)
  {
    SCIRCLE * circ = ( SCIRCLE  * ) PG_GETARG_POINTER ( 0 ) ;
    SPATH   * path = PG_GETARG_SPATH( 1 ) ;
    PG_RETURN_BOOL ( path_circle_pos ( path, circ ) != PGS_CIRCLE_CONT_PATH );
  }

  Datum spherecircle_cont_path_com (PG_FUNCTION_ARGS)
  {
    SCIRCLE * circ = ( SCIRCLE  * ) PG_GETARG_POINTER ( 1 ) ;
    SPATH   * path = PG_GETARG_SPATH( 0 ) ;
    PG_RETURN_BOOL ( path_circle_pos ( path, circ ) == PGS_CIRCLE_CONT_PATH );
  }

  Datum spherecircle_cont_path_com_neg (PG_FUNCTION_ARGS)
  {
    SCIRCLE * circ = ( SCIRCLE  * ) PG_GETARG_POINTER ( 1 ) ;
    SPATH   * path = PG_GETARG_SPATH( 0 ) ;
    PG_RETURN_BOOL ( path_circle_pos ( path, circ ) != PGS_CIRCLE_CONT_PATH );
  }

  Datum spherecircle_overlap_path (PG_FUNCTION_ARGS)
  {
     SCIRCLE * circ = ( SCIRCLE  * ) PG_GETARG_POINTER ( 0 ) ;
     SPATH   * path = PG_GETARG_SPATH( 1 ) ;
     PG_RETURN_BOOL ( path_circle_pos ( path, circ ) > PGS_CIRCLE_PATH_AVOID );
  }

  Datum spherecircle_overlap_path_neg (PG_FUNCTION_ARGS)
  {
     SCIRCLE * circ = ( SCIRCLE  * ) PG_GETARG_POINTER ( 0 ) ;
     SPATH   * path = PG_GETARG_SPATH( 1 ) ;
     PG_RETURN_BOOL ( path_circle_pos ( path, circ ) == PGS_CIRCLE_PATH_AVOID );
  }

  Datum spherecircle_overlap_path_com (PG_FUNCTION_ARGS)
  {
     SCIRCLE * circ = ( SCIRCLE  * ) PG_GETARG_POINTER ( 1 ) ;
     SPATH   * path = PG_GETARG_SPATH( 0 ) ;
     PG_RETURN_BOOL ( path_circle_pos ( path, circ ) > PGS_CIRCLE_PATH_AVOID );
  }

  Datum spherecircle_overlap_path_com_neg (PG_FUNCTION_ARGS)
  {
     SCIRCLE * circ = ( SCIRCLE  * ) PG_GETARG_POINTER ( 1 ) ;
     SPATH   * path = PG_GETARG_SPATH( 0 ) ;
     PG_RETURN_BOOL ( path_circle_pos ( path, circ ) == PGS_CIRCLE_PATH_AVOID );
  }

  Datum spherepoly_cont_path (PG_FUNCTION_ARGS)
  {
     SPOLY   * poly = PG_GETARG_SPOLY( 0 ) ;
     SPATH   * path = PG_GETARG_SPATH( 1 ) ;
     PG_RETURN_BOOL ( path_poly_pos ( path, poly ) == PGS_POLY_CONT_PATH );
  }

  Datum spherepoly_cont_path_neg (PG_FUNCTION_ARGS)
  {
     SPOLY   * poly = PG_GETARG_SPOLY( 0 ) ;
     SPATH   * path = PG_GETARG_SPATH( 1 ) ;
     PG_RETURN_BOOL ( path_poly_pos ( path, poly ) != PGS_POLY_CONT_PATH );
  }

  Datum spherepoly_cont_path_com (PG_FUNCTION_ARGS)
  {
     SPOLY   * poly = PG_GETARG_SPOLY( 1 ) ;
     SPATH   * path = PG_GETARG_SPATH( 0 ) ;
     PG_RETURN_BOOL ( path_poly_pos ( path, poly ) == PGS_POLY_CONT_PATH );
  }

  Datum spherepoly_cont_path_com_neg (PG_FUNCTION_ARGS)
  {
     SPOLY   * poly = PG_GETARG_SPOLY( 1 ) ;
     SPATH   * path = PG_GETARG_SPATH( 0 ) ;
     PG_RETURN_BOOL ( path_poly_pos ( path, poly ) != PGS_POLY_CONT_PATH );
  }

  Datum spherepoly_overlap_path (PG_FUNCTION_ARGS)
  {
     SPOLY   * poly = PG_GETARG_SPOLY( 0 ) ;
     SPATH   * path = PG_GETARG_SPATH( 1 ) ;
     PG_RETURN_BOOL ( path_poly_pos ( path, poly ) != PGS_POLY_PATH_AVOID );
  }

  Datum spherepoly_overlap_path_neg (PG_FUNCTION_ARGS)
  {
     SPOLY   * poly = PG_GETARG_SPOLY( 0 ) ;
     SPATH   * path = PG_GETARG_SPATH( 1 ) ;
     PG_RETURN_BOOL ( path_poly_pos ( path, poly ) == PGS_POLY_PATH_AVOID );
  }

  Datum spherepoly_overlap_path_com (PG_FUNCTION_ARGS)
  {
     SPOLY   * poly = PG_GETARG_SPOLY( 1 ) ;
     SPATH   * path = PG_GETARG_SPATH( 0 ) ;
     PG_RETURN_BOOL ( path_poly_pos ( path, poly ) != PGS_POLY_PATH_AVOID );
  }

  Datum spherepoly_overlap_path_com_neg (PG_FUNCTION_ARGS)
  {
     SPOLY   * poly = PG_GETARG_SPOLY( 1 ) ;
     SPATH   * path = PG_GETARG_SPATH( 0 ) ;
     PG_RETURN_BOOL ( path_poly_pos ( path, poly ) == PGS_POLY_PATH_AVOID );
  }

  Datum spherepath_overlap_path (PG_FUNCTION_ARGS)
  {
     SPATH   * p1 = PG_GETARG_SPATH( 0 ) ;
     SPATH   * p2 = PG_GETARG_SPATH( 1 ) ;
     PG_RETURN_BOOL ( path_overlap ( p1, p2 ) );
  }

  Datum spherepath_overlap_path_neg (PG_FUNCTION_ARGS)
  {
     SPATH   * p1 = PG_GETARG_SPATH( 0 ) ;
     SPATH   * p2 = PG_GETARG_SPATH( 1 ) ;
     PG_RETURN_BOOL ( !path_overlap ( p1, p2 ) );
  }

  Datum sphereellipse_cont_path (PG_FUNCTION_ARGS)
  {
    SELLIPSE * ell = ( SELLIPSE  * ) PG_GETARG_POINTER ( 0 ) ;
    SPATH   * path = PG_GETARG_SPATH( 1 ) ;
    PG_RETURN_BOOL ( path_ellipse_pos ( path, ell ) == PGS_ELLIPSE_CONT_PATH );
  }

  Datum sphereellipse_cont_path_neg (PG_FUNCTION_ARGS)
  {
    SELLIPSE * ell = ( SELLIPSE  * ) PG_GETARG_POINTER ( 0 ) ;
    SPATH   * path = PG_GETARG_SPATH( 1 ) ;
    PG_RETURN_BOOL ( path_ellipse_pos ( path, ell ) != PGS_ELLIPSE_CONT_PATH );
  }

  Datum sphereellipse_cont_path_com (PG_FUNCTION_ARGS)
  {
    SELLIPSE * ell = ( SELLIPSE  * ) PG_GETARG_POINTER ( 1 ) ;
    SPATH   * path = PG_GETARG_SPATH( 0 ) ;
    PG_RETURN_BOOL ( path_ellipse_pos ( path, ell ) == PGS_ELLIPSE_CONT_PATH );
  }

  Datum sphereellipse_cont_path_com_neg (PG_FUNCTION_ARGS)
  {
    SELLIPSE * ell = ( SELLIPSE  * ) PG_GETARG_POINTER ( 1 ) ;
    SPATH   * path = PG_GETARG_SPATH( 0 ) ;
    PG_RETURN_BOOL ( path_ellipse_pos ( path, ell ) != PGS_ELLIPSE_CONT_PATH );
  }

  Datum sphereellipse_overlap_path (PG_FUNCTION_ARGS)
  {
    SELLIPSE * ell = ( SELLIPSE  * ) PG_GETARG_POINTER ( 0 ) ;
    SPATH   * path = PG_GETARG_SPATH( 1 ) ;
    PG_RETURN_BOOL ( path_ellipse_pos ( path, ell ) != PGS_ELLIPSE_PATH_AVOID );
  }

  Datum sphereellipse_overlap_path_neg (PG_FUNCTION_ARGS)
  {
    SELLIPSE * ell = ( SELLIPSE  * ) PG_GETARG_POINTER ( 0 ) ;
    SPATH   * path = PG_GETARG_SPATH( 1 ) ;
    PG_RETURN_BOOL ( path_ellipse_pos ( path, ell ) == PGS_ELLIPSE_PATH_AVOID );
  }

  Datum sphereellipse_overlap_path_com (PG_FUNCTION_ARGS)
  {
    SELLIPSE * ell = ( SELLIPSE  * ) PG_GETARG_POINTER ( 1 ) ;
    SPATH   * path = PG_GETARG_SPATH( 0 ) ;
    PG_RETURN_BOOL ( path_ellipse_pos ( path, ell ) != PGS_ELLIPSE_PATH_AVOID );
  }

  Datum sphereellipse_overlap_path_com_neg (PG_FUNCTION_ARGS)
  {
    SELLIPSE * ell = ( SELLIPSE  * ) PG_GETARG_POINTER ( 1 ) ;
    SPATH   * path = PG_GETARG_SPATH( 0 ) ;
    PG_RETURN_BOOL ( path_ellipse_pos ( path, ell ) == PGS_ELLIPSE_PATH_AVOID );
  }


  Datum  spheretrans_path(PG_FUNCTION_ARGS)
  {
    SPATH   * sp  =  PG_GETARG_SPATH( 0 ) ;
    SEuler  * se  =  ( SEuler  * ) PG_GETARG_POINTER ( 1 ) ;
    SPATH   * out =  ( SPATH   * ) MALLOC ( VARSIZE(sp) );
    PG_RETURN_POINTER ( euler_spath_trans ( out , sp, se ) );
  }

  Datum  spheretrans_path_inverse(PG_FUNCTION_ARGS)
  {
   Datum sp     = PG_GETARG_DATUM ( 0 );
   SEuler *  se = ( SEuler * ) PG_GETARG_POINTER( 1 );
   SEuler tmp   ;
   Datum ret;
   
   spheretrans_inverse ( &tmp , se );
   ret =  DirectFunctionCall2(
                       spheretrans_path ,
                       sp, PointerGetDatum(&tmp) );
   PG_RETURN_DATUM( ret );
  }

  Datum  spherepath_add_point(PG_FUNCTION_ARGS)
  {
    SPATH   * path  =  ( SPATH   * ) PG_GETARG_POINTER ( 0 ) ;
    SPoint  * p     =  ( SPoint  * ) PG_GETARG_POINTER ( 1 ) ;
    int32     size  = 0 ;
    SPATH * path_new = NULL;

    if ( p == NULL ){
      PG_RETURN_POINTER ( path );
    }
    if ( path == NULL ){
      size = offsetof(SPATH, p[0]) + sizeof(SPoint) ;
      path = ( SPATH * ) MALLOC ( size );
      memcpy( (void*) &path->p[0] , (void*) p, sizeof(SPoint) );
#if PG_VERSION_NUM < 80300
      path->size = size;
#else
      SET_VARSIZE(path, size);
#endif
      path->npts = 1;
      PG_RETURN_POINTER ( path );
    }

    path = PG_GETARG_SPATH( 0 );

    // skip if equal
    if ( spoint_eq (p, &path->p[ path->npts - 1 ]) ){
      PG_RETURN_POINTER ( path );
    }

    // Skip if distance is equal 180deg
    if ( FPeq ( spoint_dist ( p, &path->p[ path->npts - 1 ]) , PI ) )
    {
      elog ( NOTICE , "spath(spoint): Skip point, distance of previous point is 180deg" );
    }

    size = offsetof(SPATH, p[0]) + sizeof(SPoint) * ( path->npts + 1 );
    path_new = palloc( size );
    memcpy( (void*) path , (void*) path_new, VARSIZE(path) );
    path_new->npts++;

#if PG_VERSION_NUM < 80300
    path_new->size = size ;
#else
    SET_VARSIZE( path_new, size );
#endif

    memcpy( (void*) &path_new->p[path->npts] , (void*) p, sizeof(SPoint) );
    PG_RETURN_POINTER ( path_new );
  }        

  Datum  spherepath_add_points_finalize(PG_FUNCTION_ARGS)
  {
    SPATH   * path  =  ( SPATH   * ) PG_GETARG_POINTER ( 0 ) ;
    if ( path == NULL ){
      PG_RETURN_NULL ( );
    }

    path = PG_GETARG_SPATH( 0 );

    if ( path->npts < 2 ){
      elog ( NOTICE , "spath(spoint): At least 2 points required" );
      FREE ( path );
      PG_RETURN_NULL ( );
    }
    PG_RETURN_POINTER ( path );
  }

