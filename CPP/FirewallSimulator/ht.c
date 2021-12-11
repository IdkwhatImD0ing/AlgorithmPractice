#include "ht.h"

#include "ll.h"
#include "speck.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//HashTable structure
//Salt: The Hash Salt of the hashTable
//Size: size of hashtable
//Mtf: Determines if Move To Front should be enabled
//Lists: The list of linked lists for this HashTable
struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};

HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        //Leviathan
        ht->salt[0] = 0x9846e4f157fe8840;
        ht->salt[1] = 0xc5f318d7e055afb8;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

void ht_delete(HashTable **ht) {
    if (*ht) {
        for (uint32_t x = 0; x < (*ht)->size; x++) {
            ll_delete(&(*ht)->lists[x]);
        }
        free((*ht)->lists);
        free(*ht);
        *ht = NULL;
    }
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

//Checks to see if oldspeak is in this Hashtable
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    Node *result = NULL;
    uint32_t index = hash(ht->salt, oldspeak) % ht_size(ht);
    if (!ht->lists[index]) {
        return false;
    } else {
        result = ll_lookup(ht->lists[index], oldspeak);
    }
    return result;
}

//Inserts this oldspeak with new speak into the hashtable
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t index = hash(ht->salt, oldspeak) % ht_size(ht);

    if (!ht->lists[index]) {
        ht->lists[index] = ll_create(ht->mtf);
    }
    ll_insert(ht->lists[index], oldspeak, newspeak);
}

//COunts how many linked lists are in this hashtable
uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t x = 0; x < ht->size; x++) {
        if (ht->lists[x]) {
            count++;
        }
    }
    return count;
}

void ht_print(HashTable *ht) {
    for (uint32_t x = 0; x < ht->size; x++) {
        if (ht->lists[x]) {
            ll_print(ht->lists[x]);
        }
    }
}
