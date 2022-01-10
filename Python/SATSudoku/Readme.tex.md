# Sats
(Open readme in VS for formatted output. Github markdown does not support some of the syntax I use)

## General Representation

To represent an instance of SAT, we represent literals, clauses, and the overall expression, as follows.

**Literals.** We represent the literal $p_k$ via the positive integer $k$, and the literal $\bar{p}_k$ via the negative integer $-k$. 

**Clauses.** We represent a clause via the set of integers representing the clause literals.  
For instance, we represent the clause $p_1 \vee \bar{p}_3 \vee p_4$ via the set $\{1, -3, 4\}$. 

**SAT problem.**  We represent a SAT problem (again, in conjunctive normal form) via the set consisting in the representation of its clauses. 
For instance, the problem 
$$
(p_1 \vee \bar{p}_2 \vee p_3) \wedge (p_2 \vee p_5)
$$
is represented by the set of sets:
$$
\{ \{1, -2, 3\}, \{2, 5\} \} \; .
$$

## Clause Representation
Clause.py

This is the class representing a clause.  It is written in such a way that: 

* The list of literals is stored as a frozenset `self.literals`, so that we automatically remove duplicate literals, and so that we can easily define clause equality.
* It can be initialized either with a list of integers, or with a clause.  In the first case, the integers are the literals.  In the second case, we create a copy of the original clause. 
* A clause is true iff it contains both a literal and its complement. 
* A clause is false iff it is empty.

### Simplifying clauses

To solve a SAT instance, we need to search for a truth assignment to its propositional variables that will make all the clauses true. 
We will search for such a truth assignment by trying to build it one variable at a time.  So a basic operation on a clause will be: 

> Given a clause, and a truth assignment for one variable, compute the result on the clause. 

What is the result on the clause?  Consider a clause  with representation $c$ (thus, $c$ is a set of integers) and a truth assignment $i$ (recall that $i$ can be positive or negative, depending on whether it assigns True or False to $p_i$).  There are three cases:

* If $i \in c$, then the $i$ literal of $c$ is true, and so is the whole clause. We return True to signify it. 
* If $-i \in c$, then the $-i$ literal of $c$ is false, and it cannot help make the clause true.  We return the clause $c \setminus \{-i\}$, which corresponds to the remaining ways of making the clause true under assignment $i$. 
* If neither $i$ nor $-i$ is in $c$, then we return $c$ itself, as $c$ is not affected by the truth assignment $i$. 

## SAT Representation

Sat.py

A SAT instance consists in a set of clauses. 

The SAT instance is satisfiable if and only if there is a truth assignment to predicates that satisfies all of its clauses. 
Therefore: 

* If the SAT instance contains no clauses, it is trivially satisfiable.
* If the SAT instance contains an empty clause, it is unsatisfiable, since there is no way to satisfy that clause. 

Based on this idea, the initializer method for our SAT class will get a list of clauses as input.  It will discard the tautologically true ones (as indicated by the istrue clause method).  If there is even a single unsatisfiable clause, then we set the SAT problem to consist of only one unsatisfiable clause, as a shorthand for denoting that the SAT problem cannot be satisfied. 

We endow the SAT class with methods isfalse and istrue, that detect SAT problems that are trivially satisfiable by any truth assignment, or trivially unsatisfiable by any truth assignment. 

* A SAT instance is true only if it contains no clauses.  This because empty clauses are not added to the SAT instance (see above initializer). 
* A SAT instance is false if it contains a false clause. 

### Candidate Assignments

In order to solve a SAT instance, we proceed with the choice-constraint propagation-recursion setting.  Let us build the choice piece first. 
The idea is this: if we are to make true a clause $c$, we have to make true at least one of its literals.  Thus, we can pick a clause $c$, and try the truth assignment corresponding to each of its literals in turn: at least one of them should work.  Which clause is best to pick?  As in the Sudoku case, one with minimal length, so that the probability of one of its literals being true is highest. 

### Applying Assignments

Once we pick a truth assignment from one of the literals above, we need to propagate its effect to the clauses of the SAT instance. 

