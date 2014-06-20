--
-- ellipse and path
--
  
-- negators , commutator @,&&

SELECT spath '{(280d, -9d),(280d, -8d)}'   @  sellipse '<{10d,5d},(280d,-20d),90d>';
SELECT spath '{(280d, -9d),(280d,-12d)}'   @  sellipse '<{10d,5d},(280d,-20d),90d>';
SELECT spath '{(280d,-11d),(280d,-12d)}'   @  sellipse '<{10d,5d},(280d,-20d),90d>';
SELECT spath '{(280d, -9d),(280d, -8d)}'  &&  sellipse '<{10d,5d},(280d,-20d),90d>';
SELECT spath '{(280d, -9d),(280d,-12d)}'  &&  sellipse '<{10d,5d},(280d,-20d),90d>';
SELECT spath '{(280d,-11d),(280d,-12d)}'  &&  sellipse '<{10d,5d},(280d,-20d),90d>';
SELECT spath '{(280d, -9d),(280d, -8d)}'  !@  sellipse '<{10d,5d},(280d,-20d),90d>';
SELECT spath '{(280d, -9d),(280d,-12d)}'  !@  sellipse '<{10d,5d},(280d,-20d),90d>';
SELECT spath '{(280d,-11d),(280d,-12d)}'  !@  sellipse '<{10d,5d},(280d,-20d),90d>';
SELECT spath '{(280d, -9d),(280d, -8d)}' !&&  sellipse '<{10d,5d},(280d,-20d),90d>';
SELECT spath '{(280d, -9d),(280d,-12d)}' !&&  sellipse '<{10d,5d},(280d,-20d),90d>';
SELECT spath '{(280d,-11d),(280d,-12d)}' !&&  sellipse '<{10d,5d},(280d,-20d),90d>'; 
SELECT sellipse '<{10d,5d},(280d,-20d),90d>'   ~  spath '{(280d, -9d),(280d, -8d)}'; 
SELECT sellipse '<{10d,5d},(280d,-20d),90d>'   ~  spath '{(280d, -9d),(280d,-12d)}'; 
SELECT sellipse '<{10d,5d},(280d,-20d),90d>'   ~  spath '{(280d,-11d),(280d,-12d)}'; 
SELECT sellipse '<{10d,5d},(280d,-20d),90d>'   &&  spath '{(280d, -9d),(280d, -8d)}';
SELECT sellipse '<{10d,5d},(280d,-20d),90d>'   &&  spath '{(280d, -9d),(280d,-12d)}';
SELECT sellipse '<{10d,5d},(280d,-20d),90d>'   &&  spath '{(280d,-11d),(280d,-12d)}';
SELECT sellipse '<{10d,5d},(280d,-20d),90d>'  !~  spath '{(280d, -9d),(280d, -8d)}'; 
SELECT sellipse '<{10d,5d},(280d,-20d),90d>'  !~  spath '{(280d, -9d),(280d,-12d)}'; 
SELECT sellipse '<{10d,5d},(280d,-20d),90d>'  !~  spath '{(280d,-11d),(280d,-12d)}'; 
SELECT sellipse '<{10d,5d},(280d,-20d),90d>'  !&&  spath '{(280d, -9d),(280d, -8d)}';
SELECT sellipse '<{10d,5d},(280d,-20d),90d>'  !&&  spath '{(280d, -9d),(280d,-12d)}';
SELECT sellipse '<{10d,5d},(280d,-20d),90d>'  !&&  spath '{(280d,-11d),(280d,-12d)}';

