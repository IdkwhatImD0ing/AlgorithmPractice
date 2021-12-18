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
