#include "node.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Given by professor long in piazza
#define stringdup(s) strcpy(malloc(strlen(s) + 1), s)

//Node adt
//Oldspeak = oldspeak of node
//Newspeak = corresponding newspeak of node
//Next: Next node in linked list
//Prev: previous node in linked list
Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        //printf("%s\n", oldspeak);
        //printf("%s\n", newspeak);
        if (oldspeak == NULL) {
            n->oldspeak = NULL;
        } else {
            n->oldspeak = stringdup(oldspeak);
        }
        if (newspeak == NULL) {
            n->newspeak = NULL;
        } else {
            n->newspeak = stringdup(newspeak);
        }

        n->next = NULL;
        n->prev = NULL;
    }
    return n;
}

void node_delete(Node **n) {
    if (*n) {
        free((*n)->oldspeak);
        free((*n)->newspeak);
        (*n)->oldspeak = NULL;
        (*n)->newspeak = NULL;
        free(*n);
        *n = NULL;
    }
}

void node_print(Node *n) {
    if (n->newspeak == NULL) {
        printf("%s\n", n->oldspeak);
    } else {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    }
}
