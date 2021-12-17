from collections import defaultdict
import numpy as np

class AD(dict):

    def __init__(self, *args, **kwargs):
        """This initializer simply passes all arguments to dict, so that
        we can create an AD with the same ease with which we can create
        a dict.  There is no need, indeed, to repeat the initializer,
        but we leave it here in case we like to create attributes specific
        of an AD later."""
        super().__init__(*args, **kwargs)

    #addition
    def __add__(self, other):
        return AD._binary_op(self, other, lambda x, y: x + y, 0)

    #subtraction
    def __sub__(self, other):
        return AD._binary_op(self, other, lambda x, y: x - y, 0)

    #multiplication
    def __mul__(self, other):
        return AD._binary_op(self, other, lambda x, y: x + y if x == 0 or y == 0 else x * y, 0)

    #division
    def __truediv__(self, other):
        return AD._binary_op(self, other, lambda x, y: 1/y if x == 0 else x/1 if y == 0 else x/y  , 0)

    #integer division
    def __floordiv__(self, other):
        return AD._binary_op(self, other, lambda x, y: 1//y if x == 0 else x//1 if y == 0 else x//y  , 0)

    #Less than inequality
    def __lt__(self, other):
        return AD._binary_op(self, other, lambda x, y: x < y, 0)

    #Greater than inequality
    def __gt__(self, other):
        return AD._binary_op(self, other, lambda x, y: x > y, 0)

    #Less than or equal inequality
    def __le__(self, other):
        return AD._binary_op(self, other, lambda x, y: x <= y, 0)

    #Greater than or equal inequality
    def __ge__(self, other):
        return AD._binary_op(self, other, lambda x, y: x >= y, 0)
        
    #Check if all values are true
    def all(self):
        return all(self.values())

    #Checks if any vfalues are true
    def any(self):
        return any(self.values())

    #Filter function
    def filter(self, f=None):
        return AD({k: v for k, v in self.items() if (f(v) if f is not None else v)})

    @staticmethod
    def _binary_op(left, right, op, neutral):
        r = AD()
        l_keys = set(left.keys()) if isinstance(left, dict) else set()
        r_keys = set(right.keys()) if isinstance(right, dict) else set()
        for k in l_keys | r_keys:
            # If the right (or left) element is a dictionary (or an AD),
            # we get the elements from the dictionary; else we use the right
            # or left value itself.  This implements a sort of dictionary
            # broadcasting.
            l_val = left.get(k, neutral) if isinstance(left, dict) else left
            r_val = right.get(k, neutral) if isinstance(right, dict) else right
            r[k] = op(l_val, r_val)
        return r

    @property
    def max_items(self):
        """Returns a pair consisting of the max value in the AD, and of the
        set of keys that attain that value."""
        if len(self) == 0:
            return (None, set())
        largest = 0
        a = set()
        for key in self:
            if  (self[key] > largest):
                largest = self[key]
        for key in self:
            if (self[key] == largest):
                a.add(key)
        return(largest, a)
"""
#Tests if two elements are equal
def check_equal(x, y, msg=None):
    if x != y:
        if msg is None:
            print("Error:")
        else:
            print("Error in", msg, ":")
        print("    Your answer was:", x)
        print("    Correct answer: ", y)
    else:
        print("Success!")
    assert x == y, "%r and %r are different" % (x, y)

# Addition and subtraction tests
print(AD(red=2, green=3) + AD(red=1, blue=4))
print(AD(red=2, green=3) - AD(red=1, blue=4))

# Multiplication Tests
d = AD(a=2, b=3) * AD(b=4, c=5)
check_equal(d, AD(a=2, b=12, c=5))

# Division Tests
d = AD(a=8, b=6) / AD(a=2, c=4)
check_equal(d, AD(a=4, b=6, c=0.25))

# Integer Division Tests
d = AD(a=8, b=6) // AD(a=2, b=4, c=4)
check_equal(d, AD(a=4, b=1, c=0))

# Tests for max items`

# For empty ADs, it has to return None as value, and the empty set as key set.
check_equal(AD().max_items, (None, set()))
# Case of one maximum.
check_equal(AD(red=2, green=3, blue=1).max_items, (3, {'green'}))
# Case of multiple maxima.
check_equal(AD(red=2, yellow=3, blue=3, violet=3, pink=1).max_items,
             (3, {'yellow', 'blue', 'violet'}))

#Tests Inequalities
print(AD(red=4, bird=2) > 2)

#Tests Filters
d = AD(green=3, blue=2, red=1)
print("Expected output: {'blue': 2, 'green': 3}")
print(d.filter(lambda x : x > 1))

d = AD(green=3, blue=2, red=1)
print("Expected output: {'blue': True, 'green': True}")
print((d > 1).filter())

print("Expected output: False")
print((d > 1).all())

print("Expected output: True")
print((d > 0).all())    
"""