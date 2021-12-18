from numbers import Number
from IPython.display import display, Math

# Takes an expression e and returns a string 
# which is the LaTeX representation of the expression e
def expr_to_latex(e):
    if (type(e) != tuple):
        return (str(e))
    elif (type(e) == tuple):
        operation = e[0]
        num1 = e[1]
        num2 = e[2]
        
        leftstring = expr_to_latex(num1)
        rightstring = expr_to_latex(num2)
        
        if (operation != "/"):
            if (len(leftstring) > 2 and "\\" not in leftstring):
                leftstring = "(" + leftstring + ")"
            if (len(rightstring) > 2 and "\\" not in rightstring ):
                rightstring = "(" + rightstring + ")"
                
            answer = leftstring + operation + rightstring
            return(answer)
        elif (operation == "/"):
            answer = "\\frac{"+leftstring+"}{"+rightstring+"}"
            return(answer)

# Computes expressoin e using recursion
def compute(e, varval={}):
    if isinstance(e, Number):
        return e
    elif isinstance(e, str):
        v = varval.get(e)
        # If we find a value for e, we return it; otherwise we return e.
        return e if v is None else v
    else:
        op, l, r = e
        # We simplify the left and right subexpressions first.
        ll = compute(l, varval=varval)
        rr = compute(r, varval=varval)
        # And we carry out the operation if we can.
        if isinstance(ll, Number) and isinstance(rr, Number):
            if op == '+':
                return ll + rr
            elif op == '-':
                return ll - rr
            elif op == '*':
                return ll * rr
            elif op == '/' and rr != 0:
                return ll / rr
        # Not simplifiable.
        return (op, ll, rr)

def derivate(e, x):
    """Returns the derivative of e with respect to  x."""
    if (type(e) != tuple):
        if (e == x):
            return 1
        else:
            return 0
    elif (type(e) == tuple):
        operation = e[0]
        num1 = e[1]
        num2 = e[2]
        
        if (operation == ("-") or operation == ("+")):
            return(operation, derivate(num1, x), derivate(num2, x))
        elif (operation == "*"):
            return("+", ("*", num2, derivate(num1, x)), ("*", num1, derivate(num2, x)))
        elif (operation == "/"):
            return("/",("-", ("*", num2, derivate(num1, x)), ("*", num1, derivate(num2, x))),("*",num2,num2))

# Prints latex in readable forms
def niceprint(e):
    display(Math(expr_to_latex(e)))

# Checking function to see if X and Y are equal
def check_equal(x, y, msg=None):
    if x != y:
        if msg is None:
            print("Error:")
        else:
            print("Error in", msg, ":")
        print("    Your answer was:", x)
        print("    Correct answer: ", y)
    assert x == y, "%r and %r are different" % (x, y)
    print("Success")



# Simple checks
print("Simple Checks")
check_equal(expr_to_latex(3), "3")
check_equal(expr_to_latex("x"), "x")

# Simple Expressions
print("Simple expressions")
e = ("+", 3, "x")
check_equal(expr_to_latex(e), "3+x")
e = ("-", "y", "x")
check_equal(expr_to_latex(e), "y-x")
e = ("*", "y", "2")
check_equal(expr_to_latex(e), "y*2")
e = ("/", "y", "2")
check_equal(expr_to_latex(e), "\\frac{y}{2}")

# Parenthesis
print("Simple parentheses")
e = ("*", ("+", 1, "x"), ("-", 3, "y"))
check_equal(expr_to_latex(e), "(1+x)*(3-y)")
e = ("*", ("+", 1, "x"), "z")
check_equal(expr_to_latex(e), "(1+x)*z")

# Harder Checks
print("General expressions")
e = ("*", ("+", 1, "x"), ("-", ("*", "x", "y"), "y"))
check_equal(expr_to_latex(e), "(1+x)*((x*y)-y)")
e = ("*", ("/", ("*", 3, "y"), "x"), ("-", ("*", "x", "y"), "y"))
check_equal(expr_to_latex(e), "\\frac{3*y}{x}*((x*y)-y)")

# Partial and Complete Evaluations
e = ('+', ('-', 'y', 3), ('*', 'x', 4))
print(compute(e, varval={'x': 2}))
print(compute(e, varval={'y': 3}))
print(compute(e, varval={'x': 2, 'y': 3}))

print("Derivative Tests")
# Base case tests for `derivate`
check_equal(derivate(3, 'x'), 0)
check_equal(derivate('y', 'x'), 0)
check_equal(derivate('x', 'x'), 1)

# Tests for `derivate` for single-operator expressions
check_equal(derivate(('+', 'x', 'x'), 'x'), ('+', 1, 1))
check_equal(derivate(('-', 4, 'x'), 'x'), ('-', 0, 1))
check_equal(derivate(('*', 2, 'x'), 'x'),
             ('+', ('*', 'x', 0), ('*', 2, 1)))
check_equal(derivate(('/', 2, 'x'), 'x'),
             ('/', ('-', ('*', 'x', 0), ('*', 2, 1)), ('*', 'x', 'x')))

# Tests for `derivate` for composite expressions
e1 = ('*', 'x', 'x')
e2 = ('*', 3, 'x')
num = ('-', e1, e2)
e3 = ('*', 'a', 'x')
den = ('+', e1, e3)
e = ('/', num, den)

f = ('/',
 ('-',
  ('*',
   ('+', ('*', 'x', 'x'), ('*', 'a', 'x')),
   ('-',
    ('+', ('*', 'x', 1), ('*', 'x', 1)),
    ('+', ('*', 'x', 0), ('*', 3, 1)))),
  ('*',
   ('-', ('*', 'x', 'x'), ('*', 3, 'x')),
   ('+',
    ('+', ('*', 'x', 1), ('*', 'x', 1)),
    ('+', ('*', 'x', 0), ('*', 'a', 1))))),
 ('*',
  ('+', ('*', 'x', 'x'), ('*', 'a', 'x')),
  ('+', ('*', 'x', 'x'), ('*', 'a', 'x'))))

check_equal(derivate(e, 'x'), f)