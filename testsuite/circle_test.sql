\echo -- Input/Output ---
-- Input/Output ---

\echo SELECT set_sphere_output( 'RAD' );
SELECT set_sphere_output( 'RAD' );

\echo SELECT '< (1h 2m 30s , +1d 2m 30s), 1.0d >'::scircle;
SELECT '< (1h 2m 30s , +1d 2m 30s), 1.0d >'::scircle;

\echo SELECT '< (1h 2m 30s , +1d 2m 30s), 1d 30m >'::scircle;
SELECT '< (1h 2m 30s , +1d 2m 30s), 1d 30m >'::scircle;

\echo SELECT '< (1h 2m 30s , +1d 2m 30s), 0.1 >'::scircle;
SELECT '< (1h 2m 30s , +1d 2m 30s), 0.1 >'::scircle;

\echo SELECT '< (1h 2m 30s , +1d 2m 30s), 90d >'::scircle;
SELECT '< (1h 2m 30s , +1d 2m 30s), 90d >'::scircle;

\echo SELECT set_sphere_output( 'DEG' );
SELECT set_sphere_output( 'DEG' );

\echo SELECT '< (1h 2m 30s , +1d 2m 30s), 1.0d >'::scircle;
SELECT '< (1h 2m 30s , +1d 2m 30s), 1.0d >'::scircle;

\echo SELECT '< (1h 2m 30s , +1d 2m 30s), 1d 30m >'::scircle;
SELECT '< (1h 2m 30s , +1d 2m 30s), 1d 30m >'::scircle;

\echo SELECT '< (1h 2m 30s , +1d 2m 30s), 0.1 >'::scircle;
SELECT '< (1h 2m 30s , +1d 2m 30s), 0.1 >'::scircle;

\echo SELECT '< (1h 2m 30s , +1d 2m 30s), 90d >'::scircle;
SELECT '< (1h 2m 30s , +1d 2m 30s), 90d >'::scircle;

\echo SELECT set_sphere_output( 'DMS' );
SELECT set_sphere_output( 'DMS' );

\echo SELECT '< (1h 2m 30s , +1d 2m 30s), 1.0d >'::scircle;
SELECT '< (1h 2m 30s , +1d 2m 30s), 1.0d >'::scircle;

\echo SELECT '< (1h 2m 30s , +1d 2m 30s), 1d 30m >'::scircle;
SELECT '< (1h 2m 30s , +1d 2m 30s), 1d 30m >'::scircle;

\echo SELECT '< (1h 2m 30s , +1d 2m 30s), 0.1 >'::scircle;
SELECT '< (1h 2m 30s , +1d 2m 30s), 0.1 >'::scircle;

\echo SELECT '< (1h 2m 30s , +1d 2m 30s), 90d >'::scircle;
SELECT '< (1h 2m 30s , +1d 2m 30s), 90d >'::scircle;

\echo SELECT set_sphere_output( 'HMS' );
SELECT set_sphere_output( 'HMS' );

\echo SELECT '< (1h 2m 30s , +1d 2m 30s), 1.0d >'::scircle;
SELECT '< (1h 2m 30s , +1d 2m 30s), 1.0d >'::scircle;

\echo SELECT '< (1h 2m 30s , +1d 2m 30s), 1d 30m >'::scircle;
SELECT '< (1h 2m 30s , +1d 2m 30s), 1d 30m >'::scircle;

\echo SELECT '< (1h 2m 30s , +1d 2m 30s), 0.1 >'::scircle;
SELECT '< (1h 2m 30s , +1d 2m 30s), 0.1 >'::scircle;

\echo SELECT '< (1h 2m 30s , +1d 2m 30s), 90d >'::scircle;
SELECT '< (1h 2m 30s , +1d 2m 30s), 90d >'::scircle;

\echo SELECT set_sphere_output( 'DMS' );
SELECT set_sphere_output( 'DMS' );

\echo 


\echo -- Functions
-- Functions

\echo 


\echo -- float8 dist(scircle,scircle)
-- float8 dist(scircle,scircle)

\echo SELECT 180.0*dist('<( 0h 2m 30s , 10d 0m 0s), 0.1d>'::scircle,'<( 0h 2m 30s , -10d 0m 0s),0.1d>'::scircle)/pi();
SELECT 180.0*dist('<( 0h 2m 30s , 10d 0m 0s), 0.1d>'::scircle,'<( 0h 2m 30s , -10d 0m 0s),0.1d>'::scircle)/pi();

\echo SELECT 180.0*dist('<( 0h 0m 00s , 0d 0m 0s), 1.0d>'::scircle,'<( 1h 0m 00s , 0d 0m 0s),1.0d>'::scircle)/pi();
SELECT 180.0*dist('<( 0h 0m 00s , 0d 0m 0s), 1.0d>'::scircle,'<( 1h 0m 00s , 0d 0m 0s),1.0d>'::scircle)/pi();

