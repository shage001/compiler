/* codegen-lowlev.c  for CS 433 project
 *
 * code generation: low-level routines
 *
 * Philip Chang & Sam Hage
 *
 * version for hw9
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "symtab.h"
#include "syntree.h"
#include "codegen.h"


/* Debugging output for low-level code-generation functions: */
#define CODEDEBUG 1

/* Data structure (linked list) to keep track of the displacements of
 * free memory temporaries.  The global variable "availMemTemps"
 * points to the beginning of this list.
 */
typedef struct memTempStr {
    int disp;
    struct memTempStr *next;
} memTemp;

/***********************************************************************
 *  Global variables
 */

/* Register names - used to output code */
char *regname[REGCOUNT] = {
    "eax",
    "ecx",
    "edx",
    "ebx",
    "edi",
    "esi",
    "ebp",
    "esp"
};

/* A table to keep track of the status of "general" registers (eax..edi).
 * If register r is free, then regTab[r].op == NULL
 * If register r is used, then regTab[r].op points to the associated opdesc
 * Used registers can be spilled to memory or moved to other registers
 * unless regTab[r].locked == TRUE.
 * We allocate an entry for all registers, including the reserved ones (esi,
 * esp, ebp) so we don't need special cases in the code below, but of
 * course the reserved registers are never considered free.
 */
struct {
    opdesc *op;
    int locked;
} regTab[REGCOUNT];

int codeLine = 0;       /* last line number processed */

int printComma = FALSE; /* remember to print commas between arguments */

memTemp *availMemTemps = NULL;      /* list of memory temporaries */

int labelCount = 0;     /* current label number */

/* Protoypes of functions defined below */
void spill(opdesc *op, regnum r);
void makeAvailable(regnum r, int line);
void freeRegs(opdesc *op);
void freeMemtemp(opdesc *op);
opdesc *newRegOp(regnum r);

/***********************************************************************
 *  Operations on registers
 */

/* mark all non-reserved registers free and unlocked */
void initRegTab()
{
    regnum r;
    for (r = FIRSTREG; r <= LASTREG; r++) {
        regTab[r].op = NULL;
        regTab[r].locked = FALSE;
    }
}

/* Lock register so it won't get moved or spilled */
void lockReg(regnum r) 
{
    regTab[r].locked = TRUE;
}

/* Unlock register */
void unlockReg(regnum r) 
{
    regTab[r].locked = FALSE;
}

/* Get the number of a free register.  If none are left, spill an unlocked
 * used register into a memory temporary.
 */
regnum getFreeRegnum() 
{
    // return first free non-reserved register (starting with eax)
    regnum r;
    for (r = FIRSTREG; r <= LASTREG; r++) {
        if (regTab[r].op == NULL) {
            return r;
        }
    }

    /* not enough regs - need to spill one into memtemp */
    // find the first used non-locked register r and spill its opdesc op
    // by calling spill(op, r);
    opdesc *op;
    for (r = FIRSTREG; r <= LASTREG; r++) {
        if (regTab[r].locked == FALSE) {
            op = regTab[r].op;
            assert(op != NULL);
            spill(regTab[r].op, r);
            return r;
        }
    }

    assert(FALSE); /* should always find a register to spill... */
    return 0;
}

/* Spill register r into memory temp if it is used.  This is necessary for
 * volatile (callee-saved) registers before a function call is made.
 */
void saveReg(regnum r) {
    // FILL IN:
    // simply call spill() if r is in use
    opdesc *op = regTab[r].op;
    if (regTab[r].op != NULL) {
        spill(op, r);
    }
}

/* compute the address of a memory location */
opdesc *computeAddress(opdesc *op, int line)
{
    // FILL IN
    // similar to forceToReg, except uses "leal" instead of "movl"

    // DO WE NEED TO CHECK THE TYPE OF OP?
    freeRegs(op);
    opdesc *newregop = newRegOp(getFreeRegnum());
    outputCmd("leal", line);
    outputOp(op);
    outputOp(newregop);
    freeMemtemp(op);
    free(op);
    return newregop;
}


/***********************************************************************
 *  Operations on opdescs
 */

/* Allocate a new opdesc of type constop and value val */
opdesc *newConstOp(int val) 
{
    opdesc* newopdesc = (opdesc*) malloc(sizeof(opdesc));
    newopdesc->type = constop;
    newopdesc->val = val;
    return newopdesc;
}

