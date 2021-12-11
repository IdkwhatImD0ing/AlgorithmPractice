#include "io.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BLOCK 4096

uint64_t bytes_written = 0;
uint64_t bytes_read = 0;

static uint8_t buffer[BLOCK];
static uint32_t bufferIndex = 0;
static uint64_t endBuffer = 0;

//Reads Number of bytes
//Returns number of bytes written
int read_bytes(int infile, uint8_t *buf, int nbytes) {

    //printf("Starting to read bytes\n");
    uint64_t totalBytesRead = 0;
    uint64_t singleCallRead = 0;
    //SingleCallRead = 0 when end of file
    while (totalBytesRead != (uint64_t) nbytes) {

        singleCallRead = read(infile, buf + totalBytesRead, nbytes - totalBytesRead);
        totalBytesRead += singleCallRead;
        //printf("Single Call Read: %ld\n" , singleCallRead);
        //printf("TotalBytesRead: %ld\n" , totalBytesRead);

        if (singleCallRead == 0) {
            break;
        }
    }
    bytes_read += totalBytesRead;
    return totalBytesRead;
}

//Writes nbyes of bytes
//Returns number of bytes read
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    uint64_t totalBytesWritten = 0;
    uint64_t singleCallWritten = 0;
    //SingleCallRead = 0 when end of file
    while (totalBytesWritten != (uint64_t) nbytes) {
        singleCallWritten = write(outfile, buf + totalBytesWritten, nbytes - totalBytesWritten);
        totalBytesWritten += singleCallWritten;
        if (singleCallWritten == 0) {
            break;
        }
    }
    bytes_written += totalBytesWritten;
    return totalBytesWritten;
}

//Reads bit at infile and return true if there another bit to read
bool read_bit(int infile, uint8_t *bit) {
    //printf("Starting to read bit\n");
    uint64_t read;
    if (bufferIndex == 0) {
        //printf("Buffer index is 0\n");
        read = read_bytes(infile, buffer, BLOCK);
        if (read < BLOCK) {
            //End buffer is set to the empty bit right after last bit
            endBuffer = (8 * read) + 1;
            //printf("Read less than block: %lu\n", endBuffer);
        } else {
            endBuffer = BLOCK * 8;
        }
    }
    *bit = ((buffer[bufferIndex / 8] >> bufferIndex % 8) & 1);
    bufferIndex++;
    if (bufferIndex == 8 * BLOCK) {
        bufferIndex = 0;
    }

    //Return false if no more bits to read
    if (bufferIndex >= endBuffer) {
        return false;
    } else {
        //Return true if there are more bits to read
        return true;
    }
}

//Write a code to outfile
void write_code(int outfile, Code *c) {
    uint8_t bit;
    for (uint32_t i = 0; i < (c->top); i++) {
        bit = (c->bits[i / 8] >> i % 8) & 1;
        if (bit == 1) {
            //Set buffer bit at index bufferIndex
            buffer[bufferIndex / 8] |= 1 << bufferIndex % 8;
            bufferIndex++;
        } else {
            //Clr buffer bit at index bufferIndex
            buffer[bufferIndex / 8] &= ~(1 << bufferIndex % 8);
            bufferIndex++;
        }

        if (bufferIndex == 8 * BLOCK) {
            flush_codes(outfile);
        }
    }
}

//Flush remaining codes in buffer
void flush_codes(int outfile) {
    if (bufferIndex > 0) {
        write_bytes(outfile, buffer, bufferIndex / 8);
        bufferIndex = 0;
    }
}
/*
int main(){
        int fdw = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
        uint8_t bit;
	Code c = code_init();
	code_push_bit(&c, 1);
	code_push_bit(&c, 0);
	code_push_bit(&c, 0);
	code_push_bit(&c, 0);
	code_push_bit(&c, 0);
	code_push_bit(&c, 1);
	code_push_bit(&c, 1);
	code_push_bit(&c, 0);
	code_print(&c);
	printf("Buffer Index: %u\n", bufferIndex);
	
	for (int i = 0; i < 6; i++){
		write_code(fdw, &c);
	}
	
	flush_codes(fdw);
	printf("Buffer Index after flushing: %u\n", bufferIndex);
	lseek(fdw, 0, SEEK_SET);

	for(int x = 0;x < 50; x++){
       	printf("Read bit? %d\n", read_bit(fdw, &bit));
		printf("Bit: %u\n", bit);
	}
	close(fdw);
}
*/
