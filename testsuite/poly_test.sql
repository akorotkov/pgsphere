\echo SELECT set_sphere_output('DEG');
SELECT set_sphere_output('DEG');

\echo 


\echo SELECT spoly '{(10d,0d),(10d,1d),(15d,0d)}';
SELECT spoly '{(10d,0d),(10d,1d),(15d,0d)}';

\echo SELECT spoly '{(359d,0d),(359d,1d),(4d,0d)}';
SELECT spoly '{(359d,0d),(359d,1d),(4d,0d)}';

\echo SELECT spoly '{(10d,0d),(10d,1d),(15d,0d)}';
SELECT spoly '{(10d,0d),(10d,1d),(15d,0d)}';

\echo 


\echo -- incorrect input -----
-- incorrect input -----

\echo SELECT spoly '{(10d,0d),(10d,1d)}';
SELECT spoly '{(10d,0d),(10d,1d)}';

\echo 


\echo --- self-crossing input -----
--- self-crossing input -----

\echo SELECT spoly '{(0d,0d),(10d,10d),(0d,10d),(10d,0d)}';
SELECT spoly '{(0d,0d),(10d,10d),(0d,10d),(10d,0d)}';

\echo 


\echo --- functions
--- functions

\echo SELECT npoints( spoly '{(10d,0d),(10d,1d),(15d,0d)}');
SELECT npoints( spoly '{(10d,0d),(10d,1d),(15d,0d)}');

\echo SELECT npoints( spoly '{(10d,0d),(10d,1d),(15d,0d),(5d,-5d)}');
SELECT npoints( spoly '{(10d,0d),(10d,1d),(15d,0d),(5d,-5d)}');

\echo --SELECT npoints( spoly '{(0d,0d),(0d,90d),(15d,90d),(15d,0d)}');
--SELECT npoints( spoly '{(0d,0d),(0d,90d),(15d,90d),(15d,0d)}');

\echo 


\echo SELECT area(spoly '{(0d,0d),(0d,90d),(1,0d)}');
SELECT area(spoly '{(0d,0d),(0d,90d),(1,0d)}');

\echo SELECT area(spoly '{(0d,0d),(0d,90d),(90d,0d)}')/(4.0*pi());
SELECT area(spoly '{(0d,0d),(0d,90d),(90d,0d)}')/(4.0*pi());

\echo 


\echo --- operations
--- operations

\echo --- = operator
--- = operator

\echo --- should be true
--- should be true

\echo SELECT spoly '{(1d,0d),(1d,1d),(2d,1d)}' = spoly '{(1d,1d),(2d,1d),(1d,0d)}';
SELECT spoly '{(1d,0d),(1d,1d),(2d,1d)}' = spoly '{(1d,1d),(2d,1d),(1d,0d)}';

\echo SELECT spoly '{(1d,0d),(1d,1d),(2d,1d)}' = spoly '{(2d,1d),(1d,1d),(1d,0d)}';
SELECT spoly '{(1d,0d),(1d,1d),(2d,1d)}' = spoly '{(2d,1d),(1d,1d),(1d,0d)}';

\echo SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' = spoly '{(1d,0d),(0d,0d),(0d,1d),(1d,1d)}';
SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' = spoly '{(1d,0d),(0d,0d),(0d,1d),(1d,1d)}';

\echo SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' = spoly '{(0d,0d),(1d,0d),(1d,1d),(0d,1d)}';
SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' = spoly '{(0d,0d),(1d,0d),(1d,1d),(0d,1d)}';

\echo --- should be false
--- should be false

\echo SELECT spoly '{(1d,0d),(1d,1d),(2d,1d)}' = spoly '{(1d,1d),(3d,1d),(1d,0d)}';
SELECT spoly '{(1d,0d),(1d,1d),(2d,1d)}' = spoly '{(1d,1d),(3d,1d),(1d,0d)}';

\echo SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' = spoly '{(1d,0d),(0d,0d),(0d,1d),(2d,2d)}';
SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' = spoly '{(1d,0d),(0d,0d),(0d,1d),(2d,2d)}';

\echo 


\echo --- <> operator
--- <> operator

\echo --- should be false
--- should be false

\echo SELECT spoly '{(1d,0d),(1d,1d),(2d,1d)}' <> spoly '{(1d,1d),(2d,1d),(1d,0d)}';
SELECT spoly '{(1d,0d),(1d,1d),(2d,1d)}' <> spoly '{(1d,1d),(2d,1d),(1d,0d)}';

\echo SELECT spoly '{(1d,0d),(1d,1d),(2d,1d)}' <> spoly '{(2d,1d),(1d,1d),(1d,0d)}';
SELECT spoly '{(1d,0d),(1d,1d),(2d,1d)}' <> spoly '{(2d,1d),(1d,1d),(1d,0d)}';

