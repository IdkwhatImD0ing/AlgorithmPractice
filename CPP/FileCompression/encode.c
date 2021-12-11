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

#define OPTIONS "hvi:o:"
static uint32_t bufferIndex;

void post_order(Node *n, uint8_t *buf) {
    //node_print(n);
    //printf("\n");

    if (n == NULL) {
        return;
    }
    if (n->left != NULL) {
        post_order(n->left, buf);
    }
    if (n->right != NULL) {
        post_order(n->right, buf);
    }
    if (n->left == NULL && n->right == NULL) {
        buf[bufferIndex] = 'L';
        bufferIndex++;
        buf[bufferIndex] = n->symbol;
        bufferIndex++;
    } else {
        buf[bufferIndex] = 'I';
        bufferIndex++;
    }
}

int main(int argc, char **argv) {
    int32_t opt = 0;
    bool verbose;
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
        case 'o': outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC); break;
        case 'v': verbose = true;
        }
    }

    //Sets file permissions
    struct stat file_buf;
    fstat(infile, &file_buf);
    fchmod(outfile, file_buf.st_mode);
    //printf("Passed file permissions \n");

    //Make hist and clear
    uint64_t hist[ALPHABET];
    for (int x = 0; x < 256; x++) {
        hist[x] = 0;
    }
    uint8_t buffer[BLOCK];
    Code table[ALPHABET];

    //Create histogram
    uint64_t readAmount;
    readAmount = read_bytes(infile, buffer, BLOCK);
    //printf("Read bytes: %lu\n", readAmount);
    while (readAmount != 0) {
        for (uint64_t x = 0; x < readAmount; x++) {
            hist[buffer[x]]++;
        }
        readAmount = read_bytes(infile, buffer, BLOCK);
    }
    hist[0]++;
    hist[255]++;
    //printf("Created Histogram \n");

    //Calculate Tree Size
    uint16_t size = 0;
    for (uint32_t i = 0; i < ALPHABET; i++) {
        if (hist[i] > 0) {
            size++;
        }
    }
    size = 3 * size - 1;
    //printf("Calculated tree size: %u\n", size);

    //Create huffman Tree from Histogram
    Node *huffmanTree = build_tree(hist);
    /*
    for(int x = 0; x < 256; x++){
    	printf("%u: %lu\n", x, hist[x]);
    }
    */

    //Build code from the Huffman Tree
    build_codes(huffmanTree, table);

    //Create Header
    Header h;
    h.magic = MAGIC;
    h.permissions = file_buf.st_mode;
    h.file_size = file_buf.st_size;
    h.tree_size = size;
    //printf("Made Header \n");

    write_bytes(outfile, (uint8_t *) &h, sizeof(Header));
    //printf("\nWrote Header\n");

    //Post-order traversal of Huffman tree + print
    bufferIndex = 0;
    post_order(huffmanTree, buffer);

    write_bytes(outfile, buffer, bufferIndex);

    lseek(infile, 0, SEEK_SET);
    //Convert infile to code;
    for (int x = 0; x < BLOCK; x++) {
        buffer[x] = 0;
    }

    while ((readAmount = read_bytes(infile, buffer, BLOCK)) != 0) {
        for (uint64_t x = 0; x < readAmount; x++) {
            write_code(outfile, &table[buffer[x]]);
        }
    }

    //printf("Converted infile to code\n");

    //Flushing remaining codes;
    flush_codes(outfile);
    //printf("Flushed code\n");

    if (verbose) {
        printf("Uncompressed file size: %lu bytes\n", h.file_size);
        printf("Compressed file size: %lu bytes\n", bytes_written);
        printf("Space saving %.2f%%\n", 100 - (float) bytes_written / (float) h.file_size * 100);
    }

    //Clearing memory
    close(infile);
    close(outfile);

    return 0;
}