\echo SELECT 180.0*dist('<( 23h 30m 00s , 0d 0m 0s), 1.0d>'::scircle,'<( 1h 0m 00s , 0d 0m 0s),1.5d>'::scircle)/pi();
SELECT 180.0*dist('<( 23h 30m 00s , 0d 0m 0s), 1.0d>'::scircle,'<( 1h 0m 00s , 0d 0m 0s),1.5d>'::scircle)/pi();

\echo SELECT 180.0*dist('<( 0h 40m 00s , 0d 0m 0s), 1.0d>'::scircle,'<( 0h 50m 00s , 0d 0m 0s),1.0d>'::scircle)/pi();
SELECT 180.0*dist('<( 0h 40m 00s , 0d 0m 0s), 1.0d>'::scircle,'<( 0h 50m 00s , 0d 0m 0s),1.0d>'::scircle)/pi();

\echo SELECT 180.0*dist('<( 0h 40m 00s , 0d 0m 0s), 1.5d>'::scircle,'<( 0h 50m 00s , 0d 0m 0s),1.5d>'::scircle)/pi();
SELECT 180.0*dist('<( 0h 40m 00s , 0d 0m 0s), 1.5d>'::scircle,'<( 0h 50m 00s , 0d 0m 0s),1.5d>'::scircle)/pi();

\echo SELECT 180.0*dist('<( 0h 40m 00s , 90d 0m 0s), 1.5d>'::scircle,'<( 0h 50m 00s , 0d 0m 0s),1.5d>'::scircle)/pi();
SELECT 180.0*dist('<( 0h 40m 00s , 90d 0m 0s), 1.5d>'::scircle,'<( 0h 50m 00s , 0d 0m 0s),1.5d>'::scircle)/pi();

\echo SELECT 180.0*dist('<( 0h 40m 00s , 90d 0m 0s), 1.0d>'::scircle,'<( 0h 50m 00s , -90d 0m 0s),1.0d>'::scircle)/pi();
SELECT 180.0*dist('<( 0h 40m 00s , 90d 0m 0s), 1.0d>'::scircle,'<( 0h 50m 00s , -90d 0m 0s),1.0d>'::scircle)/pi();

\echo 


\echo -- spoint spoint(scircle)
-- spoint spoint(scircle)

\echo SELECT spoint('< (1h 2m 30s , +1d 2m 30s), 1.0d >'::scircle);
SELECT spoint('< (1h 2m 30s , +1d 2m 30s), 1.0d >'::scircle);

\echo SELECT spoint('< (1h 2m 30s , +90d 0m 0s), 1.0d >'::scircle);
SELECT spoint('< (1h 2m 30s , +90d 0m 0s), 1.0d >'::scircle);

\echo 


\echo -- scircle scircle(spoint)
-- scircle scircle(spoint)

\echo SELECT scircle('(0d,0d)'::spoint);
SELECT scircle('(0d,0d)'::spoint);

\echo SELECT scircle('(0d,90d)'::spoint);
SELECT scircle('(0d,90d)'::spoint);

\echo SELECT scircle('(0d,-90d)'::spoint);
SELECT scircle('(0d,-90d)'::spoint);

\echo 


\echo -- Operators
-- Operators

\echo -- = operator
-- = operator

\echo -- should be "true"
-- should be "true"

\echo SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle='< (1h 0m 0s,+1d), 1.5d >'::scircle ;
SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle='< (1h 0m 0s,+1d), 1.5d >'::scircle ;

\echo SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle='< (25h 0m 0s,+1d), 1d 30m >'::scircle ;
SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle='< (25h 0m 0s,+1d), 1d 30m >'::scircle ;

\echo SELECT '< (1h 0m 0s,+95d), 1.5d >'::scircle='< (13h 0m 0s,+85d), 1.5d >'::scircle ;
SELECT '< (1h 0m 0s,+95d), 1.5d >'::scircle='< (13h 0m 0s,+85d), 1.5d >'::scircle ;

\echo SELECT '< (1h 0m 0s,-95d), 1.5d >'::scircle='< (13h 0m 0s,-85d), 1.5d >'::scircle ;
SELECT '< (1h 0m 0s,-95d), 1.5d >'::scircle='< (13h 0m 0s,-85d), 1.5d >'::scircle ;

\echo SELECT '< (1h 0m 0s,+90d), 1.5d >'::scircle='< (2h 0m 0s,+90d), 1.5d >'::scircle ;
SELECT '< (1h 0m 0s,+90d), 1.5d >'::scircle='< (2h 0m 0s,+90d), 1.5d >'::scircle ;

\echo SELECT '< (1h 0m 0s,-90d), 1.5d >'::scircle='< (2h 0m 0s,-90d), 1.5d >'::scircle ;
SELECT '< (1h 0m 0s,-90d), 1.5d >'::scircle='< (2h 0m 0s,-90d), 1.5d >'::scircle ;

\echo -- should be "false"
-- should be "false"

\echo SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle='< (1h 0m 0s,-1d), 1.5d >'::scircle ;
SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle='< (1h 0m 0s,-1d), 1.5d >'::scircle ;

\echo SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle='< (1h 0m 0s,+1d), 2.5d >'::scircle ;
SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle='< (1h 0m 0s,+1d), 2.5d >'::scircle ;