/* Allocate a new opdesc of type regop and register r and update regtab[r] */
opdesc *newRegOp(regnum r) 
{
    opdesc* newopdesc = (opdesc*) malloc(sizeof(opdesc));
    newopdesc->reg = r;
    newopdesc->type = regop;
    assert(regTab[r].op == NULL);
    regTab[r].op = newopdesc;
    return newopdesc;
}

/* Allocate a new opdesc of type dispop, register r, displacement disp,
 * isTemp==FALSE, and update regtab[r] 
 */
opdesc *newDispOp(int disp, regnum r) 
{
    opdesc* newopdesc = (opdesc*) malloc(sizeof(opdesc));
    newopdesc->type = dispop;
    newopdesc->reg = r;
    newopdesc->disp = disp;
    newopdesc->isTemp = FALSE;
    regTab[r].op = newopdesc;
    return newopdesc;
}

/* Turn regop 'op' (register) into a dispop (memory location) */
void makeDispOp(opdesc *op, int disp, int isTemp) 
{
    assert(op->type == regop);
    op->disp = disp;
    op->isTemp = isTemp;
    op->type = dispop;
}

/* Turn dispop 'op1' (memory location) into an indexop (array location),
 * using register 'op2' as index and 's' as scale factor.  Free op2's
 * memory, but don't call freeOp(), which would also mark op'2 register
 * as free.  Instead, update regTab of op2's register to point to op1.
 */
void makeIndexOp(opdesc *op1, opdesc *op2, int s) 
{
    assert(op1->type == dispop);
    assert(op2->type == regop);

    op1->type = indexop;
    op1->reg2 = op2->reg;
    op1->val = s;
    regTab[op2->reg].op = op1;
    free(op2);
}

/* Lock 'op' by locking its register(s) */
void lock(opdesc *op)
{
    /* constop should not have a register to lock */
    if (op->type != constop) {
        regTab[op->reg].locked = TRUE;
        if (op->type == indexop) {
            regTab[op->reg2].locked = TRUE;
        }     
    }
}

/* Unlock 'op' by unlocking its register(s) */
void unlock(opdesc *op)
{ 
    if (op->type != constop) {
        regTab[op->reg].locked = FALSE;
        if (op->type == indexop) {
            regTab[op->reg2].locked = FALSE;
        }     
    }
}

/* Force an operand to a register.  If it is a register already, just
 * return it. Otherwise, allocate a new register, output code to move
 * the operand to the register, free the old operand, and return the
 * new register.  In order to allow the operand's register(s) to be
 * reused, call freeRegs(op) before allocating a new register, but
 * don't call freeOp(op) until the end.
 */
opdesc *forceToReg(opdesc *op, int line)
{
    // use getFreeRegnum and newRegOp
    if (op->type == regop) {return op;}
    else {
        freeRegs(op);
        opdesc *newregop = newRegOp(getFreeRegnum());
        outputCmd("movl", line);
        outputOp(op);
        outputOp(newregop);
        freeMemtemp(op);
        free(op);
        return newregop;
    }
}

/* Make a specific register available (used for "idivl") */
opdesc *clearSpecificReg(regnum r, int line)
{
    makeAvailable(r, line);
    return newRegOp(r);
}

/* Force an operand to a specific register (used for "idivl" and
 * returning values from functions) 
 */
opdesc *forceToSpecificReg(opdesc *op, regnum r, int line)
{
    // if it's in the correct register already, just return it
    if (op->type == regop && op->reg == r) {
        return op;
    }

    // call makeAvailable to make r available, UNLESS op is a memloc
    // that uses this register (e.g., if op is "0(%eax)" and we want
    // eax, we want to simply output "movl 0(%eax), %eax"

    /* dispop and reg == r OR indexop and reg2 == r */
    if (!(isMemloc(op) && op->type == dispop && op->reg == r) && 
        !(isMemloc(op) && op->type == indexop && op->reg == r) &&
        !(isMemloc(op) && op->type == indexop && op->reg2 == r)) {
        makeAvailable(r, line);
    }

    // output a movl instruction from the old op to register r
    outputCmd("movl", line);
    outputOp(op);
    outputReg(r);


    // THEN call freeOp to free the old op, THEN call newRegOp
    // (so that register allocation table is correct; we can't call
    // freeOp earlier since the debugging output created by freeMemTemps
    // could mess things up)
    // Note that this makes outputting the new register tricky
    // in the movl instruction above (hint: use outputReg)
    freeOp(op);
    // return the new regop
    return newRegOp(r);

}