\echo SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' <> spoly '{(1d,0d),(0d,0d),(0d,1d),(1d,1d)}';
SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' <> spoly '{(1d,0d),(0d,0d),(0d,1d),(1d,1d)}';

\echo SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' <> spoly '{(0d,0d),(1d,0d),(1d,1d),(0d,1d)}';
SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' <> spoly '{(0d,0d),(1d,0d),(1d,1d),(0d,1d)}';

\echo --- should be true
--- should be true

\echo SELECT spoly '{(1d,0d),(1d,1d),(2d,1d)}' <> spoly '{(1d,1d),(3d,1d),(1d,0d)}';
SELECT spoly '{(1d,0d),(1d,1d),(2d,1d)}' <> spoly '{(1d,1d),(3d,1d),(1d,0d)}';

\echo SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' <> spoly '{(1d,0d),(0d,0d),(0d,1d),(2d,2d)}';
SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' <> spoly '{(1d,0d),(0d,0d),(0d,1d),(2d,2d)}';

\echo 


\echo --- spoint @ spoly
--- spoint @ spoly

\echo --- should be true
--- should be true

\echo SELECT '(0.5d,0.5d)'::spoint @ spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';
SELECT '(0.5d,0.5d)'::spoint @ spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';

\echo SELECT '(0d,0.5d)'::spoint @ spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';
SELECT '(0d,0.5d)'::spoint @ spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';

\echo SELECT '(0d,0d)'::spoint @ spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';
SELECT '(0d,0d)'::spoint @ spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';

\echo SELECT '(0.5d,0.5d)'::spoint @ spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}';
SELECT '(0.5d,0.5d)'::spoint @ spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}';

\echo SELECT '(0d,89.9d)'::spoint @ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT '(0d,89.9d)'::spoint @ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo SELECT '(0d,90d)'::spoint @ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT '(0d,90d)'::spoint @ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo SELECT '(0d,-89.9d)'::spoint @ spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';
SELECT '(0d,-89.9d)'::spoint @ spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';

\echo SELECT '(0d,-90d)'::spoint @ spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';
SELECT '(0d,-90d)'::spoint @ spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';

\echo 


\echo --- should be false
--- should be false

\echo SELECT '(0.1d,0.5d)'::spoint @ spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}';
SELECT '(0.1d,0.5d)'::spoint @ spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}';

\echo SELECT '(45d,-89d)'::spoint @ spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';
SELECT '(45d,-89d)'::spoint @ spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';

\echo SELECT '(0d,1d)'::spoint @ spoly '{(0d,0d),(1d,1d),(1d,0d)}';
SELECT '(0d,1d)'::spoint @ spoly '{(0d,0d),(1d,1d),(1d,0d)}';

\echo 


\echo --- spoly ~ spoint
--- spoly ~ spoint

\echo --- should be true
--- should be true

\echo SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' ~ '(0.5d,0.5d)'::spoint;
SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' ~ '(0.5d,0.5d)'::spoint;

\echo SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' ~ '(0d,0.5d)'::spoint;
SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' ~ '(0d,0.5d)'::spoint;

\echo SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' ~ '(0d,0d)'::spoint;
SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' ~ '(0d,0d)'::spoint;

\echo SELECT  spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}' ~ '(0.5d,0.5d)'::spoint;
SELECT  spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}' ~ '(0.5d,0.5d)'::spoint;

\echo SELECT  spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' ~ '(0d,89.9d)'::spoint;
SELECT  spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' ~ '(0d,89.9d)'::spoint;

\echo SELECT  spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' ~ '(0d,90d)'::spoint;
SELECT  spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' ~ '(0d,90d)'::spoint;

\echo SELECT  spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' ~ '(0d,-89.9d)'::spoint;
SELECT  spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' ~ '(0d,-89.9d)'::spoint;

\echo SELECT  spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' ~ '(0d,-90d)'::spoint;
SELECT  spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' ~ '(0d,-90d)'::spoint;

\echo 


\echo --- should be false
--- should be false

\echo SELECT  spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}' ~ '(0.1d,0.5d)'::spoint;
SELECT  spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}' ~ '(0.1d,0.5d)'::spoint;

\echo SELECT  spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' ~ '(45d,-89d)'::spoint;
SELECT  spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' ~ '(45d,-89d)'::spoint;

\echo SELECT  spoly '{(0d,0d),(1d,1d),(1d,0d)}' ~ '(0d,1d)'::spoint;
SELECT  spoly '{(0d,0d),(1d,1d),(1d,0d)}' ~ '(0d,1d)'::spoint;