### Solving the SAT

The main method for searching for a solution of the SAT instance is the `solve` method. 
The `solve` method takes no arguments, and should return either False, if the SAT instance is unsatisfiable, or a truth assignment that satisfies it.  The satisfying truth assignment should be returned as a set (of integers).  

The `solve` method uses _generate_candidate_assignments_ and _apply_assignment_ above. 

First, the `solve` method should check whether the SAT instance $S$ is trivially unsatisfiable (and return False) or trivially satisfiable (and return the empty set), using the `istrue` and `isfalse` methods. 
This takes care of the base cases of the search. 

If none of the above applies, `solve` must generate candiate truth assignments, and try them one by one.  
Let $a$ be the candidate assignment we are trying.  We apply $a$ to the current SAT problem via `apply_assignment`, obtaining $S'$. 
We recursively try to solve $S'$, via a call to `solve` of $S'$.  Then: 

* If the new SAT problem $S'$ has no solution, you can move on to the next candidate assignment, if any; 
* if the new SAT problem $S'$ returns as a solution a truth-assignment $L$ ($L$ is a list of integers), the solution is obtaining by combining $L$ and $a$ (returning the set obtained by adding $a$ to $L$). 

# Sudoku Using Sats

## Main class
The first thing we do is to write a Sudoku class that can represent a Sudoku problem to be solved. Unlike our previosu representation, each cell here will contain either a digit 1..9, or 0, where 0 represents an unknown digit. We do not need to represent our solver's state of knowledge in terms of sets of digits, since the seach for a solution will be done in the SAT solver.

The class has three methods: one for translating the Sudoku into a SAT instance, one for solving the SAT instance, and another one for using the solution to the SAT instance to fill in the unspecified cells of the Sudoku problem.

Contrary to the previous approach, we keep the state of the board as a numpy array, of size 9 x 9; this will make indexing in the array a little bit more pleasant. The reason we could not use this representation earlier is that we wanted to associate with each cell a set of digits, and sets are not pleasant to represent in Numpy; single digits are.

## Variables
We base our trasnslation of Sudoku into SAT on variables $p_{dij}$, where $p_{dij}$ expresses the fact that the digit $d$ appears at coordinates $(i, j)$. 
Since SAT solvers represent a variable by an integer, we will have that $p_{dij}$ is encoded simply using the integer $dij$ (in decimal notation), and the literal $\bar{p}_{dij}$ will be encoded as $-dij$. 

For example, to express that digit 3 appears at coordinates 6, 7, we use the literal 367.  To express the negation of this, $\bar{p}_{367}$, that is, that digit 3 _does not_ appear at coordinates 6, 7, we use the literal -367. 

We thus start by writing two helper functions, `encode_variable` and `decode_variable`, that go from $d, i, j$ to the corresponding integer, and vice versa.  

## Creating the clauses that represent a generic Sudoku problem

The key to translating Sudoku to SAT consists in producing a list of clauses that encodes the rules of Sudoku.  We will create list of clauses expressing the following. 
Below, we have $1 \leq d \leq 9$, and $0 \leq i, j \leq 8$. 

1. At each cell $i, j$ at least one digit $d$ must appear.
2. At each cell $i, j$, at most one digit $d$ must appear. 
* If a digit $d$ appears at cell $i, j$, the same digit $d$ will not appear elsewhere on: 
    3. The same column. 
    4. The same row. 
    5. The same 3x3 Sudoku block. 

Note that conditions 1 and 2 are obvious to a human, and were encoded implicitly in our Sudoku solver.  Our SAT solver, however, has no idea of what a variable like $p_{367}$ means, or that digit 3 appears in cell 6, 7; therefore, we must teach it that exactly one digit apppears in each cell, via clauses. 

As an example, you can say that at at least one digit appears in cell 6, 7 via the clause: 

$$
[p_{167}, p_{267}, \ldots, p_{967}]
$$

and you can say that if 2 appears in cell 67, then 3 does not apper in that same cell, via: 

