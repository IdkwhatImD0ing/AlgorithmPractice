#include "bm.h"
#include "hamming.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTIONS "hi:o:"

//Lower nibble of byte
uint8_t lower_nibble(uint8_t val) {
    return val & 0xF;
}

//Upper nibble of byte
uint8_t upper_nibble(uint8_t val) {
    return val >> 4;
}

//Turns 2 nibbles into a byte
uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower * 0xF);
}

int main(int argc, char **argv) {
    int32_t opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("SYNOPSIS\n");
            printf("  A Hamming(8, 4) systematic code generator.\n");
            printf("\n");
            printf("USAGE\n");
            printf("  ./encode [-h] [-i infile] [-o outfile]\n");
            printf("\n");
            printf("OPTIONS\n");
            printf("  -h             Program usage and help.\n");
            printf("  -i infile      Input data to encode.\n");
            printf("  -o outfile     Output of encoded data.\n");
            return (0);
            break;
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        }
    }

    if (infile == NULL) {
        fprintf(stderr, "Error: failed to open infile.\n");
        return 0;
    }
    if (outfile == NULL) {
        fprintf(stderr, "Error: failed to open outfile.\n");
        fclose(infile);
        return 0;
    }

    //Sets file permissions
    struct stat statbuf;
    fstat(fileno(infile), &statbuf);
    fchmod(fileno(outfile), statbuf.st_mode);
    //Creates generator matrix
    BitMatrix *generatorMatrix = bm_create(4, 8);
    bm_set_bit(generatorMatrix, 0, 0);
    bm_set_bit(generatorMatrix, 1, 1);
    bm_set_bit(generatorMatrix, 2, 2);
    bm_set_bit(generatorMatrix, 3, 3);
    for (uint32_t x = 0; x < 4; x++) {
        for (uint32_t y = 0; y < 4; y++) {
            if (x != y) {
                bm_set_bit(generatorMatrix, x, y + 4);
            }
        }
    }
    int32_t c;
    uint8_t readByte;
    uint8_t lowerNibble;
    uint8_t upperNibble;
    while ((c = fgetc(infile)) != EOF) {
        readByte = (uint8_t) c;
        //printf("Byte: %u\n", readByte);
        lowerNibble = lower_nibble(readByte);
        //printf("Lower: %u\n", lowerNibble);
        upperNibble = upper_nibble(readByte);
        //printf("Upper: %u\n", upperNibble);
        uint8_t lowerHamming = ham_encode(generatorMatrix, lowerNibble);
        uint8_t upperHamming = ham_encode(generatorMatrix, upperNibble);
        fputc(lowerHamming, outfile);
        //printf("Hamming lower: %u\n", lowerHamming);
        fputc(upperHamming, outfile);
        //printf("Hamming upper: %u\n", upperHamming);
    }

    //Clearing memory
    fclose(infile);
    fclose(outfile);
    bm_delete(&generatorMatrix);

    return 0;
}
