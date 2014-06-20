-- without idx

SELECT count(*) FROM spheretmp1 WHERE p @ scircle '<(1,1),0.3>';

SELECT count(*) FROM spheretmp1 WHERE p = spoint '(3.09 , 1.25)' ;

SELECT count(*) FROM spheretmp2 WHERE c @ scircle '<(1,1),0.3>';

SELECT count(*) FROM spheretmp2 WHERE c && scircle '<(1,1),0.3>';

SELECT count(*) FROM spheretmp3 WHERE b && scircle '<(1,1),0.3>';

SELECT count(*) FROM spheretmp3 WHERE spoint '(3.09 , 1.25)' @ b ;

SELECT count(*) FROM spheretmp4 WHERE l @  scircle '<(1,1),0.3>';

SELECT count(*) FROM spheretmp4 WHERE l && scircle '<(1,1),0.3>';


-- create idx

CREATE INDEX aaaidx ON spheretmp1 USING gist ( p );

CREATE INDEX bbbidx ON spheretmp2 USING gist ( c );

CREATE INDEX cccidx ON spheretmp3 USING gist ( b );

CREATE INDEX dddidx ON spheretmp4 USING gist ( l );

--with idx

SET enable_seqscan = OFF ;

SELECT count(*) FROM spheretmp1 WHERE p @ scircle '<(1,1),0.3>'  ;

SELECT count(*) FROM spheretmp1 WHERE p = spoint '(3.09 , 1.25)' ;

SELECT count(*) FROM spheretmp2 WHERE c @ scircle '<(1,1),0.3>'  ;

SELECT count(*) FROM spheretmp2 WHERE c && scircle '<(1,1),0.3>' ;

SELECT count(*) FROM spheretmp3 WHERE b && scircle '<(1,1),0.3>';

SELECT count(*) FROM spheretmp3 WHERE spoint '(3.09 , 1.25)' @ b ;

SELECT count(*) FROM spheretmp4 WHERE l @  scircle '<(1,1),0.3>' ;

SELECT count(*) FROM spheretmp4 WHERE l && scircle '<(1,1),0.3>' ;

