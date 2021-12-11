#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
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
    int infile = 0;
    int outfile = 1;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("SYNOPSIS\n");
            printf("  A Huffman encoder.\n");
            printf("  Compresses a file using the Huffman coding algorithm.\n");
            printf("\n");
            printf("USAGE\n");
            printf("  ./encode [-h] [-i infile] [-o outfile]\n");
            printf("\n");
            printf("OPTIONS\n");
            printf("  -h             Program usage and help.\n");
            printf("  -v             Print compression statistics.\n");
            printf("  -i infile      Input data to encode.\n");
            printf("  -o outfile     Output of encoded data.\n");
            return (0);
            break;
        case 'i': infile = open(optarg, O_RDONLY); break;
        case 'o': outfile = open(optarg, O_WRONLY | O_CREAT); break;
        case 'v': verbose = true;
        }
    }

    Header h;
    read_bytes(infile, (uint8_t *) &h, sizeof(Header));
    if (h.magic != MAGIC) {
        fprintf(stderr, "Error, invalid file");
        return 0;
    }

    //Sets file permissions
    fchmod(outfile, h.permissions);

    uint16_t treeSize = h.tree_size;
    uint8_t treeDump[treeSize];
    uint8_t buffer[BLOCK];
    uint64_t fileSize = h.file_size;

    read_bytes(infile, buffer, treeSize);

    for (uint16_t x = 0; x < treeSize; x++) {
        treeDump[x] = buffer[x];
    }
    printf("\n");

    Node *rebuiltTree = rebuild_tree(treeSize, treeDump);
    Node *currentNode = rebuiltTree;

    uint32_t bufferIndex = 0;
    uint8_t bit;
    uint64_t currentSize = 0;

    bool next = read_bit(infile, &bit);
    while (next) {
        if (bit == 0) {
            currentNode = currentNode->left;
        } else if (bit == 1) {
            currentNode = currentNode->right;
        }

        if (currentNode->left == NULL && currentNode->right == NULL) {
            buffer[bufferIndex] = currentNode->symbol;
            currentNode = rebuiltTree;
            bufferIndex++;
            currentSize++;
        }

        if (bufferIndex == BLOCK) {
            write_bytes(outfile, buffer, bufferIndex);
            bufferIndex = 0;
        }
        if (currentSize == fileSize) {
            write_bytes(outfile, buffer, bufferIndex);
            break;
        }

        next = read_bit(infile, &bit);
    }
    if (verbose) {
        printf("Compressed file size: %lu bytes\n", bytes_read);
        printf("Decompressed file size: %lu bytes\n", h.file_size);
        printf("Space saving %.2f%%\n", 100 - (float) bytes_read / (float) h.file_size * 100);
    }

    //Clearing memory
    close(infile);
    close(outfile);

    return 0;
}
