# Sats and Sudoku

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