\echo 


\echo --- scircle @ spoly
--- scircle @ spoly

\echo --- should be true
--- should be true

\echo SELECT '<(0.5d,0.5d),0.1d>'::scircle @ spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';
SELECT '<(0.5d,0.5d),0.1d>'::scircle @ spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';

\echo SELECT '<(0d,89.9d),0.1d>'::scircle @ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT '<(0d,89.9d),0.1d>'::scircle @ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo SELECT '<(0d,90d),0.1d>'::scircle @ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT '<(0d,90d),0.1d>'::scircle @ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo SELECT '<(0d,-89.9d),0.1d>'::scircle @ spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';
SELECT '<(0d,-89.9d),0.1d>'::scircle @ spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';

\echo SELECT '<(0d,-90d),0.1d>'::scircle @ spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';
SELECT '<(0d,-90d),0.1d>'::scircle @ spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';

\echo 


\echo --- should be false
--- should be false

\echo SELECT '<(0.1d,0.5d),0.1d>'::scircle @ spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}';
SELECT '<(0.1d,0.5d),0.1d>'::scircle @ spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}';

\echo SELECT '<(45d,-89d),0.1d>'::scircle @ spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';
SELECT '<(45d,-89d),0.1d>'::scircle @ spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';

\echo SELECT '<(0d,1d),0.1d>'::scircle @ spoly '{(0d,0d),(1d,1d),(1d,0d)}';
SELECT '<(0d,1d),0.1d>'::scircle @ spoly '{(0d,0d),(1d,1d),(1d,0d)}';

\echo SELECT '<(0d,0.5d),0.1d>'::scircle @ spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';
SELECT '<(0d,0.5d),0.1d>'::scircle @ spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';

\echo SELECT '<(0d,0d),0.1d>'::scircle @ spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';
SELECT '<(0d,0d),0.1d>'::scircle @ spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';

\echo SELECT '<(0.5d,0.5d),0.1d>'::scircle @ spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}';
SELECT '<(0.5d,0.5d),0.1d>'::scircle @ spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}';

\echo 


\echo --- spoly ~ scircle
--- spoly ~ scircle

\echo --- should be true
--- should be true

\echo SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' ~ '<(0.5d,0.5d),0.1d>'::scircle;
SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' ~ '<(0.5d,0.5d),0.1d>'::scircle;

\echo SELECT  spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' ~ '<(0d,89.9d),0.1d>'::scircle;
SELECT  spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' ~ '<(0d,89.9d),0.1d>'::scircle;

\echo SELECT  spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' ~ '<(0d,90d),0.1d>'::scircle;
SELECT  spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' ~ '<(0d,90d),0.1d>'::scircle;

\echo SELECT  spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' ~ '<(0d,-89.9d),0.1d>'::scircle;
SELECT  spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' ~ '<(0d,-89.9d),0.1d>'::scircle;

\echo SELECT  spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' ~ '<(0d,-90d),0.1d>'::scircle;
SELECT  spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' ~ '<(0d,-90d),0.1d>'::scircle;

\echo 


\echo --- should be false
--- should be false

\echo SELECT  spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}' ~ '<(0.1d,0.5d),0.1d>'::scircle;
SELECT  spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}' ~ '<(0.1d,0.5d),0.1d>'::scircle;

\echo SELECT  spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' ~ '<(45d,-89d),0.1d>'::scircle;
SELECT  spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' ~ '<(45d,-89d),0.1d>'::scircle;

\echo SELECT  spoly '{(0d,0d),(1d,1d),(1d,0d)}' ~ '<(0d,1d),0.1d>'::scircle;
SELECT  spoly '{(0d,0d),(1d,1d),(1d,0d)}' ~ '<(0d,1d),0.1d>'::scircle;

\echo SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' ~ '<(0d,0.5d),0.1d>'::scircle;
SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' ~ '<(0d,0.5d),0.1d>'::scircle;

\echo SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' ~ '<(0d,0d),0.1d>'::scircle;
SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' ~ '<(0d,0d),0.1d>'::scircle;

\echo SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' ~ '<(0.1d,0.5d),0.1d>'::scircle;
SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' ~ '<(0.1d,0.5d),0.1d>'::scircle;

\echo SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' ~ '<(0.1d,0.1d),0.1d>'::scircle;
SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' ~ '<(0.1d,0.1d),0.1d>'::scircle;

\echo SELECT  spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}' ~ '<(0.6d,0.5d),0.1d>'::scircle;
SELECT  spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}' ~ '<(0.6d,0.5d),0.1d>'::scircle;

