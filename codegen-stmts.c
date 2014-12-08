/* codegen-stmts.c  for CS 433 project
 *
 * code generation for statements
 *
 * version for hw8
 * Philip Chang & Sam Hage
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "symtab.h"
#include "syntree.h"
#include "codegen.h"

/* global variable for return statements */
codelabel funend; /* label of last statement in function */


/* generate code for an assignment statement */
void genAssign(node *stmt)
{
    node *var = stmt->internal.child[0];
    node *expr = stmt->internal.child[1];

    assert (stmt->unk.type == Nassign || stmt->unk.type == Ndecl);

    if (expr == NULL)
        return; /* declaration without assignment */
    
    opdesc *value = genExpr(expr);
    opdesc *target = genVar(var);
    if (isMemloc(value))
        value = forceToReg(value, stmt->internal.line);
    outputCmd("movl", stmt->internal.line);
    outputOp(value);
    outputOp(target);
    freeOp(value);
    freeOp(target);
}

/* handle vardecls as list of assignments */
void genVardecl(node *vardeclnode)
{
    node *decllist = vardeclnode->internal.child[1];
    applytolist(decllist, genAssign);
}

/* Generate code for expressions appearing as actual parameters.
 * Recursive method pushes actuals in reverse order.
 */
void genActuals(node *actualList, decldesc *formal)
{
    // use recursive strategy:
    // if the lists are NULL, we're done
    if (actualList == NULL && formal == NULL) {
        return;
    }

    // otherwise, call genActuals recursively with the rests of
    // both lists (which will generate code to push the parameters
    // in reverse order)
    genActuals(actualList->internal.child[1], formal->formal.formallink);

    node* actualnode = actualList->internal.child[0];
    opdesc* actual = genExpr(actualnode);
    int line = actualList->unk.line;
    // then, generate code to compute the current actual
    // - it it's an array parameter, need to adjust the displacement again
    //   since the called function thinks the lowbound is 0
    // - if it's a refparam (which includes arrays), call computeAddress

    /* refparam */
    if (formal->formal.valparam == FALSE) {
        if (formal->formal.vartype->isArray == TRUE) {
            int eltsize = formal->formal.vartype->typespec == integer ? INTSIZE : BOOLSIZE;
            actual->disp -= actualnode->ident.decl->formal.vartype->lowbound * eltsize; /* adjust for lowbound */
        }
        actual = computeAddress(actual, line);
    }

    // finally, push the actual on the stack
    outputCmd("pushl", line);
    outputOp(actual);
    freeOp(actual);
}

/* Generate code for a function call. */
opdesc *genCall(node *stmt)
{
    assert(stmt->unk.type == Nfuncall);

    decldesc *fundesc = stmt->internal.child[0]->ident.decl;
    decldesc *formallist = fundesc->fun.formallist;
    node *actualList = stmt->internal.child[1];

    // call genActuals with actualList and the function's formallist
    genActuals(actualList, formallist);

    // save volatile regs eax, ecx, edx (call saveReg, which calls spill)
    saveReg(eax);
    saveReg(ecx);
    saveReg(edx);

    // if non-void function, get opdesc for eax to hold the return value
    opdesc *returnop = NULL;
    if (fundesc->fun.returntype != NULL) {
        returnop = clearSpecificReg(eax, stmt->unk.line);
    }

    // output a call command
    outputCmd("call", stmt->unk.line);
    outputFunLabel(fundesc->fun.STentry->lexptr);

    // restore stackpointer after call by adding the function's paramsize
    outputCmd("addl", stmt->unk.line);
    opdesc *paramsize = newConstOp(fundesc->fun.paramsize);
    outputOp(paramsize);
    outputReg(esp);
    free(paramsize);

    // return opdesc for eax or NULL if void function
    return returnop;
}

