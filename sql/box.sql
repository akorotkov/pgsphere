
--
-- sbox and spoint 
--

SELECT spoint '(0d,90d)' @ sbox '((0d,80d),(360d,90d))' ;

SELECT sbox '((309d,309d),(313d,313d))' ~ spoint '(310d,310d)' ;
SELECT spoint '(310d,310d)' @ sbox '((309d,309d),(313d,313d))' ;
SELECT sbox '((309d,309d),(313d,313d))' ~ spoint '(10d,10d)' ;
SELECT spoint '(10d,10d)' @ sbox '((309d,309d),(313d,313d))' ;

SELECT sbox '((309d,309d),(313d,313d))' !~ spoint '(310d,310d)' ;
SELECT spoint '(310d,310d)' !@ sbox '((309d,309d),(313d,313d))' ;
SELECT sbox '((309d,309d),(313d,313d))' !~ spoint '(10d,10d)' ;
SELECT spoint '(10d,10d)' !@ sbox '((309d,309d),(313d,313d))' ;

SELECT sbox '((10d,10d),(20d,20d))' ~ spoint '(10d,10d)';
SELECT sbox '((10d,10d),(20d,20d))' ~ spoint '(10d,20d)';
SELECT sbox '((10d,10d),(20d,20d))' ~ spoint '(20d,10d)';
SELECT sbox '((10d,10d),(20d,20d))' ~ spoint '(20d,20d)';

SELECT sbox '((310d,10d),(320d,20d))' ~ spoint '(310d,10d)';
SELECT sbox '((310d,10d),(320d,20d))' ~ spoint '(310d,20d)';
SELECT sbox '((310d,10d),(320d,20d))' ~ spoint '(320d,10d)';
SELECT sbox '((310d,10d),(320d,20d))' ~ spoint '(320d,20d)';

SELECT sbox '((310d,10d),(320d,20d))' ~ spoint '(310d,15d)';
SELECT sbox '((310d,10d),(320d,20d))' ~ spoint '(315d,20d)';
SELECT sbox '((310d,10d),(320d,20d))' ~ spoint '(315d,10d)';
SELECT sbox '((310d,10d),(320d,20d))' ~ spoint '(320d,15d)';

SELECT spoint '(320d, 15d)' @ sbox '((310d,10d),(320d,20d))' ;
SELECT spoint '(140d,-15d)' @ sbox '((310d,10d),(320d,20d))' ;

SELECT sbox '((310d,10d),(20d,20d))' ~ spoint '(300d,10d)';
SELECT sbox '((310d,10d),(20d,20d))' ~ spoint '(300d,15d)';
SELECT sbox '((310d,10d),(20d,20d))' ~ spoint '(300d,20d)';
SELECT sbox '((310d,10d),(20d,20d))' ~ spoint '(330d,10d)';
SELECT sbox '((310d,10d),(20d,20d))' ~ spoint '(330d,15d)';
SELECT sbox '((310d,10d),(20d,20d))' ~ spoint '(330d,20d)';
SELECT sbox '((310d,10d),(20d,20d))' ~ spoint '(0d,10d)';
SELECT sbox '((310d,10d),(20d,20d))' ~ spoint '(0d,15d)';
SELECT sbox '((310d,10d),(20d,20d))' ~ spoint '(0d,20d)';
SELECT sbox '((310d,10d),(20d,20d))' ~ spoint '(10d,10d)';
SELECT sbox '((310d,10d),(20d,20d))' ~ spoint '(10d,15d)';
SELECT sbox '((310d,10d),(20d,20d))' ~ spoint '(10d,20d)';
SELECT sbox '((310d,10d),(20d,20d))' ~ spoint '(30d,10d)';
SELECT sbox '((310d,10d),(20d,20d))' ~ spoint '(30d,15d)';
SELECT sbox '((310d,10d),(20d,20d))' ~ spoint '(30d,20d)';
SELECT sbox '((310d,10d),(20d,20d))' ~ spoint '(180d,10d)';
SELECT sbox '((310d,10d),(20d,20d))' ~ spoint '(180d,15d)';
SELECT sbox '((310d,10d),(20d,20d))' ~ spoint '(180d,20d)';

