\echo -- I/O test --
-- I/O test --

\echo 


\echo -- Output ---
-- Output ---

\echo SELECT set_sphere_output( 'DEG' );
SELECT set_sphere_output( 'DEG' );

\echo SELECT '( 1h 2m 30s , +1d 2m 30s)'::spoint;
SELECT '( 1h 2m 30s , +1d 2m 30s)'::spoint;

\echo SELECT '( 0h 2m 30s , +0d 2m 30s)'::spoint;
SELECT '( 0h 2m 30s , +0d 2m 30s)'::spoint;

\echo SELECT '( 1h 2m 30s , -1d 2m 30s)'::spoint;
SELECT '( 1h 2m 30s , -1d 2m 30s)'::spoint;

\echo SELECT '( 0h 2m 30s , -0d 2m 30s)'::spoint;
SELECT '( 0h 2m 30s , -0d 2m 30s)'::spoint;

\echo SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint;

\echo SELECT '( 0h 2m 30s ,-90d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s ,-90d 0m 0s)'::spoint;

\echo SELECT set_sphere_output( 'DMS' );
SELECT set_sphere_output( 'DMS' );

\echo SELECT '( 1h 2m 30s , +1d 2m 30s)'::spoint;
SELECT '( 1h 2m 30s , +1d 2m 30s)'::spoint;

\echo SELECT '( 0h 2m 30s , +0d 2m 30s)'::spoint;
SELECT '( 0h 2m 30s , +0d 2m 30s)'::spoint;

\echo SELECT '( 1h 2m 30s , -1d 2m 30s)'::spoint;
SELECT '( 1h 2m 30s , -1d 2m 30s)'::spoint;

\echo SELECT '( 0h 2m 30s , -0d 2m 30s)'::spoint;
SELECT '( 0h 2m 30s , -0d 2m 30s)'::spoint;

\echo SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint;

\echo SELECT '( 0h 2m 30s ,-90d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s ,-90d 0m 0s)'::spoint;

\echo SELECT set_sphere_output( 'HMS' );
SELECT set_sphere_output( 'HMS' );

\echo SELECT '( 1h 2m 30s , +1d 2m 30s)'::spoint;
SELECT '( 1h 2m 30s , +1d 2m 30s)'::spoint;

\echo SELECT '( 0h 2m 30s , +0d 2m 30s)'::spoint;
SELECT '( 0h 2m 30s , +0d 2m 30s)'::spoint;

\echo SELECT '( 1h 2m 30s , -1d 2m 30s)'::spoint;
SELECT '( 1h 2m 30s , -1d 2m 30s)'::spoint;

\echo SELECT '( 0h 2m 30s , -0d 2m 30s)'::spoint;
SELECT '( 0h 2m 30s , -0d 2m 30s)'::spoint;

\echo SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint;

\echo SELECT '( 0h 2m 30s ,-90d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s ,-90d 0m 0s)'::spoint;

\echo SELECT set_sphere_output( 'RAD' );
SELECT set_sphere_output( 'RAD' );

\echo SELECT '( 1h 2m 30s , +1d 2m 30s)'::spoint;
SELECT '( 1h 2m 30s , +1d 2m 30s)'::spoint;

\echo SELECT '( 0h 2m 30s , +0d 2m 30s)'::spoint;
SELECT '( 0h 2m 30s , +0d 2m 30s)'::spoint;

\echo SELECT '( 1h 2m 30s , -1d 2m 30s)'::spoint;
SELECT '( 1h 2m 30s , -1d 2m 30s)'::spoint;

\echo SELECT '( 0h 2m 30s , -0d 2m 30s)'::spoint;
SELECT '( 0h 2m 30s , -0d 2m 30s)'::spoint;

\echo SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint;

\echo SELECT '( 0h 2m 30s ,-90d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s ,-90d 0m 0s)'::spoint;

\echo 


\echo -- "incorrect dec. values"
-- "incorrect dec. values"

\echo SELECT set_sphere_output( 'DEG' );
SELECT set_sphere_output( 'DEG' );

\echo SELECT '( 0h 2m 30s , 95d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , 95d 0m 0s)'::spoint;

