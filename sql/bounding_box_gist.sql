CREATE TABLE bbox_ellipse (e sellipse not null);
INSERT INTO bbox_ellipse VALUES ('<{10d, 0.1d}, (0d,0d), 0d>');
SELECT spoint '(5d, 0d)' @ sellipse '<{10d, 0.1d}, (0d,0d), 0d>' AS inside;
SELECT COUNT(*) FROM bbox_ellipse WHERE spoint '(5d, 0d)' @ e;
-- The ellipse has semi-major axis length of 10 degrees along the equator,
-- so (lon,lat) = (5,0) should be inside.
CREATE INDEX idx_bbox_ellipse ON bbox_ellipse USING gist (e);
ANALYZE bbox_ellipse;
SET enable_seqscan=false;
SELECT COUNT(*) FROM bbox_ellipse WHERE spoint '(5d, 0d)' @ e;

CREATE TABLE bbox_poly (p spoly not null);
INSERT INTO bbox_poly VALUES ('{(40d,-40d), (0d,80d), (-40d,-40d)}');
SELECT spoint '(0d, 0d)' @ spoly '{(40d,-40d), (0d,80d), (-40d,-40d)}' AS inside;
SELECT COUNT(*) FROM bbox_poly WHERE spoint '(0d, 0d)' @ p;
CREATE INDEX idx_bbox_poly ON bbox_poly USING gist (p);
ANALYZE bbox_poly;
SET enable_seqscan=false;
SELECT COUNT(*) FROM bbox_poly WHERE spoint '(0d, 0d)' @ p;

CREATE TABLE bbox_path (p spath not null);
INSERT INTO bbox_path VALUES ('{(-46d,0d), (-45d,80d), (-45d,0d), (80d,0d)}');
SELECT sline(spoint '(0d, -10d)', spoint '(0d, 10d)') && spath '{(-46d,0d), (-45d,80d), (-45d,0d), (80d,0d)}' AS crossing;
SELECT spoint '(0d, 0d)' @ spath '{(-46d,0d), (-45d,80d), (-45d,0d), (80d,0d)}' AS inside;
SELECT COUNT(*) FROM bbox_path WHERE sline(spoint '(0d, -10d)', spoint '(0d, 10d)') && p;
SELECT COUNT(*) FROM bbox_path WHERE spoint '(0d, 0d)' @ p;
CREATE INDEX idx_bbox_path ON bbox_path USING gist (p);
ANALYZE bbox_path;
SET enable_seqscan=false;
SELECT COUNT(*) FROM bbox_path WHERE sline(spoint '(0d, -10d)', spoint '(0d, 10d)') && p;
SELECT COUNT(*) FROM bbox_path WHERE spoint '(0d, 0d)' @ p;
