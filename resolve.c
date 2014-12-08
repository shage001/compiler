/* resolve.c
 *
 * CS 433 - declaration resolution 
 * version for hw6 - type checking
 * Philip Chang & Sam Hage
 * This assignment took us about 7 hours to complete
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "symtab.h"
#include "syntree.h"

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

/***********************************************************************
 *  Global variables
 */

#define MAXDEPTH 100    /* Maximum allowed depth of scope nesting  */

extern int errorcount;  /* keep track of number of errors */

int curlevel;           /* Current scope nesting level */

decldesc *scopestack[MAXDEPTH];  /* Stack of headers for lists of
                                    declarations made in open scopes */

typedesc *IntType, *BoolType;   /* pointers to typedescs for basic types */
typedesc *IntArrType, *BoolArrType;  /* pointers to typedescs for array param types */

decldesc *currentfundesc;        /* current function being processed        */
int curdisp;                     /* keep track of current displacement      */
int globalsize;                  /* total size of global variables required */

/***********************************************************************
 *  Utilities
 */

/* applytolist - Apply the function 'action' to each of the nodes in
 *      some subtree that forms a list.
 */
void applytolist(node *listhead, void (*action)()) 
{
    for( ; listhead != NULL; listhead = listhead->internal.child[1])
        action(listhead->internal.child[0]);
}

/* applytolist2 - Same as applytolist, except that it also passes a
 *      parameter 'param' to 'action'.
 */
void applytolist2(node *listhead, void (*action)(), void *param) 
{
    for( ; listhead != NULL; listhead = listhead->internal.child[1])
        action(listhead->internal.child[0], param);
}

/***********************************************************************
 * Initialization of global variables for basic type descriptors
 */

void initialize_basic_typedescs()
{
    IntType = (typedesc *)malloc(sizeof(typedesc));
    IntType->typespec = integer;
    IntType->isArray = FALSE;
    IntType->typesize = INTSIZE;
    
    BoolType = (typedesc *)malloc(sizeof(typedesc));
    BoolType->typespec = bool;
    BoolType->isArray = FALSE;
    BoolType->typesize = BOOLSIZE;

    /* Create typedescs for IntArrType and BoolArrType */
    IntArrType = (typedesc *)malloc(sizeof(typedesc));
    IntArrType->typespec = integer;
    IntArrType->isArray = TRUE;
    IntArrType->highbound = 0;
    IntArrType->lowbound = 0;
    IntArrType->typesize = PTRSIZE;

    BoolArrType = (typedesc *)malloc(sizeof(typedesc));
    BoolArrType->typespec = bool;
    BoolArrType->isArray = TRUE;
    BoolArrType->highbound = 0;
    BoolArrType->lowbound = 0;
    BoolArrType->typesize = PTRSIZE;

    /*** FILL IN ***/
    // also create typedescs for IntArrType and BoolArrType here
    // (used when resolving array parameters)
    // set their low and high bounds both to 0
}

/***********************************************************************
 * Initialization of I/O functions
 */

/* create decldesc for I/O function */
void makeIOfun(char *funName, char *paramName, typedesc *retType)
{
    STrec *STentr;
    decldesc *iofundsc = (decldesc *)malloc(sizeof(struct fundesc));
    decldesc *ioformaldsc = NULL;
    

    if (paramName != NULL) {   /* putc, put functions have a parameter */
        /* add the parameter name to the symbol table */
        STentr = STlookup(paramName);
        if (STentr == NULL)
            STentr = STinsert(paramName);
        STentr->declstack = NULL;

        /* create a declaration descriptor for the formal parameter */
        ioformaldsc = (decldesc *)malloc(sizeof(struct formaldesc));
        ioformaldsc->formal.type = formaldecl;
        ioformaldsc->formal.STentry = STentr;
        ioformaldsc->formal.line = 0;
        ioformaldsc->formal.levellink = NULL;
        ioformaldsc->formal.level = 1;
        ioformaldsc->formal.decllink = NULL;
        ioformaldsc->formal.vartype = IntType;
        ioformaldsc->formal.valparam = TRUE;
        ioformaldsc->formal.formallink = NULL;
        ioformaldsc->formal.vardisp = 0;
    }

    /* add the function name to the symbol table */
    STentr = STlookup(funName);
    if (STentr == NULL)
        STentr = STinsert(funName);
    STentr->declstack = iofundsc;

    /* create a declaration descriptor for the function */
    iofundsc->fun.type = fundecl;
    iofundsc->fun.STentry = STentr;
    iofundsc->fun.line = 0;
    iofundsc->fun.levellink = NULL;
    iofundsc->fun.level = 0;
    iofundsc->fun.decllink = NULL;
    iofundsc->fun.returntype = retType;
    iofundsc->fun.formallist = ioformaldsc;
    iofundsc->fun.localsize = 0;
    iofundsc->fun.paramsize = (iofundsc->fun.formallist != NULL) ? INTSIZE : 0;
}

