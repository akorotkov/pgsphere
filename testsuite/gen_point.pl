#!/usr/bin/perl

my $dist=$ARGV[0];
if ($#ARGV == -1) {
	print "gen_point.pl: Generic pg_sphere \"spoint\" data generator\n";
	print "usage:\n\tgen_point.pl <step> | psql pgsphere_db\n\n";

	print "Program generates spherical points located in the\n";
	print "intersections of parallels and meridians and SQL script\n";
	print "to load them into existing database. Distance\n";
	print "between meridians is chosen equal to \"step\" in degrees\n";
	print "The modulus of 360 and step should be equal to zero.\n\n";
	print "Example: \"gen_point.pl 1\" generates dataset containing 64442\n";
	print "spherical points with integer spherical coordinate values\n";
	print "when written in degrees.\n\n";
	print "Program automatically creates \"spoint_data\" table\n";
	print "but does not DROP an existing table with this name.\n\n";
	print "Program attempts to create index \"sp_idx\" on this table\n";
	exit(0);
}


my $pi=3.1415926535897932;
my $degra=$pi/180.0;

if ((180 % $dist)!=0) {
	print STDERR "incorrect step, using 1 degree instead.\n";
	$dist = 1;
}

print <<END ;
CREATE TABLE spoint_data (sp spoint);

COPY spoint_data (sp) FROM stdin;
END


print "(0, -90d)\n";
for (my $i=-90+$dist;$i<=90-$dist;$i+=$dist) {
    for (my $j=0; $j<360; $j+=$dist) {
	print "(${j}d, ${i}d)\n";
    }
}
print "(0, 90d)\n";

print "\\.\n\n";

print <<ENDIDX ;
CREATE INDEX sp_idx ON spoint_data USING gist (sp);
ENDIDX
