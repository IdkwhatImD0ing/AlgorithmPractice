# Expressions as Classes, Optimization, and Machine Learning

The inspiration for this project came directly from my LatexMath project. In that project, derivatives were calculated in a function and expressions were expressed as tuples. 

Here, we will now describe a more sophisticated representation for an expression, based on a hierarchy of classes. The class Expr is the generic class denoting an expression. It is an abstract class: only its subclasses will be instantiated. 

For every operator, such as +, there will be a subclass, such as Plus. Variables will correspond to a special subclass, called V. Numerical constants will be just represented by numbers, and not by subclasses of Expr. The derivates for each expression (add, minus, multiple, divide) are also implemented in individual classes.

## Classes

### The `Expr` class

The Expr class implements the various methods used to emulate numerical types, such as __add__, __sub__, and so forth. In this way, we can build an expression simply by writing

`3 * V('x') / 2`

Like LatexMath, the `Expr` also contains an eval function to evaluate an expression based on given values of variables.

The method `compute_gradient` calculates the gradient for the expression by:

- add  ∂L/∂e  to the gradient `self.gradient` of the expression;
- compute  ∂e/∂x~i~  for each child  x~~i  by calling the method `derivate` of itself;
- propagate to each child  xi  the gradient  ∂L/∂e⋅∂e/∂x~i~ , by calling the method `compute_gradient` of the child  i  with argument  ∂L/∂e⋅∂e/∂x~i~ .


### The `V` class

Variables are expressions containing only one child, of type string or int, which is the name or value of the variable respectively. So V('X') will be a variable with name "x" and V(3) will be equal to 3. The method eval of a variable over-rides that of Expr.

### The operator classes `Plus`, `Subtract`, `Multiply`, `Divide`, `Pow`, `Log`, `Negative`

Each class contains the `op` function, which applys the operation of the class

Each class also contains the `derivate` function, which applies the corresponding derivative for the operation with respect to variable `var`.

The derivative function works by:

- The method derivate will first call the method derivate for all the subexpressions, that is, the children of the expression, accumulating the results into a list partials (so called because these are partial derivatives).

- Then, the method derivate will call op_derivate. This method is an abstract method of Expr, and is implemented in each operator (Plus, Minus, etc). The method op_derivate will compute the derivative of the expression, according to the operator type. For example, the derivative of of a + b would be the derivative of a + derivative of b

Each class will also contain the `gradDerivate` function, which applies derivations for use in the gradient calculation function.

This function differes from the `derivate` function in the following ways:

- The output will be a list with size one or two
- For simplicity's sake, each expression will be represented by x and y only. For example, addition will be x + y and multiplication will be x*y
- The first entry of the list will be derivative with respect to x
- The second entry of the list will be derivative with respect to y

## Optimization
### Optimize.py

First, we come up somehow with a very complicated model y = M(x, θ), which computes an output y as a function of an input x  and of a vector of parameters θ . In general, x, y, and θ are vectors, as the model has multiple inputs, multiple outputs, and several parameters. The model M needs to be complicated, because only complicated models can represent complicated phenomena; for instance, M can be a multi-layer neural net with parameters θ =[θ1,…,θk], where k is the number of parameters of the model.

Second, you come up with a notion of loss L, that is, how badly the model is doing. Once the loss is chosen, we decrease it, by computing its gradient with respect to θ.

The gradient is a vector that indicates how to tweak θ to decrease the loss. You then choose a small step size δ, and you update θ. This makes the loss a little bit smaller, and the model a little bit better. If you repeat this step many times, the model will hopefully get (a good bit) better.

We will provide a representaton for expressions that enables both the calculation of the expression value, and the differentiation with respect to any of the inputs. This will enable us to implement autogradient. On the basis of this, we will be able to implement a simple ML framework.

### Machine Learning

We will demonstrate machine learning using `linear regression`, `quadratic regression`, and `cubic regression` on a given set of points. To build a line to fit these points, we will build an `Expr` that represents the equation we use for regression. 

For quadratic regression, we will use the equation `y^=ax^2^+bx+c`, where y^ is the value of y predicted by our parabola. If y^ is the predicted value, and y is the observed value, to obtain a better prediction of the observations, we minimize the loss L =(y^−y)^2^, that is, the square prediction error.

Here,  a,b,c  are parameters that we need to tune to minimize the loss, and obtain a good fit between the parabola and the points.

### Tuning

This tuning, or training, is done by repeating the following process many times:
- Zero the gradient
- For each point:
  - Set the values of x, y to the value of the point.
  - Compute the expression giving the loss.
  - Backpropagate. This computes all gradients with respect to the loss, and in particular, the gradients of the coefficients  a,b,c .
- Update the coefficients  a,b,c  by taking a small step in the direction of the negative gradien(negative, so that the loss decreases).

### Fit line to points

The `fit` function minimizes the loss of fitting a series of (x,y) points with a function. Precisely, the fit function takes as input:

- An expression loss, which gives the loss as a function of the values of two variables, vx and vy, as well as a list of parameters params. In the above example, params = [va, vb, vc].
- A list points of (x,y)-pairs, such as [(2, 3), (3.2, 4.1)].
- A list params of parameters to be optimized. In the above example, params = [va, vb, vc].
- A learning-step size delta.
- A number of iterations num_iterations.

After running the fit function, we can just graph the quadratic equation using va, vb, and vc as a, b, and c respectively to get our line.

Similar steps are used for the linear and cubic regressions.