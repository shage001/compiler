/* syntree.h
 *
 * CS 433
 *
 * Definitions for syntax tree
 *
 * version for homework 4
 */

/* Number of child pointers required in syntax tree nodes */
#define MAXKIDS 4
                   
/* Enumeration type whose elements are used as phrase-type labels
 * in syntax tree nodes */
typedef enum nodeenum {

    /* leaf nodes */
    Nident,
    Ntype,
    Nconst,

    /* internal nodes (in brackets = optional, i.e. possibly NULL):
                        child[0]       child[1]     child[2]     child[3]   */
    Nprogram,        /*[Ngloblist]    [Nfunlist]                            */
    Ngloblist,       /* Nvardecl      [Ngloblist]                           */
    Nvardecl,        /* N[array]type   Ndecllist                            */
    Narraytype,      /* Ntype          Nconst       Nconst                  */
    Ndecllist,       /* Ndecl         [Ndecllist]                           */
    Ndecl,           /* Nident        [<exprnode>]                          */

    Nfunlist,        /* Nfundecl      [Nfunlist]                            */
    Nfundecl,        /*[Ntype]         Nident      [Nparamlist] [Nstmtlist] */
    Nparamlist,      /* <paramnode>   [Nparamlist]                          */
    /* a <paramnode> is either Nvalparam, Nrefparam, or Narrparam:          */
    Nvalparam,       /* Ntype          Nident                               */
    Nrefparam,       /* Ntype          Nident                               */
    Narrparam,       /* Ntype          Nident                               */

    Nstmtlist,       /* <stmtnode>    [Nstmtlist]                           */
    /* a <stmtnode> is one of Nvardecl,Nassign,Nfuncall,Nreturn,Nif,Nwhile  */
    Nassign,         /* <varnode>      <exprnode>                           */
    Nfuncall,        /* Nident        [Nexprlist]                           */
    Nreturn,         /*[<exprnode>]                                         */
    Nif,             /* <exprnode>     <stmtlist>  [Nelseif/Nelse]          */
    Nelseif,         /* <exprnode>     <stmtlist>  [Nelseif/Nelse]          */
    Nelse,           /* <stmtlist>                                          */
    Nwhile,          /* <exprnode>     <stmtlist>                           */

    /* a <varnode> is either Nident or Narray:                              */
    Narray,          /* Nident         <exprnode>                           */
    Nexprlist,       /* <exprnode>    [Nexprlist]                           */

    /* an <exprnode> is one of <varnode>, Nconst, Nfuncall, or any of:       */
    Nor,             /* <exprnode>     <exprnode>                            */
    Nand,            /* <exprnode>     <exprnode>                            */
    Nnot,            /* <exprnode>                                           */
    Nlt,             /* <exprnode>     <exprnode>                            */
    Nle,             /* <exprnode>     <exprnode>                            */
    Ngt,             /* <exprnode>     <exprnode>                            */
    Nge,             /* <exprnode>     <exprnode>                            */
    Neq,             /* <exprnode>     <exprnode>                            */
    Nne,             /* <exprnode>     <exprnode>                            */
    Nplus,           /* <exprnode>     <exprnode>                            */
    Nminus,          /* <exprnode>     <exprnode>                            */
    Ntimes,          /* <exprnode>     <exprnode>                            */
    Ndiv,            /* <exprnode>     <exprnode>                            */
    Nmod,            /* <exprnode>     <exprnode>                            */
    Nneg,            /* <exprnode>                                           */
} nodetype;

/* Syntax tree nodes come in four different flavors: internal nodes,
 * or one of the three leaf types (Nident, Ntype, Nconst).  The following
 * structure declarations describe each of the different types.  All
 * types of node begin with a 'type' field that is used to hold the
 * phrase-type of the node.  This field is sufficient to determine the
 * type and therefore the layout of the remainder of the node.  All
 * nodes also contain a 'line' component which indicates the source
 * line on which the first character belonging to the phrase
 * represented by the node occurred.  
 */

/* The type 'unknode' provides a template that can be used to access
 * the common components found in all node types when the actual type
 * of the node is unknown.
 */
struct unknode {
    nodetype type;
    int line;
};

/* Nodes of type 'internalnode' are used for all nodes that are
 * internal to the tree.
 */
struct internalnode {
    nodetype type;
    int line;
    union nodeunion *child[MAXKIDS]; /* pointers to the node's sub-trees */
};

/* Nodes of type 'ident' are used for leaf nodes corresponding to
 * identifiers in the source code.  The value in the 'type' component
 * of such a node will always be 'Nident'.
 */
struct identnode {
    nodetype type;
    int line;
    STrec *STentry;      /* Pointer to associated symbol table entry  */
    decldesc *decl;      /*** NEW HW4: pointer to declaration descriptor */
};

/* Nodes of type 'typenode' are used for leaf nodes corresponding to
 * basic type specifications (integer and bool) in the source code.  The
 * value in the 'type' component of such a node will always be 'Ntype'.
 */

/*** NEW HW 4: definition of basictype has been moved to symtab.h */

struct typenode {
    nodetype type;
    int line;
    basictype typespec;   /* integer or bool */
};

/* Nodes of type 'const' are used for leaf nodes corresponding to
 * constants (integers and 'yes'/'no') in the source code.  The value
 * in the 'type' component of such a node will always be 'Nconst'.
 */
struct constnode {
    nodetype type;
    int line;
    basictype typespec; /* type of the constant (integer or bool) */
    int val;            /* value of the constant (use 0 and 1 for bool) */
};

/* Union type that combines the structure types described above */
typedef union nodeunion {
    struct unknode unk;
    struct internalnode internal;
    struct identnode ident;
    struct typenode type;
    struct constnode constant;
} node;

/* global variable pointing to root of tree for the whole program */
extern node *syntree;

/* procedure to print a syntax tree (provided by printtree.c) */
void printtree(node *root, int indent);


/* Tree building operations (provided by syntree.c) */

/* makenode1  -  Make internal node with one child. */
node *makenode1(nodetype ntype, node *child0, int line);

/* makenode2  -  Make internal node with two children. */
node *makenode2(nodetype ntype, node *child0, node *child1, int line);

/* makenode3  -  Make internal node with three children. */
node *makenode3(nodetype ntype, node *child0, node *child1, node *child2, 
                int line);

/* makenode4  -  Make internal node with four children.    */
node *makenode4(nodetype ntype, node *child0, node *child1, node *child2, 
                node *child3, int line);

/* makelist - Add 'newnode' to the tail of (possibly empty) list 'list'. */
node *makelist(nodetype ntype, node *list, node *newnode, int line);
