class SockDrawer(object):

    def __init__(self):
        self.drawer = []

    def add_sock(self, color):
        """Adds a sock of the given color to the drawer."""
        self.drawer.append(color)

    def get_pair(self, color):
        """Returns False if there is no pair of the given color, and True
        if there is.  In the latter case, it removes the pair from the drawer."""
        if self.drawer.count(color) >= 2:
            self.drawer.remove(color)
            self.drawer.remove(color)
            return True
        else:
            return False

    @property
    def available_colors(self):
        """Lists the colors for which we have at least two socks available."""
        colors = set()
        for el in self.drawer:
            if self.drawer.count(el) >= 2:
                colors.add(el)
        return colors
        
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

test_drawer(SockDrawer)
