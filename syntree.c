/* syntree.c
 *
 * CS 433 - syntax tree creation routines 
 */

#include <stdlib.h>
#include "symtab.h"
#include "syntree.h"

/* pointer to the root of the tree for the whole program */
node *syntree;

/* getnode - Allocate space for an internal node and fill in the 
   common fields */
node *getnode(nodetype ntype, int line, int childcount)
{
    node *newnode = (node *) malloc(sizeof(node) 
                                    - (MAXKIDS-childcount)*sizeof(node *));
    newnode->internal.type = ntype;
    newnode->internal.line = line;
    return newnode;
}

/* makenode1 - Make internal node with one child. */
node *makenode1(nodetype ntype, node *child0, int line)
{
    node *newnode = getnode(ntype, line, 1);
    newnode->internal.child[0] = child0;
    return newnode;
}

/* makenode2 - Make internal node with two children. */
node *makenode2(nodetype ntype, node *child0, node *child1, int line)
{
    node *newnode = getnode(ntype, line, 2);
    newnode->internal.child[0] = child0;
    newnode->internal.child[1] = child1;
    return newnode;
}

/* makenode3 - Make internal node with three children. */
node *makenode3(nodetype ntype, node *child0, node *child1, node *child2, 
                int line)
{
    node *newnode = getnode(ntype, line, 3);
    newnode->internal.child[0] = child0;
    newnode->internal.child[1] = child1;
    newnode->internal.child[2] = child2;
    return newnode;
}

/* makenode4 - Make internal node with four children. */
node *makenode4(nodetype ntype, node *child0, node *child1, node *child2, 
                node *child3, int line)
{
    node *newnode = getnode(ntype, line, 4);
    newnode->internal.child[0] = child0;
    newnode->internal.child[1] = child1;
    newnode->internal.child[2] = child2;
    newnode->internal.child[3] = child3;
    return newnode;
}


/* makelist - Add 'newnode' to the tail of (possibly empty) list 'list'.  
   child[2] of the first node is used as a pointer to the tail of the list. */
node *makelist(nodetype ntype, node *list, node *newnode, int line)
{
    node *newlist, *listtail;

    if (list != NULL) {
        newlist = getnode(ntype, line, 2);
        listtail = list->internal.child[2];
        listtail->internal.child[1] = newlist;
    } else {
        newlist = getnode(ntype, line, 3);
        list = newlist;
    }

    newlist->internal.child[0] = newnode;
    newlist->internal.child[1] = NULL;
     
    list->internal.child[2] = newlist;

    return list;
}
