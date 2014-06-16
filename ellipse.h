#ifndef __PGS_ELLIPSE_H__
#define __PGS_ELLIPSE_H__

#include "line.h"

/*!
  \file
  \brief Ellipse declarations
*/


/*!
  A spherical ellipse is represented using two radii and
  a Euler transformation ( ZXZ-axis ). The "untransformed"
  ellipse is located on equator at position (0,0). The 
  large radius is along equator.
  \brief Spherical ellipse
*/
typedef struct {
  float8 rad[2] ; //!< rad[0] the large radius, rad[1] the small radius of an ellipse in radians
  float8    phi , //!< the first  rotation angle around z axis
          theta , //!< the second rotation angle around x axis
           psi  ; //!< the last   rotation angle around z axis
} SELLIPSE;



/*!
  \addtogroup PGS_RELATIONSHIPS
  @{
*/
/*! \defgroup PGS_ELLIPSE_LINE_REL Ellipse and line */
/*!
  \addtogroup PGS_ELLIPSE_LINE_REL
  @{
*/
#define PGS_ELLIPSE_LINE_AVOID 0    //!< ellipse avoids line
#define PGS_ELLIPSE_CONT_LINE  1    //!< ellipse contains line
#define PGS_ELLIPSE_LINE_OVER  2    //!< ellipse overlaps line
/*! @} */

/*! \defgroup PGS_ELLIPSE_CIRCLE_REL Ellipse and circle */
/*!
  \addtogroup PGS_ELLIPSE_CIRCLE_REL
  @{
*/
#define PGS_ELLIPSE_CIRCLE_AVOID 0    //!< ellipse avoids circle
#define PGS_CIRCLE_CONT_ELLIPSE  1    //!< circle contains ellipse
#define PGS_ELLIPSE_CONT_CIRCLE  2    //!< ellipse contains circle
#define PGS_ELLIPSE_CIRCLE_EQUAL 3    //!< ellipse equals circle
#define PGS_ELLIPSE_CIRCLE_OVER  4    //!< ellipse overlaps circle
/*! @} */

