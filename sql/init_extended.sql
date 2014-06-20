-- indexed operations.....

-- spoint_data and scircle_data tables have to be created and indexed using

\! testsuite/gen_point.pl 1 > results/gen_point_1.sql
\i results/gen_point_1.sql

-- and

\! testsuite/gen_circle.pl 1 0.1 > results/gen_circle_1_0.1.sql
\i results/gen_circle_1_0.1.sql

--

\! testsuite/gen_poly.pl 1 0.1 4 > results/gen_poly_1_0.1_4.sql
\i results/gen_poly_1_0.1_4.sql
