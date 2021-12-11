#include "stack.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//Definitnion of struct Stack, a stack
//
//top: top of stack
//capacity: capacity of stack
//maxSize; the highest stack size over the course of the program
//*items: contents of stack

struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t maxSize;
    int64_t *items;
};

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->maxSize = 0;
        s->top = 0;
        s->capacity = capacity;
        s->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    }
    return false;
}

bool stack_full(Stack *s) {
    if (s->top == s->capacity - 1) {
        return true;
    }
    return false;
}

uint32_t stack_size(Stack *s) {
    return (s->top);
}

bool stack_push(Stack *s, int64_t x) {
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = x;
    s->top++;
    if (s->top > s->maxSize) {
        s->maxSize = s->top;
    }
    return true;
}

bool stack_pop(Stack *s, int64_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    s->top--;
    *x = s->items[s->top];
    return true;
}

void stack_print(Stack *s) {
    printf("[");
    for (uint32_t i = 0; i < s->top - 1; i++) {
        printf("%ld%s", s->items[i], " ");
    }
    printf("]\n");
    return;
}

uint32_t stack_max(Stack *s) {
    return s->maxSize;
}
