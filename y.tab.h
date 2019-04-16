/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INS = 258,
    RECORD = 259,
    NUM = 260,
    GETT = 261,
    AND = 262,
    OR = 263,
    UPDATE = 264,
    DEL = 265,
    INTO = 266,
    IN = 267,
    SET = 268,
    TO = 269,
    WHERE = 270,
    FROM = 271,
    VAR = 272,
    STRING = 273,
    LB = 274,
    RB = 275,
    COLON = 276,
    REL_OP = 277,
    COMMA = 278,
    NL = 279
  };
#endif
/* Tokens.  */
#define INS 258
#define RECORD 259
#define NUM 260
#define GETT 261
#define AND 262
#define OR 263
#define UPDATE 264
#define DEL 265
#define INTO 266
#define IN 267
#define SET 268
#define TO 269
#define WHERE 270
#define FROM 271
#define VAR 272
#define STRING 273
#define LB 274
#define RB 275
#define COLON 276
#define REL_OP 277
#define COMMA 278
#define NL 279

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 1737 "mql.y" /* yacc.c:1909  */

		char str[200];            

#line 106 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
