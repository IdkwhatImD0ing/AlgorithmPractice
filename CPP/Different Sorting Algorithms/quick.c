#include "quick.h"

#include "queue.h"
#include "stack.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//3 global variables
//Comparisons: total comparisons
//Moves: total moves
//sqmax: max of queue or stack
uint32_t comparisons;
uint32_t moves;
uint32_t sqmax;

//parition code
int64_t partition(uint32_t *A, uint32_t lo, uint32_t hi) {
    uint32_t pivot = A[lo + ((hi - lo) / 2)];
    uint32_t i = lo - 1;
    uint32_t j = hi + 1;
    uint32_t temp;
    do {
        comparisons++;
        i++;
        while (A[i] < pivot) {
            comparisons++;
            i++;
        }
        j--;
        while (A[j] > pivot) {
            comparisons++;
            j--;
        }
        if (i < j) {
            comparisons++;
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            moves += 3;
        }
    } while (i < j);
    return j;
}

//Quick sort using stacks
void quick_sort_stack(uint32_t *A, uint32_t n) {
    moves = 0;
    comparisons = 0;
    int64_t lo = 0;
    int64_t hi = n - 1;
    int64_t p;
    Stack *stack = stack_create(n);
    stack_push(stack, lo);
    stack_push(stack, hi);
    while (stack_size(stack) != 0) {
        stack_pop(stack, &hi);
        stack_pop(stack, &lo);
        p = partition(A, lo, hi);
        if (lo < p) {
            comparisons++;
            stack_push(stack, lo);
            stack_push(stack, p);
        }
        if (hi > p + 1) {
            comparisons++;
            stack_push(stack, (p + 1));
            stack_push(stack, hi);
        }
    }
    sqmax = stack_max(stack);
    stack_delete(&stack);
    return;
}

//Quick sorts using queue
void quick_sort_queue(uint32_t *A, uint32_t n) {
    moves = 0;
    comparisons = 0;
    int64_t lo = 0;
    int64_t hi = n - 1;
    int64_t p;
    Queue *queue = queue_create(n);
    enqueue(queue, lo);
    enqueue(queue, hi);
    while (queue_size(queue) != 0) {
        dequeue(queue, &lo);
        dequeue(queue, &hi);
        p = partition(A, lo, hi);
        if (lo < p) {
            comparisons++;
            enqueue(queue, lo);
            enqueue(queue, p);
        }
        if (hi > p + 1) {
            comparisons++;
            enqueue(queue, p + 1);
            enqueue(queue, hi);
        }
    }
    sqmax = queue_max(queue);
    queue_delete(&queue);
    return;
}

//Returns the total moves made
uint32_t get_quick_moves(void) {
    return (moves);
}

//Returns to total comparisons made
uint32_t get_quick_compares(void) {
    return (comparisons);
}

//Returns the highest stack/queue size reached
uint32_t get_sq_max(void) {
    return (sqmax);
}
