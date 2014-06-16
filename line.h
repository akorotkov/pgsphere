#ifndef __PGS_LINE_H__
#define __PGS_LINE_H__

#include "circle.h"

/*!
  \file
  \brief Line declarations
*/


/*!
  \brief Spherical line.
*/
typedef struct {
  float8      phi,  //!< the first  rotation angle around z axis
            theta,  //!< the second rotation angle around x axis
              psi;  //!< the last   rotation angle around z axis
  float8   length;  //!< the length of the line
} SLine;

/*!
  \defgroup PGS_RELATIONSHIPS Object relationships
  @{
*/
/*! \defgroup PGS_CIRCLE_LINE_REL Circle and line
  @{
*/
#define PGS_CIRCLE_LINE_AVOID 0    //!< circle avoids line
#define PGS_CIRCLE_CONT_LINE  1    //!< circle contains line
#define PGS_CIRCLE_LINE_OVER  2    //!< circle overlaps line
/*! @} */

/*! \defgroup PGS_LINE_LINE_REL Line and line
  @{
*/
#define PGS_LINE_AVOID        1    //!< line avoids other line
#define PGS_LINE_EQUAL        2    //!< lines are equal
#define PGS_LINE_CONT_LINE    3    //!< line contains line
#define PGS_LINE_CROSS        4    //!< lines cross each other
#define PGS_LINE_CONNECT      5    //!< line are "connected"  
#define PGS_LINE_OVER         6    //!< lines overlap each other
/*! @} */
/*! @} */

  /*!
    The function returns NULL, if the distance between begin and end
    is 180deg.
    \brief Returns a line from given begin and end
    \param sl    the result pointer to a spherical line
    \param pbeg  the input pointer to the begin of line
    \param pend  the input pointer to the end of line
    \return a pointer to created spherical line 
  */
  bool sline_from_points ( SLine  * sl, const SPoint * pbeg, const SPoint * pend );

  /*!
    \brief returns a meridian line
    \param sl   pointer to result line
    \param lng  longitude in radians
    \return pointer to result line
  */
  SLine * sline_meridian( SLine * sl, float8 lng );

  /*!
    \brief Returns the begin of a line
    \param p  the pointer to the begin
    \param l  the input pointer to the line
    \return a pointer to begin
  */
  SPoint * sline_begin ( SPoint * p , const SLine  * l  );

  /*!
    \brief Returns the end of a line
    \param p  the pointer to the end
    \param l  the input pointer to the line
    \return a pointer to end
  */
  SPoint * sline_end ( SPoint * p , const SLine  * l  );


  /*!
    \brief Returns minimum and maximum latitude of a spherical line
    \param sl pointer to a line
    \param minlat pointer to minimum latitude
    \param maxlat pointer to maximum latitude
    \return void
  */
  void sline_min_max_lat ( const SLine * sl , float8 * minlat, float8 * maxlat );


  /*!
    \brief Calculates the spherical points with a latitude lat at a spherical line
    \param sl pointer to a line
    \param lat latitude
    \param p1 first  returned spherical point
    \param p2 second returned spherical point
    \return count of found points or <0 if undefined
  */
  int32 sphereline_latitude_points ( const SLine * sl, float8 lat, SPoint *p1, SPoint *p2 );

  /*!
    \brief Returns true, if the two lines are equal
    \param l1  the pointer to first line
    \param l2  the pointer to second line
    \return bool ( true, if equal )
  */
  bool sline_eq ( const SLine * l1 , const SLine * l2  );

  /*!
    \brief Returns the relationship between line and circle
    \param sl  the pointer to a line
    \param sc  the pointer to a circle
    \return relationship as a \link PGS_CIRCLE_LINE_REL int8 value \endlink (\ref  PGS_CIRCLE_LINE_REL )
  */
  int8 sphereline_circle_pos ( const SLine * sl , const SCIRCLE * sc );

  /*!
    Take sure that line and circle are overlapping before calling this function!
    Otherwise, the result will be undefined.
    \see sphereline_circle_pos ( const SLine * , const SCIRCLE * )
    \brief If line and circle are overlapping, this function returns true if line and circle are touching
    \param sl  the pointer to a line
    \param sc  the pointer to a circle
    \return true, if touching
  */
  bool sline_circle_touch( const SLine * sl , const SCIRCLE * sc );

  /*!
    \brief Returns the relationship between two lines
    \param l1  pointer to first line
    \param l2  pointer to second line
    \return relationship as a \link PGS_LINE_LINE_REL int8 value \endlink (\ref  PGS_LINE_LINE_REL )
  */
  int8 sline_sline_pos ( const SLine * l1 , const SLine * l2  ); 

  /*!
    \brief Checks, whether the point is on line
    \param p  pointer to given point
    \param sl pointer to the line
    \return bool, true if point at line
  */
  bool spoint_at_sline          ( const SPoint * p , const SLine * sl  );  

  /*!
    \brief Returns the Euler transformation of a line
    \param se  result pointer to Euler transformation
    \param sl  input  pointer to the line
    \return pointer to Euler transformation
    \see spheretrans_from_line (PG_FUNCTION_ARGS)
  */
  SEuler * sphereline_to_euler ( SEuler * se, const SLine * sl  );

  /*!
    \brief Returns the inverse Euler transformation of a line
    \param se  result pointer to Euler transformation
    \param sl  input  pointer to the line
    \return pointer to Euler transformation
    \see spheretrans_from_line (PG_FUNCTION_ARGS)
  */
  SEuler * sphereline_to_euler_inv  ( SEuler * se, const SLine * sl  );

  /*!
    \brief Transforms a line using  Euler transformation
    \param out  result pointer to the line
    \param in   input  pointer of the line
    \param se   pointer to the Euler transformation
    \return pointer to transformed line
    \see spheretrans_line (PG_FUNCTION_ARGS)
  */
  SLine * euler_sline_trans ( SLine * out , const SLine  * in , const SEuler * se );

  /*!
    \brief Returns the center of a line
    \param c    result pointer to center
    \param sl   input  pointer of the line
    \return pointer to center
  */
  SPoint * sline_center( SPoint * c, const SLine * sl );

  /*!
    \brief The input function for spherical lines
    \return a spherical line datum
    \note PostgreSQL function
  */
  Datum  sphereline_in                  (PG_FUNCTION_ARGS);

  /*!
    \brief Casts spherical point as line
    \return a spherical line datum
    \note PostgreSQL function
  */
  Datum  sphereline_from_point         (PG_FUNCTION_ARGS);

  /*!
    This function provides the input of a line using begin and end.
    The distance of begin and end have to be not equal 180deg.
    \brief input function for spherical lines from spherical points
    \return a spherical line datum
    \note PostgreSQL function
  */
  Datum  sphereline_from_points         (PG_FUNCTION_ARGS);

  /*!
    This function returns a spherical line from given Euler transformation
    and length of line. If the length is less than zero, an error occurs.
    If the length is larger than 360deg, the length is truncated to 360deg.
    \brief input function for spherical lines from Euler transformation and length
    \return a spherical line datum
    \note PostgreSQL function
  */
  Datum  sphereline_from_trans          (PG_FUNCTION_ARGS);

  /*!
    This function returns a meridian starting from "south"
    to north. The float8 param gives the longitude in radians.
    \brief Creates a line as meridian
    \return a spherical line datum
    \note PostgreSQL function
  */
  Datum  sphereline_meridian            (PG_FUNCTION_ARGS);

  /*!
    \brief Swaps begin and end of a line.
    \return a spherical line datum
    \note PostgreSQL function
  */
  Datum  sphereline_swap_beg_end        (PG_FUNCTION_ARGS);

  /*!
    \brief Turns the line, but keeps begin and end of the line.
    \return a spherical line datum
    \note PostgreSQL function
  */
  Datum  sphereline_turn                (PG_FUNCTION_ARGS);

  /*!
    \brief Returns the begin of a line.
    \return a spherical point datum
    \note PostgreSQL function
  */
  Datum  sphereline_begin               (PG_FUNCTION_ARGS);

  /*!
    \brief Returns the end of a line.
    \return a spherical point datum
    \note PostgreSQL function
  */
  Datum  sphereline_end                 (PG_FUNCTION_ARGS);

  /*!
    \brief Returns the length of a line in radians.
    \return a float8 datum
    \note PostgreSQL function
  */
  Datum  sphereline_length              (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether a line contains a point.
    \return a bool datum
    \note PostgreSQL function
  */
  Datum  sphereline_cont_point          (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether a line doesn't contain a point.
    \return a bool datum
    \note PostgreSQL function
  */
  Datum  sphereline_cont_point_neg      (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether a line contains a point.
    \return a bool datum
    \note PostgreSQL function
  */
  Datum  sphereline_cont_point_com      (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether a line doesn't contain a point.
    \return a bool datum
    \note PostgreSQL function
  */
  Datum  sphereline_cont_point_com_neg  (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether a circle contains a line.
    \return a bool datum
    \note PostgreSQL function
  */
  Datum  spherecircle_cont_line         (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether a circle doesn't contain a line.
    \return a bool datum
    \note PostgreSQL function
  */
  Datum  spherecircle_cont_line_neg     (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether a circle contains a line.
    \return a bool datum
    \note PostgreSQL function
  */
  Datum  spherecircle_cont_line_com     (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether a circle doesn't contain a line.
    \return a bool datum
    \note PostgreSQL function
  */
  Datum  spherecircle_cont_line_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether a circle and line overlap.
    \return a bool datum
    \note PostgreSQL function
  */
  Datum  sphereline_overlap_circle      (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether circle and line are not overlapping.
    \return a bool datum
    \note PostgreSQL function
  */
  Datum  sphereline_overlap_circle_neg  (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether a circle and line overlap.
    \return a bool datum
    \note PostgreSQL function
  */
  Datum  sphereline_overlap_circle_com  (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether circle and line are not overlapping.
    \return a bool datum
    \note PostgreSQL function
  */
  Datum  sphereline_overlap_circle_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether two lines are equal
    \return a bool datum
    \note PostgreSQL function
  */
  Datum  sphereline_equal               (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether two lines are not equal
    \return a bool datum
    \note PostgreSQL function
  */
  Datum  sphereline_equal_neg           (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether two lines crosses each other.
    \return a bool datum
    \note PostgreSQL function
  */
  Datum  sphereline_crosses             (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether two lines don't cross each other.
    \return a bool datum
    \note PostgreSQL function
  */
  Datum  sphereline_crosses_neg         (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether two lines overlap.
    \return a bool datum
    \note PostgreSQL function
  */
  Datum  sphereline_overlap             (PG_FUNCTION_ARGS);

  /*!
    \brief Checks whether two lines are not overlapping.
    \return a bool datum
    \note PostgreSQL function
  */
  Datum  sphereline_overlap_neg         (PG_FUNCTION_ARGS);

  /*!
    Returns a Euler transformation. A inverse transformation 
    with it puts the line into equator beginning at (0,0) and
    ending at (0,length).
    \brief Returns the Euler transformation of a line
    \return a Euler transformation datum
    \note PostgreSQL function
  */
  Datum  spheretrans_from_line          (PG_FUNCTION_ARGS);

  /*!
    \brief Transforms a line with an Euler transformation
    \return a spherical line datum
    \note PostgreSQL function
  */
  Datum  spheretrans_line               (PG_FUNCTION_ARGS);

  /*!
    \brief Inverse transformation of a line with an Euler transformation
    \return a spherical line datum
    \note PostgreSQL function
  */
  Datum  spheretrans_line_inverse       (PG_FUNCTION_ARGS);

#endif