void initialize_IOfuns()
{
    makeIOfun("getc", NULL, IntType);  /* int getc()  */
    makeIOfun("get",  NULL, IntType);  /* int get()   */
    makeIOfun("putc", "c",  NULL);     /* putc(int #c) */
    makeIOfun("put",  "n",  NULL);     /* put(int #n)  */
}

/***********************************************************************
 * Declaration processing
 ***********************************************************************/
 
/* insertdecl -- Insert a new declaration descriptor into the stack of
 *      declarations associated with its identifier and the list of
 *      all declarations made at the current level.  Create a pointer
 *      from the Nident node to the new declaration descriptor.
 *      Before inserting the new declaration, make sure that the
 *      identifier was not previously defined in this scope.  If it
 *      was, free its space and return NULL.  Otherwise, return a
 *      pointer to the new declaration descriptor.
 *
 *      This function is called for three types of declarations:
 *      variables, function names, and formal parameters.
 */
decldesc *insertdecl(decldesc *newdecl, decltype newdecltype, node *identnode)
{
    assert(identnode->ident.type == Nident);
    
    /* 1. check for multiple declaration at same level
       (print error message to stderr and return NULL if so) */

	// check the declstack pointed to by the symbol table for this identifier
    STrec* rec = identnode->ident.STentry;
    if (rec->declstack != NULL && rec->declstack->unk.level == curlevel) {
        fprintf(stderr, "Declaration of var (%s) at line (%d) failed, already declared in current scope (%d) at line (%d)\n", rec->lexptr, 
            identnode->ident.line, curlevel, rec->declstack->unk.line);
        errorcount++;
        free(newdecl);
        return NULL;
    }

    /* 2. set common fields (type, line, level) */
    newdecl->unk.type = newdecltype;
    newdecl->unk.line = identnode->ident.line;
    newdecl->unk.level = curlevel;

    /* 3. set back pointer to ST record */
    newdecl->unk.STentry = rec;

    /* 4. insert into stack of declarations */
    newdecl->unk.decllink = rec->declstack;
    rec->declstack = newdecl;

    /* 5. insert into chain of levellinks */
    newdecl->unk.levellink = scopestack[curlevel];
    scopestack[curlevel] = newdecl;

    /* 6. create pointer from identnode to new declaration descriptor */
    identnode->ident.decl = newdecl;

    return newdecl;
}


/***********************************************************************
 *  Basic Function for resolving an identifier
 */

/* resolve_ident -- Attempt to resolve the declaration descriptor pointer
 *      in an Nident node by setting it to the declstack pointer
 *      stored in the node's symbol table entry.  If successful,
 *      return the descriptor.  Otherwise, print an error message and
 *      return NULL.
 *
 *      This function is called when USES of an identifier are encountered,
 *      i.e., in statements and expressions.
 */
decldesc *resolve_ident(node *identnode)
{
    assert(identnode->ident.type == Nident);

    STrec* STentry = identnode->ident.STentry;
    if (STentry->declstack != NULL) {
        identnode->ident.decl = STentry->declstack;
        return STentry->declstack;
    }
    /* STrec entry points to a NULL decldesc */
    errorcount++;
    fprintf(stderr, 
            "Failed to resolve declaration descriptor for identifier node %s (line %d)\n", 
            identnode->ident.STentry->lexptr,
            identnode->ident.line);
    return NULL;
}


/***********************************************************************
 *  Types
 */

/* resolve_type -- Check that 'typenode' represents a valid type, i.e.,
 *      either is 'Ntype' or 'Narraytype'.  In the former case, return
 *      either IntType or BoolType; in the latter case, malloc a new
 *      type descriptor, set the fields appropriately, and return it.
 */
