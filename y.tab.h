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
     ID = 258,
     CONST = 259,
     INT = 260,
     YONO = 261,
     GLOBAL = 262,
     RETWEET = 263,
     YO = 264,
     NO = 265,
     END = 266,
     NOT = 267,
     OR = 268,
     AND = 269,
     LIKE = 270,
     REF = 271,
     HASH = 272,
     LT = 273,
     LE = 274,
     GT = 275,
     GE = 276,
     PLUS = 277,
     MINUS = 278,
     MULT = 279,
     DIV = 280,
     MOD = 281,
     ASSIGN = 282,
     COLON = 283,
     BANG = 284,
     LPAREN = 285,
     RPAREN = 286,
     LBRACK = 287,
     RBRACK = 288,
     DOTDOT = 289,
     COMMA = 290,
     IF = 291,
     ELSE = 292,
     WHILE = 293
   };
#endif
/* Tokens.  */
#define ID 258
#define CONST 259
#define INT 260
#define YONO 261
#define GLOBAL 262
#define RETWEET 263
#define YO 264
#define NO 265
#define END 266
#define NOT 267
#define OR 268
#define AND 269
#define LIKE 270
#define REF 271
#define HASH 272
#define LT 273
#define LE 274
#define GT 275
#define GE 276
#define PLUS 277
#define MINUS 278
#define MULT 279
#define DIV 280
#define MOD 281
#define ASSIGN 282
#define COLON 283
#define BANG 284
#define LPAREN 285
#define RPAREN 286
#define LBRACK 287
#define RBRACK 288
#define DOTDOT 289
#define COMMA 290
#define IF 291
#define ELSE 292
#define WHILE 293




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

