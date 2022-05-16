# Range Searching using Self-Balancing Avl Trees

## Description:
  This algorithm inserts strings into an avl tree and finds the range of two strings. Input file should be structured with:
  
  i string - to insert strings into the tree
  r str1 str2 - find the numbers of strings that fall between these two strings lexicographically, inclusive

## Usage:

### Compiling
  make

### Running
  ./wordrange inputfile outputfile

### Cleaning
  make clean

## Code Used in this Lab:
  PrintTree method in avlt.cpp was taken from GeekstoGeeks printing a binary tree in 2 dimensions
  This code was mainly used to print out the avlt tree in a readable manner for debugging

  Base insert method in avlt.cpp was taking from Professor Sesh's BST tree, however I later modified it to better suit my purposes

  My wordrange io code was code using Professor Sesh's IO code from BST tree, with slight modifications of my own.

## Additional Notes:
  There is 2 ways I have right now to find the range. 
  I first made the range(Node, str, str) function, this works for simple input and all words basic; however, it still wasnt done with allwords-more-range after 40 minutes

  2nd Method works very efficiently for all 1.8 million operations.


