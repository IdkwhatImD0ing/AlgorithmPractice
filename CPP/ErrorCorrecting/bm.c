#include "bm.h"

#include "bv.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//BitMatrix Structure
//Rows of matrix
//cols of matrix
//Bit vector for containing bits
struct BitMatrix {
    uint32_t rows;
    uint8_t cols;
    BitVector *vector;
};

//Creates the bit matrix
//allocates memory for matrix and creates bv
BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *m = (BitMatrix *) malloc(sizeof(BitMatrix));
    if (m) {
        m->rows = rows;
        m->cols = cols;
        m->vector = bv_create(rows * cols);
        if (!m->vector) {
            free(m);
            m = NULL;
        }
    }
    return m;
}

//Deletes bit matrix and frees memory
void bm_delete(BitMatrix **m) {
    if (*m && (*m)->vector) {
        bv_delete(&(*m)->vector);
        free(*m);
        *m = NULL;
    }
}

uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
}

uint32_t bm_cols(BitMatrix *m) {
    return m->cols;
}

void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_set_bit(m->vector, r * m->cols + c);
}

void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_clr_bit(m->vector, r * m->cols + c);
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    return (bv_get_bit(m->vector, r * m->cols + c));
}
//Creates a bit matrix using first length bits in byte
BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    BitMatrix *result = bm_create(1, length);
    for (uint32_t i = 0; i < length; i++) {
        if (((byte >> i) & 1) == 1) {
            bm_set_bit(result, 0, i);
        }
    }
    return result;
}

//Creates a byte using first 8 bits in bitmatrix m
uint8_t bm_to_data(BitMatrix *m) {
    uint8_t data = 0;
    for (int x = 0; x < 8; x++) {
        if (bv_get_bit(m->vector, x) == 1) {
            data |= 1 << x;
        }
    }
    return data;
}

//Code given by Eugene during lecture, modified a bit
//Multiplys 2 matrices
BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    assert(bm_cols(A) == bm_rows(B));
    BitMatrix *result = bm_create(bm_rows(A), bm_cols(B));
    for (uint32_t i = 0; i < bm_rows(A); i++) {
        for (uint32_t j = 0; j < bm_cols(B); j++) {
            uint8_t sum = 0;
            for (uint32_t k = 0; k < bm_cols(A); k++) {
                sum += bm_get_bit(A, i, k) * bm_get_bit(B, k, j);
            }
            if (sum % 2 == 1) {
                bm_set_bit(result, i, j);
            }
        }
    }
    return result;
}

//Debug printing code
void bm_print(BitMatrix *m) {
    for (uint32_t i = 0; i < bm_rows(m); i++) {
        for (uint32_t j = 0; j < bm_cols(m); j++) {
            printf("%u", bm_get_bit(m, i, j));
        }
        printf("\n");
    }
}
