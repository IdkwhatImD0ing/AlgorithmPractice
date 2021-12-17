from collections import defaultdict

class SmartDrawer(object):

    def __init__(self):
        self.socks = defaultdict(int)

    def add_sock(self, color):
        self.socks[color] += 1

    def get_pair(self, color):
        if self.socks[color] > 1:
            self.socks[color] -= 2
            return True
        else:
            return False

    @property
    def available_colors(self):
        return {c for c, n in self.socks.items() if n > 1}


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

def test_drawer(c):
    """Tests a drawer class c."""
    d = c()
    d.add_sock('red')
    d.add_sock('red')
    d.add_sock('red')
    d.add_sock('green')
    check_equal(d.available_colors, {'red'})
    check_equal(d.get_pair('red'), True)
    check_equal(d.get_pair('green'), False)
    check_equal(d.get_pair('red'), False)
    d.add_sock('blue')
    d.add_sock('blue')
    d.add_sock('blue')
    d.add_sock('red')
    check_equal(d.available_colors, {'red', 'blue'})

test_drawer(SmartDrawer)