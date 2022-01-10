# Sats
(Change to light mode to see equations)

## General Representation

To represent an instance of SAT, we represent literals, clauses, and the overall expression, as follows.

**Literals.** We represent the literal <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/a28020cb9b58a3a875adec3adf5d824a.svg?invert_in_darkmode&sanitize=true" align=middle width=15.536596349999991pt height=14.15524440000002pt/> via the positive integer <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/63bb9849783d01d91403bc9a5fea12a2.svg?invert_in_darkmode&sanitize=true" align=middle width=9.075367949999992pt height=22.831056599999986pt/>, and the literal <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/686f8f23f0cbcce0a1eac8c41611e3a9.svg?invert_in_darkmode&sanitize=true" align=middle width=15.536596349999991pt height=18.666631500000015pt/> via the negative integer <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/7b18cd2c554b7f8c28274ddd0530f1bf.svg?invert_in_darkmode&sanitize=true" align=middle width=21.860802149999987pt height=22.831056599999986pt/>. 

**Clauses.** We represent a clause via the set of integers representing the clause literals.  
For instance, we represent the clause <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/97e8c7c4ff93fdd336911a55ad565d9c.svg?invert_in_darkmode&sanitize=true" align=middle width=82.64254514999998pt height=18.666631500000015pt/> via the set <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/925c9ee08b69d89de7e942b8009a4cfd.svg?invert_in_darkmode&sanitize=true" align=middle width=68.49324734999999pt height=24.65753399999998pt/>. 

**SAT problem.**  We represent a SAT problem (again, in conjunctive normal form) via the set consisting in the representation of its clauses. 
For instance, the problem 
<p align="center"><img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/c7cf01ec238140bd213815c59c9a40f1.svg?invert_in_darkmode&sanitize=true" align=middle width=176.8547748pt height=16.438356pt/></p>
is represented by the set of sets:
<p align="center"><img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/9a6727f5a006de6ec11f6b3b38ddb1d4.svg?invert_in_darkmode&sanitize=true" align=middle width=141.5525925pt height=16.438356pt/></p>

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

What is the result on the clause?  Consider a clause  with representation <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/3e18a4a28fdee1744e5e3f79d13b9ff6.svg?invert_in_darkmode&sanitize=true" align=middle width=7.11380504999999pt height=14.15524440000002pt/> (thus, <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/3e18a4a28fdee1744e5e3f79d13b9ff6.svg?invert_in_darkmode&sanitize=true" align=middle width=7.11380504999999pt height=14.15524440000002pt/> is a set of integers) and a truth assignment <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/77a3b857d53fb44e33b53e4c8b68351a.svg?invert_in_darkmode&sanitize=true" align=middle width=5.663225699999989pt height=21.68300969999999pt/> (recall that <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/77a3b857d53fb44e33b53e4c8b68351a.svg?invert_in_darkmode&sanitize=true" align=middle width=5.663225699999989pt height=21.68300969999999pt/> can be positive or negative, depending on whether it assigns True or False to <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/0d19b0a4827a28ecffa01dfedf5f5f2c.svg?invert_in_darkmode&sanitize=true" align=middle width=12.92146679999999pt height=14.15524440000002pt/>).  There are three cases:

