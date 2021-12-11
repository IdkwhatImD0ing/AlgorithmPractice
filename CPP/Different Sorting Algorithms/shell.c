#include "shell.h"

#include "gaps.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//2 Global variables for comparisons and moves
uint32_t comparisons;
uint32_t moves;

void shell_sort(uint32_t *A, uint32_t n) {
    comparisons = 0;
    moves = 0;
    uint32_t j;
    uint32_t temp;
    uint32_t length = n;
    uint32_t gap;
    for (int x = 0; x < GAPS; x++) {
        gap = gaps[x];
        for (uint32_t i = gap; i < length; i++) {
            j = i;
            comparisons++;
            temp = A[i];
            moves++;
            while (j >= gap && temp < A[j - gap]) {
                comparisons += 2;
                A[j] = A[j - gap];
                j = j - gap;
                moves++;
            }
            A[j] = temp;
            moves += 1;
        }
    }
    return;
}

//Returns total moves made
uint32_t get_shell_moves(void) {
    return (moves);
}

//Returns total comparisons made
uint32_t get_shell_compares(void) {
    return (comparisons);
}