\echo 


\echo -- <> operator
-- <> operator

\echo -- should be "false"
-- should be "false"

\echo SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle <> '< (1h 0m 0s,+1d), 1.5d >'::scircle ;
SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle <> '< (1h 0m 0s,+1d), 1.5d >'::scircle ;

\echo SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle <> '< (25h 0m 0s,+1d), 1d 30m >'::scircle ;
SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle <> '< (25h 0m 0s,+1d), 1d 30m >'::scircle ;

\echo SELECT '< (1h 0m 0s,+95d), 1.5d >'::scircle <> '< (13h 0m 0s,+85d), 1.5d >'::scircle ;
SELECT '< (1h 0m 0s,+95d), 1.5d >'::scircle <> '< (13h 0m 0s,+85d), 1.5d >'::scircle ;

\echo SELECT '< (1h 0m 0s,-95d), 1.5d >'::scircle <> '< (13h 0m 0s,-85d), 1.5d >'::scircle ;
SELECT '< (1h 0m 0s,-95d), 1.5d >'::scircle <> '< (13h 0m 0s,-85d), 1.5d >'::scircle ;

\echo SELECT '< (1h 0m 0s,+90d), 1.5d >'::scircle <> '< (2h 0m 0s,+90d), 1.5d >'::scircle ;
SELECT '< (1h 0m 0s,+90d), 1.5d >'::scircle <> '< (2h 0m 0s,+90d), 1.5d >'::scircle ;

\echo SELECT '< (1h 0m 0s,-90d), 1.5d >'::scircle <> '< (2h 0m 0s,-90d), 1.5d >'::scircle ;
SELECT '< (1h 0m 0s,-90d), 1.5d >'::scircle <> '< (2h 0m 0s,-90d), 1.5d >'::scircle ;

\echo -- should be "true"
-- should be "true"

\echo SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle <> '< (1h 0m 0s,-1d), 1.5d >'::scircle ;
SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle <> '< (1h 0m 0s,-1d), 1.5d >'::scircle ;

\echo SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle <> '< (1h 0m 0s,+1d), 2.5d >'::scircle ;
SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle <> '< (1h 0m 0s,+1d), 2.5d >'::scircle ;

\echo 


\echo -- && operator
-- && operator

\echo -- should be "true"
-- should be "true"

\echo SELECT  '< (1h 0m 0s,+1d), 1.5d >'::scircle && '< (1h 0m 0s,+1d), 1.5d >'::scircle;
SELECT  '< (1h 0m 0s,+1d), 1.5d >'::scircle && '< (1h 0m 0s,+1d), 1.5d >'::scircle;

\echo SELECT  '< (1h 0m 0s,+1d), 1.5d >'::scircle && '< (1h 0m 0s,+1d), 0.5d >'::scircle;
SELECT  '< (1h 0m 0s,+1d), 1.5d >'::scircle && '< (1h 0m 0s,+1d), 0.5d >'::scircle;

\echo SELECT  '< (1h 0m 0s,+1d), 1.5d >'::scircle && '< (1h 0m 0s,-1d), 1.5d >'::scircle;
SELECT  '< (1h 0m 0s,+1d), 1.5d >'::scircle && '< (1h 0m 0s,-1d), 1.5d >'::scircle;

\echo SELECT  '< (1h 0m 0s,0d), 15d >'::scircle && '< (0h 0m 0s,0d), 15d >'::scircle;
SELECT  '< (1h 0m 0s,0d), 15d >'::scircle && '< (0h 0m 0s,0d), 15d >'::scircle;

\echo SELECT  '< (2h 0m 0s,0d), 15d >'::scircle && '< (0h 0m 0.1s,0d), 15d >'::scircle;
SELECT  '< (2h 0m 0s,0d), 15d >'::scircle && '< (0h 0m 0.1s,0d), 15d >'::scircle;

\echo SELECT  '< (1h 0m 0s,0d), 15d >'::scircle && '< (23h 0m 0.1s,0d), 15d >'::scircle;
SELECT  '< (1h 0m 0s,0d), 15d >'::scircle && '< (23h 0m 0.1s,0d), 15d >'::scircle;

\echo -- should be "false"
-- should be "false"

\echo SELECT  '< (1h 0m 0s,+1d), 0.5d >'::scircle && '< (1h 0m 0s,-1d), 0.5d >'::scircle;
SELECT  '< (1h 0m 0s,+1d), 0.5d >'::scircle && '< (1h 0m 0s,-1d), 0.5d >'::scircle;

\echo SELECT  '< (1d 0m 0s,+1d), 1.0d >'::scircle && '< (0d 0m 0s,0d), 0.1d >'::scircle;
SELECT  '< (1d 0m 0s,+1d), 1.0d >'::scircle && '< (0d 0m 0s,0d), 0.1d >'::scircle;

\echo 


\echo -- @@ operator
-- @@ operator

\echo SELECT @@ '< (1h 2m 3s , +1d 2m 3s), 1.0d >'::scircle;
SELECT @@ '< (1h 2m 3s , +1d 2m 3s), 1.0d >'::scircle;

