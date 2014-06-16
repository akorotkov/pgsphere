#!/usr/bin/perl

use strict;
use warnings;
use Getopt::Std;
use Math::Trig;

my %opts;
getopts( 'r:d:p:', \%opts );

my $dist = $opts{ 'd' };
my $rad = $opts{ 'r' };
my $pert = $opts{ 'p' } / 180 * pi;
my $id = 0;

print <<__END_SQL__;

CREATE TABLE spoint2_data( id int, sp spoint );
COPY spoint2_data( id, sp ) FROM stdin;
__END_SQL__

my( $ra, $dec, $ra_offset, $dec_offset, $ra_loc, $dec_loc );
for ( $ra = 0; $ra < (360 - $dist); $ra += $dist )
   {
   for ( $dec = -90; $dec <= (90 - $dist); $dec += $dist )
      {
#      printf "-- (%9.5fd, %9.5fd)\n", $ra, $dec;
      for ( $ra_offset = 0; $ra_offset < ($ra/$rad); ++$ra_offset )
         {
            $ra_loc = $ra + $dist * $ra_offset / ($ra/$rad);
         for ( $dec_offset = 0; $dec_offset < ($ra/$rad); ++$dec_offset )
            {
            $dec_loc = $dec + $dist * $dec_offset / ($ra/$rad);
            printf "%12d\t(%9.5fd, %9.5fd)\n", ++$id, $ra_loc, $dec_loc;
            }
         }
      }
   }

print "\\.\n\n";

print <<__END_INDEX__ ;

SELECT id, spoint( long(sp)+$pert*random(), lat(sp)+$pert*random()) AS sp
INTO spoint2_data_perterb
FROM spoint2_data;

-- No index on either table
--SELECT a.id AS a_id, a.sp AS a_sp,
--       b.id AS b_id, b.sp AS b_sp
--INTO spoint2_join_no_index
--FROM spoint2_data AS a, spoint2_data_perterb as b
--WHERE b.sp @ scircle( a.sp, $pert );

CREATE INDEX sp_tmp2_idx ON spoint2_data(sp);
CLUSTER sp_tmp2_idx ON spoint2_data;
DROP INDEX sp_tmp2_idx;
CREATE INDEX sp2_idx ON spoint2_data USING gist (sp);

VACUUM FULL ANALYZE;

-- Index on a table only
SELECT a.id AS a_id, a.sp AS a_sp,
       b.id AS b_id, b.sp AS b_sp
INTO spoint2_join_a_index
FROM spoint2_data AS a, spoint2_data_perterb as b
WHERE b.sp @ scircle( a.sp, $pert );

CREATE INDEX sp_tmp2_pert_idx ON spoint2_data_perterb(sp);
CLUSTER sp_tmp2_pert_idx ON spoint2_data_perterb;
DROP INDEX sp_tmp2_pert_idx;
CREATE INDEX sp2_pert_idx ON spoint2_data_perterb USING gist (sp);
VACUUM FULL ANALYZE;

-- Index on a and b table
SELECT a.id AS a_id, a.sp AS a_sp,
       b.id AS b_id, b.sp AS b_sp
INTO spoint2_join_a_b_index
FROM spoint2_data AS a, spoint2_data_perterb as b
WHERE b.sp @ scircle( a.sp, $pert );

DROP INDEX sp2_idx;
-- Index on b table only
SELECT a.id AS a_id, a.sp AS a_sp,
       b.id AS b_id, b.sp AS b_sp
INTO spoint2_join
FROM spoint2_data AS a, spoint2_data_perterb as b
WHERE b.sp @ scircle( a.sp, $pert );

__END_INDEX__
