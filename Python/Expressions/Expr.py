class Expr(object):
    """Abstract class representing expressions"""

    def __init__(self, *args):
        self.children = list(args)
        self.child_values = None

    def eval(self, valuation=None):
        """Evaluates the value of the expression with respect to a given
        variable evaluation."""
        # First, we evaluate the children.
        child_values = [c.eval(valuation=valuation) if isinstance(c, Expr) else c
                        for c in self.children]
        # Then, we evaluate the expression itself.
        if any([isinstance(v, Expr) for v in child_values]):
            # Symbolic result.
            return self.__class__(*child_values)
        else:
            # Concrete result.
            return self.op(*child_values)

    def op(self, *args):
        """The op method computes the value of the expression, given the
        numerical value of its subexpressions.  It is not implemented in
        Expr, but rather, each subclass of Expr should provide its
        implementation."""
        raise NotImplementedError()

    def __repr__(self):
        """Represents the expression as the name of the class, followed by the
        children."""
        return "%s(%s)" % (self.__class__.__name__,
                        ', '.join(repr(c) for c in self.children))

    # Expression constructors

    def __add__(self, other):
        return Plus(self, other)

    def __radd__(self, other):
        return Plus(self, other)

    def __sub__(self, other):
        return Minus(self, other)

    def __rsub__(self, other):
        return Minus(other, self)

    def __mul__(self, other):
        return Multiply(self, other)

    def __rmul__(self, other):
        return Multiply(other, self)

    def __truediv__(self, other):
        return Divide(self, other)

    def __rtruediv__(self, other):
        return Divide(other, self)

    def derivate(self, var):
        """Computes the derivative of the expression with respect to var."""
        partials = [(c.derivate(var) if isinstance(c, Expr) else 0)
                for c in self.children]
        return self.op_derivate(var, partials).eval()

    def op_derivate(self, var, partials):
        raise NotImplementedError()


class Plus(Expr):
    def op(self, x, y):
        return x + y

    def op_derivate(self, var, partials):
        return Plus(partials[0], partials[1])

class Minus(Expr):
    def op(self, x, y):
        return x - y
    
    def op_derivate(self, var, partials):
        return Minus(partials[0], partials[1])

class Multiply(Expr):
    def op(self, x, y):
        return x * y
    
    def op_derivate(self, var, partials):
        """Please generate a formula exactly as described by the above math formula."""
        return(Plus(Multiply(partials[1], self.children[0]), Multiply(self.children[1], partials[0])))

class Divide(Expr):
    def op(self, x, y):
        return x / y

    def op_derivate(self, var, partials):
        f = self.children[0]
        g = self.children[1]
        """print(var)
        print(self.children)
        print(partials)"""
        return(Divide(Minus(Multiply(partials[0],g),Multiply(f,partials[1])),g*g))

class V(Expr):
    """Variable."""

    def __init__(self, *args):
        """Variables must be of type string."""
        assert len(args) == 1
        assert isinstance(args[0], str)
        super().__init__(*args)

    def eval(self, valuation=None):
        """If the variable is in the evaluation, returns the
        value of the variable; otherwise, returns the expression."""
        if valuation is not None and self.children[0] in valuation:
            return valuation[self.children[0]]
        else:
            return self 
    
    def derivate(self, var):
        if (var == self.children[0]):
            return 1
        return 0