/***********************************************************************
 *  Freeing opdescs
 */

/* Mark the register(s) used by 'op' as free */
void freeRegs(opdesc *op)
{
    if (!isConst(op)) {
        regTab[op->reg].op = NULL;
        if (op->type == indexop) {
            regTab[op->reg2].op = NULL;
        }     
    }
}

/* Free memory temporary 'op' (in case it is one) by pushing its displacement
 * onto the front of the linked list availMemTemps
 */
void freeMemtemp(opdesc *op) 
{
    // if op is a memory temporary:
    if (op->type == dispop && op->isTemp == TRUE) {
        outputDebugN("freeing memory temp at disp %d", op->disp);
        // allocate a new memTemp structure with op's displacement and push
        // it onto the front of availMemTemps
        memTemp *temp = (memTemp*) malloc(sizeof(memTemp));
        temp->disp = op->disp;
        temp->next = availMemTemps;
        availMemTemps = temp;
    } 
}

void freeOp(opdesc *op) 
{
    freeRegs(op);
    freeMemtemp(op);
    free(op);
}

/***********************************************************************
 *  Spilling and moving of opdescs
 */

/* Free op's register(s) by spilling it into a memtemp.  Update op to reflect
 * the change.  If op is a dispop or indexop, need to 'movl' it into the
 * register it occupies (parameter r) before spilling.
 * If availMemTemps is not NULL, reuse first available displacement, else
 * increase localsize to get a new displacement.
 */
void spill(opdesc *op, regnum r) 
{
    int disp;
    /* if there are available memtemps, use the top one and adjust availMemTemps */
    if (availMemTemps != NULL) {
        memTemp *memFree = availMemTemps;
        disp = availMemTemps->disp;
        availMemTemps = memFree->next;
        free(memFree);
        outputDebugN("reusing memtemp at disp %d", disp);
    }
    /* else we need to increase localsize and calculate the new displacement */
    else {
        currentfundesc->fun.localsize += 4;
        disp = -1*(currentfundesc->fun.localsize) + LOCAL_OFFS;
        outputDebugN("creating new memtemp at disp %d", disp);
    }

    // if memory location (dispop or indexop), need to move it into reg first:
    //   output movl instruction and op, then mark op's register(s) as free,
    //   then change op into register r and output that
    if (isMemloc(op)) {
        outputCmd("movl", 0);
        outputOp(op);
        freeRegs(op);
        op->type = regop;
        op->reg = r;
        outputReg(r);
    }

    // now we are ready for the actual spilling:
    // output movl instruction and op, then mark op's register as free
    // then use makeDispOp to change op into a temporary displacement off ebp
    // and output op
    assert(op->type == regop);
    outputCmd("movl", 0);
    outputOp(op);
    freeRegs(op);
    op->reg = ebp;
    makeDispOp(op, disp, TRUE);
    outputOp(op);
}

/* Make register r available by making the opdesc that uses it (if
 * any) use a different register.  Call getFreeRegnum to get a new
 * register (which in turn may cause spilling of some other register).
 * If 'op' is the opdesc that uses r, we need to MODIFY op since it is
 * still being used.  Note that op could be a regop, dispop, or
 * indexop (in which case r could be either op->reg or op->reg2), but
 * in all cases we want to output "movl r, newreg" and update op to
 * use newreg instead of r.
 */
void makeAvailable(regnum r, int line) 
{
    opdesc* op = regTab[r].op;
    // if r is free, return, else:
    if (op == NULL) {
        return;
    }

    outputDebugS("making reg %s available", regname[r]);
    assert(!regTab[r].locked);

    // lock the opdesc's register(s) while getting a new regnum
    lock(op);
    regnum newreg = getFreeRegnum();
    unlock(op);

    // output a movl instruction from the old to the new register
    // update the opdesc so it refers to the new register
    outputCmd("movl", line);
    outputReg(r);
    outputReg(newreg);
    
    // mark the opdesc's register(s) (r and perhaps another) as free
    freeRegs(op);

    // change the opdesc to the new register and output that

    /* index op */
    if (op->type == indexop) {
        /* check if reg or reg2 is r */
        if (op->reg == r) {
            op->reg = newreg;
        }
        else {
            op->reg2 = newreg;
        }
    }
    /* dispop or regop */
    else {
        op->reg = newreg;
    }
    
    // update regTab to reflect that the new register now belongs to the opdesc and that the old register is free
    regTab[newreg].op = op;
    regTab[r].op = NULL;
}