\echo SELECT @@ '< (1h 2m 3s , +90d 0m 0s), 1.0d >'::scircle;
SELECT @@ '< (1h 2m 3s , +90d 0m 0s), 1.0d >'::scircle;

\echo 


\echo -- <-> operator
-- <-> operator

\echo SELECT 180.0*('<( 0h 2m 30s , 10d 0m 0s), 0.1d>'::scircle<->'<( 0h 2m 30s , -10d 0m 0s),0.1d>'::scircle)/pi();
SELECT 180.0*('<( 0h 2m 30s , 10d 0m 0s), 0.1d>'::scircle<->'<( 0h 2m 30s , -10d 0m 0s),0.1d>'::scircle)/pi();

\echo SELECT 180.0*('<( 0h 0m 00s , 0d 0m 0s), 1.0d>'::scircle<->'<( 1h 0m 00s , 0d 0m 0s),1.0d>'::scircle)/pi();
SELECT 180.0*('<( 0h 0m 00s , 0d 0m 0s), 1.0d>'::scircle<->'<( 1h 0m 00s , 0d 0m 0s),1.0d>'::scircle)/pi();

\echo SELECT 180.0*('<( 23h 30m 00s , 0d 0m 0s), 1.0d>'::scircle<->'<( 1h 0m 00s , 0d 0m 0s),1.5d>'::scircle)/pi();
SELECT 180.0*('<( 23h 30m 00s , 0d 0m 0s), 1.0d>'::scircle<->'<( 1h 0m 00s , 0d 0m 0s),1.5d>'::scircle)/pi();

\echo SELECT 180.0*('<( 0h 40m 00s , 0d 0m 0s), 1.0d>'::scircle<->'<( 0h 50m 00s , 0d 0m 0s),1.0d>'::scircle)/pi();
SELECT 180.0*('<( 0h 40m 00s , 0d 0m 0s), 1.0d>'::scircle<->'<( 0h 50m 00s , 0d 0m 0s),1.0d>'::scircle)/pi();

\echo SELECT 180.0*('<( 0h 40m 00s , 0d 0m 0s), 1.5d>'::scircle<->'<( 0h 50m 00s , 0d 0m 0s),1.5d>'::scircle)/pi();
SELECT 180.0*('<( 0h 40m 00s , 0d 0m 0s), 1.5d>'::scircle<->'<( 0h 50m 00s , 0d 0m 0s),1.5d>'::scircle)/pi();

\echo SELECT 180.0*('<( 0h 40m 00s , 90d 0m 0s), 1.5d>'::scircle<->'<( 0h 50m 00s , 0d 0m 0s),1.5d>'::scircle)/pi();
SELECT 180.0*('<( 0h 40m 00s , 90d 0m 0s), 1.5d>'::scircle<->'<( 0h 50m 00s , 0d 0m 0s),1.5d>'::scircle)/pi();

\echo SELECT 180.0*('<( 0h 40m 00s , 90d 0m 0s), 1.0d>'::scircle<->'<( 0h 50m 00s , -90d 0m 0s),1.0d>'::scircle)/pi();
SELECT 180.0*('<( 0h 40m 00s , 90d 0m 0s), 1.0d>'::scircle<->'<( 0h 50m 00s , -90d 0m 0s),1.0d>'::scircle)/pi();

\echo 


\echo -- scircle @ scircle operator
-- scircle @ scircle operator

\echo -- should be "true"
-- should be "true"

\echo SELECT  '< (1h 0m 0s,+1d),  0.5d >'::scircle @ '< (1h 0m 0s,+1d),  1.5d >'::scircle;
SELECT  '< (1h 0m 0s,+1d),  0.5d >'::scircle @ '< (1h 0m 0s,+1d),  1.5d >'::scircle;

\echo SELECT  '< (2d 0m 0s,+1d),  0.5d >'::scircle @ '< (1d 0m 0s,0d),   3.5d >'::scircle;
SELECT  '< (2d 0m 0s,+1d),  0.5d >'::scircle @ '< (1d 0m 0s,0d),   3.5d >'::scircle;

\echo SELECT  '< (1h 0m 0s,+89d), 0.5d >'::scircle @ '< (1h 0m 0s,+90d), 1.5d >'::scircle;
SELECT  '< (1h 0m 0s,+89d), 0.5d >'::scircle @ '< (1h 0m 0s,+90d), 1.5d >'::scircle;

\echo SELECT  '< (1h 0m 0s,-89d), 0.5d >'::scircle @ '< (1h 0m 0s,-90d), 1.5d >'::scircle;
SELECT  '< (1h 0m 0s,-89d), 0.5d >'::scircle @ '< (1h 0m 0s,-90d), 1.5d >'::scircle;

\echo -- should be "false"
-- should be "false"

\echo SELECT  '< (1h 0m 0s,+1d),  0.5d >'::scircle @ '< (2h 0m 0s,+1d),  1.5d >'::scircle;
SELECT  '< (1h 0m 0s,+1d),  0.5d >'::scircle @ '< (2h 0m 0s,+1d),  1.5d >'::scircle;

