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

### Guessing Solution

When constant propagation fails, the only thing we can do is make a guess.  We can take one of the cells whose set contains multiple digits, such as cell (2, 0), which contains $\{1, 2\}$, and try one of the values, for instance $1$.  
We can see whether assigning to the cell the singleton set $\{1\}$ leads to the solution. 
If not, we try the value $\{2\}$ instead. 
If the Sudoku problem has a solution, one of these two values must work. 

The search function works like this: 

search():
 * propagate constraints.
 * if solved, hoorrayy!
 * if impossible, raise Unsolvable()
 * if not fully solved, pick a cell with multiple digits possible, and iteratively:
   * Assign one of the possible values to the cell. 
   * Call search() with that value for the cell.
   * If Unsolvable is raised by the search() call, move on to the next value.
   * If all values returned Unsolvable (if we tried them all), then we raise Unsolvable.

### Where can it go?

The method is global: it examines all rows, all columns, and all blocks.  
If it finds that in a row (or column, or block), a value can fit in only one cell, and that cell is not currently a singleton (for otherwise there is nothing to be done), it sets the value in the cell, and it adds the cell to the newly_singleton set that is returned, just as in propagate_cell. 

### Full propagation with where can it go algorithm

This is basically combining the `full_propagation` function with the _where can it go algorithm_. This results in a vastly more efficient algorithm for solving sudoku puzzles.

Before, when our only constraint was the uniqueness in each row, column, and block, we needed to propagate only from cells that hold a singleton value. 
If a cell held a non-singleton set of digits, such as $\{2, 5\}$, no values could be ruled out as a consequence of this on the same row, column, or block. 

The _where can it go_ heuristic, instead, benefits from knowing that in a cell, the set of values went for instance from $\{2, 3, 5\}$ to $\{2, 5\}$: by ruling out the possibility of a $3$ in this cell, it may be possibe to deduct that the digit $3$ can appear in only one (other) place in the block, and place it there. 

Thus, we modify the `full_propagation` method.  The method does:
* Repeat:
  * first does propagation as before, based on singletons; 
  * then, it applies the _where can it go_ heuristic on the whole Sudoku board. 

### Two search functions

The regular `search` function uses the old `full_propagation` method.

The `betterSearch` function uses the more efficient `full_propagation_with_where_can_it_go` function

### Helper Functions

`get_el`: Returns first element of set

`occurs_once_in_sets`: Returns the elements that appear only once in a sequence of sets