\echo 


\echo --- spoly @ scircle
--- spoly @ scircle

\echo --- should be true
--- should be true

\echo SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' @ '<(0d,0d),2.0d>'::scircle;
SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' @ '<(0d,0d),2.0d>'::scircle;

\echo SELECT spoly '{(-1d,0d),(0d,1d),(1d,0d),(0d,-1d)}' @ '<(0d,0d),1.0d>'::scircle;
SELECT spoly '{(-1d,0d),(0d,1d),(1d,0d),(0d,-1d)}' @ '<(0d,0d),1.0d>'::scircle;

\echo SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' @ '<(0d,90d),1.0d>'::scircle;
SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' @ '<(0d,90d),1.0d>'::scircle;

\echo SELECT spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' @ '<(180d,-90d),1.0d>'::scircle;
SELECT spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' @ '<(180d,-90d),1.0d>'::scircle;

\echo SELECT spoly '{(0d,0d),(0d,1d),(1d,0d)}' @ '<(0d,0d),1.0d>'::scircle;
SELECT spoly '{(0d,0d),(0d,1d),(1d,0d)}' @ '<(0d,0d),1.0d>'::scircle;

\echo 


\echo --- should be false
--- should be false

\echo SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' @ '<(0d,0d),1.0d>'::scircle;
SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' @ '<(0d,0d),1.0d>'::scircle;

\echo SELECT spoly '{(-1d,0d),(0d,1d),(1d,0d),(0d,-1d)}' @ '<(0d,0d),0.99d>'::scircle;
SELECT spoly '{(-1d,0d),(0d,1d),(1d,0d),(0d,-1d)}' @ '<(0d,0d),0.99d>'::scircle;

\echo SELECT spoly '{(-1d,0d),(0d,1d),(1d,0d),(0d,-1d)}' @ '<(60d,0d),0.99d>'::scircle;
SELECT spoly '{(-1d,0d),(0d,1d),(1d,0d),(0d,-1d)}' @ '<(60d,0d),0.99d>'::scircle;

\echo SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,88d)}' @ '<(0d,90d),1.0d>'::scircle;
SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,88d)}' @ '<(0d,90d),1.0d>'::scircle;

\echo SELECT spoly '{(0d,-87d),(90d,-87d),(180d,-87d),(270d,-87d)}' @ '<(180d,-90d),1.0d>'::scircle;
SELECT spoly '{(0d,-87d),(90d,-87d),(180d,-87d),(270d,-87d)}' @ '<(180d,-90d),1.0d>'::scircle;

\echo SELECT spoly '{(0d,0d),(0d,1d),(2d,0d)}' @ '<(0d,0d),1.0d>'::scircle;
SELECT spoly '{(0d,0d),(0d,1d),(2d,0d)}' @ '<(0d,0d),1.0d>'::scircle;

\echo 


\echo --- scircle ~ spoly
--- scircle ~ spoly

\echo --- should be true
--- should be true

\echo SELECT '<(0d,0d),2.0d>'::scircle ~ spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';
SELECT '<(0d,0d),2.0d>'::scircle ~ spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';

\echo SELECT '<(0d,0d),1.0d>'::scircle ~ spoly '{(-1d,0d),(0d,1d),(1d,0d),(0d,-1d)}';
SELECT '<(0d,0d),1.0d>'::scircle ~ spoly '{(-1d,0d),(0d,1d),(1d,0d),(0d,-1d)}';

\echo SELECT '<(0d,90d),1.0d>'::scircle ~ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT '<(0d,90d),1.0d>'::scircle ~ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo SELECT '<(180d,-90d),1.0d>'::scircle ~ spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';
SELECT '<(180d,-90d),1.0d>'::scircle ~ spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';

\echo SELECT '<(0d,0d),1.0d>'::scircle ~ spoly '{(0d,0d),(0d,1d),(1d,0d)}';
SELECT '<(0d,0d),1.0d>'::scircle ~ spoly '{(0d,0d),(0d,1d),(1d,0d)}';

\echo 


\echo --- should be false
--- should be false

\echo SELECT '<(0d,0d),1.0d>'::scircle ~ spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';
SELECT '<(0d,0d),1.0d>'::scircle ~ spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';

\echo SELECT '<(0d,0d),0.99d>'::scircle ~ spoly '{(-1d,0d),(0d,1d),(1d,0d),(0d,-1d)}';
SELECT '<(0d,0d),0.99d>'::scircle ~ spoly '{(-1d,0d),(0d,1d),(1d,0d),(0d,-1d)}';

