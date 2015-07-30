-- Create tables

SET client_min_messages = 'warning';

CREATE TABLE spheretmp1 (p spoint);

\copy spheretmp1 from 'data/test_spherepoint.data'
\copy spheretmp1 from 'data/test_spherepoint.data'
\copy spheretmp1 from 'data/test_spherepoint.data'
\copy spheretmp1 from 'data/test_spherepoint.data'

CREATE TABLE spheretmp2 (c scircle);

\copy spheretmp2 from 'data/test_spherecircle.data'
\copy spheretmp2 from 'data/test_spherecircle.data'
\copy spheretmp2 from 'data/test_spherecircle.data'
\copy spheretmp2 from 'data/test_spherecircle.data'

CREATE TABLE spheretmp3 (b sbox);
\copy spheretmp3 from 'data/test_spherebox.data'

CREATE TABLE spheretmp4 AS                
  SELECT sline ( p , p - strans '-15d,-15d,-15d,ZXZ' ) AS l
  FROM spheretmp1;

CREATE TABLE spheretmp5 (id int PRIMARY KEY , p spoly );
\copy spheretmp5 from 'data/test_spherepolygon.data'

CREATE TABLE spheretmp6 (id int PRIMARY KEY , p spath );
\copy spheretmp6 from 'data/test_spherepath.data'

-- Aggregate data from tables

CREATE TABLE spheretmp7 (p spoint);
\copy spheretmp7 from 'data/test_spherepolygon_aggregate.data'
SELECT spoly(p) FROM spheretmp7;
CREATE TABLE spheretmp8 (p spoint);
\copy spheretmp8 from 'data/test_spherepoint.data'
SELECT spath(p) FROM spheretmp8 WHERE p IS NOT NULL;
