#include "ll.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Linked List structure
//Length: length of this linked list
//Head: head node
//Tail: tail node
//Mtf: if Move to Front is on or not
struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
};

uint64_t seeks = 0;
uint64_t links = 0;

//Next is right
//Prev is left
LinkedList *ll_create(bool mtf) {
    LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
    if (ll) {
        ll->length = 0;
        ll->mtf = mtf;
        ll->head = node_create(NULL, NULL);
        ll->tail = node_create(NULL, NULL);
        ll->head->next = ll->tail;
        ll->tail->prev = ll->head;
    }
    return ll;
}

void linked_delete(Node *node) {
    if (node->next != NULL) {
        linked_delete(node->next);
    }
    node_delete(&node);
    return;
}

void ll_delete(LinkedList **ll) {
    if (*ll) {
        linked_delete((*ll)->head);
        free(*ll);
        *ll = NULL;
    }
}

uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

//Checks to see if oldspeak is in this linked list
Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    seeks++;
    Node *currentNode = ll->head;
    while (currentNode->next != NULL) {
        links++;
        currentNode = currentNode->next;
        if (currentNode->oldspeak != NULL && oldspeak != NULL
            && strcmp(currentNode->oldspeak, oldspeak) == 0) {
            //Only run this portion if move to front is enabled
            if (ll->mtf) {
                currentNode->prev->next = currentNode->next;
                currentNode->next->prev = currentNode->prev;
                currentNode->prev = ll->head;
                currentNode->next = ll->head->next;
                ll->head->next->prev = currentNode;
                ll->head->next = currentNode;
            }
            links--;
            return (currentNode);
        }
    }
    links--;
    currentNode = NULL;
    return (currentNode);
}
//Inserts oldspeak into this linked list
void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    if (oldspeak == NULL) {
        fprintf(stderr, "ERROR: Oldspeak is null for ll_insert.\n");
    }
    //See if oldspeak already in linked list;
    if (ll_lookup(ll, oldspeak)) {
        return;
    }

    //Insert new node into linked list with oldspeak and newspeak;
    Node *newNode = node_create(oldspeak, newspeak);
    newNode->prev = ll->head;
    newNode->next = ll->head->next;
    ll->head->next->prev = newNode;
    ll->head->next = newNode;
}

void ll_print(LinkedList *ll) {
    Node *currentNode = ll->head;
    while (currentNode->next != NULL) {
        currentNode = currentNode->next;
        if (currentNode->oldspeak != NULL) {
            node_print(currentNode);
        }
    }
    return;
}
