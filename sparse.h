/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     HOUR = 258,
     DEG = 259,
     MIN = 260,
     SEC = 261,
     COMMA = 262,
     OPENCIRC = 263,
     CLOSECIRC = 264,
     OPENPOINT = 265,
     CLOSEPOINT = 266,
     OPENARR = 267,
     CLOSEARR = 268,
     SIGN = 269,
     INT = 270,
     FLOAT = 271,
     EULERAXIS = 272
   };
#endif
/* Tokens.  */
#define HOUR 258
#define DEG 259
#define MIN 260
#define SEC 261
#define COMMA 262
#define OPENCIRC 263
#define CLOSECIRC 264
#define OPENPOINT 265
#define CLOSEPOINT 266
#define OPENARR 267
#define CLOSEARR 268
#define SIGN 269
#define INT 270
#define FLOAT 271
#define EULERAXIS 272




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 36 "sparse.y"
{ 
 int    i;
 double d;
 char   c[3];
}
/* Line 1529 of yacc.c.  */
#line 89 "sparse.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE sphere_yylval;

