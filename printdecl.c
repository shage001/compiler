/* printdecl.c
 *
 * print declaration descriptors
 *
 * for CS 433 HW 6
 */

#include <stdio.h>
#include <assert.h>
#include "symtab.h"
#include "syntree.h"

extern int globalsize; /* total size of global variables - defined in resolve.c */

/* Print out the information found in a type descriptor. */
void printtypedesc(typedesc *desc, int isValParam)
{
    fprintf(stderr, "type: ");
    if (desc != NULL) {
        if (!isValParam)
            fprintf(stderr, "&");
        fprintf(stderr, desc->typespec == integer ? "int" : "bool");
        if (desc->isArray) {
	    if (desc->lowbound == 0 && desc->highbound == 0)
		fprintf(stderr, "[]");
	    else
		fprintf(stderr, "[%d..%d]", desc->lowbound, desc->highbound);
        }

        fprintf(stderr, ", typesize = %d", isValParam ? desc->typesize : PTRSIZE);
    }
    else
        fprintf(stderr, "NULL");
    fprintf(stderr, "\n");
}

char *desctypename(decldesc *desc)
{
    switch(desc->unk.type) {
    case vardecl: 
        return "variable";
    case formaldecl:
        return desc->formal.valparam ? "valparam" : "refparam";
    default: /* fundecl */
        return "function";
    }
}

/* Print out the information found in a declaration descriptor. */
void printdcldesc(decldesc *desc, int indent)
{
    int i;
    fprintf(stderr, "\n");
    for (i = 0; i < indent; i++) fprintf(stderr, " ");

    fprintf(stderr, "%8s - %s, line %d, level %d\n",
            desc->unk.STentry->lexptr,
            desctypename(desc),
            desc->unk.line,
            desc->unk.level);

    for (i = 0; i < indent; i++) fprintf(stderr, " ");
    fprintf(stderr, "           ");

    switch(desc->unk.type) {
    case vardecl:
        fprintf(stderr, "displacement %d, ", desc->var.vardisp);
        printtypedesc(desc->var.vartype, 1);
        break;
    case formaldecl:
        fprintf(stderr, "displacement %d, ", desc->formal.vardisp);
        printtypedesc(desc->formal.vartype, desc->formal.valparam);
        break;
    case fundecl:
        fprintf(stderr, "paramsize %d, ", desc->fun.paramsize);
        fprintf(stderr, "localsize %d, ", desc->fun.localsize);
	fprintf(stderr, "return ");
        if (desc->fun.returntype != NULL) {
            printtypedesc(desc->fun.returntype, 1);
        } else
            fprintf(stderr, "type: NULL\n");
        break;
    default:
        assert(0);
    }
}

/* applytolisti - Apply the function 'action' to each of the nodes in
 *      some subtree that forms a list, passing integer parameter.
 */
void applytolisti(node *listhead, void (*action)(), int ident) 
{
    for( ; listhead != NULL; listhead = listhead->internal.child[1])
        action(listhead->internal.child[0], ident);
}

/* prints decldesc of Nident node */
void printident(node *id, int indent)
{
    assert(id->unk.type == Nident);
    if (id->ident.decl != NULL)
        printdcldesc(id->ident.decl, indent);
}

void printdecl(node *decl, int indent)
{
    assert(decl->unk.type == Ndecl);
    printident(decl->internal.child[0], indent);
}

void printvardecl(node *decls, int indent)
{
    applytolisti(decls->internal.child[1], printdecl, indent);
}

void printdecl_stmt(node *stmtnode, int indent)
{
    node *node0 = stmtnode->internal.child[0];
    node *node1 = stmtnode->internal.child[1];
    node *node2 = stmtnode->internal.child[2];

    switch (stmtnode->internal.type) {
    case Nvardecl:
        printvardecl(stmtnode, indent);
        break;

    case Nif:
    case Nelseif:
        applytolisti(node1, printdecl_stmt, indent+4);
        if (node2 != NULL)
            printdecl_stmt(node2, indent);
        break;

    case Nelse:
        applytolisti(node0, printdecl_stmt, indent+4);
        break;

    case Nwhile:
        applytolisti(node1, printdecl_stmt, indent+4);
        break;

    default:
        break;
    }
}

void printparam(node *n, int indent)
{
    printident(n->internal.child[1], indent);
}

void printdecl_fun(node *funnode, int indent)
{
    node *funname = funnode->internal.child[1];
    node *funformals = funnode->internal.child[2];
    node *funstmts = funnode->internal.child[3];

    printident(funname, indent);

    applytolisti(funformals, printparam, indent+4);
    applytolisti(funstmts, printdecl_stmt, indent+4);
}

/* prints out the decldescs attached to the program syntax tree */
void printdecldescs(node *syntree)
{
    if (syntree != NULL) {
        node *globlist = syntree->internal.child[0];
        node *funlist = syntree->internal.child[1];
        fprintf(stderr, "\nglobalsize = %d\n", globalsize);
        applytolisti(globlist, printvardecl, 0);
        applytolisti(funlist, printdecl_fun, 0);
        fprintf(stderr, "\n");
    }
}