typedesc *resolve_type(node *typenode)
{

    assert(typenode->unk.type == Ntype || typenode->unk.type == Narraytype);

    if (typenode->type.type == Ntype) {
        if (typenode->type.typespec == integer) return IntType;
        else return BoolType;
    }

	// if the type is an array, grab the lower and high bound
    else {

        node* basictypenode = typenode->internal.child[0];
        node* lowboundnode = typenode->internal.child[1];
        node* highboundnode = typenode->internal.child[2];

        assert(basictypenode->unk.type == Ntype);
        assert(lowboundnode->unk.type  == Nconst);
        assert(highboundnode->unk.type == Nconst);

        typedesc* ArrayType = (typedesc *)malloc(sizeof(typedesc));
        ArrayType->typespec = basictypenode->type.typespec;
        ArrayType->isArray = TRUE;
        ArrayType->lowbound = lowboundnode->constant.val;
        ArrayType->highbound = highboundnode->constant.val;

        if (ArrayType->lowbound > ArrayType->highbound) {
            fprintf(stderr, "Lowbound is greater than highbound (line %d)\n", typenode->type.line);
            errorcount++;
            // return NULL;
        }

        /* Check what type of array it is and calculate its size */
        if (ArrayType->typespec == integer) {
            ArrayType->typesize = (ArrayType->highbound - ArrayType->lowbound + 1) * INTSIZE;
        }
        else {
            ArrayType->typesize = (ArrayType->highbound - ArrayType->lowbound + 1) * BOOLSIZE;            
        }

        return ArrayType;
    }
    
}

/***********************************************************************
 *  Variable declarations
 */

/* prototype for function defined below */
typedesc* resolve_expression(node *exprnode);

void resolve_actuals(node *actuallist, decldesc *ddsc, int linenum);

/* resolve_singledecl -- Allocate a new 'vardesc' declaration
 *      descriptor, set its 'vartype' field, and push it onto the
 *      stack of declaration descriptors by calling 'insertdecl()'.
 *      If initialized variable, also resolve the expression.
 */
void resolve_singledecl(node *declnode, typedesc *vartypedesc)
{

	// create a new decldesc
    decldesc* declaration = (decldesc*) malloc(sizeof(struct vardesc));
    declaration->var.vartype = vartypedesc;

    /* set var displacement to current displacement then increment current displacement */
    declaration->var.vardisp = curdisp;
    curdisp = curdisp + vartypedesc->typesize;
    assert(declnode->internal.child[0]->unk.type == Nident);

    insertdecl(declaration, vardecl, declnode->internal.child[0]);

	// check if it has a child, which is an exprnode
    if (declnode->internal.child[1] != NULL) {
        if (declaration->unk.level == 0) {
            fprintf(stderr, "Global variables can not be initialized (line %d)\n", declnode->internal.line);
            errorcount++;
        }
        resolve_expression(declnode->internal.child[1]);
    }

    
}

/* resolve_vardecl -- Process variable declarations, i.e., a bunch of
 *      identifiers declared to be of a certain type.
 */
void resolve_vardecl(node *vardeclnode)
{
    node *typenode = vardeclnode->internal.child[0];
    node *decllist = vardeclnode->internal.child[1];

    typedesc *vartypedesc = resolve_type(typenode);
  
    applytolist2(decllist, resolve_singledecl, vartypedesc);
}


/***********************************************************************
 *  Opening and closing scopes
 */

/* open new scope: increase curlevel, and initialize the scopestack at
 * this level to NULL */
void open_scope()
{

    if (curlevel+1 < MAXDEPTH) {
        curlevel++;
        scopestack[curlevel] = NULL;
    }
    else {
        fprintf(stderr, "Exceded max depth for scope\n");
        errorcount++;
    }

}

/* close_scope: pop all declarations made in current scope by following the
 * current levellink-list, then decrease curlevel */
void close_scope()
{

    decldesc* desc;
    for (desc = scopestack[curlevel]; desc != NULL; desc = desc->unk.levellink) {
        desc->unk.STentry->declstack = desc->unk.decllink;
    }
    curlevel--;
}

/* prototype for forward declaration */
void resolve_stmt(node *stmtnode);