\echo SELECT '<(60d,0d),0.99d>'::scircle ~ spoly '{(-1d,0d),(0d,1d),(1d,0d),(0d,-1d)}';
SELECT '<(60d,0d),0.99d>'::scircle ~ spoly '{(-1d,0d),(0d,1d),(1d,0d),(0d,-1d)}';

\echo SELECT '<(0d,90d),1.0d>'::scircle ~ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,88d)}';
SELECT '<(0d,90d),1.0d>'::scircle ~ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,88d)}';

\echo SELECT '<(180d,-90d),1.0d>'::scircle ~ spoly '{(0d,-87d),(90d,-87d),(180d,-87d),(270d,-87d)}';
SELECT '<(180d,-90d),1.0d>'::scircle ~ spoly '{(0d,-87d),(90d,-87d),(180d,-87d),(270d,-87d)}';

\echo SELECT '<(0d,0d),1.0d>'::scircle ~ spoly '{(0d,0d),(0d,1d),(2d,0d)}';
SELECT '<(0d,0d),1.0d>'::scircle ~ spoly '{(0d,0d),(0d,1d),(2d,0d)}';

\echo 


\echo --- scircle && spoly
--- scircle && spoly

\echo --- should be true
--- should be true

\echo SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' && '<(0.5d,0.5d),0.1d>'::scircle;
SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' && '<(0.5d,0.5d),0.1d>'::scircle;

\echo SELECT  spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' && '<(0d,89.9d),0.1d>'::scircle;
SELECT  spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' && '<(0d,89.9d),0.1d>'::scircle;

\echo SELECT  spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' && '<(0d,90d),0.1d>'::scircle;
SELECT  spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' && '<(0d,90d),0.1d>'::scircle;

\echo SELECT  spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' && '<(0d,-89.9d),0.1d>'::scircle;
SELECT  spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' && '<(0d,-89.9d),0.1d>'::scircle;

\echo SELECT  spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' && '<(0d,-90d),0.1d>'::scircle;
SELECT  spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' && '<(0d,-90d),0.1d>'::scircle;

\echo SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' && '<(0d,0d),2.0d>'::scircle;
SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' && '<(0d,0d),2.0d>'::scircle;

\echo SELECT  spoly '{(-1d,0d),(0d,1d),(1d,0d),(0d,-1d)}' && '<(0d,0d),1.0d>'::scircle;
SELECT  spoly '{(-1d,0d),(0d,1d),(1d,0d),(0d,-1d)}' && '<(0d,0d),1.0d>'::scircle;

\echo SELECT  spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' && '<(0d,90d),1.0d>'::scircle;
SELECT  spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' && '<(0d,90d),1.0d>'::scircle;

\echo SELECT  spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' && '<(180d,-90d),1.0d>'::scircle;
SELECT  spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' && '<(180d,-90d),1.0d>'::scircle;

\echo SELECT  spoly '{(0d,0d),(0d,1d),(1d,0d)}' && '<(0d,0d),1.0d>'::scircle;
SELECT  spoly '{(0d,0d),(0d,1d),(1d,0d)}' && '<(0d,0d),1.0d>'::scircle;

\echo SELECT  spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' && '<(0d,2d),1.0d>'::scircle;
SELECT  spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' && '<(0d,2d),1.0d>'::scircle;

\echo SELECT  spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' && '<(2d,0d),1.0d>'::scircle;
SELECT  spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' && '<(2d,0d),1.0d>'::scircle;

\echo SELECT  spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}' && '<(0.5d,0.5d),0.1d>'::scircle;
SELECT  spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}' && '<(0.5d,0.5d),0.1d>'::scircle;

\echo 


\echo --- should be false
--- should be false

\echo SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' && '<(1.5d,0.5d),0.1d>'::scircle;
SELECT  spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' && '<(1.5d,0.5d),0.1d>'::scircle;

\echo SELECT  spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' && '<(0d,88.0d),0.1d>'::scircle;
SELECT  spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' && '<(0d,88.0d),0.1d>'::scircle;

\echo SELECT  spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}' && '<(0.3d,0.5d),0.1d>'::scircle;
SELECT  spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}' && '<(0.3d,0.5d),0.1d>'::scircle;

\echo SELECT  spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' && '<(0d,-87d),0.1d>'::scircle;
SELECT  spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}' && '<(0d,-87d),0.1d>'::scircle;

\echo 


\echo --- spoly && scircle
--- spoly && scircle

\echo --- should be true
--- should be true

\echo SELECT  '<(0.5d,0.5d),0.1d>'::scircle && spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';
SELECT  '<(0.5d,0.5d),0.1d>'::scircle && spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';

