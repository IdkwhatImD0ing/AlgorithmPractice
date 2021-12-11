#include "bf.h"

#include "bv.h"
#include "speck.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//BloomFilter ADT
//Primary: Primary Hash Value
//Secondary: Secondary Hash Value
//Tertiary: Third Hash Value
//Setted: How many bits are setted
//Filter: The bit vector based filter of this Bloom Filter
struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    uint32_t setted;
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        bf->setted = 0;
        //Grimm's Fairy Tales
        bf->primary[0] = 0x5adf08ae86d36f21;
        bf->primary[1] = 0xa267bbd3116f3957;
        //The Adventures of Sherlock Holmes
        bf->secondary[0] = 0x419d292ea2ffd49e;
        bf->secondary[1] = 0x09601433057d5786;
        // The  Strange  Case of Dr. Jekyll  and Mr. Hyde
        bf->tertiary[0] = 0x50d8bb08de3818df;
        bf->tertiary[1] = 0x4deaae187c16ae1d;
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}
void bf_delete(BloomFilter **bf) {
    if (*bf) {
        bv_delete(&(*bf)->filter);
        free(*bf);
        *bf = NULL;
    }
}

uint32_t bf_size(BloomFilter *bf) {
    return (bv_length(bf->filter));
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    if (oldspeak == NULL) {
        fprintf(stderr, "ERROR: Oldspeak is null for bf_insert.\n");
    }
    //Hash the oldspeak and then set corresponding bits in the bit vector
    uint32_t one = hash(bf->primary, oldspeak) % bf_size(bf);
    uint32_t two = hash(bf->secondary, oldspeak) % bf_size(bf);
    uint32_t three = hash(bf->tertiary, oldspeak) % bf_size(bf);
    if (bv_get_bit(bf->filter, one) == 0) {
        bf->setted++;
        bv_set_bit(bf->filter, one);
    }
    if (bv_get_bit(bf->filter, two) == 0) {
        bf->setted++;
        bv_set_bit(bf->filter, two);
    }
    if (bv_get_bit(bf->filter, three) == 0) {
        bf->setted++;
        bv_set_bit(bf->filter, three);
    }
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    //Hash the oldspeak and find corresponding bits in the bit vector
    uint32_t one = hash(bf->primary, oldspeak);
    uint32_t two = hash(bf->secondary, oldspeak);
    uint32_t three = hash(bf->tertiary, oldspeak);
    three = three % bf_size(bf);
    two = two % bf_size(bf);
    one = one % bf_size(bf);
    if ((bv_get_bit(bf->filter, one) == 1) && (bv_get_bit(bf->filter, two) == 1)
        && (bv_get_bit(bf->filter, three) == 1)) {
        return true;
    }
    return false;
}

uint32_t bf_count(BloomFilter *bf) {
    return bf->setted;
}

void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}

//Test code for BloomFilter ignore this
/*
int main(void){
	BloomFilter *filter = bf_create(1000000);
	printf("Size = %u\n", bf_size(filter));
	bf_insert(filter, "one");
	bf_insert(filter, "two");
	bf_insert(filter, "three");
	bf_insert(filter, "five");
	bf_insert(filter, "six");
	printf("Passed inserts\n");
	printf("Contains one? %u\n", bf_probe(filter, "one"));
	printf("Contains four? %u\n", bf_probe(filter, "four"));
	printf("Current count: %u\n", bf_count(filter));
	bf_delete(&filter);
	return 1;
}
*/