* If <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/68d3fed286d02574d74d961ef7b01f95.svg?invert_in_darkmode&sanitize=true" align=middle width=32.86816829999999pt height=21.68300969999999pt/>, then the <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/77a3b857d53fb44e33b53e4c8b68351a.svg?invert_in_darkmode&sanitize=true" align=middle width=5.663225699999989pt height=21.68300969999999pt/> literal of <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/3e18a4a28fdee1744e5e3f79d13b9ff6.svg?invert_in_darkmode&sanitize=true" align=middle width=7.11380504999999pt height=14.15524440000002pt/> is true, and so is the whole clause. We return True to signify it. 
* If <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/77ba3806439a46ee747fe857a76a9e11.svg?invert_in_darkmode&sanitize=true" align=middle width=45.653602499999984pt height=21.68300969999999pt/>, then the <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/a1b87a364d2766a83d85fc6b5c14aa3b.svg?invert_in_darkmode&sanitize=true" align=middle width=18.44865989999999pt height=21.68300969999999pt/> literal of <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/3e18a4a28fdee1744e5e3f79d13b9ff6.svg?invert_in_darkmode&sanitize=true" align=middle width=7.11380504999999pt height=14.15524440000002pt/> is false, and it cannot help make the clause true.  We return the clause <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/f32c6d155ed722e473f40d10e4081a94.svg?invert_in_darkmode&sanitize=true" align=middle width=57.52585079999999pt height=24.65753399999998pt/>, which corresponds to the remaining ways of making the clause true under assignment <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/77a3b857d53fb44e33b53e4c8b68351a.svg?invert_in_darkmode&sanitize=true" align=middle width=5.663225699999989pt height=21.68300969999999pt/>. 
* If neither <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/77a3b857d53fb44e33b53e4c8b68351a.svg?invert_in_darkmode&sanitize=true" align=middle width=5.663225699999989pt height=21.68300969999999pt/> nor <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/a1b87a364d2766a83d85fc6b5c14aa3b.svg?invert_in_darkmode&sanitize=true" align=middle width=18.44865989999999pt height=21.68300969999999pt/> is in <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/3e18a4a28fdee1744e5e3f79d13b9ff6.svg?invert_in_darkmode&sanitize=true" align=middle width=7.11380504999999pt height=14.15524440000002pt/>, then we return <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/3e18a4a28fdee1744e5e3f79d13b9ff6.svg?invert_in_darkmode&sanitize=true" align=middle width=7.11380504999999pt height=14.15524440000002pt/> itself, as <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/3e18a4a28fdee1744e5e3f79d13b9ff6.svg?invert_in_darkmode&sanitize=true" align=middle width=7.11380504999999pt height=14.15524440000002pt/> is not affected by the truth assignment <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/77a3b857d53fb44e33b53e4c8b68351a.svg?invert_in_darkmode&sanitize=true" align=middle width=5.663225699999989pt height=21.68300969999999pt/>. 

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
The idea is this: if we are to make true a clause <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/3e18a4a28fdee1744e5e3f79d13b9ff6.svg?invert_in_darkmode&sanitize=true" align=middle width=7.11380504999999pt height=14.15524440000002pt/>, we have to make true at least one of its literals.  Thus, we can pick a clause <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/3e18a4a28fdee1744e5e3f79d13b9ff6.svg?invert_in_darkmode&sanitize=true" align=middle width=7.11380504999999pt height=14.15524440000002pt/>, and try the truth assignment corresponding to each of its literals in turn: at least one of them should work.  Which clause is best to pick?  As in the Sudoku case, one with minimal length, so that the probability of one of its literals being true is highest. 

### Applying Assignments

Once we pick a truth assignment from one of the literals above, we need to propagate its effect to the clauses of the SAT instance. 

### Solving the SAT

The main method for searching for a solution of the SAT instance is the `solve` method. 
The `solve` method takes no arguments, and should return either False, if the SAT instance is unsatisfiable, or a truth assignment that satisfies it.  The satisfying truth assignment should be returned as a set (of integers).  

The `solve` method uses _generate_candidate_assignments_ and _apply_assignment_ above. 

First, the `solve` method should check whether the SAT instance <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/e257acd1ccbe7fcb654708f1a866bfe9.svg?invert_in_darkmode&sanitize=true" align=middle width=11.027402099999989pt height=22.465723500000017pt/> is trivially unsatisfiable (and return False) or trivially satisfiable (and return the empty set), using the `istrue` and `isfalse` methods. 
This takes care of the base cases of the search. 

If none of the above applies, `solve` must generate candiate truth assignments, and try them one by one.  
Let <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/44bc9d542a92714cac84e01cbbb7fd61.svg?invert_in_darkmode&sanitize=true" align=middle width=8.68915409999999pt height=14.15524440000002pt/> be the candidate assignment we are trying.  We apply <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/44bc9d542a92714cac84e01cbbb7fd61.svg?invert_in_darkmode&sanitize=true" align=middle width=8.68915409999999pt height=14.15524440000002pt/> to the current SAT problem via `apply_assignment`, obtaining <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/9df9cc8c13822e8722019b07dff39ebc.svg?invert_in_darkmode&sanitize=true" align=middle width=14.81734484999999pt height=24.7161288pt/>. 
We recursively try to solve <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/9df9cc8c13822e8722019b07dff39ebc.svg?invert_in_darkmode&sanitize=true" align=middle width=14.81734484999999pt height=24.7161288pt/>, via a call to `solve` of <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/9df9cc8c13822e8722019b07dff39ebc.svg?invert_in_darkmode&sanitize=true" align=middle width=14.81734484999999pt height=24.7161288pt/>.  Then: 

