/* main.c
 *
 * Main program for CS 433 compiler project
 *
 * final version
 */

static char usage[] = "\n\
  usage: %s [-t] [-d] [-y] [-p] [-n] sourcefile [codefile]\n\
\n\
  options:\n\
        -t  print out syntax tree\n\
        -d  print out declaration descriptors\n\
        -y  turn on yacc debugging\n\
        -p  print out productions\n\
        -n  don't generate code\n\
\n";


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <getopt.h>
#include "symtab.h"
#include "syntree.h"

int yyparse();
extern FILE *yyin;
extern int yydebug;
extern int PRINT_PRODUCTIONS;   /* defined in parser.y */

int errorcount;
void resolve(node *syntree);    /* defined in resolve.c */

void printdecldescs(node *syntree); /* defined in printdecl.c */

void codegen(node *syntree);    /* defined in codegen-stmts.c */

#define MAXCHARS 50000
char sourcechar[MAXCHARS];    /* array to store input file */
#define MAXLINES 1000
char *sourceline[MAXLINES];   /* array to pointers to  lines of input file */

FILE *OUTPUT;

int main (int argc, char *argv[])
{
    int o;
    int ptree = 0;
    int pdecldescs = 0;
    int gencode = 1;
    char *inputfile = NULL;
    char *outputfile = NULL;

    /* Parse the options */
    while ((o = getopt(argc, argv, "yptdn")) != -1)
        switch (o) {
        case 'y': yydebug = 1; break;           /* turn on yacc debugging */
        case 'p': PRINT_PRODUCTIONS = 1; break; /* print productions */
        case 't': ptree = 1; break;
        case 'd': pdecldescs = 1; break;
        case 'n': gencode = 0; break;
        default:
            fprintf(stderr, usage, argv[0]);
            exit(1);
        }
    if (argc < optind+1 || argc > optind+2) {
        fprintf(stderr, usage, argv[0]);
        exit(1);
    }
    inputfile = argv[optind];
    if (argc == optind+2) {
        outputfile = argv[optind+1];
    }
  
    init_symtab();                /* initialize the symbol table */

    yyin = fopen(inputfile, "r"); /* open the source file */
    if (yyin == NULL) {
        fprintf(stderr, "Cannot open input file '%s'\n", inputfile);
        exit(1);
    }

    yyparse();                    /* invoke the parser */

    errorcount = 0;
    resolve(syntree);             /* do declaration resolution */

    if (ptree)
        printtree(syntree, 1);

    if (pdecldescs)
        printdecldescs(syntree);

    if (errorcount > 0) {
        fprintf(stderr,"\n%d error%s detected.\n", errorcount,
                errorcount > 1 ? "s" : "");
	exit(1);
    }

    if (gencode) {

	/* read input file into sourcechar array */
	char c, *fileptr = sourcechar;
	int k = 1;
	sourceline[k++] = fileptr;
      
	rewind(yyin);
	while((c = getc(yyin)) != EOF) {
	    if (c == '\n') {
		*fileptr++ = 0;
		sourceline[k++] = fileptr;
		assert(k < MAXLINES);
	    } else
		*fileptr++ = c;
	    assert(fileptr < &sourcechar[MAXCHARS]);
	}
	fclose(yyin);

	/* setup outputfile for generated assemby code */
	if (outputfile != NULL)
	    OUTPUT = fopen(outputfile, "w");
	else
	    OUTPUT = stdout;

	/* generate the code */
	codegen(syntree);

	if (outputfile != NULL)
	    fclose(OUTPUT);
    }
  
    return 0;
}
