#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//2 global variables to save comparisons and moves
uint32_t comparisons;
uint32_t moves;

void bubble_sort(uint32_t *A, uint32_t n) {
    comparisons = 0;
    moves = 0;
    uint32_t length = n;
    uint32_t temp;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (uint32_t i = 1; i < length; i++) {
            if (A[i] < A[i - 1]) {
                comparisons++;
                temp = A[i];
                A[i] = A[i - 1];
                A[i - 1] = temp;
                moves += 3;
                swapped = true;
                comparisons++;
            }
        }
        length = length - 1;
    }
    return;
}

//Get total swaps
uint32_t get_bubble_moves(void) {
    return (moves);
}

//Get total comaparisons
uint32_t get_bubble_compares(void) {
    return (comparisons);
}
