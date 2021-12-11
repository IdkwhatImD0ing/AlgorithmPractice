#include "bubble.h"
#include "quick.h"
#include "set.h"
#include "shell.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum SORT {
    BUBBLE,
    SHELL,
    QUICK,
    QUICKQ,
} SORT;

#define OPTIONS "absqQr:n:p:"
uint32_t seed = 13371453;
uint32_t size = 100;
uint32_t elements = 100;

void bubble(uint32_t *A);
void shell(uint32_t *A);
void quick(uint32_t *A);
void quickq(uint32_t *A);

int main(int argc, char **argv) {
    int32_t opt = 0;
    Set sorts = set_empty();
    void (*sort_functions[4])(uint32_t * A) = { bubble, shell, quick, quickq };
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            sorts = set_insert(sorts, BUBBLE);
            sorts = set_insert(sorts, SHELL);
            sorts = set_insert(sorts, QUICK);
            sorts = set_insert(sorts, QUICKQ);
            break;
        case 'b': sorts = set_insert(sorts, BUBBLE); break;
        case 's': sorts = set_insert(sorts, SHELL); break;
        case 'q': sorts = set_insert(sorts, QUICK); break;
        case 'Q': sorts = set_insert(sorts, QUICKQ); break;
        case 'r': seed = strtoul(optarg, NULL, 10); break;
        case 'n': size = strtoul(optarg, NULL, 10); break;
        case 'p': elements = strtoul(optarg, NULL, 10); break;
        }
    }

    srandom(seed);
    uint32_t randomArray[size];
    uint32_t testArray[size];
    for (uint32_t i = 0; i < size; i++) {
        randomArray[i] = rand();
        testArray[i] = randomArray[i];
    }

    for (SORT s = BUBBLE; s <= QUICKQ; s++) {
        if (set_member(sorts, s)) {
            for (uint32_t i = 0; i < size; i++) {
                testArray[i] = randomArray[i];
            }
            sort_functions[s](testArray);
        }
    }

    return 0;
}

//Tests bubble sort code
void bubble(uint32_t *A) {
    uint8_t counter = 0;
    printf("Bubble Sort\n");
    bubble_sort(A, size);
    uint32_t moves = get_bubble_moves();
    uint32_t compares = get_bubble_compares();
    if (elements > size) {
        elements = size;
    }
    printf("%d%s%d%s%d%s", size, " elements, ", moves, " moves, ", compares, " compares \n");
    for (uint32_t x = 0; x < elements; x++) {
        printf("%13" PRIu32, A[x]);
        counter++;
        if (counter == 5) {
            printf("\n");
            counter = 0;
        }
    }
    return;
}

//Tests shell sort code
void shell(uint32_t *A) {
    uint8_t counter = 0;
    printf("Shell Sort\n");
    shell_sort(A, size);
    if (elements > size) {
        elements = size;
    }
    uint32_t moves = get_shell_moves();
    uint32_t compares = get_shell_compares();
    printf("%d%s%d%s%d%s", size, " elements, ", moves, " moves, ", compares, " compares \n");
    for (uint32_t x = 0; x < elements; x++) {
        printf("%13" PRIu32, A[x]);
        counter++;
        if (counter == 5) {
            printf("\n");
            counter = 0;
        }
    }
    return;
}

//Tests quick sort code
void quick(uint32_t *A) {
    uint8_t counter = 0;
    printf("Quick Sort (Stack)\n");
    quick_sort_stack(A, size);
    if (elements > size) {
        elements = size;
    }
    uint32_t moves = get_quick_moves();
    uint32_t compares = get_quick_compares();
    printf("%d%s%d%s%d%s", size, " elements, ", moves, " moves, ", compares, " compares \n");
    uint32_t maxSize = get_sq_max();
    printf("%s%d%s", "Max stack size: ", maxSize, "\n");
    for (uint32_t x = 0; x < elements; x++) {
        printf("%13" PRIu32, A[x]);
        counter++;
        if (counter == 5) {
            printf("\n");
            counter = 0;
        }
    }
    return;
}

//Tests 2nd quick sort code using queues
void quickq(uint32_t *A) {
    uint8_t counter = 0;
    printf("Quick Sort (Queue)\n");
    quick_sort_queue(A, size);
    if (elements > size) {
        elements = size;
    }
    uint32_t moves = get_quick_moves();
    uint32_t compares = get_quick_compares();
    printf("%d%s%d%s%d%s", size, " elements, ", moves, " moves, ", compares, " compares \n");
    uint32_t maxSize = get_sq_max();
    printf("%s%d%s", "Max queue size: ", maxSize, "\n");
    for (uint32_t x = 0; x < elements; x++) {
        printf("%13" PRIu32, A[x]);
        counter++;
        if (counter == 5) {
            printf("\n");
            counter = 0;
        }
    }
    return;
}