/***********************************************************************
 *  Outputting assembly code
 */

/* Output a comment */
void outputComment(char *s)
{
    fprintf(OUTPUT, "\n//%s", s);
}

/* Output a debugging message with an integer */
void outputDebugN(char *m, int n)
{
    if (CODEDEBUG) {
        fprintf(OUTPUT, "\n//");
        fprintf(OUTPUT, m, n);
    }
}

/* Output a debugging message with a string */
void outputDebugS(char *m, char *s)
{
    if (CODEDEBUG) {
        fprintf(OUTPUT, "\n//");
        fprintf(OUTPUT, m, s);
    }
}

/* Global array containing source file (declared in main.c) */
extern char *sourceline[];

/* Output a comment when the line number changes.
 * Also show the corresponding line from source program.
 * Use line number 0 to avoid this comment. */
void checkLineNum(int line)
{
    if (line != 0 && line != codeLine) {
        fprintf(OUTPUT, "\n      //-------------------------- %2d: %s",
                line, sourceline[line]);
        codeLine = line;
    }
}

/* Output an assembly command */
void outputCmd(char *opcode, int line)
{
    checkLineNum(line);
    if (opcode == NULL) /* use NULL to force line number check only */
        return;
    fprintf(OUTPUT, "\n\t%s\t", opcode);
    printComma = FALSE;
}

/* Output an operand */
void outputOp(opdesc *op)
{
    if (printComma)
        fprintf(OUTPUT, ", ");
    switch (op->type) {
    case constop:
        fprintf(OUTPUT, "$%d", op->val); 
        break;
    case regop:
        fprintf(OUTPUT, "%%%s", regname[op->reg]); 
        break;
    case dispop:
        fprintf(OUTPUT, "%d(%%%s)", op->disp, regname[op->reg]); 
        break;
    case indexop:
        fprintf(OUTPUT, "%d(%%%s, %%%s, %d)", op->disp,
                regname[op->reg], regname[op->reg2], op->val);
        break;
    default: assert(FALSE);
    }
    printComma = TRUE;
}

/* Output a constant operand */
void outputConst(int val)
{
    if (printComma)
        fprintf(OUTPUT, ", ");
    fprintf(OUTPUT, "$%d", val); 
    printComma = TRUE;
}

/* Output a register operand */
void outputReg(regnum r)
{
    if (printComma)
        fprintf(OUTPUT, ", ");
    fprintf(OUTPUT, "%%%s", regname[r]);
    printComma = TRUE;
}

/***********************************************************************
 *  Labels and branches
 */

/* initialize a new label */
void initLabel(codelabel *label, char *name)
{
  label->name = name;
  label->num = ++labelCount;
  label->referenced = FALSE;
}

/* output a label as operand */
void outputLabel(codelabel *label)
{
  fprintf(OUTPUT, "%s%d", label->name, label->num);
  label->referenced = TRUE;
}

/* output a label as target */
void placeLabel(codelabel *label)
{
  if (label->referenced)
    fprintf(OUTPUT, "\n%s%d:", label->name, label->num);
}

/* Output a function label (prepend "yo_" to avoid conflicts) */
void outputFunLabel(char *funname)
{
    fprintf(OUTPUT, "yo_%s", funname);
}

/* Output a function label as target (prepend "yo_" to avoid conflicts) */
void placeFunLabel(char *funname)
{
    outputComment("================================");
    fprintf(OUTPUT, "\nyo_%s:", funname);
}

/***********************************************************************
 *  Code for Functions
 */

/* Create frame and save registers.  Since the frame size (local vars
 * and memtemps) isn't known until the body has been processed,
 * decrement %esp by symbolic value 'frsize_funname', which will be
 * defined at the end of the function when the localsize is known.
 */
void createFrame(int saveRegs, char *funname)
{
    outputCmd("pushl", 0); outputReg(ebp);
    outputCmd("movl", 0);  outputReg(esp); outputReg(ebp);
    if (saveRegs) {
        outputCmd("pushl", 0); outputReg(ebx);
        outputCmd("pushl", 0); outputReg(edi);
        outputCmd("pushl", 0); outputReg(esi);
    }
 
    if (funname != NULL) {
        fprintf(OUTPUT, "\n\tsubl\t$frsize_%s, %%esp", funname);
    }
}