$$
[\bar{p}_{267}, \bar{p}_{367}] \; . 
$$

In literals ready for SAT, the latter is [-267, -367]. 
Similarly, to say that if a 2 appears at 6, 7, it does not appear on the same row at 6, 8, you would use the clause [-267, -268]. 

### Cells contain at least one digit
For each cell $i, j$, you have to create a clause stating that at least one $p_{dij}$ is true, for some $d$.  You can easily build it as the disjunction $p_{1ij} \vee p_{2ij} \vee \cdots \vee p_{9ij}$, corresponding to the clause:  

$$
[p_{1ij}, p_{2ij}, \ldots, p_{9ij}] \; . 
$$

### Cells contain at most one digit
Next, we need to express the fact that each cell can contain at most one digit $d$. 
The idea is to write clauses that say that if a cell $i,j$ contains a digit $d$, it does not contain a different digit $d'$. 
This is expressed by $p_{dij} \rightarrow \bar{p}_{d'ij}$ for all $0 \leq i, j \leq 8$ and all $1 \leq d, d' \leq 9$ with $d \neq d'$.  In turn, the implication $p_{dij} \rightarrow \bar{p}_{d'ij}$ can be expressed as the clause 

$$
[\bar{p}_{dij}, \bar{p}_{d'ij}] \; , 
$$

for all $0 \leq i, j \leq 8$ and all $1 \leq d, d' \leq 9$ with $d \neq d'$. 
The clause says that either $d$ is not at $i,j$, or $d'$ is not at $i,j$: this ensures that $d, d'$ are not both at $i, j$.

### No identical digits in the same row
We now need to experss one of the basic rules of Sudoku: a digit can appear in only one cell along a row. 
Precisely, for all rows $0 \leq i \leq 8$, and all digits $1 \leq d \leq 9$, we write 

$$
    p_{dij} \rightarrow \bar{p}_{dij'}
$$

for all $0 \leq j, j' \leq 8$ with $j \neq j'$. 
These implications stipulate that if digit $d$ is at position $j$ in the row, it cannot also be in position $j'$ with $j' \neq j$. 
These implications can be translated into clauses with two literals, exactly as we did in point 2 above. 

### No idientical digits in same column
Similar idea as rows, but for columns

### No idientical digits in the same 3x3 block
The idea here is to state that if a digit $d$ appears at a position $i,j$ in a 3x3 Sudoku block, it does not appear in any other position $i',j'$ in the same 3x3 block, with $i \neq i'$ or $j \neq j'$. 

## Putting everything togethor
We can create the rules for sudoku bu adding all these rules to a single list in `sudoku_rules`

### Translating state of board into clauses
We now need to translate the intial state of the board into clauses.  This is easy to do: whenever the board contains a (known) digit $d$ in position $i,j$, you generate a clause

$$
[p_{dij}]
$$

stating that $d$ is in position $i,j$.  That's all! 
Method `_board_to_SAT` returns the list of such unary clauses.

### Translating Sudoku to SAT
We now write a `_to_SAT` method for `SudokuViaSAT`, that translates a Sudoku problem into a list of SAT clauses, and returns the list of clauses.  The list contains: 

* all the clauses returned by the `sudoku_rules` function above, 
* all the clauses that represent the initial state of the board, returned by the `_board_to_SAT` method.  

### Solving Sudoku
It is time to put everything together in a `solve` method for `SudokuViaSAT`.  The method works as follows.  It takes as input one of the SAT solver classes, such as `Glucose3`, `Glucose4`, or `Minisat22`.  Then: 

* It uses the method `_to_SAT` to create the clauses for a SAT instance encoding the Sudoku problem. 
* It adds those clauses to the SAT solver. 
* It solves the SAT problem. 
* If the problem has a solution, it uses the solution of the SAT problem to complete the cell in the Sudoku board. 

For the last step, we can check that the problem has a solution via `g.solve()`, as in the test cases above. 
If the problem has a solution, `g.get_model()` gives us a truth assignment satisfying the SAT problem.
The model of the SAT solver enables us to directly fill the Sudoku board.