SELECT sbox '((310d,-90d),(20d,-80d))' ~ spoint '(300d,10d)';
SELECT sbox '((310d,-90d),(20d,-80d))' ~ spoint '(320d,-80d)';
SELECT sbox '((310d,-90d),(20d,-80d))' ~ spoint '(320d,-85d)';
SELECT sbox '((310d,-90d),(20d,-80d))' ~ spoint '(320d,-90d)';
SELECT sbox '((310d,-90d),(20d,-80d))' ~ spoint '(180d,-90d)';
SELECT sbox '((310d,-90d),(20d,-80d))' ~ spoint '(180d,-89.99d)';

SELECT sbox '((310d,80d),(20d,90d))' ~ spoint '(300d,10d)';
SELECT sbox '((310d,80d),(20d,90d))' ~ spoint '(320d,80d)';
SELECT sbox '((310d,80d),(20d,90d))' ~ spoint '(320d,85d)';
SELECT sbox '((310d,80d),(20d,90d))' ~ spoint '(320d,90d)';
SELECT sbox '((310d,80d),(20d,90d))' ~ spoint '(180d,90d)';
SELECT sbox '((310d,80d),(20d,90d))' ~ spoint '(180d,89.99d)';

SELECT sbox '((0d,-90d),(360d,-80d))' ~ spoint '(300d,10d)';
SELECT sbox '((0d,-90d),(360d,-80d))' ~ spoint '(320d,-80d)';
SELECT sbox '((0d,-90d),(360d,-80d))' ~ spoint '(320d,-85d)';
SELECT sbox '((0d,-90d),(360d,-80d))' ~ spoint '(320d,-90d)';
SELECT sbox '((0d,-90d),(360d,-80d))' ~ spoint '(180d,-90d)';
SELECT sbox '((0d,-90d),(360d,-80d))' ~ spoint '(180d,-89.99d)';

SELECT sbox '((0d,80d),(360d,90d))' ~ spoint '(300d,10d)';
SELECT sbox '((0d,80d),(360d,90d))' ~ spoint '(320d,80d)';
SELECT sbox '((0d,80d),(360d,90d))' ~ spoint '(320d,85d)';
SELECT sbox '((0d,80d),(360d,90d))' ~ spoint '(320d,90d)';
SELECT sbox '((0d,80d),(360d,90d))' ~ spoint '(180d,90d)';
SELECT sbox '((0d,80d),(360d,90d))' ~ spoint '(180d,89.99d)';

SELECT sbox '((0d,-10d),(360d,20d))' ~ spoint '(270d,-11d)';
SELECT sbox '((0d,-10d),(360d,20d))' ~ spoint '(270d,-10d)';
SELECT sbox '((0d,-10d),(360d,20d))' ~ spoint '(270d, -5d)';
SELECT sbox '((0d,-10d),(360d,20d))' ~ spoint '(270d,  0d)';
SELECT sbox '((0d,-10d),(360d,20d))' ~ spoint '(270d,  5d)';
SELECT sbox '((0d,-10d),(360d,20d))' ~ spoint '(270d, 20d)';
SELECT sbox '((0d,-10d),(360d,20d))' ~ spoint '(270d, 21d)';

SELECT spoint '(320d, 15d)' !@ sbox '((310d,10d),(320d,20d))' ;
SELECT spoint '(140d,-15d)' !@ sbox '((310d,10d),(320d,20d))' ;

SELECT sbox '((10d,10d),(20d,20d))' !~ spoint '(10d,10d)';
SELECT sbox '((270d,-10d),(300d,20d))' !~ spoint '(10d,10d)';

--
-- sbox (as point)  and spoint
--

SELECT sbox '((310d,310d),(310d,310d))' ~ spoint '(310d,310d)' ;
SELECT spoint '(310d,310d)' @ sbox '((310d,310d),(310d,310d))' ;
SELECT sbox '((310d,310d),(310d,310d))' ~ spoint '(10d,10d)' ;
SELECT spoint '(11d,11d)' @ sbox '((310d,310d),(310d,310d))' ;

--
-- sbox and circle
--

-- Check negators / commutators

SELECT scircle '<(0d, 70d),1d>' && sbox '((-10d, 60d),(10d, 80d))';
SELECT sbox '((-10d, 60d),(10d, 80d))' && scircle '<(0d, 70d),1d>';
SELECT scircle '<(0d, 70d),1d>' !&& sbox '((-10d, 60d),(10d, 80d))';
SELECT sbox '((-10d, 60d),(10d, 80d))' !&& scircle '<(0d, 70d),1d>';