\echo SELECT '( 24h 2m 30s , 5d 0m 0s)'::spoint;
SELECT '( 24h 2m 30s , 5d 0m 0s)'::spoint;

\echo SELECT '( -0h 2m 30s , -5d 0m 0s)'::spoint;
SELECT '( -0h 2m 30s , -5d 0m 0s)'::spoint;

\echo SELECT '( 0h 2m 30s , -95d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , -95d 0m 0s)'::spoint;

\echo 


\echo -- Input --
-- Input --

\echo SELECT '( 0h 2m 30s , -0d 2m 30s)'::spoint;
SELECT '( 0h 2m 30s , -0d 2m 30s)'::spoint;

\echo SELECT '( 0d 37m 30s , -0d 2m 30s)'::spoint;
SELECT '( 0d 37m 30s , -0d 2m 30s)'::spoint;

\echo SELECT '( 0.625d , -0.04166666666666667d)'::spoint;
SELECT '( 0.625d , -0.04166666666666667d)'::spoint;

\echo SELECT '(0.0109083078249646 , -0.000727220521664407)'::spoint;
SELECT '(0.0109083078249646 , -0.000727220521664407)'::spoint;

\echo 


\echo 


\echo -- functions for point --------------
-- functions for point --------------

\echo -- spoint(float8, float8)
-- spoint(float8, float8)

\echo SELECT spoint(0.0109083078249646 , -0.000727220521664407);
SELECT spoint(0.0109083078249646 , -0.000727220521664407);

\echo SELECT set_sphere_output( 'RAD' );
SELECT set_sphere_output( 'RAD' );

\echo SELECT spoint(7.28318530717958623 , 0.00);
SELECT spoint(7.28318530717958623 , 0.00);

\echo SELECT spoint(0.0 , 2.141592653589793116);
SELECT spoint(0.0 , 2.141592653589793116);

\echo 


\echo -- dist(spoint,spoint)
-- dist(spoint,spoint)

\echo SELECT dist('( 0h 2m 30s , 0d 0m 0s)'::spoint,'( 0h 0m 30s , 0d 0m 0s)'::spoint);
SELECT dist('( 0h 2m 30s , 0d 0m 0s)'::spoint,'( 0h 0m 30s , 0d 0m 0s)'::spoint);

\echo SELECT dist('( 0h 2m 30s , 0d 0m 0s)'::spoint,'( 0h 2m 30s , 10d 0m 0s)'::spoint);
SELECT dist('( 0h 2m 30s , 0d 0m 0s)'::spoint,'( 0h 2m 30s , 10d 0m 0s)'::spoint);

\echo SELECT dist('( 0h 2m 30s , 0d 0m 0s)'::spoint,'( 0h 2m 30s , -10d 0m 0s)'::spoint);
SELECT dist('( 0h 2m 30s , 0d 0m 0s)'::spoint,'( 0h 2m 30s , -10d 0m 0s)'::spoint);

\echo SELECT dist('( 0h 2m 30s , 95d 0m 0s)'::spoint,'( 12h 2m 30s , 85d 0m 0s)'::spoint);
SELECT dist('( 0h 2m 30s , 95d 0m 0s)'::spoint,'( 12h 2m 30s , 85d 0m 0s)'::spoint);

\echo SELECT dist('( 24h 2m 30s , 10d 0m 0s)'::spoint,'( 0h 2m 30s , -10d 0m 0s)'::spoint);
SELECT dist('( 24h 2m 30s , 10d 0m 0s)'::spoint,'( 0h 2m 30s , -10d 0m 0s)'::spoint);

\echo SELECT dist('( 0h 2m 30s , 90d 0m 0s)'::spoint,'( 12h 2m 30s , 90d 0m 0s)'::spoint);
SELECT dist('( 0h 2m 30s , 90d 0m 0s)'::spoint,'( 12h 2m 30s , 90d 0m 0s)'::spoint);

\echo SELECT dist('( 0h 2m 30s , -90d 0m 0s)'::spoint,'( 12h 2m 30s , -90d 0m 0s)'::spoint);
SELECT dist('( 0h 2m 30s , -90d 0m 0s)'::spoint,'( 12h 2m 30s , -90d 0m 0s)'::spoint);

\echo 


\echo -- long(spoint)
-- long(spoint)

