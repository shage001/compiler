/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 6 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include "symtab.h"
#include "syntree.h"
#include "syntax.h"

#define YYDEBUG 1

/* yylex is the lexical analyzer created by Lex */
extern int yylex();

/* defined in parser.y below */
void yyerror(char *s);

int PRINT_PRODUCTIONS;
#define production(s) if (PRINT_PRODUCTIONS) printf(s)



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 202 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   198

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNRULES -- Number of states.  */
#define YYNSTATES  154

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     7,    11,    15,    17,    24,    26,
      28,    30,    33,    35,    39,    42,    47,    48,    51,    60,
      70,    71,    73,    75,    79,    83,    88,    94,    95,    98,
     100,   102,   105,   107,   109,   111,   116,   119,   125,   129,
     134,   137,   141,   149,   150,   157,   161,   168,   170,   174,
     176,   180,   182,   186,   188,   191,   193,   197,   201,   205,
     209,   213,   218,   220,   224,   228,   230,   234,   238,   242,
     245,   247,   249,   251
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      40,     0,    -1,    41,    48,    -1,    -1,    41,     7,    42,
      -1,    43,    46,    29,    -1,    44,    -1,    44,    32,    45,
      34,    45,    33,    -1,     5,    -1,     6,    -1,     4,    -1,
      23,     4,    -1,    47,    -1,    46,    35,    47,    -1,    17,
       3,    -1,    17,     3,    27,    63,    -1,    -1,    48,    49,
      -1,     3,    30,    50,    31,    28,    53,    11,    29,    -1,
      44,     3,    30,    50,    31,    28,    53,    11,    29,    -1,
      -1,    51,    -1,    52,    -1,    51,    35,    52,    -1,    44,
      17,     3,    -1,    16,    44,    17,     3,    -1,    44,    32,
      33,    17,     3,    -1,    -1,    53,    54,    -1,    42,    -1,
      55,    -1,    57,    29,    -1,    58,    -1,    59,    -1,    61,
      -1,    56,    27,    63,    29,    -1,    17,     3,    -1,    17,
       3,    32,    63,    33,    -1,     3,    30,    31,    -1,     3,
      30,    62,    31,    -1,     8,    29,    -1,     8,    63,    29,
      -1,    36,    63,    28,    53,    60,    11,    29,    -1,    -1,
      37,    36,    63,    28,    53,    60,    -1,    37,    28,    53,
      -1,    38,    63,    28,    53,    11,    29,    -1,    63,    -1,
      62,    35,    63,    -1,    64,    -1,    63,    13,    64,    -1,
      65,    -1,    64,    14,    65,    -1,    66,    -1,    12,    66,
      -1,    67,    -1,    67,    18,    67,    -1,    67,    19,    67,
      -1,    67,    20,    67,    -1,    67,    21,    67,    -1,    67,
      15,    67,    -1,    67,    12,    15,    67,    -1,    68,    -1,
      67,    22,    68,    -1,    67,    23,    68,    -1,    69,    -1,
      68,    24,    69,    -1,    68,    25,    69,    -1,    68,    26,
      69,    -1,    23,    69,    -1,    56,    -1,    57,    -1,     4,
      -1,    30,    63,    31,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   105,   105,   113,   114,   119,   124,   127,   132,   133,
     136,   137,   140,   141,   144,   145,   148,   149,   152,   154,
     159,   160,   163,   164,   167,   168,   169,   172,   173,   176,
     177,   178,   179,   180,   181,   184,   188,   189,   192,   193,
     196,   197,   200,   204,   205,   207,   211,   214,   215,   218,
     219,   222,   223,   226,   227,   230,   231,   232,   233,   234,
     235,   236,   239,   240,   241,   244,   245,   246,   247,   250,
     251,   252,   253,   254
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "CONST", "INT", "YONO", "GLOBAL",
  "RETWEET", "YO", "NO", "END", "NOT", "OR", "AND", "LIKE", "REF", "HASH",
  "LT", "LE", "GT", "GE", "PLUS", "MINUS", "MULT", "DIV", "MOD", "ASSIGN",
  "COLON", "BANG", "LPAREN", "RPAREN", "LBRACK", "RBRACK", "DOTDOT",
  "COMMA", "IF", "ELSE", "WHILE", "$accept", "program", "globlist",
  "vardecl", "type", "basictype", "sconst", "decllist", "decl", "funlist",
  "fundecl", "params", "paramlist", "param", "stmtlist", "stmt",
  "assignment", "variable", "funcall", "returnstmt", "ifstmt", "elsestmt",
  "whilestmt", "exprlist", "expr", "logterm", "logfactor", "relexpr",
  "arithexpr", "term", "factor", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    40,    41,    41,    42,    43,    43,    44,    44,
      45,    45,    46,    46,    47,    47,    48,    48,    49,    49,
      50,    50,    51,    51,    52,    52,    52,    53,    53,    54,
      54,    54,    54,    54,    54,    55,    56,    56,    57,    57,
      58,    58,    59,    60,    60,    60,    61,    62,    62,    63,
      63,    64,    64,    65,    65,    66,    66,    66,    66,    66,
      66,    66,    67,    67,    67,    68,    68,    68,    68,    69,
      69,    69,    69,    69
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     3,     3,     1,     6,     1,     1,
       1,     2,     1,     3,     2,     4,     0,     2,     8,     9,
       0,     1,     1,     3,     3,     4,     5,     0,     2,     1,
       1,     2,     1,     1,     1,     4,     2,     5,     3,     4,
       2,     3,     7,     0,     6,     3,     6,     1,     3,     1,
       3,     1,     3,     1,     2,     1,     3,     3,     3,     3,
       3,     4,     1,     3,     3,     1,     3,     3,     3,     2,
       1,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,    16,     1,     0,     2,     8,     9,     4,     0,
       6,     0,     0,    17,     0,     0,    12,     0,    20,     0,
      14,     5,     0,    10,     0,     0,     0,     0,     0,    21,
      22,    20,     0,    13,    11,     0,     0,     0,     0,     0,
       0,     0,     0,    72,     0,     0,     0,     0,    70,    71,
      15,    49,    51,    53,    55,    62,    65,     0,     0,    24,
       0,    27,    23,     0,     0,    54,    36,    69,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     7,    25,     0,     0,    27,    38,     0,    47,
       0,    73,    50,    52,     0,    60,    56,    57,    58,    59,
      63,    64,    66,    67,    68,    26,     0,     0,     0,     0,
      29,    28,    30,     0,     0,    32,    33,    34,     0,    39,
       0,     0,    61,    40,     0,    18,     0,     0,     0,    31,
       0,    48,    37,    41,    27,    27,     0,    19,    43,     0,
      35,     0,     0,     0,    27,     0,     0,    46,    45,     0,
      42,    27,    43,    44
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   110,     9,    10,    25,    15,    16,     5,
      13,    28,    29,    30,    85,   111,   112,    48,    49,   115,
     116,   142,   117,    88,    50,    51,    52,    53,    54,    55,
      56
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -85
static const yytype_int16 yypact[] =
{
     -85,    24,    38,   -85,   145,    97,   -85,   -85,   -85,    25,
      37,    42,    64,   -85,    92,    36,   -85,    15,   133,    76,
      98,   -85,    25,   -85,   104,    96,   145,    -5,   109,   107,
     -85,   133,   124,   -85,   -85,    15,    94,   142,   115,   125,
     133,   136,   130,   -85,   129,   168,   129,   124,   -85,   -85,
     159,   160,   -85,   -85,   143,   144,   -85,   140,   172,   -85,
     161,   -85,   -85,   148,    93,   -85,   147,   -85,     9,   124,
     124,   162,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   -85,   -85,   177,    -1,   -85,   -85,   -10,   159,
     124,   -85,   160,   -85,   129,   112,   112,   112,   112,   112,
     144,   144,   -85,   -85,   -85,   -85,   114,   152,   124,   124,
     -85,   -85,   -85,   155,   154,   -85,   -85,   -85,     3,   -85,
     124,     0,   112,   -85,    47,   -85,    35,    91,   124,   -85,
     156,   159,   -85,   -85,   -85,   -85,    80,   -85,    41,    77,
     -85,   -13,   173,   157,   -85,   124,   158,   -85,    84,   101,
     -85,   -85,    41,   -85
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -85,   -85,   -85,   184,   -85,    81,   163,   -85,   167,   -85,
     -85,   164,   -85,   150,   -60,   -85,   -85,   -84,   -82,   -85,
     -85,    39,   -85,   -85,   -47,   123,   126,   149,   -44,    79,
     -28
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      68,   113,    42,   114,     6,     7,    42,   106,     6,     7,
     107,   106,    37,    69,   130,   144,    45,    89,    67,    23,
      45,   119,    69,   145,     3,   120,   118,    38,    95,    96,
      97,    98,    99,   132,   113,   108,   114,   109,    24,   108,
      91,   109,    14,   121,    42,     4,     6,     7,    69,   106,
     122,   102,   103,   104,   113,   113,   114,   114,    45,   124,
      69,   126,   127,   134,   113,    21,   114,    19,   113,    17,
     114,    22,    18,   131,   138,   139,   133,   108,   141,   109,
      42,   136,     6,     7,   148,   106,    12,    42,   143,     6,
       7,   152,   106,    69,    45,    20,    42,    43,   149,    27,
      11,    45,     6,     7,    69,    44,    31,    36,    34,   140,
      45,    58,    27,   108,    69,   109,    46,    42,    43,   135,
     108,    27,   109,    47,    87,    32,    44,    42,    43,   151,
      35,    45,    42,    43,    77,    78,    44,    46,     6,     7,
      39,    45,    40,   123,    47,    59,    45,    46,    60,    26,
       6,     7,    46,    61,    47,    71,   100,   101,    72,    47,
      64,    73,    74,    75,    76,    77,    78,    63,    79,    80,
      81,    66,    69,    82,    70,    83,    86,    94,    84,    90,
     105,   125,   128,   129,   146,   137,   147,   150,     8,    33,
      62,   153,    92,    65,     0,    41,    93,     0,    57
};

