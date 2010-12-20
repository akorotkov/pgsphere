\set ECHO none
SELECT set_sphere_output_precision(8);
\set ECHO all

-- checking Euler transformation operators

SELECT strans '-10d,0d,10d,ZZZ'  = '-10d,0d,10d,XXX' ;
SELECT strans '-40d,0d,40d,ZZZ' <> '-40d,0d,40d,XXX' ;

