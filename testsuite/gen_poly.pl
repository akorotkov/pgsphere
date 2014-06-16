#!/usr/bin/perl

my $dist=$ARGV[0];
my $r=$ARGV[1];
my $N=$ARGV[2];
if ($#ARGV == -1) {
	print "gen_poly.pl: Generic pg_sphere \"spoly\" data generator\n";
	print "usage:\n\tgen_poly.pl <step> <size> <N>| psql pgsphere_db\n\n";

	print "Program generates spherical N-side polygons located near the\n";
	print "intersections of parallels and meridians and SQL script\n";
	print "to load them into existing database. N have to be >=3. Distance\n";
	print "between meridians is chosen equal to \"step\" in degrees\n";
	print "The modulus of 360 and step should be equal to zero.\n\n";
	print "Example: \"gen_poly.pl 1 0.1 3\" generates dataset containing 64442\n";
	print "spherical triangles with integer spherical coordinate values\n";
	print "when written in degrees.\n\n";
	print "Program automatically creates \"spoly_data\" table\n";
	print "but does not DROP an existing table with this name.\n\n";
	print "Program attempts to create index \"spl_idx\" on this table\n";
	exit(0);
}


my $pi=3.1415926535897932;
my $degra=$pi/180.0;

if ((180 % $dist)!=0) {
	print STDERR "incorrect step, using 1 degree instead.\n";
	$dist = 1;
}

if ($r < 0) {
	print STDERR "incorrect size, using 0.1 degree instead.\n";
	$r = 0.1;
}

if ($N < 3) {
	print STDERR "incorrect N, using 3 degree instead.\n";
	$N = 3;
}

my @x;
my @y;

for ($i=0.0;$i<$N;$i+=1.0) {
	push @x,$r*sin(2.0*$pi*$i/$N);
	push @y,$r*cos(2.0*$pi*$i/$N);
}

print <<END ;
CREATE TABLE spoly_data (sp spoly);

COPY spoly_data (sp) FROM stdin;
END


#print spoly($N,-90,0,\@x,\@y)."\n";
for (my $i=-90+$dist;$i<=90-$dist;$i+=$dist) {
    for (my $j=0; $j<360; $j+=$dist) {
	print spoly($N,$i,$j,\@x,\@y)."\n";
    }
}
#print spoly($N,90,0,\@x,\@y)."\n";

print "\\.\n\n";
print "CREATE INDEX spl_idx ON spoly_data USING gist (sp);\n";

sub spoly{
my ($N,$i,$j,$x,$y) = @_;
	my $spoly="{";
	for ($nn=0;$nn<$N;$nn++){
		$spoly.=sprintf("(%fd,%fd)",$j+$x->[$nn],$i+$y->[$nn]);
		$spoly.="," unless ($nn>=($N-1));
	}
	$spoly.="}";
return $spoly;
}