\echo SELECT  '< (2d 0m 0s,+1d),  1.5d >'::scircle @ '< (0d 0m 0s, 0d),  3.5d >'::scircle;
SELECT  '< (2d 0m 0s,+1d),  1.5d >'::scircle @ '< (0d 0m 0s, 0d),  3.5d >'::scircle;

\echo SELECT  '< (1h 0m 0s,+89d), 0.5d >'::scircle @ '< (1h 0m 0s,+90d), 1.0d >'::scircle;
SELECT  '< (1h 0m 0s,+89d), 0.5d >'::scircle @ '< (1h 0m 0s,+90d), 1.0d >'::scircle;

\echo SELECT  '< (1h 0m 0s,-89d), 0.5d >'::scircle @ '< (1h 0m 0s,-90d), 1.0d >'::scircle;
SELECT  '< (1h 0m 0s,-89d), 0.5d >'::scircle @ '< (1h 0m 0s,-90d), 1.0d >'::scircle;

\echo 


\echo -- scircle ~ scircle operator
-- scircle ~ scircle operator

\echo -- should be "true"
-- should be "true"

\echo SELECT '< (1h 0m 0s,+1d),  1.5d >'::scircle  ~ '< (1h 0m 0s,+1d),  0.5d >'::scircle;
SELECT '< (1h 0m 0s,+1d),  1.5d >'::scircle  ~ '< (1h 0m 0s,+1d),  0.5d >'::scircle;

\echo SELECT '< (1d 0m 0s,0d),   3.5d >'::scircle  ~ '< (2d 0m 0s,+1d),  0.5d >'::scircle;
SELECT '< (1d 0m 0s,0d),   3.5d >'::scircle  ~ '< (2d 0m 0s,+1d),  0.5d >'::scircle;

\echo SELECT '< (1h 0m 0s,+90d), 1.5d >'::scircle  ~ '< (1h 0m 0s,+89d), 0.5d >'::scircle;
SELECT '< (1h 0m 0s,+90d), 1.5d >'::scircle  ~ '< (1h 0m 0s,+89d), 0.5d >'::scircle;

\echo SELECT '< (1h 0m 0s,-90d), 1.5d >'::scircle  ~ '< (1h 0m 0s,-89d), 0.5d >'::scircle;
SELECT '< (1h 0m 0s,-90d), 1.5d >'::scircle  ~ '< (1h 0m 0s,-89d), 0.5d >'::scircle;

\echo -- should be "false"
-- should be "false"

\echo SELECT '< (2h 0m 0s,+1d),  1.5d >'::scircle  ~ '< (1h 0m 0s,+1d),  0.5d >'::scircle;
SELECT '< (2h 0m 0s,+1d),  1.5d >'::scircle  ~ '< (1h 0m 0s,+1d),  0.5d >'::scircle;

\echo SELECT '< (0d 0m 0s, 0d),  3.5d >'::scircle  ~ '< (2d 0m 0s,+1d),  1.5d >'::scircle;
SELECT '< (0d 0m 0s, 0d),  3.5d >'::scircle  ~ '< (2d 0m 0s,+1d),  1.5d >'::scircle;

\echo SELECT '< (1h 0m 0s,+90d), 1.0d >'::scircle  ~ '< (1h 0m 0s,+89d), 0.5d >'::scircle;
SELECT '< (1h 0m 0s,+90d), 1.0d >'::scircle  ~ '< (1h 0m 0s,+89d), 0.5d >'::scircle;

\echo SELECT '< (1h 0m 0s,-90d), 1.0d >'::scircle  ~ '< (1h 0m 0s,-89d), 0.5d >'::scircle;
SELECT '< (1h 0m 0s,-90d), 1.0d >'::scircle  ~ '< (1h 0m 0s,-89d), 0.5d >'::scircle;

\echo 


\echo -- spoint @ scircle operator
-- spoint @ scircle operator

\echo -- should be "true"
-- should be "true"

\echo SELECT  '(1h 0m 0s,+1d) '::spoint @ '< (1h 0m 0s,+1d),  1.5d >'::scircle;
SELECT  '(1h 0m 0s,+1d) '::spoint @ '< (1h 0m 0s,+1d),  1.5d >'::scircle;

\echo SELECT  '(2d 0m 0s,+1d) '::spoint @ '< (1d 0m 0s, 0d),  3.5d >'::scircle;
SELECT  '(2d 0m 0s,+1d) '::spoint @ '< (1d 0m 0s, 0d),  3.5d >'::scircle;

\echo SELECT  '(1h 0m 0s,+89d)'::spoint @ '< (1h 0m 0s,+90d), 1.5d >'::scircle;
SELECT  '(1h 0m 0s,+89d)'::spoint @ '< (1h 0m 0s,+90d), 1.5d >'::scircle;

\echo SELECT  '(1h 0m 0s,-89d)'::spoint @ '< (1h 0m 0s,-90d), 1.5d >'::scircle;
SELECT  '(1h 0m 0s,-89d)'::spoint @ '< (1h 0m 0s,-90d), 1.5d >'::scircle;