\echo SELECT long('( 0h 2m 30s , 0d 0m 0s)'::spoint);
SELECT long('( 0h 2m 30s , 0d 0m 0s)'::spoint);

\echo SELECT long('( 0h 2m 30s ,95d 0m 0s)'::spoint);
SELECT long('( 0h 2m 30s ,95d 0m 0s)'::spoint);

\echo SELECT long('( 0h 2m 30s ,85d 0m 0s)'::spoint);
SELECT long('( 0h 2m 30s ,85d 0m 0s)'::spoint);

\echo SELECT long('( 0h 2m 30s ,-95d 0m 0s)'::spoint);
SELECT long('( 0h 2m 30s ,-95d 0m 0s)'::spoint);

\echo SELECT long('( 0h 2m 30s ,-85d 0m 0s)'::spoint);
SELECT long('( 0h 2m 30s ,-85d 0m 0s)'::spoint);

\echo SELECT long('( 0h 2m 30s ,90d 0m 0s)'::spoint);
SELECT long('( 0h 2m 30s ,90d 0m 0s)'::spoint);

\echo SELECT long('( 0h 2m 30s ,-90d 0m 0s)'::spoint);
SELECT long('( 0h 2m 30s ,-90d 0m 0s)'::spoint);

\echo SELECT long('(24h 2m 30s , 0d 0m 0s)'::spoint);
SELECT long('(24h 2m 30s , 0d 0m 0s)'::spoint);

\echo SELECT long('(24h 2m 30s ,95d 0m 0s)'::spoint);
SELECT long('(24h 2m 30s ,95d 0m 0s)'::spoint);

\echo SELECT long('(24h 2m 30s ,85d 0m 0s)'::spoint);
SELECT long('(24h 2m 30s ,85d 0m 0s)'::spoint);

\echo SELECT long('(24h 2m 30s ,-95d 0m 0s)'::spoint);
SELECT long('(24h 2m 30s ,-95d 0m 0s)'::spoint);

\echo SELECT long('(24h 2m 30s ,-85d 0m 0s)'::spoint);
SELECT long('(24h 2m 30s ,-85d 0m 0s)'::spoint);

\echo SELECT long('(24h 2m 30s ,90d 0m 0s)'::spoint);
SELECT long('(24h 2m 30s ,90d 0m 0s)'::spoint);

\echo SELECT long('(24h 2m 30s ,-90d 0m 0s)'::spoint);
SELECT long('(24h 2m 30s ,-90d 0m 0s)'::spoint);

\echo 


\echo -- lat(spoint)
-- lat(spoint)

\echo SELECT lat('( 0h 2m 30s , 0d 0m 0s)'::spoint);
SELECT lat('( 0h 2m 30s , 0d 0m 0s)'::spoint);

\echo SELECT lat('( 0h 2m 30s ,95d 0m 0s)'::spoint);
SELECT lat('( 0h 2m 30s ,95d 0m 0s)'::spoint);

\echo SELECT lat('( 0h 2m 30s ,85d 0m 0s)'::spoint);
SELECT lat('( 0h 2m 30s ,85d 0m 0s)'::spoint);

\echo SELECT lat('( 0h 2m 30s ,-95d 0m 0s)'::spoint);
SELECT lat('( 0h 2m 30s ,-95d 0m 0s)'::spoint);

\echo SELECT lat('( 0h 2m 30s ,-85d 0m 0s)'::spoint);
SELECT lat('( 0h 2m 30s ,-85d 0m 0s)'::spoint);

\echo SELECT lat('( 0h 2m 30s ,90d 0m 0s)'::spoint);
SELECT lat('( 0h 2m 30s ,90d 0m 0s)'::spoint);

\echo SELECT lat('( 0h 2m 30s ,-90d 0m 0s)'::spoint);
SELECT lat('( 0h 2m 30s ,-90d 0m 0s)'::spoint);

\echo SELECT lat('(24h 2m 30s , 0d 0m 0s)'::spoint);
SELECT lat('(24h 2m 30s , 0d 0m 0s)'::spoint);

\echo SELECT lat('(24h 2m 30s ,95d 0m 0s)'::spoint);
SELECT lat('(24h 2m 30s ,95d 0m 0s)'::spoint);