/* resolve_block: create new scope for statement lists in function bodies,
 * if/elseif/else and while statements */
void resolve_block(node *stmtlist)
{
    open_scope();
    applytolist(stmtlist, resolve_stmt);
    close_scope();
}

/*********************************************************************/
 
/* declaration resolution for an expression: variable (Nident,
 * Narray), Nconst, Nfuncall, unary ops (Nnot, Nneg), and binary ops
 * (Nor, Nand, Nlt, Ngt, Neq, Nle, Nge, Nne, Nplus, Nminus, Ntimes,
 * Ndiv, Nmod).
 */
typedesc* resolve_expression(node *exprnode)
{
    nodetype etype = exprnode->unk.type;
    node *node0 = exprnode->internal.child[0];
    node *node1 = exprnode->internal.child[1];
  
    decldesc* identdesc;
    typedesc *expr_type0, *expr_type1;

    switch (etype) {
    case Nident:
        identdesc = resolve_ident(exprnode);
        if (identdesc != NULL) {
            /* ident is a var */
            if (identdesc->unk.type == vardecl) {
                return identdesc->var.vartype;
            }
            /* ident is a formal */
            else if (identdesc->unk.type == formaldecl) {
                return identdesc->formal.vartype;
            }
            /* ident is a function */
            else {
                fprintf(stderr, "No amount of duct tape will change the fact that %s is already declared as a function (line %d).\n", 
                    identdesc->unk.STentry->lexptr, exprnode->unk.line);
                errorcount++;
                return NULL;
            }
        }
        /* ident node could not be resolved, the error message should have been handled by resolve_ident */
        return NULL;
    break;

    case Narray:
        identdesc = resolve_ident(node0);
        if (identdesc != NULL) {
            /* ident is not an array */
            if (identdesc->var.vartype->isArray == FALSE) {
                fprintf(stderr, "The ship's hyperdrive runs on arrays but #%s is not declared as an array (line %d).\n", 
                    identdesc->unk.STentry->lexptr, exprnode->unk.line);
                errorcount++;
                return NULL;
            }
        }
        /* check if access index is a (non-array) integer */
        if (resolve_expression(node1)->typespec != integer || resolve_expression(node1)->isArray == TRUE) {
            fprintf(stderr, "Where did you go to space pirate school? Julliard? Access of array #%s expects int type (line %d)\n", 
                identdesc->unk.STentry->lexptr, exprnode->unk.line);
            errorcount++;
            return NULL;
        }

        if (identdesc->var.vartype->typespec == integer) {
            return IntType;
        }
        else {
            return BoolType;
        }
    break;

    case Nconst:
        /* check what type of constant it is */
        if (exprnode->constant.typespec == integer) {
            return IntType;
        }
        /* else is bool */
        else {
            return BoolType;
        }
    break;

    case Nfuncall:
        identdesc = resolve_ident(node0);
        if (identdesc->unk.type != fundecl) {
            fprintf(stderr, "We'll never collect enough cereal box tops to buy a new pirate flag if you can't keep your functions straight. #%s is not a function (line %d).\n", 
                    identdesc->unk.STentry->lexptr, exprnode->unk.line);
            errorcount++;
            return NULL;
        }
        resolve_actuals(node1, identdesc, node0->unk.line);
        /* return type can be NULL if ident is a void function */
        return identdesc->fun.returntype;
    break;

    // unary ops
    case Nnot:
        /* not expects a bool */
        expr_type0 = resolve_expression(node0);
        if (expr_type0->typespec != bool) {
            fprintf(stderr, "Did you miss Captain Swillbeard's info session on boolean algebra? \"not\" expects a bool (line %d).\n", 
                exprnode->unk.line);
            errorcount++;
            return NULL;
        }
        return BoolType;
    break;
    case Nneg:
        /* negation expects integer */
        expr_type0 = resolve_expression(node0);
        if (expr_type0->typespec != integer) {
            fprintf(stderr, "Walk the space plank: You can't negate (-) a non-int value (line %d).\n", exprnode->unk.line);
            errorcount++;
            return NULL;
        }
        return IntType;
    break;

    // binary ops

    // binary logical ops
    case Nor:
    case Nand:
        expr_type0 = resolve_expression(node0);
        expr_type1 = resolve_expression(node1);
        /* first check if both parts of the expression resolved successfully */
        if (expr_type0 == NULL || expr_type1 == NULL) {
            return NULL;
        }
        /* next make sure they are both bools */
        else if (expr_type0->typespec != bool || expr_type1->typespec != bool) {
            fprintf(stderr, "Now the space navy is after us because and/or expressions expect two bools (line %d).\n", exprnode->unk.line);
            errorcount++;
            return NULL;
        }
        /* if both of those conditions pass, we are fine */
        else {
            return BoolType;
        }
    break;

    // binary equality operators
    case Neq:
    case Nne:
        expr_type0 = resolve_expression(node0);
        expr_type1 = resolve_expression(node1);

        /* first check if both parts of the expression resolved successfully */
        if (expr_type0 == NULL || expr_type1 == NULL) {
            return NULL;
        }
        /* next make sure both sides of the expression resolve to the same type */
        else if (expr_type0->typespec != expr_type1->typespec) {
            fprintf(stderr, "You have single-handedly ruined burrito night because you used string beans instead of pinto beans. They are not the same type. Just like the two sides of this [in]equality. (line %d)\n", 
                exprnode->unk.line);
            errorcount++;
            return NULL;
        }
        else {
            return BoolType;
        }
    break;

    /* comparison operators */
    case Nlt:
    case Ngt:
    case Nle:
    case Nge:
        expr_type0 = resolve_expression(node0);
        expr_type1 = resolve_expression(node1);
        /* propogate up any errors */
        if (expr_type0 == NULL || expr_type1 == NULL) {
            return NULL;
        }
        /* both children of the operator need to be integers */
        else if (expr_type0->typespec != integer || expr_type1->typespec != integer) {
            fprintf(stderr, "The ship's treasure compass is malfunctioning because this comparison (i.e. <, >, <=, >=) expects two ints (line %d)\n", exprnode->unk.line);
            errorcount++;
            return NULL;
        }
        else {
            return BoolType;
        }
    break;

    /* binary arithmetic operators */
    case Nplus:
    case Nminus:
    case Ntimes:
    case Ndiv:
    case Nmod:
        expr_type0 = resolve_expression(node0);
        expr_type1 = resolve_expression(node1);
        /* propogate errors */
        if (expr_type0 == NULL || expr_type1 == NULL) {
            return NULL;
        }
        /* both children of arithmetic operators need to be integers */
        else if (expr_type0->typespec != integer || expr_type1->typespec != integer) {
            fprintf(stderr, "Space Pirate Code Section VII Part b Subsection i clearly states that binary arithmetic requires two ints (line %d)\n", 
                exprnode->unk.line);
            errorcount++;
            return NULL;
        }
        else {
            return IntType;
        }
    break;
    
    default:
        assert(FALSE); /* should never get here */
        return NULL;
    }
  
}