SELECT scircle '<(0d, 50d),1d>' && sbox '((-10d, 60d),(10d, 80d))';
SELECT sbox '((-10d, 60d),(10d, 80d))' && scircle '<(0d, 50d),1d>';
SELECT scircle '<(0d, 50d),1d>' !&& sbox '((-10d, 60d),(10d, 80d))';
SELECT sbox '((-10d, 60d),(10d, 80d))' !&& scircle '<(0d, 50d),1d>';

SELECT scircle '<(0d, 70d),1d>' @ sbox '((-10d, 60d),(10d, 80d))';
SELECT sbox '((-10d, 60d),(10d, 80d))' @ scircle '<(0d, 70d),1d>';
SELECT scircle '<(0d, 70d),1d>' !@ sbox '((-10d, 60d),(10d, 80d))';
SELECT sbox '((-10d, 60d),(10d, 80d))' !@ scircle '<(0d, 70d),1d>';

SELECT scircle '<(0d, 50d),1d>' @ sbox '((-10d, 60d),(10d, 80d))';
SELECT sbox '((-10d, 60d),(10d, 80d))' @ scircle '<(0d, 50d),1d>';
SELECT scircle '<(0d, 50d),1d>' !@ sbox '((-10d, 60d),(10d, 80d))';
SELECT sbox '((-10d, 60d),(10d, 80d))' !@ scircle '<(0d, 50d),1d>';

SELECT scircle '<(0d, 70d),1d>' ~ sbox '((-10d, 60d),(10d, 80d))';
SELECT sbox '((-10d, 60d),(10d, 80d))' ~ scircle '<(0d, 70d),1d>';
SELECT scircle '<(0d, 70d),1d>' !~ sbox '((-10d, 60d),(10d, 80d))';
SELECT sbox '((-10d, 60d),(10d, 80d))' !~ scircle '<(0d, 70d),1d>';

SELECT scircle '<(0d, 50d),1d>' ~ sbox '((-10d, 60d),(10d, 80d))';
SELECT sbox '((-10d, 60d),(10d, 80d))' ~ scircle '<(0d, 50d),1d>';
SELECT scircle '<(0d, 50d),1d>' !~ sbox '((-10d, 60d),(10d, 80d))';
SELECT sbox '((-10d, 60d),(10d, 80d))' !~ scircle '<(0d, 50d),1d>';


-- Other Checks

SELECT scircle '<(0d, 90d),1d>'  @ sbox '((0d, 80d),(360d, 90d))'; 
SELECT scircle '<(0d,-90d),1d>'  @ sbox '((0d,-80d),(360d,-90d))'; 
SELECT scircle '<(0d, 90d),1d>' && sbox '((0d, 80d),(360d, 90d))'; 
SELECT scircle '<(0d,-90d),1d>' && sbox '((0d,-80d),(360d,-90d))'; 

SELECT scircle '<(0d, 90d),1d>'  @ sbox '((0d, 80d),(360d, 89d))'; 
SELECT scircle '<(0d,-90d),1d>'  @ sbox '((0d,-80d),(360d,-89d))'; 
SELECT scircle '<(0d, 90d),1d>' && sbox '((0d, 80d),(360d, 89d))'; 
SELECT scircle '<(0d,-90d),1d>' && sbox '((0d,-80d),(360d,-89d))'; 

SELECT scircle '<(0d, 90d),1d>'  @ sbox '((0d, 80d),(360d, 88d))'; 
SELECT scircle '<(0d,-90d),1d>'  @ sbox '((0d,-80d),(360d,-88d))'; 
SELECT scircle '<(0d, 90d),1d>' && sbox '((0d, 80d),(360d, 88d))'; 
SELECT scircle '<(0d,-90d),1d>' && sbox '((0d,-80d),(360d,-88d))'; 

SELECT scircle '<(0d, 90d),1d>'  @ sbox '((0d, 80d),(270d, 90d))'; 
SELECT scircle '<(0d,-90d),1d>'  @ sbox '((0d,-80d),(270d,-90d))'; 
SELECT scircle '<(0d, 90d),1d>' && sbox '((0d, 80d),(270d, 90d))'; 
SELECT scircle '<(0d,-90d),1d>' && sbox '((0d,-80d),(270d,-90d))'; 