/* generate code for a return statement */
void genReturn(node *stmt, codelabel *next)
{
    // FILL IN as discussed in class
    node *returnnode = stmt->internal.child[0];
    if (returnnode != NULL) {
        opdesc* returnop = genExpr(returnnode);
        forceToSpecificReg(returnop, eax, stmt->unk.line);
        freeOp(returnop);
    }

    if (next != &funend) {
        outputCmd("jmp", stmt->unk.line);
        outputLabel(&funend);
    }
    else { /* do nothing, fall through */
        outputCmd(NULL, stmt->internal.line);
    }

    // Note that you don't need to output a "jmp"
    // statement if next is the same as &funend
}

/* generate code for an if/elseif statement */
void genIf(node *stmt, codelabel *endif)
{
    // FILL IN as discussed in class
    node *expr = stmt->internal.child[0];
    node *thenstmts = stmt->internal.child[1]; /* stmtlist */
    node *elsestmt = stmt->internal.child[2];  /* Nelseif/Nelse */

    if (elsestmt == NULL) {
        genCondExpr(expr, FALSE, endif);
        genStmtList(thenstmts, endif);
    } else {
        codelabel elsePart;
        initLabel(&elsePart, "else");

        genCondExpr(expr, FALSE, &elsePart);
        genStmtList(thenstmts, endif);
        outputCmd("jmp", 0);
    outputLabel(endif);
        placeLabel(&elsePart);
        genStmt(elsestmt, endif);
    }
}

/* generate code for a while statement */
void genWhile(node *stmt, codelabel *endwhile)
{
    node *expr = stmt->internal.child[0];
    node *stmts = stmt->internal.child[1];

    codelabel loop;
    initLabel(&loop, "while");
    loop.referenced = TRUE;
    placeLabel(&loop);

    genCondExpr(expr, FALSE, endwhile);
    genStmtList(stmts, &loop);
    outputCmd("jmp", 0);
    outputLabel(&loop);
}

/* Generate code for a statement (vardecl, assign, funcall,
 * return, if/elseif/else, or while).
 */
void genStmt(node *stmtnode, codelabel *next)
{
    switch (stmtnode->internal.type) {

    case Nvardecl:
        genVardecl(stmtnode);
        break;
        
    case Nassign:
        genAssign(stmtnode);
        break;
    
    case Nfuncall: /* later */
        genCall(stmtnode);
        break;

    case Nreturn:
        genReturn(stmtnode, next);
        break;

    case Nif:
    case Nelseif:
        genIf(stmtnode, next);
        break;

    case Nelse:
        genStmtList(stmtnode->internal.child[0], next);
        break;
    
    case Nwhile:
        genWhile(stmtnode, next);
        break;

    default:
        assert(FALSE); /* should never get here */
    }
}

/* Generate code for a statement list */
void genStmtList(node *stmtlist, codelabel *next)
{
    codelabel label;

    if (stmtlist == NULL)
        return;

    while(stmtlist->internal.child[1] != NULL) {
        initLabel(&label, "stmt");
        genStmt(stmtlist->internal.child[0], &label);
        placeLabel(&label);
        stmtlist = stmtlist->internal.child[1];
    }
    genStmt(stmtlist->internal.child[0], next);
}

/* Generate code for function */
void genFun(node *funnode)
{
    node *funname = funnode->internal.child[1];
    char* name = funname->ident.STentry->lexptr;
    node *funstmts = funnode->internal.child[3];

    placeFunLabel(funname->ident.STentry->lexptr);
    createFrame(TRUE, name);
    currentfundesc = funname->ident.decl;

    initLabel(&funend, "funend");
    genStmtList(funstmts, &funend);
    placeLabel(&funend);

    removeFrame(TRUE, name);
}

/***********************************************************************
 *  Top-level routine
 */

/* Generate code for the entire program. */
void codegen(node *syntree)
{
    node *funlist = syntree->internal.child[1];

    initRegTab();
    outputHeader();

    applytolist(funlist, genFun);

    outputTrailer();
}