\echo SELECT  '(1h 0m 0s,+89d)'::spoint @ '< (1h 0m 0s,+90d), 1.0d >'::scircle;
SELECT  '(1h 0m 0s,+89d)'::spoint @ '< (1h 0m 0s,+90d), 1.0d >'::scircle;

\echo SELECT  '(1h 0m 0s,-89d)'::spoint @ '< (1h 0m 0s,-90d), 1.0d >'::scircle;
SELECT  '(1h 0m 0s,-89d)'::spoint @ '< (1h 0m 0s,-90d), 1.0d >'::scircle;

\echo -- should be "false"
-- should be "false"

\echo SELECT  '(1h 0m  0s,+1d    )'::spoint @ '< (2h 0m 0s,-1d),  1.5d >'::scircle;
SELECT  '(1h 0m  0s,+1d    )'::spoint @ '< (2h 0m 0s,-1d),  1.5d >'::scircle;

\echo SELECT  '(3d 30m 0s,+1d    )'::spoint @ '< (0d 0m 0s, 0d),  3.5d >'::scircle;
SELECT  '(3d 30m 0s,+1d    )'::spoint @ '< (0d 0m 0s, 0d),  3.5d >'::scircle;

\echo SELECT  '(1h 0m  0s,+88.99d)'::spoint @ '< (1h 0m 0s,+90d), 1.0d >'::scircle;
SELECT  '(1h 0m  0s,+88.99d)'::spoint @ '< (1h 0m 0s,+90d), 1.0d >'::scircle;

\echo SELECT  '(1h 0m  0s,-88.99d)'::spoint @ '< (1h 0m 0s,-90d), 1.0d >'::scircle;
SELECT  '(1h 0m  0s,-88.99d)'::spoint @ '< (1h 0m 0s,-90d), 1.0d >'::scircle;

\echo 


\echo -- spoint ~ scircle operator
-- spoint ~ scircle operator

\echo -- should be "true"
-- should be "true"

\echo SELECT '< (1h 0m 0s,+1d),  1.5d >'::scircle ~ '(1h 0m 0s,+1d) '::spoint;
SELECT '< (1h 0m 0s,+1d),  1.5d >'::scircle ~ '(1h 0m 0s,+1d) '::spoint;

\echo SELECT '< (1d 0m 0s, 0d),  3.5d >'::scircle ~ '(2d 0m 0s,+1d) '::spoint;
SELECT '< (1d 0m 0s, 0d),  3.5d >'::scircle ~ '(2d 0m 0s,+1d) '::spoint;

\echo SELECT '< (1h 0m 0s,+90d), 1.5d >'::scircle ~ '(1h 0m 0s,+89d)'::spoint;
SELECT '< (1h 0m 0s,+90d), 1.5d >'::scircle ~ '(1h 0m 0s,+89d)'::spoint;

\echo SELECT '< (1h 0m 0s,-90d), 1.5d >'::scircle ~ '(1h 0m 0s,-89d)'::spoint;
SELECT '< (1h 0m 0s,-90d), 1.5d >'::scircle ~ '(1h 0m 0s,-89d)'::spoint;

\echo SELECT '< (1h 0m 0s,+90d), 1.0d >'::scircle ~ '(1h 0m 0s,+89d)'::spoint;
SELECT '< (1h 0m 0s,+90d), 1.0d >'::scircle ~ '(1h 0m 0s,+89d)'::spoint;

\echo SELECT '< (1h 0m 0s,-90d), 1.0d >'::scircle ~ '(1h 0m 0s,-89d)'::spoint;
SELECT '< (1h 0m 0s,-90d), 1.0d >'::scircle ~ '(1h 0m 0s,-89d)'::spoint;

\echo -- should be "false"
-- should be "false"

\echo SELECT '< (2h 0m 0s,-1d),  1.5d >'::scircle ~ '(1h 0m  0s,+1d    )'::spoint;
SELECT '< (2h 0m 0s,-1d),  1.5d >'::scircle ~ '(1h 0m  0s,+1d    )'::spoint;

\echo SELECT '< (0d 0m 0s, 0d),  3.5d >'::scircle ~ '(3d 30m 0s,+1d    )'::spoint;
SELECT '< (0d 0m 0s, 0d),  3.5d >'::scircle ~ '(3d 30m 0s,+1d    )'::spoint;

\echo SELECT '< (1h 0m 0s,+90d), 1.0d >'::scircle ~ '(1h 0m  0s,+88.99d)'::spoint;
SELECT '< (1h 0m 0s,+90d), 1.0d >'::scircle ~ '(1h 0m  0s,+88.99d)'::spoint;

\echo SELECT '< (1h 0m 0s,-90d), 1.0d >'::scircle ~ '(1h 0m  0s,-88.99d)'::spoint;
SELECT '< (1h 0m 0s,-90d), 1.0d >'::scircle ~ '(1h 0m  0s,-88.99d)'::spoint;

\echo 


\echo -- indexed operations.....
-- indexed operations.....