\echo SELECT  '<(0d,89.9d),0.1d>'::scircle && spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT  '<(0d,89.9d),0.1d>'::scircle && spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo SELECT  '<(0d,90d),0.1d>'::scircle && spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT  '<(0d,90d),0.1d>'::scircle && spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo SELECT  '<(0d,-89.9d),0.1d>'::scircle && spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';
SELECT  '<(0d,-89.9d),0.1d>'::scircle && spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';

\echo SELECT  '<(0d,-90d),0.1d>'::scircle && spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';
SELECT  '<(0d,-90d),0.1d>'::scircle && spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';

\echo SELECT  '<(0d,0d),2.0d>'::scircle && spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';
SELECT  '<(0d,0d),2.0d>'::scircle && spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';

\echo SELECT  '<(0d,0d),1.0d>'::scircle && spoly '{(-1d,0d),(0d,1d),(1d,0d),(0d,-1d)}';
SELECT  '<(0d,0d),1.0d>'::scircle && spoly '{(-1d,0d),(0d,1d),(1d,0d),(0d,-1d)}';

\echo SELECT  '<(0d,90d),1.0d>'::scircle && spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT  '<(0d,90d),1.0d>'::scircle && spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo SELECT  '<(180d,-90d),1.0d>'::scircle && spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';
SELECT  '<(180d,-90d),1.0d>'::scircle && spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';

\echo SELECT  '<(0d,0d),1.0d>'::scircle && spoly '{(0d,0d),(0d,1d),(1d,0d)}';
SELECT  '<(0d,0d),1.0d>'::scircle && spoly '{(0d,0d),(0d,1d),(1d,0d)}';

\echo SELECT  '<(0d,2d),1.0d>'::scircle && spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';
SELECT  '<(0d,2d),1.0d>'::scircle && spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';

\echo SELECT  '<(2d,0d),1.0d>'::scircle && spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';
SELECT  '<(2d,0d),1.0d>'::scircle && spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';

\echo SELECT  '<(0.5d,0.5d),0.1d>'::scircle && spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}';
SELECT  '<(0.5d,0.5d),0.1d>'::scircle && spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}';

\echo 


\echo --- should be false
--- should be false

\echo SELECT  '<(1.5d,0.5d),0.1d>'::scircle && spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';
SELECT  '<(1.5d,0.5d),0.1d>'::scircle && spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';

\echo SELECT  '<(0d,88.0d),0.1d>'::scircle && spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT  '<(0d,88.0d),0.1d>'::scircle && spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo SELECT  '<(0.3d,0.5d),0.1d>'::scircle && spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}';
SELECT  '<(0.3d,0.5d),0.1d>'::scircle && spoly '{(0d,0d),(0.5d,0.5d),(0d,1d),(1d,1d),(1d,0d)}';

\echo SELECT  '<(0d,-87d),0.1d>'::scircle && spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';
SELECT  '<(0d,-87d),0.1d>'::scircle && spoly '{(0d,-89d),(90d,-89d),(180d,-89d),(270d,-89d)}';

\echo 


\echo --- spoly @ spoly
--- spoly @ spoly

\echo --- should be true
--- should be true

\echo SELECT spoly '{(0d,0d),(0d,0.5d),(0.5d,0.5d),(0.5d,0d)}' @ spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';
SELECT spoly '{(0d,0d),(0d,0.5d),(0.5d,0.5d),(0.5d,0d)}' @ spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';

\echo SELECT spoly '{(-0.5d,-0.5d),(-0.5d,0.5d),(0.5d,0.5d),(0.5d,-0.5d)}' @ spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';
SELECT spoly '{(-0.5d,-0.5d),(-0.5d,0.5d),(0.5d,0.5d),(0.5d,-0.5d)}' @ spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';

\echo SELECT spoly '{(0d,0d),(0d,0.5d),(0.5d,0.5d),(0.5d,0d)}' @ spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';
SELECT spoly '{(0d,0d),(0d,0.5d),(0.5d,0.5d),(0.5d,0d)}' @ spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';

\echo SELECT spoly '{(0d,0d),(0d,1d),(1d,0d)}' @ spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';
SELECT spoly '{(0d,0d),(0d,1d),(1d,0d)}' @ spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';

\echo SELECT spoly '{(0d,0d),(0d,1d),(1d,0d)}' @ spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';
SELECT spoly '{(0d,0d),(0d,1d),(1d,0d)}' @ spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';

\echo SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' @ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' @ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo SELECT spoly '{(45d,89.3d),(135d,89.3d),(225d,89.3d),(315d,89.3d)}' @ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT spoly '{(45d,89.3d),(135d,89.3d),(225d,89.3d),(315d,89.3d)}' @ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo 