\echo SELECT lat('(24h 2m 30s ,85d 0m 0s)'::spoint);
SELECT lat('(24h 2m 30s ,85d 0m 0s)'::spoint);

\echo SELECT lat('(24h 2m 30s ,-95d 0m 0s)'::spoint);
SELECT lat('(24h 2m 30s ,-95d 0m 0s)'::spoint);

\echo SELECT lat('(24h 2m 30s ,-85d 0m 0s)'::spoint);
SELECT lat('(24h 2m 30s ,-85d 0m 0s)'::spoint);

\echo SELECT lat('(24h 2m 30s ,90d 0m 0s)'::spoint);
SELECT lat('(24h 2m 30s ,90d 0m 0s)'::spoint);

\echo SELECT lat('(24h 2m 30s ,-90d 0m 0s)'::spoint);
SELECT lat('(24h 2m 30s ,-90d 0m 0s)'::spoint);

\echo 


\echo -- operators for points -------------
-- operators for points -------------

\echo -- = operator -----------------------
-- = operator -----------------------

\echo SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint='( 12h 2m 30s , 90d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint='( 12h 2m 30s , 90d 0m 0s)'::spoint;

\echo SELECT '( 12h 2m 30s , 90d 0m 0s)'::spoint='( 12h 2m 30s , 90d 0m 0s)'::spoint;
SELECT '( 12h 2m 30s , 90d 0m 0s)'::spoint='( 12h 2m 30s , 90d 0m 0s)'::spoint;

\echo SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint='( 24h 2m 30s , 90d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint='( 24h 2m 30s , 90d 0m 0s)'::spoint;

\echo SELECT '( 0h 2m 30s , -90d 0m 0s)'::spoint='( 12h 2m 30s , -90d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , -90d 0m 0s)'::spoint='( 12h 2m 30s , -90d 0m 0s)'::spoint;

\echo SELECT '( 12h 2m 30s , -90d 0m 0s)'::spoint='( 12h 2m 30s , -90d 0m 0s)'::spoint;
SELECT '( 12h 2m 30s , -90d 0m 0s)'::spoint='( 12h 2m 30s , -90d 0m 0s)'::spoint;

\echo SELECT '( 0h 2m 30s , -90d 0m 0s)'::spoint='( 24h 2m 30s , -90d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , -90d 0m 0s)'::spoint='( 24h 2m 30s , -90d 0m 0s)'::spoint;

\echo SELECT '( 0h 2m 30s , 95d 0m 0s)'::spoint='( 12h 2m 30s , 85d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , 95d 0m 0s)'::spoint='( 12h 2m 30s , 85d 0m 0s)'::spoint;

\echo SELECT '( 24h 2m 30s , 10d 0m 0s)'::spoint='( 0h 2m 30s , 10d 0m 0s)'::spoint;
SELECT '( 24h 2m 30s , 10d 0m 0s)'::spoint='( 0h 2m 30s , 10d 0m 0s)'::spoint;

\echo 


\echo SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint='( 12h 2m 30s , -90d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint='( 12h 2m 30s , -90d 0m 0s)'::spoint;

\echo SELECT '( 12h 2m 30s , 90d 0m 0s)'::spoint='( 12h 2m 30s , -90d 0m 0s)'::spoint;
SELECT '( 12h 2m 30s , 90d 0m 0s)'::spoint='( 12h 2m 30s , -90d 0m 0s)'::spoint;

\echo SELECT '( 0h 2m 30s , 0d 0m 0s)'::spoint='( 12h 2m 30s , 45d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , 0d 0m 0s)'::spoint='( 12h 2m 30s , 45d 0m 0s)'::spoint;

\echo 


\echo -- <> operator -----------------------
-- <> operator -----------------------

\echo SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint<>'( 12h 2m 30s , 90d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint<>'( 12h 2m 30s , 90d 0m 0s)'::spoint;

\echo SELECT '( 12h 2m 30s , 90d 0m 0s)'::spoint<>'( 12h 2m 30s , 90d 0m 0s)'::spoint;
SELECT '( 12h 2m 30s , 90d 0m 0s)'::spoint<>'( 12h 2m 30s , 90d 0m 0s)'::spoint;