/*! \defgroup PGS_ELLIPSE_ELLIPSE_REL Ellipse and ellipse */
/*!
  \addtogroup PGS_ELLIPSE_ELLIPSE_REL
  @{
*/
#define PGS_ELLIPSE_AVOID 0    //!< ellipse avoids other ellipse
#define PGS_ELLIPSE_CONT  1    //!< ellipse contains other ellipse
#define PGS_ELLIPSE_OVER  2    //!< ellipse overlaps other ellipse
/*! @} */
/*! @} */



  /*!
    \brief Checks, whether two ellipses are equal
    \param e1 first ellipse
    \param e2 second ellipse
    \return true, if equal
  */
  bool        sellipse_eq              ( const SELLIPSE * e1 , const SELLIPSE * e2 );

  /*!
    \brief Returns the center of an ellipse
    \param e pointer to ellipse
    \param sp pointer to center of ellipse
    \return pointer to center of ellipse
  */
  SPoint   *  sellipse_center          ( SPoint * sp, const SELLIPSE * e );

  /*!
    \brief Checks, whether a ellipse contains point
    \param se pointer to ellipse
    \param sp pointer to point
    \return true if ellipse contains point
  */
  bool sellipse_cont_point ( const SELLIPSE * se , const SPoint * sp );


  /*!
    \brief Returns the large axis of an ellipse as line
    \note The direction of line is undefined.
    \param e pointer to ellipse
    \param sl pointer to result line
    \return pointer to result line
  */
  SLine    *  sellipse_line            ( SLine * sl, const SELLIPSE * e );  

  /*!
    \brief Relationship between line and ellipse
    \param sl pointer to a line
    \param se pointer to an ellipse
    \return relationship as a \link PGS_ELLIPSE_LINE_REL int8 value \endlink (\ref  PGS_ELLIPSE_LINE_REL )
  */
  int8        sellipse_line_pos        ( const SELLIPSE * se , const SLine * sl ); 

  /*!
    \brief Relationship between circle and ellipse
    \param sc pointer to a circle
    \param se pointer to an ellipse
    \return relationship as a \link PGS_ELLIPSE_CIRCLE_REL int8 value \endlink (\ref  PGS_ELLIPSE_CIRCLE_REL )
  */
  int8        sellipse_circle_pos      ( const SELLIPSE * se , const SCIRCLE * sc ) ;

  /*!
    \brief Returns the Euler transformation of an ellipse
    \param e pointer to ellipse
    \param se pointer to Euler transformation
    \return pointer to Euler transformation
  */
  SEuler * sellipse_trans( SEuler * se , const SELLIPSE * e );


  /*!
    \brief Input of spherical ellipse
    \return spherical ellipse datum
    \note PostgreSQL function
  */
  Datum sphereellipse_in              (PG_FUNCTION_ARGS);

  /*!
    \brief Input of spherical ellipse from center, axes and inclination
    \return spherical ellipse datum
    \note PostgreSQL function
  */
  Datum sphereellipse_infunc          (PG_FUNCTION_ARGS);

  /*!
    \brief returns the inclination of an ellipse
    \return float8 datum
    \note PostgreSQL function
  */
  Datum sphereellipse_incl            (PG_FUNCTION_ARGS);

  /*!
    \brief returns the length of major axis of an ellipse
    \return float8 datum
    \note PostgreSQL function
  */
  Datum sphereellipse_rad1            (PG_FUNCTION_ARGS);

  /*!
    \brief returns the length of minor axis of an ellipse
    \return float8 datum
    \note PostgreSQL function
  */
  Datum sphereellipse_rad2            (PG_FUNCTION_ARGS);

  /*!
    \brief returns the center of an ellipse
    \return Spoint datum
    \note PostgreSQL function
  */
  Datum sphereellipse_center          (PG_FUNCTION_ARGS);

  /*!
    \brief returns the Euler transformation of an ellipse
    \return SEuler datum
    \note PostgreSQL function
  */
  Datum sphereellipse_trans          (PG_FUNCTION_ARGS);

  /*!
    The created circle is the boundary circle of ellipse. The diameter
    of returned circle is equal to length of major axis of ellipse.
    \brief Casts a spherical ellipse as circle
    \return SCIRCLE datum
    \note PostgreSQL function
  */
  Datum sphereellipse_circle          (PG_FUNCTION_ARGS);

  /*!
    \brief Casts a spherical point to an ellipse
    \return SELLIPSE datum
    \note PostgreSQL function
  */
  Datum spherepoint_ellipse          (PG_FUNCTION_ARGS);

  /*!
    \brief Casts a spherical circle to an ellipse
    \return SELLIPSE datum
    \note PostgreSQL function
  */
  Datum spherecircle_ellipse          (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether two ellipses are equal
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_equal           (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether two ellipses are not equal
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_equal_neg       (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether ellipse contains point
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_cont_point      (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether ellipse doesn't contain point
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_cont_point_neg  (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether ellipse contains point
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_cont_point_com      (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether ellipse doesn't contain point
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_cont_point_com_neg  (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether ellipse contains line
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_cont_line       (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether ellipse doesn't contain line
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_cont_line_neg   (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether ellipse contains line
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_cont_line_com   (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether ellipse doesn't contain line
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_cont_line_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether ellipse and line are overlapping
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_overlap_line    (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether ellipse and line are not overlapping
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_overlap_line_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether ellipse and line are overlapping
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_overlap_line_com (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether ellipse and line are not overlapping
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_overlap_line_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether ellipse contains circle
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_cont_circle     (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether ellipse doesn't contain circle
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_cont_circle_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether ellipse contains circle
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_cont_circle_com     (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether ellipse doesn't contain circle
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_cont_circle_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether circle contains ellipse
    \return boolean datum
    \note PostgreSQL function
  */
  Datum spherecircle_cont_ellipse     (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether circle doesn't contain ellipse
    \return boolean datum
    \note PostgreSQL function
  */
  Datum spherecircle_cont_ellipse_neg  (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether circle contains ellipse
    \return boolean datum
    \note PostgreSQL function
  */
  Datum spherecircle_cont_ellipse_com (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether circle doesn't contain ellipse
    \return boolean datum
    \note PostgreSQL function
  */
  Datum spherecircle_cont_ellipse_com_neg (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether circle and ellipse are overlapping
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_overlap_circle  (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether circle and ellipse are not overlapping
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_overlap_circle_neg  (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether circle and ellipse are overlapping
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_overlap_circle_com  (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether circle and ellipse are not overlapping
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_overlap_circle_com_neg  (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether an ellipse contains an other ellipse
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_cont_ellipse    (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether an ellipse doesn't contain an other ellipse
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_cont_ellipse_neg    (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether an ellipse is contained by an other ellipse
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_cont_ellipse_com    (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether an ellipse isn't contained by an other ellipse
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_cont_ellipse_com_neg    (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether two ellipses are overlapping
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_overlap_ellipse (PG_FUNCTION_ARGS);

  /*!
    \brief Checks, whether two ellipses are not overlapping
    \return boolean datum
    \note PostgreSQL function
  */
  Datum sphereellipse_overlap_ellipse_neg (PG_FUNCTION_ARGS);

  /*!
    \brief transforms an ellipse using Euler transformation
    \return SELLIPSE datum
    \note PostgreSQL function
  */
  Datum spheretrans_ellipse           (PG_FUNCTION_ARGS);

  /*!
    \brief transforms an ellipse using Euler transformation
    \return SELLIPSE datum
    \note PostgreSQL function
  */
  Datum spheretrans_ellipse_inv       (PG_FUNCTION_ARGS);

#endif
