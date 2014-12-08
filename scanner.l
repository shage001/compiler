/* scanner.l
 *
 * CS 433 - input file for lex
 *
 * Philip Chang
 */

/* lexical definitions for #YOCO */

%{
#include <string.h>
#include <stdlib.h>
#include "symtab.h"
#include "syntree.h"
#include "syntax.h"
#include "y.tab.h"

int curlineno = 1;

extern YYSTYPE yylval;

#define RETURN(toknum) yylval.lexeme.line = curlineno; return(toknum)

void create_ident_node();
void create_type_node(basictype t);
void create_const_node(basictype t);

%}

/* regular definitions */

delim           [ \t]
ws              {delim}+
newline         \n
letter          [A-Za-z_\?]
digit           [0-9]
id              {letter}({letter}|{digit})*
numconst        {digit}+
charconst       "'"([^\n'\\]|"\\"[n'\\])"'"
/* single-line (sl) and multi-line (ml) comments: */
slcomment       "//".*\n
mlcomstart      "/\*"
noStar          [^\*\n]*
starNoSlash     "\*"+[^/\n]
starNewline     "\*"+\n
mlcomend        "\*"+"/"

/* use start condition for multi-line comments
   (see http://www.gnu.org/software/flex/manual/html_mono/flex.html#SEC11 )
*/
%x mlcom
%%
{ws}            {} /* no action and no return */
{newline}       {curlineno++;}
{slcomment}     {curlineno++;}
{mlcomstart}         BEGIN(mlcom);  /* start multi-line comment mode */
<mlcom>{noStar}      {}             /* eat up anything that's not a "*" or a "\n" */
<mlcom>{starNoSlash} {}             /* eat up "*" not followed by "/" */
<mlcom>{newline}     {curlineno++;} /* keep track of linenumbers in multi-line comments */
<mlcom>{starNewline} {curlineno++;} /* keep track of linenumbers in multi-line comments */
<mlcom>{mlcomend}    BEGIN(INITIAL); /* end multi-line comment mode */
int             {create_type_node(integer); return(INT);}
yono            {create_type_node(bool); return(YONO);}
yo              {create_const_node(bool); return(CONST);}
no              {create_const_node(bool); return(CONST);}
global          {RETURN(GLOBAL);}
retweet         {RETURN(RETWEET);}
if              {RETURN(IF);}
else            {RETURN(ELSE);}
while           {RETURN(WHILE);}
end             {RETURN(END);}
or              {RETURN(OR);}
and             {RETURN(AND);}
not             {RETURN(NOT);}
like            {RETURN(LIKE);}
ref             {RETURN(REF);}
{id}            {create_ident_node(); return(ID);}       /* need to put "id" AFTER keywords */
{numconst}      {create_const_node(integer); return(CONST);}
{charconst}     {create_const_node(integer); return(CONST);}
"#"             {RETURN(HASH);}
"<"             {RETURN(LT);}
"<="            {RETURN(LE);}
">"             {RETURN(GT);}
">="            {RETURN(GE);}
"+"             {RETURN(PLUS);}
"-"             {RETURN(MINUS);}
"*"             {RETURN(MULT);}
"/"             {RETURN(DIV);}
"%"             {RETURN(MOD);}
"@"             {RETURN(ASSIGN);}
":"             {RETURN(COLON);}
"!"             {RETURN(BANG);}
"("             {RETURN(LPAREN);}
")"             {RETURN(RPAREN);}
"["             {RETURN(LBRACK);}
"]"             {RETURN(RBRACK);}
".."            {RETURN(DOTDOT);}
","             {RETURN(COMMA);}
.               {printf("\nline %d: illegal character '%c'\n", 
                 curlineno, yytext[0]);}


%%
/* user functions: */

/* First, install the lexeme, whose first character is pointed to
   by yytext and whose length is yyleng, into the symbol table.
   Then create an "identnode" leaf for the syntax tree. */
   
void create_ident_node() 
{
    STrec *p = STlookup(yytext);
    if (p == NULL)                /* insert s into symbol table */
	p = STinsert(yytext);

    yylval.treenode = (node *)malloc(sizeof(struct identnode));
    yylval.treenode->ident.type = Nident;
    yylval.treenode->ident.line = curlineno;
    yylval.treenode->ident.STentry = p;
    yylval.treenode->ident.decl = NULL;  /* NEW HW 4: not resolved yet */
}

/* For integer or bool, create a "typenode" leaf for the syntax tree. */
void create_type_node(basictype t)
{
    yylval.treenode = (node *)malloc(sizeof(struct typenode));
    yylval.treenode->type.type = Ntype;
    yylval.treenode->type.line = curlineno;
    yylval.treenode->type.typespec = t;
}

/* For numbers and 'yo'/'no', create a "constnode" leaf for the syntax tree. */
void create_const_node(basictype t)
{
    yylval.treenode = (node *)malloc(sizeof(struct constnode));
    yylval.treenode->constant.type = Nconst;
    yylval.treenode->constant.line = curlineno;
    yylval.treenode->constant.typespec = t;

    if (t == bool) {
        if (strcmp("yo", yytext) == 0) {
            yylval.treenode->constant.val = 1;
        }
        else {
            yylval.treenode->constant.val = 0;
        }
    }
    else {
        // If yytext is a char constant
        if (yytext[0] == '\'') {
            if (yytext[1] != '\\') {
                yylval.treenode->constant.val = yytext[1];
            }
            else if ((yytext[2] == 'n') || (yytext[2] == 'N')) {
                yylval.treenode->constant.val = '\n';
            }
            else {
                yylval.treenode->constant.val = yytext[2];
            }
        }
        // If yytext is an integer
        else {
            yylval.treenode->constant.val = atoi(yytext);
        }
    }
}

int yywrap() 
{
    return(1);
}       