/********************************************************************/

/* declaration resolution for a statement: vardecl, assign, funcall,
 * return, if/elseif/else, or while
 */
void resolve_stmt(node *stmtnode)
{
    node *node0 = stmtnode->internal.child[0];
    node *node1 = stmtnode->internal.child[1];
    node *node2 = stmtnode->internal.child[2];

    decldesc* ddsc;
    typedesc *ident_typedesc, *exprdesc;

    switch (stmtnode->internal.type) {

    case Nvardecl:
        resolve_vardecl(stmtnode);
    break;

    case Nassign:
        ident_typedesc = resolve_expression(node0);
        if (ident_typedesc != NULL) {
            if (ident_typedesc->isArray == TRUE) {
                fprintf(stderr, "There is no wind in outer space. We have no use for sails and we also cannot assign #%s because it is an array (line %d).\n",
                node0->ident.STentry->lexptr, stmtnode->unk.line);
                errorcount++;
            }
            else {
                /* if we are assigning our ident to the result of a funcall */
                if (node1->unk.type == Nfuncall) {
                    ddsc = resolve_ident(node1->internal.child[0]);
                    if (ddsc != NULL && ddsc->unk.type == fundecl) {
                        if (ddsc->fun.returntype == NULL) {
                            fprintf(stderr, "Polly want a cracker but #%s is being assigned to a void function (line %d)\n",
                                node0->ident.STentry->lexptr, stmtnode->unk.line);
                            errorcount++;                  
                        }
                        else {
                            resolve_actuals(node1->internal.child[1], ddsc, node1->unk.line);
                        }
                    }
                    else if (ddsc->unk.type != fundecl) {
                        fprintf(stderr, "We'll never collect enough cereal box tops to buy a new flag for our pirate ship if you can't keep your functions straight. #%s is not a function (line %d).\n", 
                            ddsc->unk.STentry->lexptr, node1->unk.line);
                        errorcount++;
                    }
                }
                /* if it is just a normal expression */
                else {
                    exprdesc = resolve_expression(node1);
                    if (exprdesc != NULL && exprdesc != ident_typedesc) {
                        char* lex;
                        if (node0->unk.type == Nident) {
                            lex = node0->ident.STentry->lexptr;
                        }
                        else {
                            lex = node0->internal.child[0]->ident.STentry->lexptr;
                        }

                        fprintf(stderr, "Face reality. You are a space pirate and space pirates do not become famous salsa dancers. Similarly, assignment of #%s has mismatched types (line %d).\n",
                        lex, stmtnode->unk.line);
                        errorcount++;
                    }
                }       
            }
        }
    break;

    case Nfuncall:
        ddsc = resolve_ident(node0);
        /* check if ident is a declared function */
        if (ddsc->unk.type != fundecl) {
            fprintf(stderr, "Swab the deck, you planet-lubber. %s is not declared as a function (line %d)\n", node0->ident.STentry->lexptr, stmtnode->unk.line);
            errorcount++;
        }
        else {
            resolve_actuals(node1, ddsc, node0->unk.line);
        }
    break;

    case Nreturn:
        if (node0 != NULL) {
            /* should be void function */
            if (currentfundesc->fun.returntype == NULL) {
                fprintf(stderr, "Function %s is void like the depths of space/my soul but it returns something (line %d).\n", currentfundesc->fun.STentry->lexptr, stmtnode->unk.line);
                errorcount++;
            }
            else {
                /* check return type */
                if (resolve_expression(node0) != currentfundesc->fun.returntype) {
                    fprintf(stderr, "Space travel changes you but it does not change the fact that function %s returns an incorrect type (line %d)\n", 
                        currentfundesc->fun.STentry->lexptr, stmtnode->unk.line);
                    errorcount++;
                }
            }
        }
        /* function does not return anything */
        else {
            if (currentfundesc->fun.returntype != NULL) {
                fprintf(stderr, "The love of my life said she needed space and moved to the far moon of Jupiter. She will never return, just like how non-void function %s does not return anything (line %d)\n",
                        currentfundesc->fun.STentry->lexptr, stmtnode->unk.line);
                errorcount++;
            }
        }
        break;    

	// for if, elseif, else, and while we need to resolve block to enter a new scope
    case Nif:
    case Nelseif:
        if (resolve_expression(node0)->typespec != bool) {
            fprintf(stderr, "if/elseif statements expect a bool expression. This error hurts more than the time that space whale took my left leg (line %d).\n",
                    stmtnode->unk.line);
            errorcount++;
        }
        resolve_block(node1);
        if (node2 != NULL) {
            resolve_stmt(node2);
        }
    break;

    case Nelse:
        resolve_block(node0);
    break;

    case Nwhile:
        if (resolve_expression(node0)->typespec != bool) {
            fprintf(stderr, "I'm the last of Barrett's space privateers and I can tell this while statement lacks a boolean expression (line %d).\n", stmtnode->unk.line);
            errorcount++;
        }
        resolve_block(node1);
    break;
       
    default:
        assert(FALSE); /* should never get here */
    }
}

