# Latex and Expressions

## Printing out an Expression using Latex

An expression consists of one of these:

1. A number
2. A variable
3. If e1 and e2 are expressions, then e1+e2, e1−e2, e1∗e2, and e1/e2 are also expressions.

Formally, the set of expressions is the least set constructed according to the rules above.

Thus, an expression can be either a constant, representing numbers and variables, or a composite expression, consisting of an operator, a left expression, and a right expression.

The function expr_to_latex(e) will produce a string which is the LaTeX representation of the expression e

The function compute(e, varval={}) evaluates an expression with the help of a variable valuation. A variable valuation is a mapping from variables to their values; we can represent it simply as a dictionary associating to each variable a number: varval = {'x': 3, 'y': 8}

## Symbolic Derivatives

As we have symbolic expressions, we can compute their (partial) derivative with respect to any variable. Given an expression  e  and a variable  x , we denote by  ∂e/∂x  the partial derivative of  e  with respect to  x . To compute it, we can simply rely on the definition of derivative.

The function derivate, given an expression e and a variable x, returns an expression for ∂e/∂x.

## Expression Equality

Given two expressions e and f, how can we decide whether they are equal in value, that is, whether they yield always the same value for all values of the variables?

Suppose you have two expressions  f,g  containing variable  x  only. The idea is that if  f  and  g  are built with the usual operators of algebra, it is exceedingly unlikely for  f  and  g  to give the same value many values of  x , and yet not be always equal.

In other words, if we use many values for x, and f,g always evaluates to be equal to another, then it is highly likely that f,g are equal. 

So our idea will simply be: pick 1000 values of  x  at random; if the two expressions are equal for all the values, then they must be equal everywhere.

The function variables(e) determines the set of variables that appear in expression e,

For finding expression equality, the idea is perform an equality test `num_samples` times.  Each time, we will produce a variable assignment (a dictionary) `d` mapping variables to random values, and then you use the `compute(e1, varval=d)` function to evaluate `e1` under that assignment, and similarly for `e2`.  We then can then compare the resulting values, up to the tolerance `tolerance`.  As long as the differences are below the tolerance (which has to be very small), we can conclude that the two expressions are equal.