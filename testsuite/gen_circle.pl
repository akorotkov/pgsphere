#!/usr/bin/perl

my $dist=$ARGV[0];
my $radius=$ARGV[1];
if ($#ARGV <= 0) {
	print "gen_circle.pl: Generic pg_sphere \"scircle\" data generator\n";
	print "usage:\n\tgen_circle.pl <step> <radius> | psql pgsphere_db\n\n";

	print "Program generates spherical circles located in the\n";
	print "intersections of parallels and meridians and SQL script\n";
	print "to load them into existing database. Distance\n";
	print "between meridians is chosen equal to \"step\" in degrees\n";
	print "radii of circles are set equal to \"radius\" in degrees\n";
	print "The modulus of 360 and step should be equal to zero.\n";
	print "The radius should be between 0 and 90\n\n";
	print "Example: \"gen_circle.pl 1 0.1\" generates dataset containing\n";
	print "64442 spherical circles with integer spherical coordinate\n";
	print "values when written in degrees and radii of 6 arcmins.\n\n";
	print "Program automatically creates \"scircle_data\" table\n";
	print "but does not DROP an table with this name.\n\n";
	print "Program attempts to create index \"sc_idx\" on this table\n";
	exit(0);
}

my $pi=3.1415926535897932;
my $degra=$pi/180.0;

if ($dist <= 0) {$dist = 1;}
if ((180 % $dist)!=0) {
	print STDERR "incorrect step, using 1 degree instead.\n";
	$dist = 1;
}
if (($radius > 90)||($radius<0)) {
	print STDERR "incorrect radius, using 6 arcmins instead.\n";
	$radius = 0.1;
}


print <<END ;
CREATE TABLE scircle_data (sc scircle);

COPY scircle_data (sc) FROM stdin;
END


print "<(0, -90d), ${radius}d>\n";
for (my $i=-90+$dist;$i<=90-$dist;$i+=$dist) {
    for (my $j=0; $j<360; $j+=$dist) {
	print "<(${j}d, ${i}d), ${radius}d>\n";
    }
}
print "<(0, 90d), ${radius}d>\n";

print "\\.\n\n";
print "CREATE INDEX sc_idx ON scircle_data USING gist (sc);\n";
