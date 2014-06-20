-- Input/Output ---

SELECT set_sphere_output( 'RAD' );

SELECT '< (1h 2m 30s , +1d 2m 30s), 1.0d >'::scircle;

SELECT '< (1h 2m 30s , +1d 2m 30s), 1d 30m >'::scircle;

SELECT '< (1h 2m 30s , +1d 2m 30s), 0.1 >'::scircle;

SELECT '< (1h 2m 30s , +1d 2m 30s), 90d >'::scircle;

SELECT set_sphere_output( 'DEG' );

SELECT '< (1h 2m 30s , +1d 2m 30s), 1.0d >'::scircle;

SELECT '< (1h 2m 30s , +1d 2m 30s), 1d 30m >'::scircle;

SELECT '< (1h 2m 30s , +1d 2m 30s), 0.1 >'::scircle;

SELECT '< (1h 2m 30s , +1d 2m 30s), 90d >'::scircle;

SELECT set_sphere_output( 'DMS' );

SELECT '< (1h 2m 30s , +1d 2m 30s), 1.0d >'::scircle;

SELECT '< (1h 2m 30s , +1d 2m 30s), 1d 30m >'::scircle;

SELECT '< (1h 2m 30s , +1d 2m 30s), 0.1 >'::scircle;

SELECT '< (1h 2m 30s , +1d 2m 30s), 90d >'::scircle;

SELECT set_sphere_output( 'HMS' );

SELECT '< (1h 2m 30s , +1d 2m 30s), 1.0d >'::scircle;

SELECT '< (1h 2m 30s , +1d 2m 30s), 1d 30m >'::scircle;

SELECT '< (1h 2m 30s , +1d 2m 30s), 0.1 >'::scircle;

SELECT '< (1h 2m 30s , +1d 2m 30s), 90d >'::scircle;

SELECT set_sphere_output( 'DMS' );



-- Functions


-- checking spherical circle operators

SELECT scircle '<(0, 90d),1>'   = '<(0, 90d),1>' ;
SELECT scircle '<(0,-90d),1>'  <> '<(0, 90d),1>' ;


-- float8 dist(scircle,scircle)

SELECT 180.0*dist('<( 0h 2m 30s , 10d 0m 0s), 0.1d>'::scircle,'<( 0h 2m 30s , -10d 0m 0s),0.1d>'::scircle)/pi();

SELECT 180.0*dist('<( 0h 0m 00s , 0d 0m 0s), 1.0d>'::scircle,'<( 1h 0m 00s , 0d 0m 0s),1.0d>'::scircle)/pi();

SELECT 180.0*dist('<( 23h 30m 00s , 0d 0m 0s), 1.0d>'::scircle,'<( 1h 0m 00s , 0d 0m 0s),1.5d>'::scircle)/pi();

SELECT 180.0*dist('<( 0h 40m 00s , 0d 0m 0s), 1.0d>'::scircle,'<( 0h 50m 00s , 0d 0m 0s),1.0d>'::scircle)/pi();

SELECT 180.0*dist('<( 0h 40m 00s , 0d 0m 0s), 1.5d>'::scircle,'<( 0h 50m 00s , 0d 0m 0s),1.5d>'::scircle)/pi();

SELECT 180.0*dist('<( 0h 40m 00s , 90d 0m 0s), 1.5d>'::scircle,'<( 0h 50m 00s , 0d 0m 0s),1.5d>'::scircle)/pi();

SELECT 180.0*dist('<( 0h 40m 00s , 90d 0m 0s), 1.0d>'::scircle,'<( 0h 50m 00s , -90d 0m 0s),1.0d>'::scircle)/pi();



-- spoint center(scircle)

SELECT center('< (1h 2m 30s , +1d 2m 30s), 1.0d >'::scircle);

SELECT center('< (1h 2m 30s , +90d 0m 0s), 1.0d >'::scircle);



-- scircle scircle(spoint)

SELECT scircle('(0d,0d)'::spoint);

SELECT scircle('(0d,90d)'::spoint);

SELECT scircle('(0d,-90d)'::spoint);



-- Operators

-- = operator

-- should be "true"

SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle='< (1h 0m 0s,+1d), 1.5d >'::scircle ;

SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle='< (25h 0m 0s,+1d), 1d 30m >'::scircle ;

SELECT '< (1h 0m 0s,+95d), 1.5d >'::scircle='< (13h 0m 0s,+85d), 1.5d >'::scircle ;

SELECT '< (1h 0m 0s,-95d), 1.5d >'::scircle='< (13h 0m 0s,-85d), 1.5d >'::scircle ;

SELECT '< (1h 0m 0s,+90d), 1.5d >'::scircle='< (2h 0m 0s,+90d), 1.5d >'::scircle ;

SELECT '< (1h 0m 0s,-90d), 1.5d >'::scircle='< (2h 0m 0s,-90d), 1.5d >'::scircle ;

-- should be "false"

SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle='< (1h 0m 0s,-1d), 1.5d >'::scircle ;

SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle='< (1h 0m 0s,+1d), 2.5d >'::scircle ;



-- <> operator

-- should be "false"

SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle <> '< (1h 0m 0s,+1d), 1.5d >'::scircle ;

SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle <> '< (25h 0m 0s,+1d), 1d 30m >'::scircle ;

SELECT '< (1h 0m 0s,+95d), 1.5d >'::scircle <> '< (13h 0m 0s,+85d), 1.5d >'::scircle ;

SELECT '< (1h 0m 0s,-95d), 1.5d >'::scircle <> '< (13h 0m 0s,-85d), 1.5d >'::scircle ;

SELECT '< (1h 0m 0s,+90d), 1.5d >'::scircle <> '< (2h 0m 0s,+90d), 1.5d >'::scircle ;

SELECT '< (1h 0m 0s,-90d), 1.5d >'::scircle <> '< (2h 0m 0s,-90d), 1.5d >'::scircle ;

-- should be "true"

SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle <> '< (1h 0m 0s,-1d), 1.5d >'::scircle ;

SELECT '< (1h 0m 0s,+1d), 1.5d >'::scircle <> '< (1h 0m 0s,+1d), 2.5d >'::scircle ;



-- && operator

-- should be "true"

SELECT  '< (1h 0m 0s,+1d), 1.5d >'::scircle && '< (1h 0m 0s,+1d), 1.5d >'::scircle;

SELECT  '< (1h 0m 0s,+1d), 1.5d >'::scircle && '< (1h 0m 0s,+1d), 0.5d >'::scircle;

SELECT  '< (1h 0m 0s,+1d), 1.5d >'::scircle && '< (1h 0m 0s,-1d), 1.5d >'::scircle;

SELECT  '< (1h 0m 0s,0d), 15d >'::scircle && '< (0h 0m 0s,0d), 15d >'::scircle;

SELECT  '< (2h 0m 0s,0d), 15d >'::scircle && '< (0h 0m 0.1s,0d), 15d >'::scircle;

SELECT  '< (1h 0m 0s,0d), 15d >'::scircle && '< (23h 0m 0.1s,0d), 15d >'::scircle;

-- should be "false"

SELECT  '< (1h 0m 0s,+1d), 0.5d >'::scircle && '< (1h 0m 0s,-1d), 0.5d >'::scircle;

SELECT  '< (1d 0m 0s,+1d), 1.0d >'::scircle && '< (0d 0m 0s,0d), 0.1d >'::scircle;



-- @@ operator

SELECT @@ '< (1h 2m 3s , +1d 2m 3s), 1.0d >'::scircle;

SELECT @@ '< (1h 2m 3s , +90d 0m 0s), 1.0d >'::scircle;



-- <-> operator

SELECT 180.0*('<( 0h 2m 30s , 10d 0m 0s), 0.1d>'::scircle<->'<( 0h 2m 30s , -10d 0m 0s),0.1d>'::scircle)/pi();

SELECT 180.0*('<( 0h 0m 00s , 0d 0m 0s), 1.0d>'::scircle<->'<( 1h 0m 00s , 0d 0m 0s),1.0d>'::scircle)/pi();

SELECT 180.0*('<( 23h 30m 00s , 0d 0m 0s), 1.0d>'::scircle<->'<( 1h 0m 00s , 0d 0m 0s),1.5d>'::scircle)/pi();

SELECT 180.0*('<( 0h 40m 00s , 0d 0m 0s), 1.0d>'::scircle<->'<( 0h 50m 00s , 0d 0m 0s),1.0d>'::scircle)/pi();

SELECT 180.0*('<( 0h 40m 00s , 0d 0m 0s), 1.5d>'::scircle<->'<( 0h 50m 00s , 0d 0m 0s),1.5d>'::scircle)/pi();

SELECT 180.0*('<( 0h 40m 00s , 90d 0m 0s), 1.5d>'::scircle<->'<( 0h 50m 00s , 0d 0m 0s),1.5d>'::scircle)/pi();

SELECT 180.0*('<( 0h 40m 00s , 90d 0m 0s), 1.0d>'::scircle<->'<( 0h 50m 00s , -90d 0m 0s),1.0d>'::scircle)/pi();



-- scircle @ scircle operator

-- should be "true"

SELECT  '< (1h 0m 0s,+1d),  0.5d >'::scircle @ '< (1h 0m 0s,+1d),  1.5d >'::scircle;

SELECT  '< (2d 0m 0s,+1d),  0.5d >'::scircle @ '< (1d 0m 0s,0d),   3.5d >'::scircle;

SELECT  '< (1h 0m 0s,+89d), 0.5d >'::scircle @ '< (1h 0m 0s,+90d), 1.5d >'::scircle;

SELECT  '< (1h 0m 0s,-89d), 0.5d >'::scircle @ '< (1h 0m 0s,-90d), 1.5d >'::scircle;

-- should be "false"

