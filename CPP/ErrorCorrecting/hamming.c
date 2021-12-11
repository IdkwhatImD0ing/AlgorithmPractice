#include "hamming.h"

//#include "bm.c"
//#include "bv.c"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
int8_t errorLookUp[] = { HAM_OK, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR, 2,
    HAM_ERR, 1, 0, HAM_ERR };

//Caches for storing values of already solved codes/messages
static uint16_t encodeCache[256];
static uint16_t decodeCache[256];

//Encodes a message using a Bit matrix
//Returns the encoded hamming code
uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    //if encoded before, used cached version to save time
    if (encodeCache[msg]) {
        return (encodeCache[msg] - 1);
    }
    BitMatrix *message = bm_from_data(msg, 4);
    BitMatrix *hamming = bm_multiply(message, G);
    uint8_t data = bm_to_data(hamming);
    encodeCache[msg] = data + 1;
    bm_delete(&message);
    bm_delete(&hamming);
    return (data);
}

//Decodes hamming code and tries to correct errors
//Returns status of correction
HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    uint8_t errorCode = 0;
    //If decoded code before, use cached version to save time
    if (decodeCache[code]) {
        errorCode = decodeCache[code] - 1;
    } else {

        BitMatrix *mcode = bm_from_data(code, 8);
        BitMatrix *error = bm_multiply(mcode, Ht);
        errorCode = bm_to_data(error);
        decodeCache[code] = errorCode + 1;
        //printf("%u\n", errorLookUp[errorCode]);
        //printf("%u\n", HAM_OK);
        bm_delete(&error);
        bm_delete(&mcode);
    }
    if (errorLookUp[errorCode] == HAM_OK) {
        code = code & 0xF;
        *msg = code;
        return (HAM_OK);
    } else if (errorLookUp[errorCode] == HAM_ERR) {
        code = code & 0xF;
        *msg = code;
        return (HAM_ERR);
    } else {
        code ^= 1 << errorLookUp[errorCode];
        code = code & 0xF;
        *msg = code;
        return (HAM_CORRECT);
    }
}