SELECT scircle '<(0d, 90d),1d>'  @ sbox '((0d, 80d),(270d, 89d))'; 
SELECT scircle '<(0d,-90d),1d>'  @ sbox '((0d,-80d),(270d,-89d))'; 
SELECT scircle '<(0d, 90d),1d>' && sbox '((0d, 80d),(270d, 89d))'; 
SELECT scircle '<(0d,-90d),1d>' && sbox '((0d,-80d),(270d,-89d))'; 

SELECT scircle '<(0d, 90d),1d>'  @ sbox '((0d, 80d),(270d, 88d))'; 
SELECT scircle '<(0d,-90d),1d>'  @ sbox '((0d,-80d),(270d,-88d))'; 
SELECT scircle '<(0d, 90d),1d>' && sbox '((0d, 80d),(270d, 88d))'; 
SELECT scircle '<(0d,-90d),1d>' && sbox '((0d,-80d),(270d,-88d))'; 

SELECT scircle '<(0d, 90d),1d>'  @ sbox '((0d, 80d),(90d, 90d))'; 
SELECT scircle '<(0d,-90d),1d>'  @ sbox '((0d,-80d),(90d,-90d))'; 
SELECT scircle '<(0d, 90d),1d>' && sbox '((0d, 80d),(90d, 90d))'; 
SELECT scircle '<(0d,-90d),1d>' && sbox '((0d,-80d),(90d,-90d))'; 

SELECT scircle '<(0d, 90d),1d>'  @ sbox '((0d, 80d),(90d, 89d))'; 
SELECT scircle '<(0d,-90d),1d>'  @ sbox '((0d,-80d),(90d,-89d))'; 
SELECT scircle '<(0d, 90d),1d>' && sbox '((0d, 80d),(90d, 89d))'; 
SELECT scircle '<(0d,-90d),1d>' && sbox '((0d,-80d),(90d,-89d))'; 

SELECT scircle '<(0d, 90d),1d>'  @ sbox '((0d, 80d),(90d, 88d))'; 
SELECT scircle '<(0d,-90d),1d>'  @ sbox '((0d,-80d),(90d,-88d))'; 
SELECT scircle '<(0d, 90d),1d>' && sbox '((0d, 80d),(90d, 88d))'; 
SELECT scircle '<(0d,-90d),1d>' && sbox '((0d,-80d),(90d,-88d))'; 

SELECT scircle '<(0d, 89d),1d>'  @ sbox '((0d, 80d),(90d, 90d))'; 
SELECT scircle '<(0d,-89d),1d>'  @ sbox '((0d,-80d),(90d,-90d))'; 
SELECT scircle '<(0d, 89d),1d>' && sbox '((0d, 80d),(90d, 90d))'; 
SELECT scircle '<(0d,-89d),1d>' && sbox '((0d,-80d),(90d,-90d))'; 

SELECT scircle '<(0d, 89d),1d>'  @ sbox '((0d, 80d),(90d, 89d))'; 
SELECT scircle '<(0d,-89d),1d>'  @ sbox '((0d,-80d),(90d,-89d))'; 
SELECT scircle '<(0d, 89d),1d>' && sbox '((0d, 80d),(90d, 89d))'; 
SELECT scircle '<(0d,-89d),1d>' && sbox '((0d,-80d),(90d,-89d))'; 

SELECT scircle '<(0d, 89d),1d>'  @ sbox '((0d, 80d),(90d, 88d))'; 
SELECT scircle '<(0d,-89d),1d>'  @ sbox '((0d,-80d),(90d,-88d))'; 
SELECT scircle '<(0d, 89d),1d>' && sbox '((0d, 80d),(90d, 88d))'; 
SELECT scircle '<(0d,-89d),1d>' && sbox '((0d,-80d),(90d,-88d))'; 

SELECT scircle '<(0d, 90d),10d>'  @ sbox '((0d, 80d),(360d, 90d))';
SELECT scircle '<(0d, 90d),10d>'  ~ sbox '((0d, 80d),(360d, 90d))'; 
SELECT scircle '<(0d, 90d),10d>'  && sbox '((0d, 80d),(360d, 90d))';


--
-- sbox and line
--

SELECT sline( spoint '(0d,0d)', spoint '(0d,10d)' ) @ sbox '((0d,0d),(10d,10d))';
SELECT sline( spoint '(0d,0d)', spoint '(0d,0d)' )  @ sbox '((0d,0d),(10d,10d))';
SELECT sline( spoint '(0d,10d)', spoint '(10d,10d)' ) @ sbox '((0d,0d),(10d,10d))';