static const yytype_int16 yycheck[] =
{
      47,    85,     3,    85,     5,     6,     3,     8,     5,     6,
      11,     8,    17,    13,    11,    28,    17,    64,    46,     4,
      17,    31,    13,    36,     0,    35,    86,    32,    72,    73,
      74,    75,    76,    33,   118,    36,   118,    38,    23,    36,
      31,    38,    17,    90,     3,     7,     5,     6,    13,     8,
      94,    79,    80,    81,   138,   139,   138,   139,    17,   106,
      13,   108,   109,    28,   148,    29,   148,     3,   152,    32,
     152,    35,    30,   120,   134,   135,    29,    36,    37,    38,
       3,   128,     5,     6,   144,     8,     5,     3,    11,     5,
       6,   151,     8,    13,    17,     3,     3,     4,   145,    18,
       3,    17,     5,     6,    13,    12,    30,    26,     4,    29,
      17,    17,    31,    36,    13,    38,    23,     3,     4,    28,
      36,    40,    38,    30,    31,    27,    12,     3,     4,    28,
      34,    17,     3,     4,    22,    23,    12,    23,     5,     6,
      31,    17,    35,    29,    30,     3,    17,    23,    33,    16,
       5,     6,    23,    28,    30,    12,    77,    78,    15,    30,
      30,    18,    19,    20,    21,    22,    23,    31,    24,    25,
      26,     3,    13,    33,    14,     3,    28,    15,    17,    32,
       3,    29,    27,    29,    11,    29,    29,    29,     4,    22,
      40,   152,    69,    44,    -1,    31,    70,    -1,    35
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    40,    41,     0,     7,    48,     5,     6,    42,    43,
      44,     3,    44,    49,    17,    46,    47,    32,    30,     3,
       3,    29,    35,     4,    23,    45,    16,    44,    50,    51,
      52,    30,    27,    47,     4,    34,    44,    17,    32,    31,
      35,    50,     3,     4,    12,    17,    23,    30,    56,    57,
      63,    64,    65,    66,    67,    68,    69,    45,    17,     3,
      33,    28,    52,    31,    30,    66,     3,    69,    63,    13,
      14,    12,    15,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    33,     3,    17,    53,    28,    31,    62,    63,
      32,    31,    64,    65,    15,    67,    67,    67,    67,    67,
      68,    68,    69,    69,    69,     3,     8,    11,    36,    38,
      42,    54,    55,    56,    57,    58,    59,    61,    53,    31,
      35,    63,    67,    29,    63,    29,    63,    63,    27,    29,
      11,    63,    33,    29,    28,    28,    63,    29,    53,    53,
      29,    37,    60,    11,    28,    36,    11,    29,    53,    63,
      29,    28,    53,    60
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 106 "parser.y"
    { syntree = makenode2(Nprogram, (yyvsp[(1) - (2)].treenode), (yyvsp[(2) - (2)].treenode),
                                      (yyvsp[(1) - (2)].treenode)? (yyvsp[(1) - (2)].treenode)->internal.line :
                                      ((yyvsp[(2) - (2)].treenode)? (yyvsp[(2) - (2)].treenode)->internal.line :
                                       1)); /* line number for empty prog... */
                  production("program -> globlist funlist\n"); }
    break;

  case 3:
#line 113 "parser.y"
    { (yyval.treenode) = NULL; production("globlist -> epsilon\n"); }
    break;

  case 4:
#line 115 "parser.y"
    {  (yyval.treenode) = makelist(Ngloblist, (yyvsp[(1) - (3)].treenode), (yyvsp[(3) - (3)].treenode), (yyvsp[(2) - (3)].lexeme).line);
                  production("globlist -> globlist GLOBAL vardecl\n"); }
    break;

  case 5:
#line 120 "parser.y"
    { (yyval.treenode) = makenode2(Nvardecl, (yyvsp[(1) - (3)].treenode), (yyvsp[(2) - (3)].treenode), (yyvsp[(1) - (3)].treenode)->internal.line);
                  production("vardecl -> type decllist !\n"); }
    break;

  case 6:
#line 124 "parser.y"
    { 
               (yyval.treenode) = (yyvsp[(1) - (1)].treenode);
               production("type -> basictype\n");}
    break;

  case 7:
#line 127 "parser.y"
    { 
               (yyval.treenode) = makenode3(Narraytype, (yyvsp[(1) - (6)].treenode), (yyvsp[(3) - (6)].treenode), (yyvsp[(5) - (6)].treenode), (yyvsp[(1) - (6)].treenode)->type.line);
               production("type -> basictype [sconst .. sconst]\n") ;}
    break;

  case 8:
#line 132 "parser.y"
    { (yyval.treenode) = (yyvsp[(1) - (1)].treenode); production("basictype -> INT\n");}
    break;

  case 9:
#line 133 "parser.y"
    { (yyval.treenode) = (yyvsp[(1) - (1)].treenode); production("basictype -> YONO\n");}
    break;

  case 10:
#line 136 "parser.y"
    { (yyval.treenode) = (yyvsp[(1) - (1)].treenode); production("sconst -> CONST\n"); }
    break;

  case 11:
#line 137 "parser.y"
    { (yyvsp[(2) - (2)].treenode)->constant.val = (yyvsp[(2) - (2)].treenode)->constant.val * -1; (yyval.treenode) = (yyvsp[(2) - (2)].treenode); production("sconst-> MINUS CONST\n");}
    break;

  case 12:
#line 140 "parser.y"
    { (yyval.treenode) = makelist(Ndecllist, NULL, (yyvsp[(1) - (1)].treenode), (yyvsp[(1) - (1)].treenode)->internal.line); production("decllist -> decl\n");}
    break;

  case 13:
#line 141 "parser.y"
    { (yyval.treenode) = makelist(Ndecllist, (yyvsp[(1) - (3)].treenode), (yyvsp[(3) - (3)].treenode), (yyvsp[(1) - (3)].treenode)->internal.line); production("decllist -> decllist, decl\n");}
    break;

  case 14:
#line 144 "parser.y"
    { (yyval.treenode) = makenode2(Ndecl, (yyvsp[(2) - (2)].treenode), NULL, (yyvsp[(2) - (2)].treenode)->ident.line); production("decl -> #ID\n");}
    break;

  case 15:
#line 145 "parser.y"
    { (yyval.treenode) = makenode2(Ndecl, (yyvsp[(2) - (4)].treenode), (yyvsp[(4) - (4)].treenode), (yyvsp[(2) - (4)].treenode)->ident.line); production("decl -> #ID @ expr\n");}
    break;

  case 16:
#line 148 "parser.y"
    { (yyval.treenode) = NULL; production("funlist -> epsilon\n");}
    break;

  case 17:
#line 149 "parser.y"
    { (yyval.treenode) = makelist(Nfunlist, (yyvsp[(1) - (2)].treenode), (yyvsp[(2) - (2)].treenode), (yyvsp[(2) - (2)].treenode)->internal.line); production("funlist -> funlist fundecl\n");}
    break;

  case 18:
#line 152 "parser.y"
    { (yyval.treenode) = makenode4(Nfundecl, NULL, (yyvsp[(1) - (8)].treenode), (yyvsp[(3) - (8)].treenode), (yyvsp[(6) - (8)].treenode), (yyvsp[(1) - (8)].treenode)->internal.line); 
               production("fundecl -> ID (params) : stmtlist END!\n");}
    break;

  case 19:
#line 154 "parser.y"
    { 
               (yyval.treenode) = makenode4(Nfundecl, (yyvsp[(1) - (9)].treenode), (yyvsp[(2) - (9)].treenode), (yyvsp[(4) - (9)].treenode), (yyvsp[(7) - (9)].treenode), (yyvsp[(2) - (9)].treenode)->internal.line); 
               production("basictype fundecl -> ID (params) : stmtlist END!\n");}
    break;

  case 20:
#line 159 "parser.y"
    { (yyval.treenode) = NULL; production("params -> epsilon\n");}
    break;

  case 21:
#line 160 "parser.y"
    { (yyval.treenode) = (yyvsp[(1) - (1)].treenode); production("params -> paramlist\n");}
    break;

  case 22:
#line 163 "parser.y"
    { (yyval.treenode) = makelist(Nparamlist, NULL, (yyvsp[(1) - (1)].treenode), (yyvsp[(1) - (1)].treenode)->internal.line); production("paramlist -> param\n");}
    break;

  case 23:
#line 164 "parser.y"
    { (yyval.treenode) = makelist(Nparamlist, (yyvsp[(1) - (3)].treenode), (yyvsp[(3) - (3)].treenode), (yyvsp[(3) - (3)].treenode)->internal.line); production("paramlist -> paramlist, param\n");}
    break;

  case 24:
#line 167 "parser.y"
    { (yyval.treenode) = makenode2(Nvalparam, (yyvsp[(1) - (3)].treenode), (yyvsp[(3) - (3)].treenode), (yyvsp[(1) - (3)].treenode)->type.line); production("param -> basictype #ID\n");}
    break;

  case 25:
#line 168 "parser.y"
    { (yyval.treenode) = makenode2(Nrefparam, (yyvsp[(2) - (4)].treenode), (yyvsp[(4) - (4)].treenode), (yyvsp[(2) - (4)].treenode)->type.line); production("param -> REF basictype #ID\n");}
    break;

  case 26:
#line 169 "parser.y"
    { (yyval.treenode) = makenode2(Narrparam, (yyvsp[(1) - (5)].treenode), (yyvsp[(5) - (5)].treenode), (yyvsp[(1) - (5)].treenode)->type.line); production("param -> basictype [] #ID\n");}
    break;

  case 27:
#line 172 "parser.y"
    { (yyval.treenode) = NULL; production("stmtlist -> epsilon\n");}
    break;

  case 28:
#line 173 "parser.y"
    { (yyval.treenode) = makelist(Nstmtlist, (yyvsp[(1) - (2)].treenode), (yyvsp[(2) - (2)].treenode), (yyvsp[(2) - (2)].treenode)->internal.line); production("stmtlist -> stmtlist stmt\n");}
    break;

  case 29:
#line 176 "parser.y"
    { (yyval.treenode) = (yyvsp[(1) - (1)].treenode); production("stmt -> vardecl\n");}
    break;

  case 30:
#line 177 "parser.y"
    { (yyval.treenode) = (yyvsp[(1) - (1)].treenode); production("stmt -> assignment\n");}
    break;

  case 31:
#line 178 "parser.y"
    { (yyval.treenode) = (yyvsp[(1) - (2)].treenode); production("stmt -> funcall!\n");}
    break;

  case 32:
#line 179 "parser.y"
    { (yyval.treenode) = (yyvsp[(1) - (1)].treenode); production("stmt -> returnstmt\n");}
    break;

  case 33:
#line 180 "parser.y"
    { (yyval.treenode) = (yyvsp[(1) - (1)].treenode); production("stmt -> ifstmt\n");}
    break;

  case 34:
#line 181 "parser.y"
    { (yyval.treenode) = (yyvsp[(1) - (1)].treenode); production("stmt -> whilestmt\n");}
    break;

  case 35:
#line 184 "parser.y"
    { (yyval.treenode) = makenode2(Nassign, (yyvsp[(1) - (4)].treenode), (yyvsp[(3) - (4)].treenode), (yyvsp[(1) - (4)].treenode)->internal.line);
               production("assignment -> variable ASSIGN expr!\n");}
    break;

  case 36:
#line 188 "parser.y"
    { (yyval.treenode) = (yyvsp[(2) - (2)].treenode); production("variable -> #ID\n");}
    break;

  case 37:
#line 189 "parser.y"
    { (yyval.treenode) = makenode2(Narray, (yyvsp[(2) - (5)].treenode), (yyvsp[(4) - (5)].treenode), (yyvsp[(2) - (5)].treenode)->ident.line); production("variable -> #ID [expr]\n");}
    break;

  case 38:
#line 192 "parser.y"
    { (yyval.treenode) = makenode2(Nfuncall, (yyvsp[(1) - (3)].treenode), NULL, (yyvsp[(1) - (3)].treenode)->ident.line); production("funcall -> ID()\n");}
    break;

  case 39:
#line 193 "parser.y"
    { (yyval.treenode) = makenode2(Nfuncall, (yyvsp[(1) - (4)].treenode), (yyvsp[(3) - (4)].treenode), (yyvsp[(1) - (4)].treenode)->ident.line); production("funcall -> ID(exprlist)\n");}
    break;

  case 40:
#line 196 "parser.y"
    { (yyval.treenode) = makenode1(Nreturn, NULL, (yyvsp[(1) - (2)].lexeme).line); production("returnstmt -> RETWEET!\n");}
    break;

  case 41:
#line 197 "parser.y"
    { (yyval.treenode) = makenode1(Nreturn, (yyvsp[(2) - (3)].treenode), (yyvsp[(1) - (3)].lexeme).line); production("returnstmt -> RETWEET expr!\n");}
    break;

  case 42:
#line 200 "parser.y"
    { (yyval.treenode) = makenode3(Nif, (yyvsp[(2) - (7)].treenode), (yyvsp[(4) - (7)].treenode), (yyvsp[(5) - (7)].treenode), (yyvsp[(1) - (7)].lexeme).line);
            production("ifstmt -> IF expr : stmtlist elsestmt END!\n");}
    break;

  case 43:
#line 204 "parser.y"
    { (yyval.treenode) = NULL; production("elsestmt -> epsilon\n");}
    break;

  case 44:
#line 205 "parser.y"
    { (yyval.treenode) = makenode3(Nelseif, (yyvsp[(3) - (6)].treenode), (yyvsp[(5) - (6)].treenode), (yyvsp[(6) - (6)].treenode), (yyvsp[(1) - (6)].lexeme).line);
               production("elsestmt -> ELSE IF expr : stmtlist elsestmt\n");}
    break;

  case 45:
#line 207 "parser.y"
    { (yyval.treenode) = makenode1(Nelse, (yyvsp[(3) - (3)].treenode), (yyvsp[(1) - (3)].lexeme).line);
               production("elsestmt -> ELSE : stmtlist\n");}
    break;

  case 46:
#line 211 "parser.y"
    { (yyval.treenode) = makenode2(Nwhile, (yyvsp[(2) - (6)].treenode), (yyvsp[(4) - (6)].treenode), (yyvsp[(1) - (6)].lexeme).line); production("whilestmt -> WHILE expr : stmtlist END!\n");}
    break;

  case 47:
#line 214 "parser.y"
    { (yyval.treenode) = makelist(Nexprlist, NULL, (yyvsp[(1) - (1)].treenode), (yyvsp[(1) - (1)].treenode)->internal.line); production("exprlist -> exprlist\n");}
    break;

  case 48:
#line 215 "parser.y"
    { (yyval.treenode) = makelist(Nexprlist, (yyvsp[(1) - (3)].treenode), (yyvsp[(3) - (3)].treenode), (yyvsp[(1) - (3)].treenode)->internal.line); production("exprlist -> exprlist, expr\n");}
    break;

  case 49:
#line 218 "parser.y"
    { (yyval.treenode) = (yyvsp[(1) - (1)].treenode); production("expr -> logterm\n");}
    break;

  case 50:
#line 219 "parser.y"
    { (yyval.treenode) = makenode2(Nor, (yyvsp[(1) - (3)].treenode), (yyvsp[(3) - (3)].treenode), (yyvsp[(1) - (3)].treenode)->internal.line); production("expr -> expr OR logterm\n");}
    break;

  case 51:
#line 222 "parser.y"
    { (yyval.treenode) = (yyvsp[(1) - (1)].treenode); production("logterm -> logfactor\n");}
    break;

  case 52:
#line 223 "parser.y"
    { (yyval.treenode) = makenode2(Nand, (yyvsp[(1) - (3)].treenode), (yyvsp[(3) - (3)].treenode), (yyvsp[(1) - (3)].treenode)->internal.line); production("logterm -> logterm AND logfactor\n");}
    break;

  case 53:
#line 226 "parser.y"
    { (yyval.treenode) = (yyvsp[(1) - (1)].treenode); production("logfactor -> relexpr\n");}
    break;

  case 54:
#line 227 "parser.y"
    { (yyval.treenode) = makenode1(Nnot, (yyvsp[(2) - (2)].treenode), (yyvsp[(1) - (2)].lexeme).line); production("logfactor -> NOT relexpr\n");}
    break;

  case 55:
#line 230 "parser.y"
    { (yyval.treenode) = (yyvsp[(1) - (1)].treenode); production("relexpr -> arithexpr\n");}
    break;

  case 56:
#line 231 "parser.y"
    { (yyval.treenode) = makenode2(Nlt, (yyvsp[(1) - (3)].treenode), (yyvsp[(3) - (3)].treenode), (yyvsp[(1) - (3)].treenode)->internal.line); production("relexpr -> arithexpr LT arithexpr\n");}
    break;

  case 57:
#line 232 "parser.y"
    { (yyval.treenode) = makenode2(Nle, (yyvsp[(1) - (3)].treenode), (yyvsp[(3) - (3)].treenode), (yyvsp[(1) - (3)].treenode)->internal.line); production("relexpr -> arithexpr LE arithexpr\n");}
    break;

  case 58:
#line 233 "parser.y"
    { (yyval.treenode) = makenode2(Ngt, (yyvsp[(1) - (3)].treenode), (yyvsp[(3) - (3)].treenode), (yyvsp[(1) - (3)].treenode)->internal.line); production("relexpr -> arithexpr GT arithexpr\n");}
    break;

  case 59:
#line 234 "parser.y"
    { (yyval.treenode) = makenode2(Nge, (yyvsp[(1) - (3)].treenode), (yyvsp[(3) - (3)].treenode), (yyvsp[(1) - (3)].treenode)->internal.line); production("relexpr -> arithexpr GE arithexpr\n");}
    break;

  case 60:
#line 235 "parser.y"
    { (yyval.treenode) = makenode2(Neq, (yyvsp[(1) - (3)].treenode), (yyvsp[(3) - (3)].treenode), (yyvsp[(1) - (3)].treenode)->internal.line); production("relexpr -> arithexpr LIKE arithexpr\n");}
    break;

  case 61:
#line 236 "parser.y"
    { (yyval.treenode) = makenode2(Nne, (yyvsp[(1) - (4)].treenode), (yyvsp[(4) - (4)].treenode), (yyvsp[(1) - (4)].treenode)->internal.line); production("relexpr -> arithexpr NOT LIKE arithexpr\n");}
    break;

  case 62:
#line 239 "parser.y"
    { (yyval.treenode) = (yyvsp[(1) - (1)].treenode); production("arithexpr -> term\n");}
    break;

  case 63:
#line 240 "parser.y"
    { (yyval.treenode) = makenode2(Nplus, (yyvsp[(1) - (3)].treenode), (yyvsp[(3) - (3)].treenode), (yyvsp[(1) - (3)].treenode)->internal.line); production("arithexpr -> arithexpr PLUS term\n");}
    break;

  case 64:
#line 241 "parser.y"
    { (yyval.treenode) = makenode2(Nminus, (yyvsp[(1) - (3)].treenode), (yyvsp[(3) - (3)].treenode), (yyvsp[(1) - (3)].treenode)->internal.line); production("arithexpr -> arithexpr MINUS term\n");}
    break;

  case 65:
#line 244 "parser.y"
    { (yyval.treenode) = (yyvsp[(1) - (1)].treenode); production("term -> factor\n");}
    break;

  case 66:
#line 245 "parser.y"
    { (yyval.treenode) = makenode2(Ntimes, (yyvsp[(1) - (3)].treenode), (yyvsp[(3) - (3)].treenode), (yyvsp[(1) - (3)].treenode)->internal.line); production("term -> term MULT factor\n");}
    break;

  case 67:
#line 246 "parser.y"
    { (yyval.treenode) = makenode2(Ndiv, (yyvsp[(1) - (3)].treenode), (yyvsp[(3) - (3)].treenode), (yyvsp[(1) - (3)].treenode)->internal.line); production("term -> term DIV factor\n");}
    break;

  case 68:
#line 247 "parser.y"
    { (yyval.treenode) = makenode2(Nmod, (yyvsp[(1) - (3)].treenode), (yyvsp[(3) - (3)].treenode), (yyvsp[(1) - (3)].treenode)->internal.line); production("term -> term Mod factor\n");}
    break;

  case 69:
#line 250 "parser.y"
    {(yyval.treenode) = makenode1(Nneg, (yyvsp[(2) - (2)].treenode), (yyvsp[(2) - (2)].treenode)->unk.line); production("factor -> MINUS factor\n");}
    break;

  case 70:
#line 251 "parser.y"
    { (yyval.treenode) = (yyvsp[(1) - (1)].treenode); production("factor -> variable\n");}
    break;

  case 71:
#line 252 "parser.y"
    { (yyval.treenode) = (yyvsp[(1) - (1)].treenode); production("factor -> funcall\n");}
    break;

  case 72:
#line 253 "parser.y"
    { (yyval.treenode) = (yyvsp[(1) - (1)].treenode); production("factor -> CONST\n");}
    break;

  case 73:
#line 254 "parser.y"
    { (yyval.treenode) = (yyvsp[(2) - (3)].treenode); production("factor -> (expr)\n");}
    break;


/* Line 1267 of yacc.c.  */
#line 1915 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 257 "parser.y"


/* report parsing error (required by yacc) */
void yyerror(char *s)
{
    fprintf(stderr, "line %d: %s\n", curlineno, s);
}

