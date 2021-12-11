#include "queue.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
// Definition of struct Queue, a queue
//
// max: max size of array
// tail: oldest element of Queue
// head: newest element of Queue
// size: size of Queue
// *items; contents of queue

struct Queue {
    uint32_t max;
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
    int64_t *items;
};

Queue *queue_create(uint32_t capacity) {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    if (q) {
        q->max = 0;
        q->head = 0;
        q->tail = 0;
        q->size = 0;
        q->capacity = capacity;
        q->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        if (!q->items) {
            free(q);
            q = NULL;
        }
    }
    return (q);
}

void queue_delete(Queue **q) {
    if (*q && (*q)->items) {
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}

bool queue_empty(Queue *q) {
    if (q->size == 0) {
        return true;
    }
    return false;
}

bool queue_full(Queue *q) {
    if (q->size == q->capacity) {
        return true;
    }
    return false;
}

uint32_t queue_size(Queue *q) {
    return (q->size);
}

bool enqueue(Queue *q, int64_t x) {
    if (queue_full(q)) {
        return false;
    }
    q->items[q->head] = x;
    q->size++;
    if (q->head == q->capacity - 1) {
        q->head = 0;
    } else {
        q->head++;
    }
    if (q->size > q->max) {
        q->max = q->size;
    }
    return true;
}

bool dequeue(Queue *q, int64_t *x) {
    if (queue_empty(q)) {
        return false;
    }

    *x = q->items[q->tail];
    q->size--;
    if (q->tail == q->capacity - 1) {
        q = 0;
    } else {
        q->tail++;
    }
    return true;
}

void queue_print(Queue *q) {
    uint32_t index = 0;
    for (uint32_t i = 0; i < q->size; i++) {
        if (q->tail + i >= q->capacity) {
            printf("%ld%s", q->items[index], " ");
            index++;
        } else {
            printf("%ld%s", q->items[q->tail + i], " ");
        }
    }
    return;
}

uint32_t queue_max(Queue *q) {
    return q->max;
}
