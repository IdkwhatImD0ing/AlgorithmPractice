#include "pq.h"

#include "node.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
//Priority Queue adt
//Capcity is size of pq
//Size is current size
struct PriorityQueue {
    uint32_t capacity;
    uint32_t size;
    Node **items;
};

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) {
        q->size = 0;
        q->capacity = capacity;
        q->items = (Node **) calloc(capacity, sizeof(Node *));
        if (!q->items) {
            free(q);
            q = NULL;
        }
    }
    return q;
}

void pq_delete(PriorityQueue **q) {
    if (*q && (*q)->items) {
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}

bool pq_empty(PriorityQueue *q) {
    if (q->size == 0) {
        return true;
    }
    return false;
}

bool pq_full(PriorityQueue *q) {
    if (q->size == q->capacity) {
        return true;
    }
    return false;
}

uint32_t pq_size(PriorityQueue *q) {
    return (q->size);
}

bool enqueue(PriorityQueue *q, Node *n) {
    //Array will be ordered from highest frequency to losest frequency,
    bool found = false;
    Node *temp = NULL;
    Node *temp2 = NULL;
    if (pq_full(q)) {
        return false;
    }

    for (uint32_t i = 0; i < q->capacity; i++) {
        if (found == false) {
            //If reached empty spot
            if (q->size == i) {
                q->items[q->size] = n;
                q->size++;
                return true;
            }
            //If given node frequency is higher than frequency of Node in array.
            if (n->frequency >= q->items[i]->frequency) {

                found = true;
                temp = q->items[i];
                q->items[i] = n;
            }
        } else if (found) {
            temp2 = q->items[i];
            q->items[i] = temp;
            temp = temp2;
        }
        if (temp == NULL && found) {
            q->size++;
            return true;
        }
    }

    return false;
}

bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) {
        return false;
    }
    q->size--;
    *n = q->items[q->size];
    return true;
}

void pq_print(PriorityQueue *q) {
    for (uint32_t x = 0; x < q->size; x++) {
        node_print(q->items[x]);
    }
}
/*
int main(void) {
    Node *removed;
    PriorityQueue *testQueue = pq_create(3);
    enqueue(testQueue, node_create(0, (uint64_t)1));
    enqueue(testQueue, node_create(1, (uint64_t)1));
    enqueue(testQueue, node_create(2, (uint64_t)1));
    pq_print(testQueue);
    
    enqueue(testQueue, node_create(5, 5));
    enqueue(testQueue, node_create(2, 2));
    enqueue(testQueue, node_create(3, 3));
    enqueue(testQueue, node_create(1, 1));
    enqueue(testQueue, node_create(6, 6));
    enqueue(testQueue, node_create(3, 3));
    enqueue(testQueue, node_create(4, 4));
    enqueue(testQueue, node_create(10, 10));
    enqueue(testQueue, node_create(50, 50));

    printf("%u\n", testQueue->size);
    pq_print(testQueue);
    printf("Removed after here: \n");
    dequeue(testQueue, &removed);
    node_print(removed);
    dequeue(testQueue, &removed);
    node_print(removed);
    dequeue(testQueue, &removed);
    node_print(removed);
    dequeue(testQueue, &removed);
    node_print(removed);
    printf("New Queue\n");
    
    dequeue(testQueue, &removed);
    node_print(removed);
    return 0;
}
*/
