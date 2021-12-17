from ArithmeticDictionary import AD
from collections import defaultdict
import numpy as np

class BoW(AD):

    def __init__(self, text):
        super().__init__()
        self.ad = AD()
        if text is not None:
            for w in text.split():
                self.ad += AD({w: 1})
        self.update(self.ad)



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

empty_bow = BoW("")
check_equal(len(empty_bow), 0)

simple_bow = BoW("I like apples")
check_equal(isinstance(simple_bow, AD), True)
check_equal(set(simple_bow.keys()), {'I', 'like', 'apples'})

bow1 = BoW("I like to eat cakes to go")
bow2 = BoW("I like to drink coffee")
bow3 = bow1 + bow2
check_equal(bow3['I'], 2)
check_equal(bow3['to'], 3)