\echo --- should be false
--- should be false

\echo --SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' @ spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';
--SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' @ spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';

\echo SELECT spoly '{(45d,89.2d),(135d,89.2d),(225d,89.2d),(315d,89.2d)}' @ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT spoly '{(45d,89.2d),(135d,89.2d),(225d,89.2d),(315d,89.2d)}' @ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' @ spoly '{(0.5d,0.5d),(0.5d,1.5d),(1.5d,1.5d),(1.5d,0.5d)}';
SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' @ spoly '{(0.5d,0.5d),(0.5d,1.5d),(1.5d,1.5d),(1.5d,0.5d)}';

\echo SELECT spoly '{(0d,88d),(90d,88d),(180d,88d),(270d,88d)}' @ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT spoly '{(0d,88d),(90d,88d),(180d,88d),(270d,88d)}' @ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo 


\echo SELECT spoly '{(0d,-88d),(90d,-88d),(180d,-88d),(270d,-88d)}' @ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT spoly '{(0d,-88d),(90d,-88d),(180d,-88d),(270d,-88d)}' @ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo 


\echo 


\echo --- spoly ~ spoly
--- spoly ~ spoly

\echo --- should be true                                                                                       
--- should be true                                                                                       

\echo SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' ~ spoly '{(0d,0d),(0d,0.5d),(0.5d,0.5d),(0.5d,0d)}';
SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' ~ spoly '{(0d,0d),(0d,0.5d),(0.5d,0.5d),(0.5d,0d)}';

\echo SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' ~ spoly '{(-0.5d,-0.5d),(-0.5d,0.5d),(0.5d,0.5d),(0.5d,-0.5d)}';
SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' ~ spoly '{(-0.5d,-0.5d),(-0.5d,0.5d),(0.5d,0.5d),(0.5d,-0.5d)}';

\echo SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' ~ spoly '{(0d,0d),(0d,0.5d),(0.5d,0.5d),(0.5d,0d)}';
SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' ~ spoly '{(0d,0d),(0d,0.5d),(0.5d,0.5d),(0.5d,0d)}';

\echo SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' ~ spoly '{(0d,0d),(0d,1d),(1d,0d)}';
SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' ~ spoly '{(0d,0d),(0d,1d),(1d,0d)}';

\echo SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' ~ spoly '{(0d,0d),(0d,1d),(1d,0d)}';
SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' ~ spoly '{(0d,0d),(0d,1d),(1d,0d)}';

\echo SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' ~ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' ~ spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' ~ spoly '{(45d,89.3d),(135d,89.3d),(225d,89.3d),(315d,89.3d)}';
SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' ~ spoly '{(45d,89.3d),(135d,89.3d),(225d,89.3d),(315d,89.3d)}';

\echo 


\echo --- should be false
--- should be false

\echo SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' ~ spoly '{(45d,89.2d),(135d,89.2d),(225d,89.2d),(315d,89.2d)}';
SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' ~ spoly '{(45d,89.2d),(135d,89.2d),(225d,89.2d),(315d,89.2d)}';

\echo SELECT spoly '{(0.5d,0.5d),(0.5d,1.5d),(1.5d,1.5d),(1.5d,0.5d)}' ~ spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';
SELECT spoly '{(0.5d,0.5d),(0.5d,1.5d),(1.5d,1.5d),(1.5d,0.5d)}' ~ spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';

\echo SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' ~ spoly '{(0d,88d),(90d,88d),(180d,88d),(270d,88d)}';
SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' ~ spoly '{(0d,88d),(90d,88d),(180d,88d),(270d,88d)}';

\echo 


\echo SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' ~ spoly '{(0d,-88d),(90d,-88d),(180d,-88d),(270d,-88d)}';
SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' ~ spoly '{(0d,-88d),(90d,-88d),(180d,-88d),(270d,-88d)}';

\echo 


\echo 


\echo --- spoly && spoly
--- spoly && spoly

\echo --- should be true                                                                                       
--- should be true                                                                                       

\echo SELECT spoly '{(0d,0d),(0d,0.5d),(0.5d,0.5d),(0.5d,0d)}' && spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';
SELECT spoly '{(0d,0d),(0d,0.5d),(0.5d,0.5d),(0.5d,0d)}' && spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';

\echo SELECT spoly '{(-0.5d,-0.5d),(-0.5d,0.5d),(0.5d,0.5d),(0.5d,-0.5d)}' && spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';
SELECT spoly '{(-0.5d,-0.5d),(-0.5d,0.5d),(0.5d,0.5d),(0.5d,-0.5d)}' && spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';

