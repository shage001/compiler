/* syntax.h
 *
 * CS 433 -  definition of token type used by scanner and parser
 *
 */

/* Redefine the type of yylval to be a union type: regular tokens' yylval
   is of type "lexval" (which simply stores the line number), while special
   tokens (the leaves in the syntax tree: identifiers and constants)
   are of type "node". */

struct lexval {
    int line;
};

typedef union {
    node *treenode;
    struct lexval lexeme;
} YYSTYPE;

#define YYSTYPE_IS_DECLARED

extern int curlineno;

extern int yydebug;

int yylex();
extern YYSTYPE yylval;
