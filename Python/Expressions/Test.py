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

def check_almost_equal(x, y, tolerance=0.001, msg=None):
    if abs(x - y) > tolerance:
        if msg is None:
            print("Error:")
        else:
            print("Error in", msg, ":")
        print("    Your answer was:", x)
        print("    Correct answer: ", y)
    assert abs(x - y) < tolerance, "%r and %r are different" % (x, y)
    print("Success")

def check_true(x, msg=None):
    if not x:
        if msg is None:
            print("Error: assertion is false")
        else:
            print("Error in", msg, ": false")
    assert x
    print("Success")


#Start regular expression and derivative tests
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

# Chain rule tests
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


# Gradient tests
print("Start gradient tests")
vx = V(3)
vz = V(4)
y = vx + vz
check_equal(y.eval(), 7)
y.zero_gradient()
y.compute_gradient()
check_equal(vx.gradient, 1.)

vx = V(3)
vz = V(4)
y = vx * vz
check_equal(y.eval(), 12)
y.zero_gradient()
y.compute_gradient()
check_equal(vx.gradient, 4)
check_equal(vz.gradient, 3)

#The gradient of a function consisting of both sums and products. 

vx = V(1)
vw = V(3)
vz = V(4)
y = (vx + vw) * (vz + 3)
check_equal(y.eval(), 28)
y.zero_gradient()
y.compute_gradient()
check_equal(vx.gradient, 7)
check_equal(vz.gradient, 4)

# And now with a repeated variable. 
vx = V(3)
vw = V(2)
vz = V(5)
y = (vx + vw) * (vz + vx)
check_equal(y.eval(), 40)
y.zero_gradient()
y.compute_gradient()
check_equal(vx.gradient, 13)
check_equal(vz.gradient, 5)

# Minus.
vx = V(3)
vy = V(2)
e = vx - vy
check_equal(e.eval(), 1.)
e.zero_gradient()
e.compute_gradient()
check_equal(vx.gradient, 1)
check_equal(vy.gradient, -1)

# Divide.
vx = V(6)
vy = V(2)
e = vx / vy
check_equal(e.eval(), 3.)
e.zero_gradient()
e.compute_gradient()
check_equal(vx.gradient, 0.5)
check_equal(vy.gradient, -1.5)

# Power.
vx = V(2)
vy = V(3)
e = vx ** vy
check_equal(e.eval(), 8.)
e.zero_gradient()
e.compute_gradient()
check_equal(vx.gradient, 12.)
check_almost_equal(vy.gradient, math.log(2.) * 8.)

# Negative
vx = V(6)
e = - vx
check_equal(e.eval(), -6.)
e.zero_gradient()
e.compute_gradient()
check_equal(vx.gradient, -1.)