\echo -- spoint_data and scircle_data tables have to be created and indexed using
-- spoint_data and scircle_data tables have to be created and indexed using

\echo -- ./gen_point.pl 1      | psql pgsphere_test
-- ./gen_point.pl 1      | psql pgsphere_test

\echo -- and
-- and

\echo -- ./gen_circle.pl 1 0.1 | psql pgsphere_test
-- ./gen_circle.pl 1 0.1 | psql pgsphere_test

\echo -- scripts
-- scripts

\echo 


\echo SET enable_indexscan=off;
SET enable_indexscan=off;

\echo select count(sp) from spoint_data where sp @ '<(0d,90d),1.0d>'::scircle;
select count(sp) from spoint_data where sp @ '<(0d,90d),1.0d>'::scircle;

\echo select count(sp) from spoint_data where '<(0d,90d),1.0d>'::scircle ~ sp;
select count(sp) from spoint_data where '<(0d,90d),1.0d>'::scircle ~ sp;

\echo select count(sp) from spoint_data where sp @ '<(0d,90d),1.1d>'::scircle;
select count(sp) from spoint_data where sp @ '<(0d,90d),1.1d>'::scircle;

\echo select count(sp) from spoint_data where '<(0d,90d),1.1d>'::scircle ~ sp;
select count(sp) from spoint_data where '<(0d,90d),1.1d>'::scircle ~ sp;

\echo select count(sp) from spoint_data where sp @ '<(0d,-90d),1.0d>'::scircle;
select count(sp) from spoint_data where sp @ '<(0d,-90d),1.0d>'::scircle;

\echo select count(sp) from spoint_data where '<(0d,-90d),1.0d>'::scircle ~ sp;
select count(sp) from spoint_data where '<(0d,-90d),1.0d>'::scircle ~ sp;

\echo select count(sp) from spoint_data where sp @ '<(0d,-90d),1.1d>'::scircle;
select count(sp) from spoint_data where sp @ '<(0d,-90d),1.1d>'::scircle;

\echo select count(sp) from spoint_data where '<(0d,-90d),1.1d>'::scircle ~ sp;
select count(sp) from spoint_data where '<(0d,-90d),1.1d>'::scircle ~ sp;

\echo select count(sp) from spoint_data where sp @ '<(0d,0d),2.1d>'::scircle;
select count(sp) from spoint_data where sp @ '<(0d,0d),2.1d>'::scircle;

\echo select count(sp) from spoint_data where '<(0d,0d),2.1d>'::scircle ~ sp;
select count(sp) from spoint_data where '<(0d,0d),2.1d>'::scircle ~ sp;

\echo 


\echo select count(sc) from scircle_data where sc && '<(0d,90d),1.0d>';
select count(sc) from scircle_data where sc && '<(0d,90d),1.0d>';

\echo select count(sc) from scircle_data where sc @ '<(0d,90d),1.0d>';
select count(sc) from scircle_data where sc @ '<(0d,90d),1.0d>';

\echo select count(sc) from scircle_data where '<(0d,90d),1.0d>' ~ sc;
select count(sc) from scircle_data where '<(0d,90d),1.0d>' ~ sc;

\echo select count(sc) from scircle_data where sc && '<(0d,90d),1.1d>';
select count(sc) from scircle_data where sc && '<(0d,90d),1.1d>';

\echo select count(sc) from scircle_data where sc @ '<(0d,90d),1.1d>';
select count(sc) from scircle_data where sc @ '<(0d,90d),1.1d>';

\echo select count(sc) from scircle_data where '<(0d,90d),1.1d>' ~ sc;
select count(sc) from scircle_data where '<(0d,90d),1.1d>' ~ sc;

\echo select count(sc) from scircle_data where sc && '<(0d,-90d),1.0d>';
select count(sc) from scircle_data where sc && '<(0d,-90d),1.0d>';

\echo select count(sc) from scircle_data where sc @ '<(0d,-90d),1.0d>';
select count(sc) from scircle_data where sc @ '<(0d,-90d),1.0d>';

\echo select count(sc) from scircle_data where '<(0d,-90d),1.0d>' ~ sc;
select count(sc) from scircle_data where '<(0d,-90d),1.0d>' ~ sc;

\echo select count(sc) from scircle_data where sc && '<(0d,-90d),1.1d>';
select count(sc) from scircle_data where sc && '<(0d,-90d),1.1d>';

\echo select count(sc) from scircle_data where sc @ '<(0d,-90d),1.1d>';
select count(sc) from scircle_data where sc @ '<(0d,-90d),1.1d>';

\echo select count(sc) from scircle_data where '<(0d,-90d),1.1d>' ~ sc;
select count(sc) from scircle_data where '<(0d,-90d),1.1d>' ~ sc;

\echo select count(sc) from scircle_data where sc && '<(0d,0d),2.1d>'::scircle;
select count(sc) from scircle_data where sc && '<(0d,0d),2.1d>'::scircle;

\echo select count(sc) from scircle_data where sc @ '<(0d,0d),2.1d>'::scircle;
select count(sc) from scircle_data where sc @ '<(0d,0d),2.1d>'::scircle;