/***********************************************************************
 *  Functions and formal parameters
 */


/* resolve_formallist -- recursive procedure to resolve a list of
 *      formal parameters.  We're not using applytolist here, because
 *      all formal parameters need to be chained together via the
 *      'formallink' pointers.  Returns the first param's decldesc.
 */
decldesc *resolve_formallist(node *paramlist)
{
    /* Basecase: if paramlist is NULL, return NULL */
    if (paramlist == NULL) {
        return NULL;
    }
    else {
        node *param = paramlist->internal.child[0];
        node *restoflist = paramlist->internal.child[1];

        node *paramtype = param->internal.child[0];
        node *paramid = param->internal.child[1];
  
        typedesc *paramtypedesc = resolve_type(paramtype);
        decldesc *newdecl, *result, *nextdecl;

        /* if array parameter, use the correct type descriptor: */
        if (param->internal.type == Narrparam) {
            if (paramtypedesc == IntType)
                paramtypedesc = IntArrType;
            else
                paramtypedesc = BoolArrType;
        }
        
        /* 1. allocate a new decl desc for a formal parameter, set its
         *    specific fields, call insertdecl and store the result.
         */
        newdecl = (decldesc *) malloc(sizeof(struct formaldesc));
        newdecl->formal.vartype = paramtypedesc;
        newdecl->formal.valparam = (param->internal.type == Nvalparam);
        result = insertdecl(newdecl, formaldecl, paramid);

        /*  2. Recursively process the rest of the formals and store the
         *     pointer to the next decldesc.
         */

        /* Set vardisp of the new decl to curdisp and then increment curdisp */
        newdecl->formal.vardisp = curdisp;
        curdisp = curdisp + newdecl->formal.vartype->typesize;

        nextdecl = resolve_formallist(restoflist);

        /* 3. If insertdecl didn't return NULL (i.e. no error), set the
         *     formallink pointer to the next decldesc (the result of the
         *     recursive call).
         */
        if (result != NULL)
            newdecl->formal.formallink = nextdecl;

        /* 4. Return the result of insertdecl (the current decldesc or NULL)
         */
        return result;
    }


}