\echo SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint<>'( 24h 2m 30s , 90d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint<>'( 24h 2m 30s , 90d 0m 0s)'::spoint;

\echo SELECT '( 0h 2m 30s , -90d 0m 0s)'::spoint<>'( 12h 2m 30s , -90d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , -90d 0m 0s)'::spoint<>'( 12h 2m 30s , -90d 0m 0s)'::spoint;

\echo SELECT '( 12h 2m 30s , -90d 0m 0s)'::spoint<>'( 12h 2m 30s , -90d 0m 0s)'::spoint;
SELECT '( 12h 2m 30s , -90d 0m 0s)'::spoint<>'( 12h 2m 30s , -90d 0m 0s)'::spoint;

\echo SELECT '( 0h 2m 30s , -90d 0m 0s)'::spoint<>'( 24h 2m 30s , -90d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , -90d 0m 0s)'::spoint<>'( 24h 2m 30s , -90d 0m 0s)'::spoint;

\echo SELECT '( 0h 2m 30s , 95d 0m 0s)'::spoint<>'( 12h 2m 30s , 85d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , 95d 0m 0s)'::spoint<>'( 12h 2m 30s , 85d 0m 0s)'::spoint;

\echo SELECT '( 24h 2m 30s , 10d 0m 0s)'::spoint<>'( 0h 2m 30s , 10d 0m 0s)'::spoint;
SELECT '( 24h 2m 30s , 10d 0m 0s)'::spoint<>'( 0h 2m 30s , 10d 0m 0s)'::spoint;

\echo --
--

\echo SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint<>'( 12h 2m 30s , -90d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint<>'( 12h 2m 30s , -90d 0m 0s)'::spoint;

\echo SELECT '( 12h 2m 30s , 90d 0m 0s)'::spoint<>'( 12h 2m 30s , -90d 0m 0s)'::spoint;
SELECT '( 12h 2m 30s , 90d 0m 0s)'::spoint<>'( 12h 2m 30s , -90d 0m 0s)'::spoint;

\echo SELECT '( 0h 2m 30s , 0d 0m 0s)'::spoint<>'( 12h 2m 30s , 45d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , 0d 0m 0s)'::spoint<>'( 12h 2m 30s , 45d 0m 0s)'::spoint;

\echo 


\echo -- <-> operator ---------------------
-- <-> operator ---------------------

\echo SELECT '( 0h 2m 30s , 0d 0m 0s)'::spoint<->'( 0h 0m 30s , 0d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , 0d 0m 0s)'::spoint<->'( 0h 0m 30s , 0d 0m 0s)'::spoint;

\echo SELECT '( 0h 2m 30s , 0d 0m 0s)'::spoint<->'( 0h 2m 30s , 10d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , 0d 0m 0s)'::spoint<->'( 0h 2m 30s , 10d 0m 0s)'::spoint;

\echo SELECT '( 0h 2m 30s , 0d 0m 0s)'::spoint<->'( 0h 2m 30s , -10d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , 0d 0m 0s)'::spoint<->'( 0h 2m 30s , -10d 0m 0s)'::spoint;

\echo SELECT '( 0h 2m 30s , 95d 0m 0s)'::spoint<->'( 12h 2m 30s , 85d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , 95d 0m 0s)'::spoint<->'( 12h 2m 30s , 85d 0m 0s)'::spoint;

\echo SELECT '( 24h 2m 30s , 10d 0m 0s)'::spoint<->'( 0h 2m 30s , -10d 0m 0s)'::spoint;
SELECT '( 24h 2m 30s , 10d 0m 0s)'::spoint<->'( 0h 2m 30s , -10d 0m 0s)'::spoint;

\echo SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint<->'( 12h 2m 30s , 90d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , 90d 0m 0s)'::spoint<->'( 12h 2m 30s , 90d 0m 0s)'::spoint;

\echo SELECT '( 0h 2m 30s , -90d 0m 0s)'::spoint<->'( 12h 2m 30s , -90d 0m 0s)'::spoint;
SELECT '( 0h 2m 30s , -90d 0m 0s)'::spoint<->'( 12h 2m 30s , -90d 0m 0s)'::spoint;

