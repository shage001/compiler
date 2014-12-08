/* symtab.c
 *
 * CS 433
 *
 * Philip Chang
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

STrec *symtab[ST_SIZE];

/* Initialize the symbol table
 * Need to store NULL's in array
 */
void init_symtab()
{
    int i;
    for (i=0; i<ST_SIZE; i++) {
        symtab[i] = NULL;
    }
}


/* Compute a hash funtion used for identifiers
 * (e.g., simply the sum of all the letters in the identifier
 *  modulo the ST size) 
 */
int SThash(char *ident)
{
    int hash = 0;
    unsigned int i;
    // iterate through ident chars and sum their ascii values
    for (i=0; i<strlen(ident); i++) {
        hash += ident[i];
    }
    // printf("hashing: %s -> %d\n", ident, hash%ST_SIZE);
    return hash%ST_SIZE;
}

/* Return pointer to ST record of lexeme s, or NULL if not found */
STrec *STlookup(char *s)
{
    int hash = SThash(s);
    STrec* rec = symtab[hash];
    /* Find the corresponding spot in the table to insert
     * If rec is null, this means the lexeme has not been inserted
     * If there is a hit, we have to iterate through the linked list
     * recursively and see if any strec points to the same lexeme
     */
    while (rec != NULL) {
        if (strcmp(s, rec->lexptr) == 0) {
            return rec;
        }
        else {
            // printf("found %s, was looking for %s\n", rec->lexptr, s);
            rec = rec->hashlink;
        }
    }
    // printf("failed to find %s\n", s);
    return NULL;
}


/* Insert lexeme s into symbol table and return pointer to new STrec */
STrec *STinsert(char *s)
{
    STrec *node;
    int hash = SThash(s);

    node = (STrec *)malloc(sizeof(STrec));
    node->lexptr = (char *)malloc(strlen(s)+1);
    strcpy(node->lexptr, s);

    node->declstack = NULL; /* NEW HW 4: initially empty stack of decldescs. */

    STrec* target = symtab[hash];
    /* If there is a clash, then we want to push node to the front
     * Do this by temporarily storing the existing node and setting
     * the temporary node (target) as the child of the new node
     */
    node->hashlink = target;
    symtab[hash] = node;

    return node;
}
