\set ECHO none
SELECT set_sphere_output_precision(8);
SET extra_float_digits TO -2;
\set ECHO all

-- operators
SELECT spoint '(0, 90d)'   = spoint '(0, 90d)';
SELECT spoint '(0, 90d)'   = spoint '(0,-90d)';
SELECT spoint '(0,-90d)'   = spoint '(0,-90d)';
SELECT spoint '(0, 90d)'  != spoint '(0, 90d)';
SELECT spoint '(0, 90d)'  != spoint '(0,-90d)';
SELECT spoint '(0,-90d)'  != spoint '(0,-90d)';
SELECT spoint '(0d,  0)'   = spoint '(360d,0)';

-- I/O test --

-- Output ---

SELECT set_sphere_output( 'DEG' );

SELECT '( 1h 2m 30s , +1d 2m 30s)'::spoint;

SELECT '( 0h 2m 30s , +0d 2m 30s)'::spoint;

SELECT '( 1h 3m 30s , -1d 3m 3.6s)'::spoint;

SELECT '( 0h 3m 30s , -0d 3m 3.6s)'::spoint;

SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s ,-90d 0m 0s)'::spoint;

SELECT set_sphere_output( 'DMS' );

SELECT '( 1h 2m 30s , +1d 2m 30s)'::spoint;

SELECT '( 0h 2m 30s , +0d 2m 30s)'::spoint;

SELECT '( 1h 2m 30s , -1d 2m 30s)'::spoint;

SELECT '( 0h 2m 30s , -0d 2m 30s)'::spoint;

SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s ,-90d 0m 0s)'::spoint;

SELECT set_sphere_output( 'HMS' );

SELECT '( 1h 2m 30s , +1d 2m 30s)'::spoint;

SELECT '( 0h 2m 30s , +0d 2m 30s)'::spoint;

SELECT '( 1h 2m 30s , -1d 2m 30s)'::spoint;

SELECT '( 0h 2m 30s , -0d 2m 30s)'::spoint;

SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s ,-90d 0m 0s)'::spoint;

SELECT set_sphere_output( 'RAD' );

SELECT '( 0h 0m 0s , 0d 0m 0s)'::spoint;

-- "incorrect dec. values"

SELECT set_sphere_output( 'DEG' );

SELECT '( 0h 2m 30s , 95d 0m 0s)'::spoint;

SELECT '( 24h 2m 30s , 5d 0m 0s)'::spoint;

SELECT '( -0h 2m 30s , -5d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s , -95d 0m 0s)'::spoint;

-- Input --

SELECT '( 0.625d , -0.04166666667d)'::spoint;

SELECT '(0.0109083078249646 , -0.000727220521664407)'::spoint;

-- functions for point --------------

-- spoint(float8, float8)

SELECT spoint(0.0109083078249646 , -0.000727220521664407);

SELECT set_sphere_output( 'RAD' );

SELECT spoint(7.28318530717958623 , 0.00);

SELECT spoint(0.0 , 2.141592653589793116);

-- dist(spoint,spoint)

SELECT dist('( 0h 2m 30s , 0d 0m 0s)'::spoint,'( 0h 0m 30s , 0d 0m 0s)'::spoint);

SELECT dist('( 0h 2m 30s , 0d 0m 0s)'::spoint,'( 0h 2m 30s , 10d 0m 0s)'::spoint);

SELECT dist('( 0h 2m 30s , 0d 0m 0s)'::spoint,'( 0h 2m 30s , -10d 0m 0s)'::spoint);

SELECT dist('( 0h 2m 30s , 95d 0m 0s)'::spoint,'( 12h 2m 30s , 85d 0m 0s)'::spoint);

SELECT dist('( 24h 2m 30s , 10d 0m 0s)'::spoint,'( 0h 2m 30s , -10d 0m 0s)'::spoint);

SELECT dist('( 0h 2m 30s , 90d 0m 0s)'::spoint,'( 12h 2m 30s , 90d 0m 0s)'::spoint);

SELECT dist('( 0h 2m 30s , -90d 0m 0s)'::spoint,'( 12h 2m 30s , -90d 0m 0s)'::spoint);

-- long(spoint)

SELECT long('( 0h 2m 30s , 0d 0m 0s)'::spoint);

SELECT long('( 0h 2m 30s ,95d 0m 0s)'::spoint);

SELECT long('( 0h 2m 30s ,85d 0m 0s)'::spoint);

SELECT long('( 0h 2m 30s ,-95d 0m 0s)'::spoint);

SELECT long('( 0h 2m 30s ,-85d 0m 0s)'::spoint);

SELECT long('( 0h 2m 30s ,90d 0m 0s)'::spoint);

SELECT long('( 0h 2m 30s ,-90d 0m 0s)'::spoint);

SELECT long('(24h 2m 30s , 0d 0m 0s)'::spoint);