* If the new SAT problem <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/9df9cc8c13822e8722019b07dff39ebc.svg?invert_in_darkmode&sanitize=true" align=middle width=14.81734484999999pt height=24.7161288pt/> has no solution, you can move on to the next candidate assignment, if any; 
* if the new SAT problem <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/9df9cc8c13822e8722019b07dff39ebc.svg?invert_in_darkmode&sanitize=true" align=middle width=14.81734484999999pt height=24.7161288pt/> returns as a solution a truth-assignment <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/ddcb483302ed36a59286424aa5e0be17.svg?invert_in_darkmode&sanitize=true" align=middle width=11.18724254999999pt height=22.465723500000017pt/> (<img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/ddcb483302ed36a59286424aa5e0be17.svg?invert_in_darkmode&sanitize=true" align=middle width=11.18724254999999pt height=22.465723500000017pt/> is a list of integers), the solution is obtaining by combining <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/ddcb483302ed36a59286424aa5e0be17.svg?invert_in_darkmode&sanitize=true" align=middle width=11.18724254999999pt height=22.465723500000017pt/> and <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/44bc9d542a92714cac84e01cbbb7fd61.svg?invert_in_darkmode&sanitize=true" align=middle width=8.68915409999999pt height=14.15524440000002pt/> (returning the set obtained by adding <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/44bc9d542a92714cac84e01cbbb7fd61.svg?invert_in_darkmode&sanitize=true" align=middle width=8.68915409999999pt height=14.15524440000002pt/> to <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/ddcb483302ed36a59286424aa5e0be17.svg?invert_in_darkmode&sanitize=true" align=middle width=11.18724254999999pt height=22.465723500000017pt/>). 

# Sudoku Using Sats

## Main class
The first thing we do is to write a Sudoku class that can represent a Sudoku problem to be solved. Unlike our previosu representation, each cell here will contain either a digit 1..9, or 0, where 0 represents an unknown digit. We do not need to represent our solver's state of knowledge in terms of sets of digits, since the seach for a solution will be done in the SAT solver.

The class has three methods: one for translating the Sudoku into a SAT instance, one for solving the SAT instance, and another one for using the solution to the SAT instance to fill in the unspecified cells of the Sudoku problem.

Contrary to the previous approach, we keep the state of the board as a numpy array, of size 9 x 9; this will make indexing in the array a little bit more pleasant. The reason we could not use this representation earlier is that we wanted to associate with each cell a set of digits, and sets are not pleasant to represent in Numpy; single digits are.

## Variables
We base our trasnslation of Sudoku into SAT on variables <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/f9ac16873e913eec64af3be67b2c3d47.svg?invert_in_darkmode&sanitize=true" align=middle width=25.869053099999988pt height=14.15524440000002pt/>, where <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/f9ac16873e913eec64af3be67b2c3d47.svg?invert_in_darkmode&sanitize=true" align=middle width=25.869053099999988pt height=14.15524440000002pt/> expresses the fact that the digit <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/2103f85b8b1477f430fc407cad462224.svg?invert_in_darkmode&sanitize=true" align=middle width=8.55596444999999pt height=22.831056599999986pt/> appears at coordinates <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/e8873e227619b7a62ee7eb981ef1faea.svg?invert_in_darkmode&sanitize=true" align=middle width=33.46496009999999pt height=24.65753399999998pt/>. 
Since SAT solvers represent a variable by an integer, we will have that <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/f9ac16873e913eec64af3be67b2c3d47.svg?invert_in_darkmode&sanitize=true" align=middle width=25.869053099999988pt height=14.15524440000002pt/> is encoded simply using the integer <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/3f4c9daf2ea5e21683d3f446111f23fb.svg?invert_in_darkmode&sanitize=true" align=middle width=21.929607149999992pt height=22.831056599999986pt/> (in decimal notation), and the literal <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/515341694114ff24b131e74f32b5b8e3.svg?invert_in_darkmode&sanitize=true" align=middle width=25.869053099999988pt height=18.666631500000015pt/> will be encoded as <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/cba062bcd3bd3f86379565fe8b16b795.svg?invert_in_darkmode&sanitize=true" align=middle width=34.71504134999999pt height=22.831056599999986pt/>. 

For example, to express that digit 3 appears at coordinates 6, 7, we use the literal 367.  To express the negation of this, <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/58cc6bd99f38275214f6b7a7bb365e42.svg?invert_in_darkmode&sanitize=true" align=middle width=27.92820689999999pt height=18.666631500000015pt/>, that is, that digit 3 _does not_ appear at coordinates 6, 7, we use the literal -367. 

We thus start by writing two helper functions, `encode_variable` and `decode_variable`, that go from <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/78d043cf9c8afccc686c0e3985926761.svg?invert_in_darkmode&sanitize=true" align=middle width=36.54137354999999pt height=22.831056599999986pt/> to the corresponding integer, and vice versa.  

## Creating the clauses that represent a generic Sudoku problem

The key to translating Sudoku to SAT consists in producing a list of clauses that encodes the rules of Sudoku.  We will create list of clauses expressing the following. 
Below, we have <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/d2426b777401dd8b032a63e939deeefa.svg?invert_in_darkmode&sanitize=true" align=middle width=68.82964439999999pt height=22.831056599999986pt/>, and <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/2eef13924372485b3f9856b4d08d448c.svg?invert_in_darkmode&sanitize=true" align=middle width=80.95320749999999pt height=21.68300969999999pt/>. 

1. At each cell <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/3e384b223dce750e6c98aa501355f00b.svg?invert_in_darkmode&sanitize=true" align=middle width=20.679527549999985pt height=21.68300969999999pt/> at least one digit <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/2103f85b8b1477f430fc407cad462224.svg?invert_in_darkmode&sanitize=true" align=middle width=8.55596444999999pt height=22.831056599999986pt/> must appear.
2. At each cell <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/3e384b223dce750e6c98aa501355f00b.svg?invert_in_darkmode&sanitize=true" align=middle width=20.679527549999985pt height=21.68300969999999pt/>, at most one digit <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/2103f85b8b1477f430fc407cad462224.svg?invert_in_darkmode&sanitize=true" align=middle width=8.55596444999999pt height=22.831056599999986pt/> must appear. 
* If a digit <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/2103f85b8b1477f430fc407cad462224.svg?invert_in_darkmode&sanitize=true" align=middle width=8.55596444999999pt height=22.831056599999986pt/> appears at cell <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/3e384b223dce750e6c98aa501355f00b.svg?invert_in_darkmode&sanitize=true" align=middle width=20.679527549999985pt height=21.68300969999999pt/>, the same digit <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/2103f85b8b1477f430fc407cad462224.svg?invert_in_darkmode&sanitize=true" align=middle width=8.55596444999999pt height=22.831056599999986pt/> will not appear elsewhere on: 
    3. The same column. 
    4. The same row. 
    5. The same 3x3 Sudoku block. 

Note that conditions 1 and 2 are obvious to a human, and were encoded implicitly in our Sudoku solver.  Our SAT solver, however, has no idea of what a variable like <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/a1b5d285cb313af5cb88bc1e55a9faa1.svg?invert_in_darkmode&sanitize=true" align=middle width=27.92820689999999pt height=14.15524440000002pt/> means, or that digit 3 appears in cell 6, 7; therefore, we must teach it that exactly one digit apppears in each cell, via clauses. 

As an example, you can say that at at least one digit appears in cell 6, 7 via the clause: 

<p align="center"><img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/d53c127fac8e640eb37a54b9b1f01d27.svg?invert_in_darkmode&sanitize=true" align=middle width=139.21807845pt height=16.438356pt/></p>

and you can say that if 2 appears in cell 67, then 3 does not apper in that same cell, via: 

<p align="center"><img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/b03835f5d9f96aa880735097e665aafa.svg?invert_in_darkmode&sanitize=true" align=middle width=83.0708373pt height=16.438356pt/></p>

In literals ready for SAT, the latter is [-267, -367]. 
Similarly, to say that if a 2 appears at 6, 7, it does not appear on the same row at 6, 8, you would use the clause [-267, -268]. 

### Cells contain at least one digit
For each cell <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/3e384b223dce750e6c98aa501355f00b.svg?invert_in_darkmode&sanitize=true" align=middle width=20.679527549999985pt height=21.68300969999999pt/>, you have to create a clause stating that at least one <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/f9ac16873e913eec64af3be67b2c3d47.svg?invert_in_darkmode&sanitize=true" align=middle width=25.869053099999988pt height=14.15524440000002pt/> is true, for some <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/2103f85b8b1477f430fc407cad462224.svg?invert_in_darkmode&sanitize=true" align=middle width=8.55596444999999pt height=22.831056599999986pt/>.  You can easily build it as the disjunction <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/1aef6b0daefeb7f4faa4f6e65acb52eb.svg?invert_in_darkmode&sanitize=true" align=middle width=152.35138874999998pt height=18.264896099999987pt/>, corresponding to the clause:  

<p align="center"><img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/7b2c60eec77fc33891db3b02ad1dc57c.svg?invert_in_darkmode&sanitize=true" align=middle width=141.30124305pt height=17.031940199999998pt/></p>

### Cells contain at most one digit
Next, we need to express the fact that each cell can contain at most one digit <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/2103f85b8b1477f430fc407cad462224.svg?invert_in_darkmode&sanitize=true" align=middle width=8.55596444999999pt height=22.831056599999986pt/>. 
The idea is to write clauses that say that if a cell <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/4fe48dde86ac2d37419f0b35d57ac460.svg?invert_in_darkmode&sanitize=true" align=middle width=20.679527549999985pt height=21.68300969999999pt/> contains a digit <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/2103f85b8b1477f430fc407cad462224.svg?invert_in_darkmode&sanitize=true" align=middle width=8.55596444999999pt height=22.831056599999986pt/>, it does not contain a different digit <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/868389164b1f8dc28cc4d7fbb181099b.svg?invert_in_darkmode&sanitize=true" align=middle width=12.345925349999991pt height=24.7161288pt/>. 
This is expressed by <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/b4e7f514f63a86c4754a23621bbb93e0.svg?invert_in_darkmode&sanitize=true" align=middle width=82.57695764999998pt height=18.666631500000015pt/> for all <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/2eef13924372485b3f9856b4d08d448c.svg?invert_in_darkmode&sanitize=true" align=middle width=80.95320749999999pt height=21.68300969999999pt/> and all <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/c8971fdbfa77201a4ed9f3711bed8530.svg?invert_in_darkmode&sanitize=true" align=middle width=89.30336579999998pt height=24.7161288pt/> with <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/52fb0eb7d2922fe585b46a08963c3022.svg?invert_in_darkmode&sanitize=true" align=middle width=42.819519599999985pt height=24.7161288pt/>.  In turn, the implication <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/b4e7f514f63a86c4754a23621bbb93e0.svg?invert_in_darkmode&sanitize=true" align=middle width=82.57695764999998pt height=18.666631500000015pt/> can be expressed as the clause 

<p align="center"><img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/640c834069f9a9afd0780cd4da81e081.svg?invert_in_darkmode&sanitize=true" align=middle width=83.3988474pt height=17.031940199999998pt/></p>

for all <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/2eef13924372485b3f9856b4d08d448c.svg?invert_in_darkmode&sanitize=true" align=middle width=80.95320749999999pt height=21.68300969999999pt/> and all <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/c8971fdbfa77201a4ed9f3711bed8530.svg?invert_in_darkmode&sanitize=true" align=middle width=89.30336579999998pt height=24.7161288pt/> with <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/52fb0eb7d2922fe585b46a08963c3022.svg?invert_in_darkmode&sanitize=true" align=middle width=42.819519599999985pt height=24.7161288pt/>. 
The clause says that either <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/2103f85b8b1477f430fc407cad462224.svg?invert_in_darkmode&sanitize=true" align=middle width=8.55596444999999pt height=22.831056599999986pt/> is not at <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/4fe48dde86ac2d37419f0b35d57ac460.svg?invert_in_darkmode&sanitize=true" align=middle width=20.679527549999985pt height=21.68300969999999pt/>, or <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/868389164b1f8dc28cc4d7fbb181099b.svg?invert_in_darkmode&sanitize=true" align=middle width=12.345925349999991pt height=24.7161288pt/> is not at <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/4fe48dde86ac2d37419f0b35d57ac460.svg?invert_in_darkmode&sanitize=true" align=middle width=20.679527549999985pt height=21.68300969999999pt/>: this ensures that <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/5eca1f8885a9c10b00f18df5b03e52ea.svg?invert_in_darkmode&sanitize=true" align=middle width=28.20777299999999pt height=24.7161288pt/> are not both at <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/3e384b223dce750e6c98aa501355f00b.svg?invert_in_darkmode&sanitize=true" align=middle width=20.679527549999985pt height=21.68300969999999pt/>.

### No identical digits in the same row
We now need to experss one of the basic rules of Sudoku: a digit can appear in only one cell along a row. 
Precisely, for all rows <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/0154c69b8d88ed2a5bd564fa80531552.svg?invert_in_darkmode&sanitize=true" align=middle width=65.93690564999999pt height=21.68300969999999pt/>, and all digits <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/d2426b777401dd8b032a63e939deeefa.svg?invert_in_darkmode&sanitize=true" align=middle width=68.82964439999999pt height=22.831056599999986pt/>, we write 

<p align="center"><img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/92cae9ee730304a6ca94759738c5f22f.svg?invert_in_darkmode&sanitize=true" align=middle width=81.75502004999998pt height=14.03648895pt/></p>

for all <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/daf2968383a1a62f08838742a4e1ba25.svg?invert_in_darkmode&sanitize=true" align=middle width=86.69902889999999pt height=24.7161288pt/> with <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/f171b1a0dc17bb07954bd038825b8c74.svg?invert_in_darkmode&sanitize=true" align=middle width=41.128427999999985pt height=24.7161288pt/>. 
These implications stipulate that if digit <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/2103f85b8b1477f430fc407cad462224.svg?invert_in_darkmode&sanitize=true" align=middle width=8.55596444999999pt height=22.831056599999986pt/> is at position <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/36b5afebdba34564d884d347484ac0c7.svg?invert_in_darkmode&sanitize=true" align=middle width=7.710416999999989pt height=21.68300969999999pt/> in the row, it cannot also be in position <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/1041e382f1560a32a7a26f335a9e77bf.svg?invert_in_darkmode&sanitize=true" align=middle width=11.500379549999991pt height=24.7161288pt/> with <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/a89c2d7f5620d9ab6f32bdd5ed097750.svg?invert_in_darkmode&sanitize=true" align=middle width=41.95034084999999pt height=24.7161288pt/>. 
These implications can be translated into clauses with two literals, exactly as we did in point 2 above. 

### No idientical digits in same column
Similar idea as rows, but for columns

### No idientical digits in the same 3x3 block
The idea here is to state that if a digit <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/2103f85b8b1477f430fc407cad462224.svg?invert_in_darkmode&sanitize=true" align=middle width=8.55596444999999pt height=22.831056599999986pt/> appears at a position <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/4fe48dde86ac2d37419f0b35d57ac460.svg?invert_in_darkmode&sanitize=true" align=middle width=20.679527549999985pt height=21.68300969999999pt/> in a 3x3 Sudoku block, it does not appear in any other position <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/2e56867f4065ed06711b99415ed79253.svg?invert_in_darkmode&sanitize=true" align=middle width=29.08136384999999pt height=24.7161288pt/> in the same 3x3 block, with <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/a36a06d2cc1932718ec0f28578b32217.svg?invert_in_darkmode&sanitize=true" align=middle width=37.03404539999999pt height=24.7161288pt/> or <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/f171b1a0dc17bb07954bd038825b8c74.svg?invert_in_darkmode&sanitize=true" align=middle width=41.128427999999985pt height=24.7161288pt/>. 

## Putting everything togethor
We can create the rules for sudoku bu adding all these rules to a single list in `sudoku_rules`

### Translating state of board into clauses
We now need to translate the intial state of the board into clauses.  This is easy to do: whenever the board contains a (known) digit <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/2103f85b8b1477f430fc407cad462224.svg?invert_in_darkmode&sanitize=true" align=middle width=8.55596444999999pt height=22.831056599999986pt/> in position <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/4fe48dde86ac2d37419f0b35d57ac460.svg?invert_in_darkmode&sanitize=true" align=middle width=20.679527549999985pt height=21.68300969999999pt/>, you generate a clause

<p align="center"><img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/d87e2aeb107ddb490592a1c12de3c7c8.svg?invert_in_darkmode&sanitize=true" align=middle width=35.8233744pt height=17.031940199999998pt/></p>

stating that <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/2103f85b8b1477f430fc407cad462224.svg?invert_in_darkmode&sanitize=true" align=middle width=8.55596444999999pt height=22.831056599999986pt/> is in position <img src="https://github.com/IdkwhatImD0ing/AlgorithmPractice/blob/main/Python/SATSudoku/svgs/4fe48dde86ac2d37419f0b35d57ac460.svg?invert_in_darkmode&sanitize=true" align=middle width=20.679527549999985pt height=21.68300969999999pt/>.  That's all! 
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
