%{
#include <stdio.h>
#include <string.h>
#include "postgres.h"
#include "utils/elog.h"
#include "sbuffer.h"

#define YYMALLOC palloc
#define YYFREE   pfree

void sphere_yyerror(const char *str)
{
	reset_buffer();
	elog(ERROR, "parsing: %s", str);
}

static double human2dec(double d, double m, double s)
{
	if (m < 0 || m >= 60 || s < 0 || s >= 60)
	{
		char err[255];
		sprintf(err, "minutes or seconds invalid (min:%f sec:%f)", m, s);
		sphere_yyerror(err);
		return 0;
	}
	else
	{
		if (d < 0)
			return (-s / 3600.0 - m / 60.0) + d;
		else
			return (s / 3600.0 + m / 60.0) + d;
	}
}

%}

%token HOUR DEG MIN SEC COMMA
%token OPENCIRC CLOSECIRC OPENPOINT CLOSEPOINT
%token OPENARR CLOSEARR

%union {
	int		i;
	double	d;
	char	c[3];
}

%token <i> SIGN
%token <i> INT
%token <d> FLOAT
%token <c> EULERAXIS
%left      COMMA


%type  <d> number
%type  <i> angle_lat
%type  <i> angle_lat_us
%type  <i> angle_long
%type  <i> angle_long_us
%type  <i> spherepoint
%type  <i> spherepointlist
%type  <i> spherepath
%%

commands:
	/* empty */
	| command
	;

command:
	spherepoint			{ set_spheretype( STYPE_POINT   ); }
	| spherecircle		{ set_spheretype( STYPE_CIRCLE  ); }
	| sphereline		{ set_spheretype( STYPE_LINE    ); }
	| eulertrans		{ set_spheretype( STYPE_EULER   ); }
	| spherepath		{ set_spheretype( STYPE_PATH    ); }
	| sphereellipse		{ set_spheretype( STYPE_ELLIPSE ); }
	| spherebox			{ set_spheretype( STYPE_BOX     ); }
	;

/* unsigned number */
number :
	FLOAT	{ $$ = $1; }
	| INT	{ $$ = $1; }
	;

/* unsigned longitude */
angle_lat_us :
	number							{ $$ = set_angle(0, $1 ); }
	| FLOAT DEG						{ $$ = set_angle(1, human2dec($1, 0, 0) ); }
	| INT DEG						{ $$ = set_angle(1, human2dec($1, 0, 0) ); }
	| INT DEG number				{ $$ = set_angle(1, human2dec($1, $3, 0) ); }
	| INT DEG FLOAT MIN				{ $$ = set_angle(1, human2dec($1, $3, 0) ); }
	| INT DEG INT MIN				{ $$ = set_angle(1, human2dec($1, $3, 0) ); }
	| INT DEG INT MIN number		{ $$ = set_angle(1, human2dec($1, $3, $5) ); }
	| INT DEG INT MIN number SEC	{ $$ = set_angle(1, human2dec($1, $3, $5) ); }
	;

/* unsigned latitude */
angle_long_us :
	number							{ $$ = set_angle(0, $1); }
	| FLOAT DEG						{ $$ = set_angle(1, human2dec($1, 0, 0)); }
	| INT DEG						{ $$ = set_angle(1, human2dec($1, 0, 0)); }
	| INT DEG number				{ $$ = set_angle(1, human2dec($1, $3, 0)); }
	| INT DEG FLOAT MIN				{ $$ = set_angle(1, human2dec($1, $3, 0)); }
	| INT DEG INT MIN				{ $$ = set_angle(1, human2dec($1, $3, 0)); }
	| INT DEG INT MIN number		{ $$ = set_angle(1, human2dec($1, $3, $5)); }
	| INT DEG INT MIN number SEC	{ $$ = set_angle(1, human2dec($1, $3, $5)); }
	| INT HOUR number				{ $$ = set_angle(1, 15 * human2dec($1, $3, 0)); }
	| INT HOUR INT MIN number		{ $$ = set_angle(1, 15 * human2dec($1, $3, $5)); }
	| INT HOUR INT MIN number SEC	{ $$ = set_angle(1, 15 * human2dec($1, $3, $5)); }
	;

/* longitude */
angle_long :
	angle_long_us			{ $$ = set_angle_sign($1, 1); }
	| SIGN angle_long_us	{ $$ = set_angle_sign($2, $1); }
	;

/* latitude */
angle_lat :
	angle_lat_us			{ $$ = set_angle_sign($1, 1); }
	| SIGN angle_lat_us		{ $$ = set_angle_sign($2, $1); }
	;


/* spherical point */
spherepoint:
	OPENPOINT angle_long COMMA angle_lat CLOSEPOINT
		{
			$$ = set_point($2, $4);
		}
	;

/* spherical circle */
spherecircle:
	OPENCIRC spherepoint COMMA angle_lat_us CLOSECIRC
		{
			set_circle($2, $4);
		}
	;

/* Euler transformation */
eulertrans :
	angle_long COMMA angle_long COMMA angle_long
		{
			set_euler($1, $3, $5, "ZXZ");
		}
	| angle_long COMMA angle_long COMMA angle_long COMMA EULERAXIS
		{
			set_euler($1, $3, $5, $7);
		}
	;

/* spherical line */
sphereline :
	OPENPOINT eulertrans CLOSEPOINT COMMA angle_long_us
		{
			set_line ($5);
		}
	;

/* Path and polygons */
spherepointlist :
	spherepoint COMMA
	| spherepointlist spherepoint COMMA
	;

spherepath :
	OPENARR spherepointlist spherepoint CLOSEARR { }
	;

/* ellipses */
sphereellipse:
	OPENCIRC OPENARR angle_lat_us COMMA angle_lat_us CLOSEARR COMMA spherepoint COMMA angle_lat CLOSECIRC
		{
			set_ellipse($3, $5, $8, $10);
		}
	;

/* boxes */
spherebox:
	OPENPOINT spherepoint COMMA spherepoint CLOSEPOINT { }
	| spherepoint COMMA spherepoint { }
	;
