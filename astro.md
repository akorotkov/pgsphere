## Astronomical related functions

### Function:

1. `spoint_deg(RA,Dec)`

`(RA,Dec) to spoint.`

Example:
```
demo=# select spoint_deg(180,60);
              spoint_deg
--------------------------------------
 (3.14159265358979 , 1.0471975511966)
(1 row)
```

2. `spoly_deg(ARRAY[RA_1,Dec_1,RA_2,Dec_2,...RA_n,Dec_n])`

`(RA,Dec)... -> spoly`

Example:
```
demo=# select spoly_deg(ARRAY[180,60,120,10,200,30]);
                                                      spoly_deg
---------------------------------------------------------------------------------------------------------------------
 {(3.14159265358979 , 1.0471975511966),(2.0943951023932 , 0.174532925199433),(3.49065850398866 , 0.523598775598299)}
(1 row)
```

3. `scircle_deg(RA,Dec,radius)`

`(RA,Dec,radius)... -> scircle`

Example:
```
demo=# select scircle_deg(180,0,0.2);
                  scircle_deg
------------------------------------------------
 <(3.14159265358979 , 0) , 0.00349065850398866>
(1 row)
```

### GiST Index

1. `spoint index`

```
CREATE INDEX some_tbl_idx_spos ON some.tbl USING(GIST(spoint_deg(RA,Dec)));
```

2. `sploy index`

```
CREATE INDEX some_tbl_idx_spoly ON some.tbl USING(GIST(spoly_deg(RA_tl,Dec_tl,RA_tr,Dec_tr,RA_br,Dec_br,RA_bl,Dec_bl)));
```

### Query

**Cone Search**

```
SELECT * FROM some.tbl WHERE spoint_deg(RA,Dec) @ scircle_deg(center_RA,center_Dec,radius);
```
