%{
#include <stdio.h>
#include "string.h"
#include "sparse.h"
#include "sbuffer.h"

#define YY_DECL int sphere_yylex( void )
YY_DECL;
#define yylval sphere_yylval

#undef YY_INPUT
#define YY_NO_INPUT
#define YY_INPUT(buf,result,max_size) \
{ \
        result = get_buffer( buf, max_size ); \
        result = ( result > 0 )?( result ):(YY_NULL); \
}

void sphere_flush_scanner_buffer(void) {
  YY_FLUSH_BUFFER;
} 


FILE *sphereget_in(void);
FILE *sphereget_out(void);
int  sphereget_leng(void);
char *sphereget_text(void);
int  sphereget_debug(void) ;
void sphereset_debug(int bdebug);
void sphereset_out (FILE * out_str);
int  sphereget_debug(void);
void sphereset_debug(int  bdebug);
void sphereset_in(FILE * in_str );  
int  spherelex_destroy(void);


%}

%option 8bit
%option never-interactive
%option nounput
%option noyywrap

int          [0-9]+
sign         [+-]
real         ({int})?\.({int})
float        ({int}|{real})([eE]{sign}{int})?

%%
{sign}       sphere_yylval.i = ( strcmp("-",yytext) )?(1):(-1); return SIGN ;
{int}        sphere_yylval.i = atoi(yytext); return INT ; 
{float}      sphere_yylval.d = atof(yytext); return FLOAT ; 
[x-zX-Z]{3}  memcpy( (void * ) &sphere_yylval.c[0], (void * ) yytext, 3 ) ; return EULERAXIS ;
h            return HOUR  ;
d            return DEG ;
'            return MIN ;
m            return MIN ;
\"           return SEC ;
s            return SEC ;
,            return COMMA ;
\<           return OPENCIRC   ;
\>           return CLOSECIRC  ;
\(           return OPENPOINT  ;
\)           return CLOSEPOINT ;
\{           return OPENARR  ;
\}           return CLOSEARR ;
[ \n\t]+     // discard spaces
.            // alert parser of the garbage
%%
