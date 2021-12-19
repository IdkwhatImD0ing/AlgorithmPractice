# Great Firewall of Santa Cruz

This program will simulate a firewall filtering bad words out and reminding the user of which new words to use in place of old words.

## Build
make all

## Running
./encode
-h for help page
-s to print statistics
-m to emable move to front
-t to specify hash table size
-f to specify bloom filter size

## Formatting
make format

## Cleaning
make clean

## Checking for build errors
make scan-build
