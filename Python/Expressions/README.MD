# Expressions as Classes

The inspiration for this project came directly from my LatexMath project. In that project, derivatives were calculated in a function and expressions were expressed as tuples. 

Here, we will now describe a more sophisticated representation for an expression, based on a hierarchy of classes. The class Expr is the generic class denoting an expression. It is an abstract class: only its subclasses will be instantiated. 

For every operator, such as +, there will be a subclass, such as Plus. Variables will correspond to a special subclass, called V. Numerical constants will be just represented by numbers, and not by subclasses of Expr. The derivates for each expression (add, minus, multiple, divide) are also implemented in individual classes.

## Classes

### The `Expr` class

The Expr class implements the various methods used to emulate numerical types, such as __add__, __sub__, and so forth. In this way, we can build an expression simply by writing

`3 * V('x') / 2`

Like LatexMath, the `Expr` also contains an eval function to evaluate an expression based on given values of variables.

### The `V` class

Variables are expressions containing only one child, of type string, which is the name of the variable. So V("x") will be a variable with name "x". The method eval of a variable over-rides that of Expr.

### The operator classes `Plus`, `Subtract`, `Multiply`, `Divide`

Each class contains the op function, which applys the operation of the class

Each class also contains the derivative function, which applies the corresponding derivative for the operation.

The derivative function works by:

- The method derivate will first call the method derivate for all the subexpressions, that is, the children of the expression, accumulating the results into a list partials (so called because these are partial derivatives).

- Then, the method derivate will call op_derivate. This method is an abstract method of Expr, and is implemented in each operator (Plus, Minus, etc). The method op_derivate will compute the derivative of the expression, according to the operator type. For example, the derivative of of a + b would be the derivative of a + derivative of b