SELECT  '< (1h 0m 0s,+1d),  0.5d >'::scircle @ '< (2h 0m 0s,+1d),  1.5d >'::scircle;

SELECT  '< (2d 0m 0s,+1d),  1.5d >'::scircle @ '< (0d 0m 0s, 0d),  3.5d >'::scircle;

SELECT  '< (1h 0m 0s,+89d), 0.5d >'::scircle @ '< (1h 0m 0s,+90d), 1.0d >'::scircle;

SELECT  '< (1h 0m 0s,-89d), 0.5d >'::scircle @ '< (1h 0m 0s,-90d), 1.0d >'::scircle;



-- scircle ~ scircle operator

-- should be "true"

SELECT '< (1h 0m 0s,+1d),  1.5d >'::scircle  ~ '< (1h 0m 0s,+1d),  0.5d >'::scircle;

SELECT '< (1d 0m 0s,0d),   3.5d >'::scircle  ~ '< (2d 0m 0s,+1d),  0.5d >'::scircle;

SELECT '< (1h 0m 0s,+90d), 1.5d >'::scircle  ~ '< (1h 0m 0s,+89d), 0.5d >'::scircle;

SELECT '< (1h 0m 0s,-90d), 1.5d >'::scircle  ~ '< (1h 0m 0s,-89d), 0.5d >'::scircle;

-- should be "false"

SELECT '< (2h 0m 0s,+1d),  1.5d >'::scircle  ~ '< (1h 0m 0s,+1d),  0.5d >'::scircle;

SELECT '< (0d 0m 0s, 0d),  3.5d >'::scircle  ~ '< (2d 0m 0s,+1d),  1.5d >'::scircle;

SELECT '< (1h 0m 0s,+90d), 1.0d >'::scircle  ~ '< (1h 0m 0s,+89d), 0.5d >'::scircle;

SELECT '< (1h 0m 0s,-90d), 1.0d >'::scircle  ~ '< (1h 0m 0s,-89d), 0.5d >'::scircle;



-- spoint @ scircle operator

-- should be "true"

SELECT  '(1h 0m 0s,+1d) '::spoint @ '< (1h 0m 0s,+1d),  1.5d >'::scircle;

SELECT  '(2d 0m 0s,+1d) '::spoint @ '< (1d 0m 0s, 0d),  3.5d >'::scircle;

SELECT  '(1h 0m 0s,+89d)'::spoint @ '< (1h 0m 0s,+90d), 1.5d >'::scircle;

SELECT  '(1h 0m 0s,-89d)'::spoint @ '< (1h 0m 0s,-90d), 1.5d >'::scircle;

SELECT  '(1h 0m 0s,+89d)'::spoint @ '< (1h 0m 0s,+90d), 1.0d >'::scircle;

SELECT  '(1h 0m 0s,-89d)'::spoint @ '< (1h 0m 0s,-90d), 1.0d >'::scircle;

-- should be "false"

SELECT  '(1h 0m  0s,+1d    )'::spoint @ '< (2h 0m 0s,-1d),  1.5d >'::scircle;

SELECT  '(3d 30m 0s,+1d    )'::spoint @ '< (0d 0m 0s, 0d),  3.5d >'::scircle;

SELECT  '(1h 0m  0s,+88.99d)'::spoint @ '< (1h 0m 0s,+90d), 1.0d >'::scircle;

SELECT  '(1h 0m  0s,-88.99d)'::spoint @ '< (1h 0m 0s,-90d), 1.0d >'::scircle;



-- spoint ~ scircle operator

-- should be "true"

SELECT '< (1h 0m 0s,+1d),  1.5d >'::scircle ~ '(1h 0m 0s,+1d) '::spoint;

SELECT '< (1d 0m 0s, 0d),  3.5d >'::scircle ~ '(2d 0m 0s,+1d) '::spoint;

SELECT '< (1h 0m 0s,+90d), 1.5d >'::scircle ~ '(1h 0m 0s,+89d)'::spoint;

SELECT '< (1h 0m 0s,-90d), 1.5d >'::scircle ~ '(1h 0m 0s,-89d)'::spoint;

SELECT '< (1h 0m 0s,+90d), 1.0d >'::scircle ~ '(1h 0m 0s,+89d)'::spoint;

SELECT '< (1h 0m 0s,-90d), 1.0d >'::scircle ~ '(1h 0m 0s,-89d)'::spoint;

-- should be "false"

SELECT '< (2h 0m 0s,-1d),  1.5d >'::scircle ~ '(1h 0m  0s,+1d    )'::spoint;

SELECT '< (0d 0m 0s, 0d),  3.5d >'::scircle ~ '(3d 30m 0s,+1d    )'::spoint;

SELECT '< (1h 0m 0s,+90d), 1.0d >'::scircle ~ '(1h 0m  0s,+88.99d)'::spoint;

SELECT '< (1h 0m 0s,-90d), 1.0d >'::scircle ~ '(1h 0m  0s,-88.99d)'::spoint;