SELECT long('(24h 2m 30s ,95d 0m 0s)'::spoint);

SELECT long('(24h 2m 30s ,85d 0m 0s)'::spoint);

SELECT long('(24h 2m 30s ,-95d 0m 0s)'::spoint);

SELECT long('(24h 2m 30s ,-85d 0m 0s)'::spoint);

SELECT long('(24h 2m 30s ,90d 0m 0s)'::spoint);

SELECT long('(24h 2m 30s ,-90d 0m 0s)'::spoint);

-- lat(spoint)

SELECT lat('( 0h 2m 30s , 0d 0m 0s)'::spoint);

SELECT lat('( 0h 2m 30s ,95d 0m 0s)'::spoint);

SELECT lat('( 0h 2m 30s ,85d 0m 0s)'::spoint);

SELECT lat('( 0h 2m 30s ,-95d 0m 0s)'::spoint);

SELECT lat('( 0h 2m 30s ,-85d 0m 0s)'::spoint);

SELECT lat('( 0h 2m 30s ,90d 0m 0s)'::spoint);

SELECT lat('( 0h 2m 30s ,-90d 0m 0s)'::spoint);

SELECT lat('(24h 2m 30s , 0d 0m 0s)'::spoint);

SELECT lat('(24h 2m 30s ,95d 0m 0s)'::spoint);

SELECT lat('(24h 2m 30s ,85d 0m 0s)'::spoint);

SELECT lat('(24h 2m 30s ,-95d 0m 0s)'::spoint);

SELECT lat('(24h 2m 30s ,-85d 0m 0s)'::spoint);

SELECT lat('(24h 2m 30s ,90d 0m 0s)'::spoint);

SELECT lat('(24h 2m 30s ,-90d 0m 0s)'::spoint);

-- operators for points -------------

-- = operator -----------------------

SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint='( 12h 2m 30s , 90d 0m 0s)'::spoint;

SELECT '( 12h 2m 30s , 90d 0m 0s)'::spoint='( 12h 2m 30s , 90d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint='( 24h 2m 30s , 90d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s , -90d 0m 0s)'::spoint='( 12h 2m 30s , -90d 0m 0s)'::spoint;

SELECT '( 12h 2m 30s , -90d 0m 0s)'::spoint='( 12h 2m 30s , -90d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s , -90d 0m 0s)'::spoint='( 24h 2m 30s , -90d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s , 95d 0m 0s)'::spoint='( 12h 2m 30s , 85d 0m 0s)'::spoint;

SELECT '( 24h 2m 30s , 10d 0m 0s)'::spoint='( 0h 2m 30s , 10d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint='( 12h 2m 30s , -90d 0m 0s)'::spoint;

SELECT '( 12h 2m 30s , 90d 0m 0s)'::spoint='( 12h 2m 30s , -90d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s , 0d 0m 0s)'::spoint='( 12h 2m 30s , 45d 0m 0s)'::spoint;

-- <> operator -----------------------

SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint<>'( 12h 2m 30s , 90d 0m 0s)'::spoint;

SELECT '( 12h 2m 30s , 90d 0m 0s)'::spoint<>'( 12h 2m 30s , 90d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint<>'( 24h 2m 30s , 90d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s , -90d 0m 0s)'::spoint<>'( 12h 2m 30s , -90d 0m 0s)'::spoint;

SELECT '( 12h 2m 30s , -90d 0m 0s)'::spoint<>'( 12h 2m 30s , -90d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s , -90d 0m 0s)'::spoint<>'( 24h 2m 30s , -90d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s , 95d 0m 0s)'::spoint<>'( 12h 2m 30s , 85d 0m 0s)'::spoint;

SELECT '( 24h 2m 30s , 10d 0m 0s)'::spoint<>'( 0h 2m 30s , 10d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint<>'( 12h 2m 30s , -90d 0m 0s)'::spoint;

SELECT '( 12h 2m 30s , 90d 0m 0s)'::spoint<>'( 12h 2m 30s , -90d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s , 0d 0m 0s)'::spoint<>'( 12h 2m 30s , 45d 0m 0s)'::spoint;

-- <-> operator ---------------------

SELECT '( 0h 2m 30s , 0d 0m 0s)'::spoint<->'( 0h 0m 30s , 0d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s , 0d 0m 0s)'::spoint<->'( 0h 2m 30s , 10d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s , 0d 0m 0s)'::spoint<->'( 0h 2m 30s , -10d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s , 95d 0m 0s)'::spoint<->'( 12h 2m 30s , 85d 0m 0s)'::spoint;

SELECT '( 24h 2m 30s , 10d 0m 0s)'::spoint<->'( 0h 2m 30s , -10d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint<->'( 12h 2m 30s , 90d 0m 0s)'::spoint;

SELECT '( 0h 2m 30s , -90d 0m 0s)'::spoint<->'( 12h 2m 30s , -90d 0m 0s)'::spoint;