SELECT sline( spoint '(0d,0d)', spoint '(0d,10d)' ) && sbox '((0d,0d),(10d,10d))';
SELECT sline( spoint '(0d,0d)', spoint '(0d,0d)' )  && sbox '((0d,0d),(10d,10d))';
SELECT sline( spoint '(0d,10d)', spoint '(10d,10d)' ) && sbox '((0d,0d),(10d,10d))';

-- sbox is point, sline is point

SELECT sbox '((310d,310d),(310d,310d))' ~ sline ( spoint '(310d,310d)', spoint '(310d,310d)' ) ;
SELECT sline ( spoint '(310d,310d)', spoint '(310d,310d)' ) @ sbox '((310d,310d),(310d,310d))' ;
SELECT sbox '((310d,310d),(310d,310d))' ~ sline ( spoint '(10d,10d)', spoint '(10d,10d)' ) ;
SELECT sline ( spoint '(11d,11d)' , spoint '(11d,11d)' ) @ sbox '((310d,310d),(310d,310d))' ;
SELECT sline ( spoint '(11d,90d)' , spoint '(11d,90d)' ) @ sbox '((310d,90d),(310d,90d))' ;
SELECT sbox '((310d,90d),(310d,90d))' ~ sline ( spoint '(11d,90d)' , spoint '(11d,90d)' ) ;

SELECT sbox '((310d,310d),(310d,310d))' && sline ( spoint '(310d,310d)', spoint '(310d,310d)' ) ;
SELECT sline ( spoint '(310d,310d)', spoint '(310d,310d)' ) && sbox '((310d,310d),(310d,310d))' ;
SELECT sbox '((310d,310d),(310d,310d))' && sline ( spoint '(10d,10d)', spoint '(10d,10d)' ) ;
SELECT sline ( spoint '(11d,11d)' , spoint '(11d,11d)' ) && sbox '((310d,310d),(310d,310d))' ;
SELECT sline ( spoint '(11d,90d)' , spoint '(11d,90d)' ) && sbox '((310d,90d),(310d,90d))' ;
SELECT sbox '((310d,90d),(310d,90d))' && sline ( spoint '(11d,90d)' , spoint '(11d,90d)' ) ;


-- sbox is point only

SELECT sbox '((310d,10d),(310d,10d))'  ~ sline ( spoint '(310d,10d)', spoint '(310d,20d)' ) ;
SELECT sbox '((310d,10d),(310d,10d))' && sline ( spoint '(310d,10d)', spoint '(310d,20d)' ) ;
SELECT sline ( spoint '(310d,10d)', spoint '(310d,20d)' )   @ sbox '((310d,10d),(310d,10d))' ;
SELECT sline ( spoint '(310d,10d)', spoint '(310d,20d)' )  && sbox '((310d,10d),(310d,10d))' ;
SELECT sbox '((310d,10d),(310d,10d))'  ~ sline ( spoint '(10d,10d)', spoint '(10d,20d)' ) ;
SELECT sbox '((310d,10d),(310d,10d))' && sline ( spoint '(10d,10d)', spoint '(10d,20d)' ) ;
SELECT sline ( spoint '(11d,11d)' , spoint '(21d,11d)' )  @ sbox '((310d,10d),(310d,10d))' ;
SELECT sline ( spoint '(11d,11d)' , spoint '(21d,11d)' ) && sbox '((310d,10d),(310d,10d))' ;
SELECT sline ( spoint '(11d,90d)' , spoint '(11d,80d)' )  @ sbox '((310d,90d),(310d,90d))' ;
SELECT sline ( spoint '(11d,90d)' , spoint '(11d,80d)' ) && sbox '((310d,90d),(310d,90d))' ;
SELECT sbox '((310d,90d),(310d,90d))'  ~ sline ( spoint '(11d,90d)' , spoint '(11d,80d)' ) ;
SELECT sbox '((310d,90d),(310d,90d))' && sline ( spoint '(11d,90d)' , spoint '(11d,80d)' ) ;

-- sline is point only