/* Remove frame and restore registers.  Define the frame size
 * 'frsize_funname' to be the localsize (can be found in global
 * variable currentfundesc)
 */
void removeFrame(int restoreRegs, char *funname)
{
    int framesize = currentfundesc->fun.localsize;
    if (restoreRegs) {
        /* if (framesize > 0) **** safest to always do this... */
    outputCmd("leal\t-12(%ebp), %esp", 0);
    
        outputCmd("popl", 0); outputReg(esi);
        outputCmd("popl", 0); outputReg(edi);
        outputCmd("popl", 0); outputReg(ebx);
    }
    outputCmd("leave", 0);
    outputCmd("ret", 0);

    /* define the frame size */
    if (funname != NULL)
        fprintf(OUTPUT, "\n\t.set\tfrsize_%s, %d", funname, framesize);
}

/* Output header code */
void outputHeader()
{
    fprintf(OUTPUT, ".globl main");
    fprintf(OUTPUT, "\nmain:");
    createFrame(TRUE, NULL);
    /* set global pointer */
    outputCmd("movl", 0);
    fprintf(OUTPUT, "$globals"); printComma = TRUE;
    outputReg(GLOBALREG);
    /* call YOCO() */
    outputCmd("call", 0);
    outputFunLabel("YOCO");
    /* return 0 from main */
    outputCmd("xorl\t%eax, %eax", 0);
    removeFrame(TRUE, NULL);
}

/* Output code for put() / get() */
void outputPutGet(char *intStr)
{
    placeFunLabel("put");     /* put(n) */
    createFrame(FALSE, NULL); /* call printf("%d", n) */
    outputCmd("pushl\t8(%ebp)", 0);  /* push n */
    outputCmd("pushl", 0); fprintf(OUTPUT, intStr); /* push "%d" */
    outputCmd("call\tprintf", 0);
    removeFrame(FALSE, NULL);

    placeFunLabel("get");     /* n = get() */
    createFrame(FALSE, NULL); /* call scanf("%d", &x) */
    outputCmd("subl\t$4, %esp", 0);       /* make room for temporary x at -4(%ebp) */
    outputCmd("leal\t-4(%ebp), %eax", 0);
    outputCmd("pushl\t%eax", 0);          /* push its address */
    outputCmd("pushl", 0); fprintf(OUTPUT, intStr); /* push "%d" */
    outputCmd("call\tscanf", 0);
    outputCmd("movl\t-4(%ebp), %eax", 0); /* return x */
    removeFrame(FALSE, NULL);
}

/* Output code for putc() / getc() */
void outputPutcGetc()
{
    placeFunLabel("putc");  /* simply jump to putchar() */
    outputCmd("jmp\tputchar", 0);
    placeFunLabel("getc");  /* simply jump to getchar() */
    outputCmd("jmp\tgetchar", 0);
}

/* Output trailer code */
void outputTrailer()
{
    outputPutGet("$intStr");
    outputPutcGetc();
    fprintf(OUTPUT, "\n");
    fprintf(OUTPUT, "\n.section\t.rodata");
    fprintf(OUTPUT, "\nintStr: .string \"%%d\"");
    fprintf(OUTPUT, "\n\n.section\t.data");
    if (globalsize < 1)
        globalsize = 1; /* to avoid assembler warning on next line */
    fprintf(OUTPUT, "\nglobals: .space %d", globalsize);
    fprintf(OUTPUT, "\n");
}

/* TEMPORARY CAN PROBABLY DELETE
void outputHeader()
{
    fprintf(OUTPUT, ".globl yocomain");
    fprintf(OUTPUT, "\nyocomain:");
    fprintf(OUTPUT, "\n\tpushl\t%%ebp");
    fprintf(OUTPUT, "\n\tmovl\t%%esp, %%ebp");
    fprintf(OUTPUT, "\n\tpushl\t%%ebx");
    fprintf(OUTPUT, "\n\tpushl\t%%edi");
    fprintf(OUTPUT, "\n\tpushl\t%%esi");
}



void outputTrailer()
{
    fprintf(OUTPUT, "\n");
    fprintf(OUTPUT, "\n\tpopl\t%%esi");
    fprintf(OUTPUT, "\n\tpopl\t%%edi");
    fprintf(OUTPUT, "\n\tpopl\t%%ebx");
    fprintf(OUTPUT, "\n\tleave");
    fprintf(OUTPUT, "\n\tret\n");
}
*/