SET enable_indexscan = OFF;
SET enable_seqscan = ON;

EXPLAIN (COSTS OFF)
SELECT count(*)
FROM spheretmp1 t1 JOIN spheretmpx tx ON dist(t1.p, tx.p) < 0.03;

SELECT count(*)
FROM spheretmp1 t1 JOIN spheretmpx tx ON dist(t1.p, tx.p) < 0.03;

SELECT DISTINCT concat_ws(', ', t1.p, tx.p) AS xm
FROM spheretmp1 t1 JOIN spheretmpx tx ON dist(t1.p, tx.p) < 0.03 ORDER BY xm;



SET enable_seqscan = OFF;
SET enable_indexscan = ON;

CREATE INDEX idx_spoint1_1 ON spheretmp1 USING gist (p spoint);
CREATE INDEX idx_spoint1_x ON spheretmpx USING gist (p spoint);

ANALYZE spheretmp1;
ANALYZE spheretmpx;

EXPLAIN (COSTS OFF)
SELECT count(*)
FROM spheretmp1 t1 JOIN spheretmpx tx ON t1.p <@ scircle(tx.p, 0.03);

SELECT count(*)
FROM spheretmp1 t1 JOIN spheretmpx tx ON t1.p <@ scircle(tx.p, 0.03);

SELECT DISTINCT concat_ws(', ', t1.p, tx.p) AS xm
FROM spheretmp1 t1 JOIN spheretmpx tx ON t1.p <@ scircle(tx.p, 0.03) ORDER BY xm;

DROP INDEX idx_spoint1_1;
DROP INDEX idx_spoint1_x;



CREATE INDEX idx_spoint2_1 ON spheretmp1 USING gist (p spoint2);
CREATE INDEX idx_spoint2_x ON spheretmpx USING gist (p spoint2);

ANALYZE spheretmp1;
ANALYZE spheretmpx;

EXPLAIN (COSTS OFF)
SELECT count(*)
FROM spheretmp1 t1 JOIN spheretmpx tx ON dist(t1.p, tx.p) < 0.03;

SELECT count(*)
FROM spheretmp1 t1 JOIN spheretmpx tx ON dist(t1.p, tx.p) < 0.03;

SELECT DISTINCT concat_ws(', ', t1.p, tx.p) AS xm
FROM spheretmp1 t1 JOIN spheretmpx tx ON dist(t1.p, tx.p) < 0.03 ORDER BY xm;

SET enable_seqscan = ON;
SET enable_indexscan = ON;

DROP INDEX idx_spoint2_1;
DROP INDEX idx_spoint2_x;
