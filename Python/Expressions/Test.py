import Expr
import math
from Expr import V

# Checking code
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

e = V('x') + 3
print(e)
print(e.eval())
print(e.eval({'x': 2}))

e = (V('x') + V('y')) * (2 + V('x'))
print(e.eval())
print(e.eval({'x': 4}))

print("Variable + operation derivative tests")
e = V('x') + 3
print(e.derivate('x'))
check_equal(e.derivate('x'), 1)
check_equal(e.derivate('y'), 0)

e = V('x') - 4
check_equal(e.derivate('x'), 1)

e = 4 - V('x')
check_equal(e.derivate('x'), -1)

e = V('x') * V('y')
check_equal(e.derivate('x').eval(dict(x=3, y=2)), 2)
check_equal(e.derivate('y').eval(dict(x=3, y=2)), 3)

e = V('x') * V('x')
check_equal(e.derivate('x').eval(dict(x=5)), 10)

e = V('x') / V('y')
check_equal(e.derivate('x').eval(dict(x=3, y=2)), 0.5)
check_equal(e.derivate('y').eval(dict(x=3, y=2)), -3 / 4) 

e = V('x') ** V('y')
check_equal(e.derivate('x').eval(dict(x=3, y=2)), 6)
check_equal(e.derivate('y').eval(dict(x=1, y=5)), 0)

e = (3 * V('x')) ** V('y')
check_equal(e.derivate('x').eval(dict(x=3, y=2)), 54)

e = (math.e * V('x')) ** V('y')
check_equal(e.derivate('y').eval(dict(x=1, y=0)), 1)

e = V('x') ** (5 * V('y'))
check_equal(e.derivate('x').eval(dict(x=2, y=1)), 80)
check_equal(e.derivate('y').eval(dict(x=math.e, y=0)), 5)

e = -V('x')
check_equal(e.derivate('x'), -1)
check_equal(e.derivate('y'), 0)