-- path is a line , ellipse is point
SELECT spath '{(280d, -8d),(280d, -9d)}'   @  sellipse '<{0d,0d},(280d,-20d),90d>';
SELECT spath '{(280d, -8d),(280d, -9d)}'   @  sellipse '<{0d,0d},(280d, -8d),90d>';
SELECT spath '{(280d, -8d),(280d, -9d)}'  &&  sellipse '<{0d,0d},(280d,-20d),90d>';
SELECT spath '{(280d, -8d),(280d, -9d)}'  &&  sellipse '<{0d,0d},(280d, -8d),90d>';
-- path is a line , ellipse is circle
SELECT spath '{(280d, -8d),(280d, -9d)}'   @  sellipse '<{5d,5d},(280d,-20d),90d>';
SELECT spath '{(280d, -8d),(280d, -9d)}'   @  sellipse '<{5d,5d},(280d, -8d),90d>';
SELECT spath '{(280d, -8d),(280d, -9d)}'  &&  sellipse '<{5d,5d},(280d,-20d),90d>';
SELECT spath '{(280d, -8d),(280d, -9d)}'  &&  sellipse '<{5d,5d},(280d, -8d),90d>';
-- path is a line , ellipse is path
SELECT spath '{(280d, -8d),(280d, -9d)}'   @  sellipse '<{5d,0d},(280d,-20d),90d>';
SELECT spath '{(280d, -8d),(280d, -9d)}'   @  sellipse '<{5d,0d},(280d, -8d),90d>';
SELECT spath '{(280d, -8d),(280d, -9d)}'  &&  sellipse '<{5d,0d},(280d,-20d),90d>';
SELECT spath '{(280d, -8d),(280d, -9d)}'  &&  sellipse '<{5d,0d},(280d, -8d),90d>';
-- path is a line , ellipse is a real ellipse
SELECT spath '{(280d, -8d),(280d, -9d)}'   @  sellipse '<{10d,5d},(280d,-20d),90d>';
SELECT spath '{(280d, -8d),(280d, -9d)}'   @  sellipse '<{10d,5d},(280d, -8d),90d>';
SELECT spath '{(280d, -8d),(280d, -9d)}'  &&  sellipse '<{10d,5d},(280d,-20d),90d>';
SELECT spath '{(280d, -8d),(280d, -9d)}'  &&  sellipse '<{10d,5d},(280d, -8d),90d>';

--
-- checking path other operators
--
  
\set poly  'spoly \'{(0.1,0),(0.2,0),(0.2,0.1),(0.3,0.1),(0.3,-0.1),(0.4,-0.1),(0.5,0.1),(0.4,0.2),(0.1,0.2)}\''
\set path1 'spath \'{(0.1,0),(0.2,0),(0.2,0.1),(0.3,0.1),(0.3,-0.1),(0.4,-0.1),(0.5,0.1),(0.4,0.2),(0.1,0.2)}\''
\set path2 'spath \'{(0,0),(1,0),(2,0),(3,0)}\''
\set path3 'spath \'{(0,0),(0,1),(0,1.5)}\''

SELECT @-@ spath '{(0,0),(1,0),(2,0),(3,0)}';
SELECT :path1 =  :path2;
SELECT :path1 =  :path1;
SELECT :path1 <> :path2;
SELECT :path1 <> :path1;
SELECT :poly  && :path1;
SELECT :path1 && :poly ;
SELECT :path1 @  :poly ;
SELECT :path2 @  :poly ;
SELECT :path1 && :path1;
SELECT :path1 && :path1;
SELECT :poly  && :path2;
SELECT :path2 && :poly ;
SELECT :path2 && :path1;
SELECT :poly  && :path3;
SELECT :path3 && :poly ;
SELECT :path3 && :path1;
SELECT :path3 && :path2;
SELECT :path1 @  scircle '<(0,1),1>';
SELECT :path3 @  scircle '<(0,1),1>';
SELECT :path3 @  scircle '<(0,1),0.7>';
SELECT :path1 && scircle '<(0,1),1>';  
SELECT :path3 && scircle '<(0,1),1>';  
SELECT :path3 && scircle '<(0,1),0.7>';
SELECT :path3 && scircle '<(0,-1),0.7>';
SELECT :path3 @  scircle '<(0,-1),0.7>';
SELECT :path3 && sline ( spoint '(0,-1)', spoint '(0,1)' );
SELECT :path3 && sline ( spoint '(-1,0)', spoint '(1,0)' );
SELECT :path3 && sline ( spoint '(-1,0)', spoint '(-0.3,0)' );
SELECT spath '{(0.11,0.15),(0.12,0.15),(0.13,0.15)}' @ :poly; 

-- create path
SELECT spath(data.p) FROM ( SELECT spoint '(0,1)' as p UNION ALL SELECT spoint '(1,1)' UNION ALL SELECT '(1,0)' ) AS data ;

SELECT set_sphere_output( 'DEG' );

-- test stored data
SELECT spoint(p,2) FROM spheretmp6 WHERE id=2;