SELECT sbox '((310d,10d),(320d,20d))'  ~ sline ( spoint '(310d,10d)', spoint '(310d,10d)' ) ;
SELECT sbox '((310d,10d),(320d,20d))' && sline ( spoint '(310d,10d)', spoint '(310d,10d)' ) ;
SELECT sbox '((310d,10d),(320d,20d))'  ~ sline ( spoint '(315d,15d)', spoint '(315d,15d)' ) ;
SELECT sbox '((310d,10d),(320d,20d))' && sline ( spoint '(315d,15d)', spoint '(315d,15d)' ) ;
SELECT sline ( spoint '(310d,10d)', spoint '(310d,10d)' )   @ sbox '((310d,10d),(320d,20d))' ;
SELECT sline ( spoint '(310d,10d)', spoint '(310d,10d)' )  && sbox '((310d,10d),(320d,20d))' ;
SELECT sline ( spoint '(315d,15d)', spoint '(315d,15d)' )   @ sbox '((310d,10d),(320d,20d))' ;
SELECT sline ( spoint '(315d,15d)', spoint '(315d,15d)' )  && sbox '((310d,10d),(320d,20d))' ;
SELECT sbox '((310d,10d),(320d,20d))'  ~ sline ( spoint '(10d,10d)', spoint '(10d,10d)' ) ;
SELECT sbox '((310d,10d),(320d,20d))' && sline ( spoint '(10d,10d)', spoint '(10d,10d)' ) ;
SELECT sline ( spoint '(11d, 11d)' , spoint '(11d,11d)' )  @ sbox '((310d,10d),(320d,20d))' ;
SELECT sline ( spoint '(11d, 11d)' , spoint '(11d,11d)' ) && sbox '((310d,10d),(320d,20d))' ;
SELECT sline ( spoint '(11d, 90d)' , spoint '(11d,90d)' )  @ sbox '((310d,80d),(320d,90d))' ;
SELECT sline ( spoint '(11d, 90d)' , spoint '(11d,90d)' ) && sbox '((310d,80d),(320d,90d))' ;
SELECT sline ( spoint '(11d, 85d)' , spoint '(11d,85d)' )  @ sbox '((310d,80d),(320d,90d))' ;
SELECT sline ( spoint '(11d, 85d)' , spoint '(11d,85d)' ) && sbox '((310d,80d),(320d,90d))' ;
SELECT sline ( spoint '(315d,85d)' , spoint '(315d,85d)' )  @ sbox '((310d,80d),(320d,90d))' ;
SELECT sline ( spoint '(315d,85d)' , spoint '(315d,85d)' ) && sbox '((310d,80d),(320d,90d))' ;
SELECT sbox '((310d,80d),(320d,90d))'  ~ sline ( spoint '(11d,90d)' , spoint '(11d,90d)' ) ;
SELECT sbox '((310d,80d),(320d,90d))' && sline ( spoint '(11d,90d)' , spoint '(11d,90d)' ) ;
SELECT sbox '((310d,80d),(320d,90d))'  ~ sline ( spoint '(315d,85d)' , spoint '(315d,85d)' ) ;
SELECT sbox '((310d,80d),(320d,90d))' && sline ( spoint '(315d,85d)' , spoint '(315d,85d)' ) ;

-- sline / sbox near pole

SELECT sbox '((20d,80d),(200d,90d))'  ~ sline ( spoint '(200d,85d)', spoint '(20d,85d)' ) ;
SELECT sbox '((20d,80d),(200d,90d))' && sline ( spoint '(200d,85d)', spoint '(20d,85d)' ) ;
SELECT sbox '((10d,80d),(210d,90d))'  ~ sline ( spoint '(200d,81d)', spoint '(20d,81d)' ) ;
SELECT sbox '((10d,80d),(210d,90d))' && sline ( spoint '(200d,81d)', spoint '(20d,81d)' ) ;
SELECT sbox '((10d,80d),(211d,90d))'  ~ sline ( spoint '(200d,81d)', spoint '(20d,81d)' ) ;
SELECT sbox '((10d,80d),(211d,90d))' && sline ( spoint '(200d,81d)', spoint '(20d,81d)' ) ;