/* In first pass, only create declaration descriptor for the function
 * name and the formal parameters, so that all function headers in
 * entire program are known by the time function calls are processed
 * in the second pass.
 */
void resolve_funheader(node *funnode)
{
    assert(funnode->unk.type == Nfundecl);

    /* Allocate a new decldesc for the function, set its specific
     * fields, and call insertdecl.  Note that if insertdecl returns
     * NULL (error), funname doesn't get resolved, i.e. its decl
     * pointer is NULL when we process the body in the second pass.
     */
    decldesc* newdecl = (decldesc*) malloc(sizeof(struct fundesc));
    
    /* set newdecl's return type */
    node* typenode = funnode->internal.child[0];

    // check if there is a return type
    if (typenode != NULL) {
        newdecl->fun.returntype = resolve_type(typenode);
    }
    else {
        newdecl->fun.returntype = NULL;
    }

    /* now insert */
    node* identnode = funnode->internal.child[1];
    // do we need to store the returned pointer from insertdecl?
    insertdecl(newdecl, fundecl, identnode);

    /* Next, process formals: open new scope, call resolve_formallist,
     * store the pointer to the first formal's decldesc in the
     * function's decldesc formallist field, and close scope again.
     */

    open_scope();

    /* Set curdisp to zero before we resolve formals */
    curdisp = 0;

    /* set newdecl's formallist */
    if (newdecl != NULL) {
        newdecl->fun.formallist = resolve_formallist(funnode->internal.child[2]);
        // added by Sam to update with solutions
        newdecl->fun.paramsize = curdisp; /* store space required for formals */
    }

    /* Paramsize must be equal to how much we have increased curdisp by */
    newdecl->fun.paramsize = curdisp;

    close_scope();
}

/* In second pass, process each function body: open the scope again
 * and add the exisiting decldescs for the formal parameters to
 * declstacks and levellinks again, then process the statements, and
 * finally close the scope again.
 */
void resolve_funbody(node *funnode)
{
    /* open new scope, add the formals to the scope again by doing
     * steps 4 and 5 of insertdecl manually.  Then, process statements
     * in function body, and close scope again.
     */
    assert(funnode->unk.type == Nfundecl);

    node *funname = funnode->internal.child[1];
    node *funstmts = funnode->internal.child[3];

    decldesc *newfundesc = funname->ident.decl;
    decldesc *curformal;

    open_scope();

    currentfundesc = newfundesc;

    if (newfundesc != NULL) {
        /* add formals to scope again */
        for (curformal = newfundesc->fun.formallist; curformal != NULL;
             curformal = curformal->formal.formallink) {
            /* do the relevant steps of "insertdecl" manually: */

            /* 4. insert into stack of declarations */
            curformal->unk.decllink = curformal->unk.STentry->declstack;
            curformal->unk.STentry->declstack = curformal;

            /* 5. insert into chain of levellinks */
            curformal->unk.levellink = scopestack[curlevel];
            scopestack[curlevel] = curformal;
        }
    }

    /* set curdisp to 0 before resolving statements */
    curdisp = 0;

    /* call resolve_stmt on each statement in the body */
    applytolist(funstmts, resolve_stmt);

    /* the local size should be how much curdisp has changed after resolving all statements */
    if (newfundesc != NULL) { // added by Sam to update with solutions
        newfundesc->fun.localsize = curdisp;
    }

    close_scope();
}

