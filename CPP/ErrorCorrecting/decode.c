#include "bm.h"
#include "hamming.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTIONS "hi:o:v"

uint8_t lower_nibble(uint8_t val) {
    return val & 0xF;
}

uint8_t upper_nibble(uint8_t val) {
    return val >> 4;
}

uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}

int main(int argc, char **argv) {
    int32_t opt = 0;
    bool verbose = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("SYNOPSIS\n");
            printf("  A Hamming(8, 4) systematic code decoder\n");
            printf("\n");
            printf("USAGE\n");
            printf("  ./decode [-h] [-v] [-i infile] [-o outfile]\n");
            printf("\n");
            printf("OPTIONS\n");
            printf("  -h             Program usage and help.\n");
            printf("  -v             Print statistics of decoding to stderr.\n");
            printf("  -i infile      Input data to encode.\n");
            printf("  -o outfile     Output of decoded data.\n");
            return (0);
            break;
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        case 'v': verbose = true;
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

    //Creates decoder matrix
    BitMatrix *checkMatrix = bm_create(8, 4);
    bm_set_bit(checkMatrix, 4, 0);
    bm_set_bit(checkMatrix, 5, 1);
    bm_set_bit(checkMatrix, 6, 2);
    bm_set_bit(checkMatrix, 7, 3);
    for (uint32_t x = 0; x < 4; x++) {
        for (uint32_t y = 0; y < 4; y++) {
            if (x != y) {
                bm_set_bit(checkMatrix, x, y);
            }
        }
    }
    int32_t c;
    uint8_t readByte;
    uint32_t totalBytes = 0;
    uint32_t uncorrected = 0;
    uint32_t corrected = 0;
    uint8_t temp = 0;
    uint8_t lower = 0;
    uint8_t upper = 0;
    HAM_STATUS status;
    while ((c = fgetc(infile)) != EOF) {
        readByte = (uint8_t) c;
        //printf("Byte: %u\n", readByte);
        status = ham_decode(checkMatrix, readByte, &temp);
        //printf("Lower: %u\n", lower);
        if (status == HAM_ERR) {
            uncorrected++;
        } else if (status == HAM_CORRECT) {
            corrected++;
            lower = temp;
        } else {
            lower = temp;
        }
        readByte = fgetc(infile);
        //printf("Byte: %u\n", readByte);
        status = ham_decode(checkMatrix, readByte, &temp);
        //printf("Upper: %u\n", upper);
        if (status == HAM_ERR) {
            uncorrected++;
        } else if (status == HAM_CORRECT) {
            corrected++;
            upper = temp;
        } else {
            upper = temp;
        }
        fputc(pack_byte(upper, lower), outfile);
        //printf("Combined message: %u\n", pack_byte(upper, lower));
        totalBytes += 2;
    }

    //Prits stats

    if (verbose) {
        double errorRate = (double) uncorrected / (double) totalBytes;
        fprintf(stderr, "Total bytes processed: %u\n", totalBytes);
        fprintf(stderr, "Uncorrected errors: %u\n", uncorrected);
        fprintf(stderr, "Corrected errors: %u\n", corrected);
        fprintf(stderr, "Error rate: %f\n", errorRate);
    }

    //Clearing memory
    fclose(infile);
    fclose(outfile);
    bm_delete(&checkMatrix);

    return 0;
}