SELECT sbox '((190d,80d),(199d,90d))'  ~ sline ( spoint '(200d,85d)', spoint '(20d,90d)' ) ;
SELECT sbox '((190d,80d),(199d,90d))' && sline ( spoint '(200d,85d)', spoint '(20d,90d)' ) ;
SELECT sbox '((190d,80d),(200d,90d))'  ~ sline ( spoint '(200d,85d)', spoint '(20d,90d)' ) ;
SELECT sbox '((190d,80d),(200d,90d))' && sline ( spoint '(200d,85d)', spoint '(20d,90d)' ) ;
SELECT sbox '((190d,80d),(210d,90d))'  ~ sline ( spoint '(200d,85d)', spoint '(20d,90d)' ) ;
SELECT sbox '((190d,80d),(210d,90d))' && sline ( spoint '(200d,85d)', spoint '(20d,90d)' ) ;
SELECT sbox '((200d,80d),(210d,90d))'  ~ sline ( spoint '(200d,81d)', spoint '(20d,90d)' ) ;
SELECT sbox '((200d,80d),(210d,90d))' && sline ( spoint '(200d,81d)', spoint '(20d,90d)' ) ;
SELECT sbox '((210d,80d),(220d,90d))'  ~ sline ( spoint '(200d,81d)', spoint '(20d,90d)' ) ;
SELECT sbox '((210d,80d),(220d,90d))' && sline ( spoint '(200d,81d)', spoint '(20d,90d)' ) ;

SELECT sbox '((190d,80d),(199d,88d))'  ~ sline ( spoint '(200d,85d)', spoint '(20d,90d)' ) ;
SELECT sbox '((190d,80d),(199d,88d))' && sline ( spoint '(200d,85d)', spoint '(20d,90d)' ) ;
SELECT sbox '((190d,80d),(200d,88d))'  ~ sline ( spoint '(200d,85d)', spoint '(20d,90d)' ) ;
SELECT sbox '((190d,80d),(200d,88d))' && sline ( spoint '(200d,85d)', spoint '(20d,90d)' ) ;
SELECT sbox '((190d,80d),(210d,88d))'  ~ sline ( spoint '(200d,85d)', spoint '(20d,90d)' ) ;
SELECT sbox '((190d,80d),(210d,88d))' && sline ( spoint '(200d,85d)', spoint '(20d,90d)' ) ;
SELECT sbox '((200d,80d),(210d,88d))'  ~ sline ( spoint '(200d,81d)', spoint '(20d,90d)' ) ;
SELECT sbox '((200d,80d),(210d,88d))' && sline ( spoint '(200d,81d)', spoint '(20d,90d)' ) ;
SELECT sbox '((210d,80d),(220d,88d))'  ~ sline ( spoint '(200d,81d)', spoint '(20d,90d)' ) ;
SELECT sbox '((210d,80d),(220d,88d))' && sline ( spoint '(200d,81d)', spoint '(20d,90d)' ) ;

-- sbox near equator

SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(200d,85d)', spoint '( 20d, 85d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(200d,85d)', spoint '( 20d, 85d)' ) ;

SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(200d, 0d)', spoint '(190d,  0d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(200d, 0d)', spoint '(190d,  0d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(200d, 0d)', spoint '(205d,  0d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(200d, 0d)', spoint '(205d,  0d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(202d, 0d)', spoint '(207d,  0d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(202d, 0d)', spoint '(207d,  0d)' ) ;

SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(200d,-5d)', spoint '(200d,  5d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(200d,-5d)', spoint '(200d,  5d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(205d,-5d)', spoint '(205d,  5d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(205d,-5d)', spoint '(205d,  5d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(200d, 0d)', spoint '(200d,  5d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(200d, 0d)', spoint '(200d,  5d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(200d, 0d)', spoint '(200d, 10d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(200d, 0d)', spoint '(200d, 10d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(205d, 0d)', spoint '(205d,  5d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(205d, 0d)', spoint '(205d,  5d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(205d, 0d)', spoint '(205d, 10d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(205d, 0d)', spoint '(205d, 10d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(200d,-5d)', spoint '(200d, 15d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(200d,-5d)', spoint '(200d, 15d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(205d,-5d)', spoint '(205d, 15d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(205d,-5d)', spoint '(205d, 15d)' ) ;

SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(200d, 0d)', spoint '(210d, 10d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(200d, 0d)', spoint '(210d, 10d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(199d,-1d)', spoint '(211d, 11d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(199d,-1d)', spoint '(211d, 11d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(200d, 0d)', spoint '(211d, 11d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(200d, 0d)', spoint '(211d, 11d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(199d,-1d)', spoint '(210d, 10d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(199d,-1d)', spoint '(210d, 10d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(199d,-1d)', spoint '(209d,  9d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(199d,-1d)', spoint '(209d,  9d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(201d, 1d)', spoint '(211d, 11d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(201d, 1d)', spoint '(211d, 11d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(200d, 0d)', spoint '(205d,  5d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(200d, 0d)', spoint '(205d,  5d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(201d, 0d)', spoint '(205d,  5d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(201d, 0d)', spoint '(205d,  5d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(201d, 1d)', spoint '(205d,  5d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(201d, 1d)', spoint '(205d,  5d)' ) ;

SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(200d,10d)', spoint '(210d, 10d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(200d,10d)', spoint '(210d, 10d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(200d,10d)', spoint '(205d, 10d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(200d,10d)', spoint '(205d, 10d)' ) ;

SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(199d,-1d)', spoint '(200d,  0d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(199d,-1d)', spoint '(200d,  0d)' ) ;

SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(200d,10d)', spoint '(200d, 20d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(200d,10d)', spoint '(200d, 20d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(205d,10d)', spoint '(205d, 20d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(205d,10d)', spoint '(205d, 20d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(210d,10d)', spoint '(210d, 20d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(210d,10d)', spoint '(210d, 20d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(200d, 0d)', spoint '(200d, -5d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(200d, 0d)', spoint '(200d, -5d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(205d, 0d)', spoint '(205d, -5d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(205d, 0d)', spoint '(205d, -5d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))'  ~ sline ( spoint '(210d, 0d)', spoint '(210d, -5d)' ) ;
SELECT sbox '((200d,0d),(210d,10d))' && sline ( spoint '(210d, 0d)', spoint '(210d, -5d)' ) ;

SELECT sbox '((200d,0d),(210d,10d))'  ~ sline '( -10d, -10d, 200d, ZXZ ), 20d' ;
SELECT sbox '((200d,0d),(210d,10d))' && sline '( -10d, -10d, 200d, ZXZ ), 20d' ;

-- general position

SELECT sbox '((170d,-50d),(190d,-40d))'   ~ sline ( spoint '(170d,  0d)', spoint '(190d,   0d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))'  && sline ( spoint '(170d,  0d)', spoint '(190d,   0d)' ) ;

SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(170d, -40d)', spoint '(190d, -40d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(170d, -40d)', spoint '(190d, -40d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(170d, -50d)', spoint '(190d, -50d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(170d, -50d)', spoint '(190d, -50d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(171d, -40d)', spoint '(189d, -40d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(171d, -40d)', spoint '(189d, -40d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(171d, -50d)', spoint '(189d, -50d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(171d, -50d)', spoint '(189d, -50d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(171d, -40d)', spoint '(191d, -40d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(171d, -40d)', spoint '(191d, -40d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(171d, -50d)', spoint '(191d, -50d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(171d, -50d)', spoint '(191d, -50d)' ) ;

SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(170d, -40d)', spoint '(170d, -50d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(170d, -40d)', spoint '(170d, -50d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(170d, -40d)', spoint '(170d, -49d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(170d, -40d)', spoint '(170d, -49d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(170d, -40d)', spoint '(170d, -51d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(170d, -40d)', spoint '(170d, -51d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(170d, -40d)', spoint '(190d, -50d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(170d, -40d)', spoint '(190d, -50d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(171d, -41d)', spoint '(189d, -49d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(171d, -41d)', spoint '(189d, -49d)' ) ;

SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(180d, -39d)', spoint '(180d, -51d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(180d, -39d)', spoint '(180d, -51d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(180d, -40d)', spoint '(180d, -51d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(180d, -40d)', spoint '(180d, -51d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(180d, -40d)', spoint '(180d, -50d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(180d, -40d)', spoint '(180d, -50d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(180d, -41d)', spoint '(180d, -50d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(180d, -41d)', spoint '(180d, -50d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(180d, -41d)', spoint '(180d, -49d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(180d, -41d)', spoint '(180d, -49d)' ) ;

SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(180d, -39d)', spoint '(182d, -51d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(180d, -39d)', spoint '(182d, -51d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(180d, -40d)', spoint '(182d, -51d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(180d, -40d)', spoint '(182d, -51d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(180d, -40d)', spoint '(182d, -50d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(180d, -40d)', spoint '(182d, -50d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(180d, -41d)', spoint '(182d, -50d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(180d, -41d)', spoint '(182d, -50d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(180d, -41d)', spoint '(182d, -49d)' ) ;
SELECT sbox '((170d,-50d),(190d,-40d))' && sline ( spoint '(180d, -41d)', spoint '(182d, -49d)' ) ;

SELECT sbox '((170d,-50d),(190d,-40d))'  ~ sline ( spoint '(170d, -40d)', spoint '(190d, -40d)' ) ;

-- wide spherical boxes
