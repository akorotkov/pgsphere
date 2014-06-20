-- checking spherical line operators

SELECT sline ( spoint '(0, 90d)', spoint '(0, -89d)' )   =
       sline ( spoint '(0, 90d)', spoint '(0, -89d)' )  ;
SELECT sline ( spoint '(0,  90d)', spoint '(0, -89d)' )   <>
       sline ( spoint '(0, -89d)', spoint '(0,  90d)' ) ;



SELECT sline ( spoint '(0,   0d)', spoint '(10d, 0d)' )   #
       sline ( spoint '(5d,  5d)', spoint '(5d, -5d)' ) ;

SELECT sline ( spoint '(0,   0d)', spoint '(10d, 0d)' )   #
       sline ( spoint '(10d,  5d)', spoint '(10d, -5d)' ) ;

SELECT sline ( spoint '(0,   0d)', spoint '(10d, 0d)' )   #
       sline ( spoint '(15d,  5d)', spoint '(15d, -5d)' ) ;

SELECT sline ( spoint '(0,   0d)', spoint '(10d, 0d)' )   #
       sline ( spoint '(10d,  0d)', spoint '(10d, -5d)' ) ;



SELECT sline ( spoint '(0,   0d)', spoint '(10d, 0d)' )   #
       sline ( spoint '(5d,  -5d)', spoint '(5d, 5d)' ) ;

SELECT sline ( spoint '(0,   0d)', spoint '(10d, 0d)' )   #
       sline ( spoint '(10d, -5d)', spoint '(10d, 5d)' ) ;

SELECT sline ( spoint '(0,   0d)', spoint '(10d, 0d)' )   #
       sline ( spoint '(15d, -5d)', spoint '(15d, 5d)' ) ;

SELECT sline ( spoint '(0,   0d)', spoint '(10d, 0d)' )   #
       sline ( spoint '(10d,  0d)', spoint '(10d, 5d)' ) ;
       
       
-- check small lines


SELECT sline ( spoint '(0,   0d)', spoint '(0.000001d, 0d)' )   #
       sline ( spoint '(0.0000005d,  0.0000005d)', spoint '(0.0000005d, -0.0000005d)' ) ;

SELECT sline ( spoint '(0,   0d)', spoint '(0.000001d, 0d)' )   #
       sline ( spoint '(0.000001d,  0.0000005d)', spoint '(0.000001d, -0.0000005d)' ) ;

SELECT sline ( spoint '(0,   0d)', spoint '(0.000001d, 0d)' )   #
       sline ( spoint '(0.0000015d,  0.0000005d)', spoint '(0.0000015d, -0.0000005d)' ) ;

SELECT sline ( spoint '(0,   0d)', spoint '(0.000001d, 0d)' )   #
       sline ( spoint '(0.000001d,  0d)', spoint '(0.000001d, -0.0000005d)' ) ;



SELECT sline ( spoint '(0,   0d)', spoint '(0.000001d, 0d)' )   #
       sline ( spoint '(0.0000005d,  -0.0000005d)', spoint '(0.0000005d, 0.0000005d)' ) ;

SELECT sline ( spoint '(0,   0d)', spoint '(0.000001d, 0d)' )   #
       sline ( spoint '(0.000001d, -0.0000005d)', spoint '(0.000001d, 0.0000005d)' ) ;

SELECT sline ( spoint '(0,   0d)', spoint '(0.000001d, 0d)' )   #
       sline ( spoint '(0.0000015d, -0.0000005d)', spoint '(0.0000015d, 0.0000005d)' ) ;

SELECT sline ( spoint '(0,   0d)', spoint '(0.000001d, 0d)' )   #
       sline ( spoint '(0.000001d,  0d)', spoint '(0.000001d, 0.0000005d)' ) ;
       