#include "code.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//Code adt
//top = size of code and the top+ entry
Code code_init(void) {
    Code c;
    c.top = 0;
    for (int x = 0; x < MAX_CODE_SIZE; x++) {
        c.bits[x] = 0;
    }
    return c;
}

uint32_t code_size(Code *c) {
    return (c->top);
}

bool code_empty(Code *c) {
    if (c->top == 0) {
        return true;
    }
    return false;
}

bool code_full(Code *c) {
    if (c->top == MAX_CODE_SIZE) {
        return true;
    }
    return false;
}
//Puses a bit onto the code
bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) {
        return false;
    }
    if (bit == 1) {
        c->bits[c->top / 8] |= 1 << c->top % 8;
    }
    if (bit == 0) {
        c->bits[c->top / 8] &= ~(1 << c->top % 8);
    }
    c->top++;
    return true;
}
//Pops a bit from the code
bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) {
        return false;
    }
    c->top--;
    *bit = (c->bits[c->top / 8] >> c->top % 8) & 1;
    return (true);
}

void code_print(Code *c) {
    for (uint32_t x = 0; x < c->top; x++) {
        printf("%u", (c->bits[x / 8] >> x % 8) & 1);
    }
    printf("\n");
    return;
}