\echo select count(sc) from scircle_data where '<(0d,0d),2.1d>'::scircle ~ sc;
select count(sc) from scircle_data where '<(0d,0d),2.1d>'::scircle ~ sc;

\echo 


\echo SET enable_indexscan=on;
SET enable_indexscan=on;

\echo select count(sp) from spoint_data where sp @ '<(0d,90d),1.0d>'::scircle;
select count(sp) from spoint_data where sp @ '<(0d,90d),1.0d>'::scircle;

\echo select count(sp) from spoint_data where '<(0d,90d),1.0d>'::scircle ~ sp;
select count(sp) from spoint_data where '<(0d,90d),1.0d>'::scircle ~ sp;

\echo select count(sp) from spoint_data where sp @ '<(0d,90d),1.1d>'::scircle;
select count(sp) from spoint_data where sp @ '<(0d,90d),1.1d>'::scircle;

\echo select count(sp) from spoint_data where '<(0d,90d),1.1d>'::scircle ~ sp;
select count(sp) from spoint_data where '<(0d,90d),1.1d>'::scircle ~ sp;

\echo select count(sp) from spoint_data where sp @ '<(0d,-90d),1.0d>'::scircle;
select count(sp) from spoint_data where sp @ '<(0d,-90d),1.0d>'::scircle;

\echo select count(sp) from spoint_data where '<(0d,-90d),1.0d>'::scircle ~ sp;
select count(sp) from spoint_data where '<(0d,-90d),1.0d>'::scircle ~ sp;

\echo select count(sp) from spoint_data where sp @ '<(0d,-90d),1.1d>'::scircle;
select count(sp) from spoint_data where sp @ '<(0d,-90d),1.1d>'::scircle;

\echo select count(sp) from spoint_data where '<(0d,-90d),1.1d>'::scircle ~ sp;
select count(sp) from spoint_data where '<(0d,-90d),1.1d>'::scircle ~ sp;

\echo select count(sp) from spoint_data where sp @ '<(0d,0d),2.1d>'::scircle;
select count(sp) from spoint_data where sp @ '<(0d,0d),2.1d>'::scircle;

\echo select count(sp) from spoint_data where '<(0d,0d),2.1d>'::scircle ~ sp;
select count(sp) from spoint_data where '<(0d,0d),2.1d>'::scircle ~ sp;

\echo 


\echo select count(sc) from scircle_data where sc && '<(0d,90d),1.0d>';
select count(sc) from scircle_data where sc && '<(0d,90d),1.0d>';

\echo select count(sc) from scircle_data where sc @ '<(0d,90d),1.0d>';
select count(sc) from scircle_data where sc @ '<(0d,90d),1.0d>';

\echo select count(sc) from scircle_data where '<(0d,90d),1.0d>' ~ sc;
select count(sc) from scircle_data where '<(0d,90d),1.0d>' ~ sc;

\echo select count(sc) from scircle_data where sc && '<(0d,90d),1.1d>';
select count(sc) from scircle_data where sc && '<(0d,90d),1.1d>';

\echo select count(sc) from scircle_data where sc @ '<(0d,90d),1.1d>';
select count(sc) from scircle_data where sc @ '<(0d,90d),1.1d>';

\echo select count(sc) from scircle_data where '<(0d,90d),1.1d>' ~ sc;
select count(sc) from scircle_data where '<(0d,90d),1.1d>' ~ sc;

\echo select count(sc) from scircle_data where sc && '<(0d,-90d),1.0d>';
select count(sc) from scircle_data where sc && '<(0d,-90d),1.0d>';

\echo select count(sc) from scircle_data where sc @ '<(0d,-90d),1.0d>';
select count(sc) from scircle_data where sc @ '<(0d,-90d),1.0d>';

\echo select count(sc) from scircle_data where '<(0d,-90d),1.0d>' ~ sc;
select count(sc) from scircle_data where '<(0d,-90d),1.0d>' ~ sc;

\echo select count(sc) from scircle_data where sc && '<(0d,-90d),1.1d>';
select count(sc) from scircle_data where sc && '<(0d,-90d),1.1d>';

\echo select count(sc) from scircle_data where sc @ '<(0d,-90d),1.1d>';
select count(sc) from scircle_data where sc @ '<(0d,-90d),1.1d>';

\echo select count(sc) from scircle_data where '<(0d,-90d),1.1d>' ~ sc;
select count(sc) from scircle_data where '<(0d,-90d),1.1d>' ~ sc;

\echo select count(sc) from scircle_data where sc && '<(0d,0d),2.1d>'::scircle;
select count(sc) from scircle_data where sc && '<(0d,0d),2.1d>'::scircle;

\echo select count(sc) from scircle_data where sc @ '<(0d,0d),2.1d>'::scircle;
select count(sc) from scircle_data where sc @ '<(0d,0d),2.1d>'::scircle;

\echo select count(sc) from scircle_data where '<(0d,0d),2.1d>'::scircle ~ sc;
select count(sc) from scircle_data where '<(0d,0d),2.1d>'::scircle ~ sc;

\echo 
