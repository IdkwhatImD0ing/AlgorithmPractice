#include "bf.h"
#include "ht.h"
#include "ll.h"
#include "messages.h"
#include "node.h"
#include "parser.h"
#include "speck.h"

#include <ctype.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTIONS "ht:f:ms"
#define WORD    "\\w+([-']\\w+)*"

int main(int argc, char **argv) {
    int32_t opt = 0;
    bool mtf = false;
    uint32_t hashSize = 10000;
    uint32_t bloomSize = 1048576;
    bool verbose = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("SYNOPSIS\n");
            printf("  A word filtering program for the GPRSC.\n");
            printf("  Filters out and reports bad words parsed from stdin.\n");
            printf("\n");
            printf("USAGE\n");
            printf("  ./banhammer [-hsm] [-t size]  [-f size]\n");
            printf("\n");
            printf("OPTIONS\n");
            printf("  -h             Program usage and help.\n");
            printf("  -s             Print program statistics.\n");
            printf("  -m             Enable move-to-front rule.\n");
            printf("  -t size        Specify hash table size (default: 10000).\n");
            printf("  -f size        Specify Bloom filter size (default 2^20).\n");
            return (0);
            break;
        case 't': hashSize = strtoul(optarg, NULL, 10); break;
        case 'f': bloomSize = strtoul(optarg, NULL, 10); break;
        case 'm': mtf = true; break;
        case 's': verbose = true; break;
        }
    }
    //Create the bloomfilter and hashtable
    BloomFilter *bFilter = bf_create(bloomSize);
    HashTable *hTable = ht_create(hashSize, mtf);

    //Insert badspeak into bloomfilter and hashtable
    FILE *badwords;
    badwords = fopen("badspeak.txt", "r");
    char *badword = (char *) malloc(1000 * sizeof(char));
    while (fscanf(badwords, "%s", badword) != EOF) {
        //printf("%s\n", badword);
        bf_insert(bFilter, badword);
        ht_insert(hTable, badword, NULL);
    }

    //Insert badspeak with newspeak into bloomfilter and hashtable
    FILE *newwords = fopen("newspeak.txt", "r");
    char *oldspeak = (char *) malloc(1000 * sizeof(char));
    char *newspeak = (char *) malloc(1000 * sizeof(char));
    while (fscanf(newwords, "%s %s\n", oldspeak, newspeak) != EOF) {
        bf_insert(bFilter, oldspeak);
        ht_insert(hTable, oldspeak, newspeak);
    }

    //Regex Portion
    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex. \n");
        free(badword);
        free(oldspeak);
        free(newspeak);
        bf_delete(&bFilter);
        ht_delete(&hTable);
        fclose(badwords);
        fclose(newwords);
        return 1;
    }

    //Reading from stdin portion
    char *word = NULL;
    Node *searched = NULL;
    bool thought = false;
    bool counseling = false;
    LinkedList *badspeaks = ll_create(mtf);
    LinkedList *oldspeaks = ll_create(mtf);
    while ((word = next_word(stdin, &re)) != NULL) {
        uint32_t i = 0;
        while (word[i]) {
            word[i] = tolower(word[i]);
            i++;
        }
        //If word is part of blacklist
        if (bf_probe(bFilter, word)) {
            //If hashtable contains this word
            if ((searched = ht_lookup(hTable, word))) {
                if (searched->newspeak == NULL) {
                    ll_insert(badspeaks, searched->oldspeak, NULL);
                    thought = true;
                } else {
                    ll_insert(oldspeaks, searched->oldspeak, searched->newspeak);
                    counseling = true;
                }
            }
        }
    }

    //Printing of statistics and other print statements
    if (verbose) {
        double seekLength = (double) links / seeks;
        double load = 100 * ((double) ht_count(hTable) / ht_size(hTable));
        double bLoad = 100 * ((double) bf_count(bFilter) / bf_size(bFilter));
        printf("Seeks: %lu\n", seeks);
        printf("Average seek length: %f\n", seekLength);
        printf("Hash table load: %f%%\n", load);
        printf("Bloom filter load: %f%%\n", bLoad);
    } else if (thought && counseling) {
        printf("%s", mixspeak_message);
        ll_print(badspeaks);
        ll_print(oldspeaks);
    } else if (thought) {
        printf("%s", badspeak_message);
        ll_print(badspeaks);
    } else if (counseling) {
        printf("%s", goodspeak_message);
        ll_print(oldspeaks);
    }

    //Freeing all the memory that was allocated
    free(word);
    free(badword);
    free(oldspeak);
    free(newspeak);
    clear_words();
    regfree(&re);
    ll_delete(&badspeaks);
    ll_delete(&oldspeaks);
    bf_delete(&bFilter);
    ht_delete(&hTable);
    fclose(badwords);
    fclose(newwords);
    return 0;
}
