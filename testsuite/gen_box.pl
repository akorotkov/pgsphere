#!/usr/bin/perl

my $diff=$ARGV[0];

if ($#ARGV < 0) {
	print "gen_box.pl: Generic pg_sphere \"sbox\" data generator\n";
	print "usage:\n\tgen_box.pl <boxsize> | psql pgsphere_db\n\n";

	print "Program generates not overlapping spherical boxes.\n";
	print "Each box has a size of <boxsize> degrees in longitude and\n";
	print "latitude\n";
	exit(0);
}

print <<END ;
BEGIN;
CREATE TABLE sbox_data (sb sbox);
COPY sbox_data (sb) FROM stdin;
END

print "((0, -90d),(0,-90d))\n";
for (my $i=-90;$i<90;$i+=$diff) {
    for (my $j=0; $j<360; $j+=$diff) {
	my $u = $i + $diff;
	my $v = $j + $diff;
	print "((${j}d, ${i}d),(${v}d, ${u}d)) \n";
    }
}
print "( (0, 90d),(0, 90d) )\n";

print "\\.\n\n";
print "CREATE INDEX sb_idx ON sbox_data USING gist (sb);\n";
print "COMMIT;\n";