\echo SELECT spoly '{(0d,0d),(0d,0.5d),(0.5d,0.5d),(0.5d,0d)}' && spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';
SELECT spoly '{(0d,0d),(0d,0.5d),(0.5d,0.5d),(0.5d,0d)}' && spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';

\echo SELECT spoly '{(0d,0d),(0d,1d),(1d,0d)}' && spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';
SELECT spoly '{(0d,0d),(0d,1d),(1d,0d)}' && spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}';

\echo SELECT spoly '{(0d,0d),(0d,1d),(1d,0d)}' && spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';
SELECT spoly '{(0d,0d),(0d,1d),(1d,0d)}' && spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}';

\echo SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' && spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' && spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo SELECT spoly '{(45d,89.3d),(135d,89.3d),(225d,89.3d),(315d,89.3d)}' && spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT spoly '{(45d,89.3d),(135d,89.3d),(225d,89.3d),(315d,89.3d)}' && spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo 


\echo SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' && spoly '{(0d,0d),(0d,0.5d),(0.5d,0.5d),(0.5d,0d)}';
SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' && spoly '{(0d,0d),(0d,0.5d),(0.5d,0.5d),(0.5d,0d)}';

\echo SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' && spoly '{(-0.5d,-0.5d),(-0.5d,0.5d),(0.5d,0.5d),(0.5d,-0.5d)}';
SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' && spoly '{(-0.5d,-0.5d),(-0.5d,0.5d),(0.5d,0.5d),(0.5d,-0.5d)}';

\echo SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' && spoly '{(0d,0d),(0d,0.5d),(0.5d,0.5d),(0.5d,0d)}';
SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' && spoly '{(0d,0d),(0d,0.5d),(0.5d,0.5d),(0.5d,0d)}';

\echo SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' && spoly '{(0d,0d),(0d,1d),(1d,0d)}';
SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' && spoly '{(0d,0d),(0d,1d),(1d,0d)}';

\echo SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' && spoly '{(0d,0d),(0d,1d),(1d,0d)}';
SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' && spoly '{(0d,0d),(0d,1d),(1d,0d)}';

\echo SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' && spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' && spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' && spoly '{(45d,89.3d),(135d,89.3d),(225d,89.3d),(315d,89.3d)}';
SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' && spoly '{(45d,89.3d),(135d,89.3d),(225d,89.3d),(315d,89.3d)}';

\echo 


\echo SELECT spoly '{(45d,89.2d),(135d,89.2d),(225d,89.2d),(315d,89.2d)}' && spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT spoly '{(45d,89.2d),(135d,89.2d),(225d,89.2d),(315d,89.2d)}' && spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' && spoly '{(0.5d,0.5d),(0.5d,1.5d),(1.5d,1.5d),(1.5d,0.5d)}';
SELECT spoly '{(0d,0d),(0d,1d),(1d,1d),(1d,0d)}' && spoly '{(0.5d,0.5d),(0.5d,1.5d),(1.5d,1.5d),(1.5d,0.5d)}';

\echo SELECT spoly '{(0d,88d),(90d,88d),(180d,88d),(270d,88d)}' && spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT spoly '{(0d,88d),(90d,88d),(180d,88d),(270d,88d)}' && spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo 


\echo --- should be false
--- should be false

\echo SELECT spoly '{(0d,-88d),(90d,-88d),(180d,-88d),(270d,-88d)}' && spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';
SELECT spoly '{(0d,-88d),(90d,-88d),(180d,-88d),(270d,-88d)}' && spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}';

\echo SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' && spoly '{(0d,-88d),(90d,-88d),(180d,-88d),(270d,-88d)}';
SELECT spoly '{(0d,89d),(90d,89d),(180d,89d),(270d,89d)}' && spoly '{(0d,-88d),(90d,-88d),(180d,-88d),(270d,-88d)}';

\echo SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' && spoly '{(3d,-1d),(3d,1d),(5d,1d),(5d,-1d)}';
SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' && spoly '{(3d,-1d),(3d,1d),(5d,1d),(5d,-1d)}';

\echo SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' && spoly '{(-1d,3d),(-1d,5d),(1d,5d),(1d,3d)}';
SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' && spoly '{(-1d,3d),(-1d,5d),(1d,5d),(1d,3d)}';

\echo SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' && spoly '{(179d,-1d),(179d,1d),(181d,1d),(181d,-1d)}';
SELECT spoly '{(-1d,-1d),(-1d,1d),(1d,1d),(1d,-1d)}' && spoly '{(179d,-1d),(179d,1d),(181d,1d),(181d,-1d)}';

\echo 
