/* symtab.h
 *
 * CS 433
 *
 * symbol table definitions - extended for homework 6
 */

/* size of the symbol table (should be prime for good hash distribution) */
#define ST_SIZE 407

/* Structure specification for symbol table records.  There will be
 * one of these records for each distinct identifier encountered in
 * the program.  They are allocated and initialized by the scanner.
 */

typedef struct strec {
    char *lexptr;             /* pointer to lexeme */
    struct strec *hashlink;   /* link for hash chains */
    union dcldesc *declstack; /* head pointer for stack of declarations  */
} STrec;

/**************************************************************************/
/* declarations for symbol table manipulation routines */

/* Initialize the symbol table  */
void init_symtab();

/* Return pointer to ST record of lexeme s, or NULL if not found */
STrec *STlookup(char *s);

/* Insert lexeme s into symbol table and return pointer to new STrec */
STrec *STinsert(char *s);

/**************************************************************************/

/* The following definitions all describe parts of the 'declaration
 * table' component of the symbol table.
 */

/* type descriptors *******************************************************/

/* A structure called 'typedesc' is used to keep track of type
 * definitions.  There will be a two global variables IntType and
 * BoolType holding the type descriptors for basic types; type
 * descriptors for arrays will be allocated dynamically.
 */

typedef enum {
    integer,
    bool
} basictype;

typedef struct {
    basictype typespec;
    int isArray;
    int lowbound;
    int highbound;
    int typesize; /* Number of bytes required */
} typedesc;

extern typedesc *IntType, *BoolType;

#define INTSIZE     4           /* size of integer */
#define BOOLSIZE    4           /* size of boolean */
#define PTRSIZE     4           /* size of pointer (ref parameter) */

/* declaration descriptors ************************************************/

/* There will be one 'declaration descriptor' for each declaration in
 * the program.  (Note: Since there may be several declarations for a
 * given identifier, there may be several declaration descriptors
 * associated with a single identifer descriptor.)  These nodes are
 * allocated and initialized during semantic processing.
 */

/* Enumeration type used to label the various type of declaration  */
/* descriptors that can occur in the symbol table.                 */
typedef enum {
    vardecl,         /* global and local variables */
    fundecl,         /* function declarations 	   */
    formaldecl,      /* formal parameter names     */
} decltype;

/* The following are structure specifications for the various types of */
/* declaration descriptors that can occur in the symbol table.         */
/* Certain common components are arranged so that they can be accessed */
/* using the structure type 'unkdesc' regardless of the actual type of */
/* the declaration descriptor.                                         */

/* All declaration descriptors contain the following components */
#define COMMONFIELDS  \
   decltype type;            /* Type of this declaration descriptor        */ \
   STrec *STentry;           /* "back pointer" to associated ST entry      */ \
   int line;                 /* Line number at which declaration occurred  */ \
   union dcldesc *levellink; /* list of declarations made at nesting level */ \
   int level;                /* nesting level of this declaration          */ \
   union dcldesc *decllink;  /* stack of active declarations of this ident */

/* Generic structure used to access common fields of declaration descriptors */
struct unkdesc {
    COMMONFIELDS
};

/* Structure used for variable declaration descriptors                  */
struct vardesc {
    COMMONFIELDS
    typedesc *vartype;           /* type of the variable                */
    int vardisp;                 /* displacement in activation record   */
};

/* Stucture used for procedure & function declaration descriptors       */
struct fundesc {
    COMMONFIELDS
    typedesc *returntype;        /* function return type (NULL for proc's) */
    union dcldesc *formallist;   /* head of list of this proc's formals    */
    int paramsize;               /* size of space required for parameters  */
    int localsize;               /* size of space required for locals      */ 
};

/* Structure used for formal parameter declaration descriptors          */
struct formaldesc {
    COMMONFIELDS
    typedesc *vartype;           /* type of the formal                   */
    int valparam;                /* TRUE: valparam, FALSE: refparam      */
    union dcldesc *formallink;   /* link to rest of proc's formals       */
    int vardisp;                 /* displacement in activation record    */ 
};

/* This union describes the type of all declaration descriptors         */
typedef union dcldesc {
    struct unkdesc unk;
    struct vardesc var;
    struct fundesc fun;
    struct formaldesc formal;
} decldesc;
