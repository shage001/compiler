/* printtree.c
 *
 * print syntax tree
 *
 * CS 433
 */

#include <stdio.h>
#include <assert.h>
#include "symtab.h"
#include "syntree.h"

#define islistheader(operator) (operator == Ngloblist  || \
                                operator == Ndecllist  || \
                                operator == Nfunlist   || \
                                operator == Nparamlist || \
                                operator == Nstmtlist  || \
                                operator == Nexprlist)

static struct nodedesc {
    char *name;
    int arity;
} nodenames[] = {

    {"ident",       0},
    {"type",        0},
    {"const",       0},


    
    {"program",     2},
    {"globlist",    2},
    {"vardecl",     2},
    {"arraytype",   3},
    {"decllist",    2},
    {"decl",        2},

    {"funlist",     2},
    {"fundecl",     4},
    {"paramlist",   2},

    {"valparam",    2},
    {"refparam",    2},
    {"arrparam",    2},
    
    {"stmtlist",    2},

    {"assign",      2},
    {"funcall",     2},
    {"return",      1},
    {"if",          3},
    {"elf",         3},
    {"else",        1},
    {"whilst",      2},


    {"array",       2},
    {"exprlist",    2},


    {"or",          2},
    {"and",         2},
    {"not",         1},
    {"lt",          2},
    {"le",          2},
    {"gt",          2},
    {"ge",          2},
    {"eq",          2},
    {"ne",          2},
    {"plus",        2},
    {"minus",       2},
    {"times",       2},
    {"div",         2},
    {"mod",         2},
    {"neg",         1},
};

void leafprint(node *leaf)
{
    switch (leaf->unk.type) {
    case Nident:
        fprintf(stderr, "= %s : ", leaf->ident.STentry->lexptr);
        if (leaf->ident.decl != NULL)
            fprintf(stderr, "Declared at line %d", leaf->ident.decl->unk.line);
        else
            fprintf(stderr, "Unresolved identifier");
        break;
    case Ntype:
        fprintf(stderr, "= %s", leaf->type.typespec==integer? "int" : "bool");
        break;
    case Nconst:
        fprintf(stderr, "= %d",leaf->constant.val);
        break;
    default:
        assert(0);
    }
}

        
/* Printtree - display syntax tree for debugging purposes */
void printtree(node *root, int indent)
{
    int i;

    if (root == NULL)
        fprintf(stderr, "#         ");
    else
        fprintf(stderr, "#line %3d:",root->unk.line);
  
    for (i = 1; i <= indent; i++)
        fprintf(stderr, " ");
  
    if (root == NULL)
        fprintf(stderr, "NULL node\n");
    else {
        fprintf(stderr, "%s ", nodenames[(int) root->unk.type].name);
        if (root->unk.type == Nident
            || root->unk.type == Ntype
            || root->unk.type == Nconst)
            leafprint(root);
        else if ( !(islistheader(root->internal.type)) )
            fprintf(stderr, "(%1d)", nodenames[(int) root->internal.type].arity);
        fprintf(stderr, "\n");
    
        if (islistheader(root->internal.type)) {
            node *current = root;
            while (current != NULL) {
                printtree(current->internal.child[0], indent+3);
                current = current->internal.child[1];
            }
        }
        else 
            for (i = 0; i < nodenames[(int) root->internal.type].arity; i++)
                printtree(root->internal.child[i],indent+3);
    }
}
