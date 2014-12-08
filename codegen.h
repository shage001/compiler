/* codegen.h  for CS 433 project
 *
 * definitions and prototypes for code generation
 *
 * version for hw 8
 */

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

/* type definitions *********************************************/

/* registers on the Pentium */
#define REGCOUNT 8
typedef enum { 
    eax,
    ecx,
    edx,
    ebx,
    edi,
    esi,
    ebp,
    esp
} regnum;

/* range of "general purpose" (i.e., non-reserved) registers */
#define FIRSTREG eax
#define LASTREG edi

/* reserve esi as a pointer to the global area */
#define GLOBALREG esi

/* Types of operands */
typedef enum { 
    constop,    /* integer constant                             */
    regop,      /* register                                     */
    dispop,     /* memory location "disp(reg)"                  */
    indexop,    /* array memory location "disp(reg,reg2,s)"     */
} optype;

/* Operand descriptor */
typedef struct {
    optype type; /* type of operand                              */
    int isTemp;  /* TRUE if this operand (dispop) is a temporary */
    regnum reg;  /* base register (for regop, dispop, indexop)   */
    regnum reg2; /* index register (used for indexop)            */
    int disp;    /* displacement (for dispop / indexop)           */
    int val;     /* constval (for constop); scale factor (for indexop) */
} opdesc;

/* offset to ebp for locals and parameters */
#define LOCAL_OFFS -12
#define PARAM_OFFS 8

/* useful macros for high-level code */
/* (the high-level code shouldn't access the fields of an opdesc directly) */
#define isConst(op) ((op)->type == constop)
#define isMemloc(op) ((op)->type == dispop || (op)->type == indexop)

/* type definition for labels */
typedef struct {
    int num;
    char *name;
    int referenced;
} codelabel;

/* global variables *********************************************/

/* defined in resolve.c: */
extern int globalsize;           /* total size required for globals */
extern decldesc *currentfundesc; /* decldesc of current function */

/* file to print output to (defined in main.c) */
extern FILE *OUTPUT;

/* prototypes ***************************************************/

/* declared in resolve.c: */

typedesc *gettype(decldesc *desc);
void applytolist(node *listhead, void (*action)());

/* declared in codegen-expr.c: */

opdesc *genVar(node *varnode);
opdesc *genExpr(node *expr);
void genCondExpr(node *expr, int sense, codelabel *target);

/* declared in codegen-stmts.c: */

void genStmt(node *stmt, codelabel *next);
void genStmtList(node *stmtlist, codelabel *next);

/* declared in codegen-lowlev.c: */

void initRegTab();

opdesc *newConstOp(int val);
opdesc *newDispOp(int disp, regnum r);

void makeDispOp(opdesc *op, int disp, int isTemp);
void makeIndexOp(opdesc *op1, opdesc *op2, int s);
void freeOp(opdesc *reg);

void lock(opdesc *op);
void unlock(opdesc *op);
opdesc *forceToReg(opdesc *op, int line);
opdesc *forceToSpecificReg(opdesc *op, regnum r, int line);
opdesc *clearSpecificReg(regnum r, int line);

void saveReg(regnum r);
opdesc *computeAddress(opdesc *op, int line);
void outputFunLabel(char *funname);
void createFrame(int saveRegs, char *funname);
void removeFrame(int restoreRegs, char *funname);

opdesc *genCall(node *stmt);

void outputComment(char *s);
void outputDebugN(char *m, int n);
void outputDebugS(char *m, char *s);

void outputCmd(char *opcode, int line);
void outputOp(opdesc *op);
void outputConst(int val);
void outputReg(regnum r);

void initLabel(codelabel *label, char *name);
void outputLabel(codelabel *label);
void placeLabel(codelabel *label);
void placeFunLabel(char *funname);

void outputHeader();
void outputTrailer();