/* resolve_actuals  -- Do declaration resolution and type checking for
 *      the expressions and variables in an actual parameter list.
 *      Pass in the function's decldesc and the line number of
 *      the call for error messages.
 */
 void resolve_actuals(node *actuallist, decldesc *ddsc, int linenum)
{
    node *actual;
    decldesc *curformal;
    typedesc *actualtype;

    if (ddsc == NULL) { /* if decldesc not available (due to error),
                           resolve the actual parameters anyway */
        applytolist(actuallist, (void (*)()) resolve_expression);
        return;
    }

    /* otherwise, follow the actuallist and the formallist in sync
       and compare the types */

    for (curformal = ddsc->fun.formallist;
         actuallist != NULL && curformal != NULL;
         actuallist = actuallist->internal.child[1],
             curformal = curformal->formal.formallink) {

        actual = actuallist->internal.child[0];
        actualtype = resolve_expression(actual);

        if (!curformal->formal.valparam   /* refparam */
            && !(actual->unk.type == Nident || actual->unk.type == Narray)) {
            errorcount++;
            fprintf(stderr,
                    "line %d: I may have a space hook for a hand but I know this function expects a ref param (#%s), so it can't HANDle a valparam\n",
                    actual->unk.line,
                    curformal->formal.STentry->lexptr);
        }

        if (actualtype != NULL &&
            (actualtype->isArray != curformal->formal.vartype->isArray ||
             actualtype->typespec != curformal->formal.vartype->typespec)) {
            errorcount++;
            fprintf(stderr,
                    "line %d: I can't see out of my right eye because of this space eye patch but I can see that the parameter type of formal %s is incorrect\n",
                    actual->unk.line,
                    curformal->formal.STentry->lexptr);
        }
    }

    if (actuallist != NULL) {
        errorcount++;
        fprintf(stderr, "line %d: I used to bullseye womp rats in my T-16 back home on Tatooine, so you have no excuse for calling %s with one or more extra parameters\n",
                linenum,
                ddsc->fun.STentry->lexptr);
    }   
    if (curformal != NULL) {
        errorcount++;
        fprintf(stderr, "line %d: Is that a belaying pin in your pants or are you just missing one or more parameters when calling '%s'\n",
                linenum,
                ddsc->fun.STentry->lexptr);
    }
}

/* Error checking for YOCO() main function */
void check_for_YOCO() {
    STrec *yocorec = STlookup("YOCO");
    if (yocorec != NULL) {
        decldesc *yocodesc = yocorec->declstack;
        if (yocodesc->fun.returntype != NULL) {
            fprintf(stderr, "YOCO() should be void (line %d)\n", yocodesc->fun.line);
            return;
        }
        if (yocodesc->fun.formallist != NULL) {
            fprintf(stderr, "YOCO() should not take parameters (line %d)\n", yocodesc->fun.line);
            return;            
        }
    }
    fprintf(stderr, "Missing valid declaration of YOCO()\n");
}

/***********************************************************************
 *  Top-level routine
 */

/* resolve  --  Do declaration resolution for the entire program. */
void resolve(node *syntree)
{
    initialize_basic_typedescs();
    initialize_IOfuns();

    if (syntree == NULL) {
        errorcount = 1;
    } else {
        node *globlist = syntree->internal.child[0];
        node *funlist = syntree->internal.child[1];

        errorcount = 0;
        curlevel = 0;       /* initialize current nesting level */
        scopestack[curlevel] = NULL;  /* initialize list of declarations
                                       * made in current scope */

        curdisp = 0;
        applytolist(globlist, resolve_vardecl);
        globalsize = curdisp;
        applytolist(funlist, resolve_funheader);
        applytolist(funlist, resolve_funbody);
        check_for_YOCO();
    }
}


