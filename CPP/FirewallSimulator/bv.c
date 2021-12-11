#include "bv.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//Structure for Bitvector
//Length: length in bits
//Array of bits stored as bytes
struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

//Creates the bitvector
//allocates memory
BitVector *bv_create(uint32_t length) {
    BitVector *v = (BitVector *) malloc(sizeof(BitVector));
    if (v) {
        v->length = length;
        v->vector = (uint8_t *) calloc(length / 8 + 1, sizeof(uint8_t));
        for (uint32_t i = 0; i < length / 8 + 1; i++) {
            v->vector[0] = 0;
        }
        if (!v->vector) {
            free(v);
            v = NULL;
        }
    }
    return v;
}

//Deletes bit vector
//and frees memory used
void bv_delete(BitVector **v) {
    if (*v && (*v)->vector) {
        free((*v)->vector);
        free(*v);
        *v = NULL;
    }
}

uint32_t bv_length(BitVector *v) {
    return (v->length);
}
void bv_set_bit(BitVector *v, uint32_t i) {
    v->vector[i / 8] |= 1 << i % 8;
}

void bv_clr_bit(BitVector *v, uint32_t i) {
    v->vector[i / 8] &= ~(1 << i % 8);
}

void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit) {
    v->vector[i / 8] ^= bit << i % 8;
}

uint8_t bv_get_bit(BitVector *v, uint32_t i) {
    uint8_t bit = (v->vector[i / 8] >> i % 8) & 1;
    return (bit);
}

void bv_print(BitVector *v) {
    for (uint32_t x = 0; x < bv_length(v); x++) {
        printf("%u", bv_get_bit(v, x));
    }
    printf("\n");
}
