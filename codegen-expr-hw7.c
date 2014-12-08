/* codegen-expr.c  for CS 433 project
 *
 * code generation for expressions
 *
 * Philip Chang & Sam Hage
 * This assignment took us roughly 11 hours to complete
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "symtab.h"
#include "syntree.h"
#include "codegen.h"


/***********************************************************************
 *  Procedures for expressions
 */
opdesc* handleConstArithmetic(node *expr, opdesc* op0, opdesc* op1);
opdesc* handleBinaryArithmetic(node *expr, opdesc* op0, opdesc* op1);

/* Code generation for a variable (Nident or Narray).  The returned
 * opdesc is always a memory location (i.e. an assignable).
 */
opdesc *genVar(node *varnode)
{
    node *subvar, *subexpr;

    switch (varnode->unk.type) {
        
    case Nident:

        // FILL IN:
        // use newDispOp to make opdesc for globals, locals, and parameters
        // for refparams, use forceToReg and makeDispOp

        if (varnode->ident.decl->unk.type == vardecl) {
            /* GLOBAL VAR */
            if (varnode->ident.decl->var.level == 0) {
                return newDispOp(varnode->ident.decl->var.vardisp, GLOBALREG);
            }
            /* LOCAL VAR */
            else {
                return newDispOp(LOCAL_OFFS - varnode->ident.decl->var.vardisp - varnode->ident.decl->var.vartype->typesize, ebp);
            }
        } else if (varnode->ident.decl->unk.type == formaldecl) {
            /* REFPARAM */
            if (varnode->ident.decl->formal.valparam == FALSE) {
                opdesc *op = newDispOp(varnode->ident.decl->formal.vardisp + PARAM_OFFS, ebp);
                op = forceToReg(op, varnode->ident.line);
                // pass in 0 as displacement because op is a regop
                makeDispOp(op, 0, FALSE);
                return op;
            }
            /* VALPARAM */
            else {
                return newDispOp(varnode->ident.decl->formal.vardisp + PARAM_OFFS, ebp);
            }
        }

    case Narray:
        subvar = varnode->internal.child[0];
        subexpr = varnode->internal.child[1];
        
        opdesc *arrVar, *subscript;
        decldesc *vardesc;
        typedesc *vartype;
        int eltsize;
        vardesc = subvar->ident.decl;
        if (subvar->ident.decl->unk.type == formaldecl) {
            vartype = subvar->ident.decl->formal.vartype;
        }
        else {
            vartype = subvar->ident.decl->var.vartype;
        }
        eltsize = vartype->typespec == integer ? INTSIZE : BOOLSIZE;
    
        subscript = genExpr(subexpr);   /* compute index */
        if (isMemloc(subscript))
            subscript = forceToReg(subscript, varnode->internal.line);
        arrVar = genVar(subvar);        /* compute base address of array */
        arrVar->disp -= vartype->lowbound * eltsize;  /* adjust for lowbound */

        /* case for constant subscript ************************/
        if (isConst(subscript)) {
            int subnum = subscript->val;
            freeOp(subscript);
            if (vartype->lowbound < vartype->highbound) { /* i.e., not a formal parameter */
                /* can't do this check at compile-time for formal params... */
                if (subnum < vartype->lowbound || subnum > vartype->highbound) {
                    fprintf(stderr, "line %d: WARNING: Array subscript out of bounds\n",
                            varnode->internal.line);
                } /* keep generating code anyway */
            }
            arrVar->disp += subnum * eltsize;
        }
        else {
            makeIndexOp(arrVar, subscript, eltsize);
            /* this frees subscript's memory but not the register */
        }
        return arrVar;
    default:
        assert(FALSE);
        return NULL;
    }
}


/* helper method for constant arithmetic operations */
int constArithOp(node *expr, int a, int b)
{
    switch (expr->unk.type) {
    case Nplus:     return a+b;
    case Nminus:    return a-b;
    case Ntimes:    return a*b;
    case Ndiv:      return a/b;
    case Nmod:      return a%b;
    default:
        assert(FALSE); return 0;
    }
}

/* Code generation for an expression: variable (Nident, Narray),
 * Nconst, Nfuncall, unary ops (Nnot, Nneg), and binary ops (Nor,
 * Nand, Nlt, Ngt, Neq, Nle, Nge, Nne, Nplus, Nminus, Ntimes, Ndiv,
 * Nmod).  Return an opdesc holding the result.
 */
opdesc *genExpr(node *expr)
{
    opdesc *op0, *op1;
  
    switch (expr->unk.type) {
    case Nident:
    case Narray:
        return genVar(expr);

    case Nconst:
        return newConstOp(expr->constant.val);
    
    case Nfuncall:
    case Nnot:
    case Nor:
    case Nand:
    case Nlt:
    case Ngt:
    case Neq:
    case Nle:
    case Nge:
    case Nne:
        return newConstOp(0);  /* later -- for now, just return constant 0 */
    
    case Nneg:
        op0 = genExpr(expr->internal.child[0]);
        if (isConst(op0)) { /* constant */
            op0->val = - op0->val;
        } else { /* register or memloc (TODO: not necess for memtemp?) */
            op0 = forceToReg(op0, expr->internal.line);
            outputCmd("negl", expr->internal.line);
            outputOp(op0);
        }
        return op0;

    case Nplus:
    case Nminus:
    case Ntimes:
    case Ndiv:
    case Nmod:
        op0 = genExpr(expr->internal.child[0]);
        op1 = genExpr(expr->internal.child[1]);
        if (isConst(op0) && isConst(op1)) { /* both constants */
            op0->val = constArithOp(expr, op0->val, op1->val);
            freeOp(op1);
            return op0;
        }
        if (expr->unk.type == Nplus ||
            expr->unk.type == Nminus ||
            expr->unk.type == Ntimes) {
            char *cmd = (expr->unk.type == Nplus ? "addl" :
                         (expr->unk.type == Nminus ? "subl" : "imull"));
            /* make sure that destination is a register */
            /* (TODO: could have a special case for constant and memtemp,
             *   also could swap order for plus and times if op1 is a register)
             */
            op0 = forceToReg(op0, expr->internal.line);
            outputCmd(cmd, expr->internal.line);
            outputOp(op1);
            outputOp(op0);    
            freeOp(op1);
            return op0;
        } else { /* expr->unk.type == Ndiv || expr->unk.type == Nmod */
            /* special case: need op0 in eax, zero-extend into edx */
            opdesc *opEax, *opEdx;
            opEdx = clearSpecificReg(edx, expr->internal.line);
            lock(opEdx);
            opEax = forceToSpecificReg(op0, eax, expr->internal.line);
            if (isConst(op1)) { /* "idivl" doesn't seem to like constants */
                lock(opEax);
                op1 = forceToReg(op1, expr->internal.line);
                unlock(opEax);
            }
            unlock(opEdx);
            outputCmd("cltd", expr->internal.line);
            outputCmd("idivl", expr->internal.line);
            outputOp(op1);
            freeOp(op1);
            if (expr->unk.type == Ndiv) {
                freeOp(opEdx); 
                return opEax;
            } else { /* Nmod */
                freeOp(opEax); 
                return opEdx;
            }
        }

    default:
        assert(FALSE);
        return NULL;    /* this is to avoid warning msg */
    }
}