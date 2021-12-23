# Sudoku Solver

## General Idea

The initial idea would be to represent a Sudoku problem via a $9 \times 9$ matrix, where each entry can be either a digit from 1 to 9, or 0 to signify "blank".  This would work in some sense, but it would not be a very useful representation. 

To solve a sudoku puzzle, use the following steps

Repeat: 
* Look at all blank spaces.  Can you find one where only one digit fits? If so, write the digit there. 
* If you cannot find any blank space as above, try to find one where only a couple or so digits can fit.  Try putting in one of those digits, and see if you can solve the puzzle with that choice.  If not, backtrack, and try another digit. 

Thus, it will be very useful to us to remember not only the known digits, but also, which digits can fit into any blank space. 
Hence, we represent a Sudoku problem via a $9 \times 9$ matrix of _sets_: each set contains the digits that can fit in a given space. 
Of course, a known digit is just a set containing only one element. 
We will solve a Sudoku problem by progressively "shrinking" these sets of possibilities, until they all contain exactly one element. 

## Important Functions

### Propagating One Cell

When the set in a Sudoku cell contains only one element, this means that the digit at that cell is known. 
We can then propagate the knowledge, ruling out that digit in the same row, in the same column, and in the same 3x3 cell. 

The method `propagate_cell(ij)` takes as input a pair `ij` of coordinates.  If the set of possible digits `self.m[i][j]` for cell i,j contains more than one digit, then no propagation is done.  If the set contains a single digit `x`, then we: 

* Remove `x` from the sets of all other cells on the same row, column, and 3x3 block. 
* Collect all the newly singleton cells that are formed, due to the digit `x` being removed, and we return them as a set.

### Propagating Repeatedly

As we propagate the constraints, cells that did not use to be singletons may have become singletons. 

The method `full_propagation` starts with a set of `to_propagate` cells (if it is not specified, then we just take it to consist of all singleton cells).  Then, it picks a cell from the to_propagate set, and propagates from it, adding any newly singleton cell to to_propagate.  Once there are no more cells to be propagated, the method returns. 
