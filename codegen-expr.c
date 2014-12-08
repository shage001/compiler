/* codegen-expr.c  for CS 433 project
 *
 * code generation for expressions
 *
 * Version for hw8
 * Philip Chang and Sam Hage
 * 
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

/* Code generation for a variable (Nident or Narray).  The returned
 * opdesc is always a memory location (i.e. an assignable).
 */
opdesc *genVar(node *varnode)
{
    node *subvar, *subexpr;

    switch (varnode->unk.type) {
        
    case Nident:

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
        typedesc *vartype;
        int eltsize;
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
    codelabel booltrue, boolend;
  
    switch (expr->unk.type) {
    case Nident:
    case Narray:
        return genVar(expr);

    case Nconst:
        return newConstOp(expr->constant.val);
    
    case Nfuncall:
        return genCall(expr);
        // return newConstOp(0);  /* later -- for now, just return constant 0 */

    case Nnot:
    case Nor:
    case Nand:
    case Nlt:
    case Ngt:
    case Neq:
    case Nle:
    case Nge:
    case Nne:
        // FILL IN as discussed in class
        // use genCondExpr() to return the value 0 or 1 in a register
        initLabel(&booltrue, "booltrue");
        initLabel(&boolend, "boolend");
        genCondExpr(expr, TRUE, &booltrue);
        
        /* if get to here, expression is false */
        op0 = newConstOp(0);
        op0 = forceToReg(op0, expr->internal.line);
        outputCmd("jmp", expr->internal.line);
        outputLabel(&boolend);
        
        /* if expression is true */
        placeLabel(&booltrue);
        outputCmd("movl", expr->internal.line);
        outputConst(1); outputOp(op0);

        /* end: */
        placeLabel(&boolend);
        return op0;
        /* return eax */
        return op0;

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
        }
        else { /* expr->unk.type == Ndiv || expr->unk.type == Nmod */
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


/***********************************************************************
 *  Procedures for conditional expressions
 */

/* Code generation for a logical expression (Nnot, Nor, Nand).
 * Uses short-circuit evaluation by calling genCondExpr approprately
 * on the subexpression(s).
 */
void genLogical(node *expr, int sense, codelabel *target)
{
    codelabel fallThru;
    node *lexp = expr->internal.child[0];
    node *rexp = expr->internal.child[1];

    switch (expr->internal.type) {
    case Nnot:
        genCondExpr(lexp, !sense, target);
        break;

    case Nor:
        if (sense) {
            genCondExpr(lexp, TRUE, target);
            genCondExpr(rexp, TRUE, target);
        }
        else {
            initLabel(&fallThru, "or");
            genCondExpr(lexp, TRUE, &fallThru);
            genCondExpr(rexp, FALSE, target);
            placeLabel(&fallThru);
        }
        break;

    case Nand:
        if (!sense) {
            genCondExpr(lexp, FALSE, target);
            genCondExpr(rexp, FALSE, target);
        }
        else {
            initLabel(&fallThru, "and");
            genCondExpr(lexp, FALSE, &fallThru);
            genCondExpr(rexp, TRUE, target);
            placeLabel(&fallThru);
        }
        break;
    
    default: assert(0);
    }
}

/* helper function for genRelational: *********************************/

/* compute a constant relational expression */
int constRelOp(node *expr, opdesc *op0, opdesc *op1)
{
    int a, b;
    assert(isConst(op0) && isConst(op1));
    a = op0->val;
    b = op1->val;
    switch (expr->unk.type) {
    case Nlt: return (a < b);
    case Nle: return (a <= b);
    case Ngt: return (a > b);
    case Nge: return (a >= b);
    case Neq: return (a == b);
    case Nne: return (a != b);
    default:
        assert(FALSE); return FALSE;
    }
}

/* Code generation for a relational expression (Nlt, Nge, Ngt, Nle,
 * Nne, Neq).  Generates code for node0 and node1, outputs a "cmpl"
 * instruction, frees the used registers, and then outputs a
 * conditional jump.
 */
void genRelational(node *expr, int sense, codelabel *target)
{
    opdesc *op0 = genExpr(expr->internal.child[0]);
    opdesc *op1 = genExpr(expr->internal.child[1]);
    int line = expr->internal.line;
    nodetype etype = expr->internal.type;

    /* constant case first: */
    if (isConst(op0) && isConst(op1)) {
        int result = constRelOp(expr, op0, op1);
        if ((result && sense) || ((!result) && (!sense))) { /* result == sense */
            outputCmd("jmp", line);
            outputLabel(target);  /* jump to target */
        } else {
            /* nothing --- don't jump, i.e. fall through */
            outputCmd(NULL, line);
        }
    }
    else {
        /* can't have two memlocs or first memloc and second constant */
        if (isMemloc(op1) && (isMemloc(op0) || isConst(op0)))
            op0 = forceToReg(op0, line);
        outputCmd("cmpl", line);
        outputOp(op1);
        outputOp(op0);
        switch (etype) {
        case Nlt: outputCmd(sense ? "jl"  : "jge", line); break;
        case Nge: outputCmd(sense ? "jge" : "jl",  line); break;
        case Ngt: outputCmd(sense ? "jg"  : "jle", line); break;
        case Nle: outputCmd(sense ? "jle" : "jg", line); break;
        case Nne: outputCmd(sense ? "jne" : "je",  line); break;
        case Neq: outputCmd(sense ? "je"  : "jne", line); break;
        default: assert(0);
        }
        outputLabel(target);
    }
    freeOp(op0);
    freeOp(op1);
    // FILL IN as discussed in class

    // Note: when outputting "cmpl", can't have two memloc operands or
    // first operand memloc and second constant:
    // cmpl memloc, memloc    - not ok
    // cmpl memloc, constant  - not ok
    // cmpl constant, memloc  - ok!
}

/* Code generation for a conditional expression.  Instead of returning an
 * opdesc, output code to branch to "target" if the result of computing
 * "expr" is equal to "sense", and fall through to code below otherwise.
 */
void genCondExpr(node *expr, int sense, codelabel *target)
{
    opdesc *op;
    switch (expr->unk.type) {
    case Nident:
    case Narray:
    case Nconst:
    case Nfuncall:
    
        // FILL IN as discussed in class
        // jump or fall through depending on whether result == 0
        op = genExpr(expr);
        if (isConst(op)) {
            int val = (op->val ? 1 : 0);
            if (val == sense) {
                outputCmd("jmp", expr->internal.line);
                outputLabel(target);
            }
            else {
                /* nothing --- don't jump, i.e. fall through */
                outputCmd(NULL, expr->internal.line);
            }
        }
        else {
            outputCmd("cmpl", expr->internal.line);
            outputConst(0); outputOp(op);
            outputCmd(sense ? "jne" : "je", expr->internal.line);
            outputLabel(target);
        }
        freeOp(op);
    
        break;
    
    case Nnot:
    case Nor:
    case Nand:
        genLogical(expr, sense, target);
        break;
    
    case Nlt:
    case Ngt:
    case Neq:
    case Nle:
    case Nge:
    case Nne:
        genRelational(expr, sense, target);
        break;

    /* none of the following should happen since they don't return a boolean */
    case Nneg:
    case Nplus:
    case Nminus:
    case Ntimes:
    case Ndiv:
    case Nmod:
    default: assert(0);
    }
}
