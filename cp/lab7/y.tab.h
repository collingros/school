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
    INT = 258,
    VOID = 259,
    BOOLEAN = 260,
    MYBEGIN = 261,
    END = 262,
    IF = 263,
    THEN = 264,
    ELSE = 265,
    WHILE = 266,
    DO = 267,
    MYRETURN = 268,
    READ = 269,
    WRITE = 270,
    AND = 271,
    OR = 272,
    TRUE = 273,
    FALSE = 274,
    NOT = 275,
    LE = 276,
    GE = 277,
    EQ = 278,
    NEQ = 279,
    NUMBER = 280,
    VARIABLE = 281
  };
#endif
/* Tokens.  */
#define INT 258
#define VOID 259
#define BOOLEAN 260
#define MYBEGIN 261
#define END 262
#define IF 263
#define THEN 264
#define ELSE 265
#define WHILE 266
#define DO 267
#define MYRETURN 268
#define READ 269
#define WRITE 270
#define AND 271
#define OR 272
#define TRUE 273
#define FALSE 274
#define NOT 275
#define LE 276
#define GE 277
#define EQ 278
#define NEQ 279
#define NUMBER 280
#define VARIABLE 281

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 42 "lab7.y" /* yacc.c:1909  */

	int number;
	char *string;
	enum DATATYPE datatype;
	enum OPERATOR op;
	struct ASTNodeType *node;

#line 114 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
