import json

class Sudoku(object):

    def __init__(self, elements):
        """Elements can be one of:
        Case 1: a list of 9 strings of length 9 each.
        Each string represents a row of the initial Sudoku puzzle,
        with either a digit 1..9 in it, or with a blank or _ to signify
        a blank cell.
        Case 2: an instance of Sudoku.  In that case, we initialize an
        object to be equal (a copy) of the one in elements.
        Case 3: a list of list of sets, used to initialize the problem."""
        if isinstance(elements, Sudoku):
            # We let self.m consist of copies of each set in elements.m
            self.m = [[x.copy() for x in row] for row in elements.m]
        else:
            assert len(elements) == 9
            for s in elements:
                assert len(s) == 9
            # We let self.m be our Sudoku problem, a 9x9 matrix of sets.
            self.m = []
            for s in elements:
                row = []
                for c in s:
                    if isinstance(c, str):
                        if c.isdigit():
                            row.append({int(c)})
                        else:
                            row.append({1, 2, 3, 4, 5, 6, 7, 8, 9})
                    else:
                        assert isinstance(c, set)
                        row.append(c)
                self.m.append(row)


    def show(self, details=False):
        """Prints out the Sudoku matrix.  If details=False, we print out
        the digits only for cells that have singleton sets (where only
        one digit can fit).  If details=True, for each cell, we display the
        sets associated with the cell."""
        if details:
            print("+-----------------------------+-----------------------------+-----------------------------+")
            for i in range(9):
                r = '|'
                for j in range(9):
                    # We represent the set {2, 3, 5} via _23_5____
                    s = ''
                    for k in range(1, 10):
                        s += str(k) if k in self.m[i][j] else '_'
                    r += s
                    r += '|' if (j + 1) % 3 == 0 else ' '
                print(r)
                if (i + 1) % 3 == 0:
                    print("+-----------------------------+-----------------------------+-----------------------------+")
        else:
            print("+---+---+---+")
            for i in range(9):
                r = '|'
                for j in range(9):
                    if len(self.m[i][j]) == 1:
                        r += str(getel(self.m[i][j]))
                    else:
                        r += "."
                    if (j + 1) % 3 == 0:
                        r += "|"
                print(r)
                if (i + 1) % 3 == 0:
                    print("+---+---+---+")


    def to_string(self):
        """This method is useful for producing a representation that
        can be used in testing."""
        as_lists = [[list(self.m[i][j]) for j in range(9)] for i in range(9)]
        return json.dumps(as_lists)


    @staticmethod
    def from_string(s):
        """Inverse of above."""
        as_lists = json.loads(s)
        as_sets = [[set(el) for el in row] for row in as_lists]
        return Sudoku(as_sets)


    def __eq__(self, other):
        """Useful for testing."""
        return self.m == other.m
    
    def ruleout(self, i, j, x):
        """The input consists in a cell (i, j), and a value x.
        The function removes x from the set self.m[i][j] at the cell, if present, and:
        - if the result is empty, raises Unsolvable;
        - if the cell used to be a non-singleton cell and is now a singleton
        cell, then returns the set {(i, j)};
        - otherwise, returns the empty set."""
        c = self.m[i][j]
        n = len(c)
        c.discard(x)
        self.m[i][j] = c
        if len(c) == 0:
            raise Unsolvable()
        return {(i, j)} if 1 == len(c) < n else set()

    def propagate_cell(self, ij):
        """Propagates the singleton value at cell (i, j), returning the list
        of newly-singleton cells."""
        i, j = ij
        if (len(self.m[i][j])) > 1:
            # Nothing to propagate from cell (i,j).
            return set()
        # We keep track of the newly-singleton cells.
        newly_singleton = set()
        x = getel(self.m[i][j]) # Value at (i, j).
        # Same row.
        for jj in range(9):
            if jj != j: # Do not propagate to the element itself.
                newly_singleton.update(self.ruleout(i, jj, x))
        # Same column.
        for ii in range(9):
            if ii != i:
                newly_singleton.update(self.ruleout(ii, j, x))
        # Same block of 3x3 cells.
        # i is rows
        # j is columns
        length = j%3 #Dividing column by 3 shows how many columns away from side
        height = i%3 #Diving row by 3 shows how many rows away from top most of 3x3 Box
        #print(" i " + str(i) + " j " + str(j) + " number " + str(self.m[i][j]) + " length " + str(length))
        if (length == 0):
            for k in range(3):
                if (k != 0):
                    newly_singleton.update(self.ruleout(i, j+k, x))
            if (height == 0):
                for k in range(3):
                    newly_singleton.update(self.ruleout(i+1, j+k, x))
                    newly_singleton.update(self.ruleout(i+2, j+k, x))
            if (height == 1):
                for k in range(3):
                    newly_singleton.update(self.ruleout(i+1, j+k, x))
                    newly_singleton.update(self.ruleout(i-1, j+k, x))
            if (height == 2):
                for k in range(3):
                    newly_singleton.update(self.ruleout(i-1, j+k, x))
                    newly_singleton.update(self.ruleout(i-2, j+k, x))
            #print("Passed1")

        
        elif (length == 1):
            newly_singleton.update(self.ruleout(i, j+1, x))
            newly_singleton.update(self.ruleout(i, j-1, x))
            if (height == 0):
                newly_singleton.update(self.ruleout(i+1, j+1, x))
                newly_singleton.update(self.ruleout(i+1, j-1, x))
                newly_singleton.update(self.ruleout(i+2, j+1, x))
                newly_singleton.update(self.ruleout(i+2, j-1, x))

            if (height == 1):
                newly_singleton.update(self.ruleout(i+1, j+1, x))
                newly_singleton.update(self.ruleout(i+1, j-1, x))
                newly_singleton.update(self.ruleout(i-1, j+1, x))
                newly_singleton.update(self.ruleout(i-1, j-1, x))
            if (height == 2):
                newly_singleton.update(self.ruleout(i-1, j+1, x))
                newly_singleton.update(self.ruleout(i-1, j-1, x))
                newly_singleton.update(self.ruleout(i-2, j+1, x))
                newly_singleton.update(self.ruleout(i-2, j-1, x))
            #print("Passed2")


        elif (length == 2):
            for k in range(3):
                if (k != 0):
                    newly_singleton.update(self.ruleout(i, j-k, x))
            if (height == 0):
                for k in range(3):
                    newly_singleton.update(self.ruleout(i+1, j-k, x))
                    newly_singleton.update(self.ruleout(i+2, j-k, x))
            if (height == 1):
                for k in range(3):
                    newly_singleton.update(self.ruleout(i+1, j-k, x))
                    newly_singleton.update(self.ruleout(i-1, j-k, x))
            if (height == 2):
                for k in range(3):
                    newly_singleton.update(self.ruleout(i-1, j-k, x))
                    newly_singleton.update(self.ruleout(i-2, j-k, x))
            #print("Passed3")
            
        # Returns the list of newly-singleton cells.
        #print(newly_singleton)
        return newly_singleton

    def propagate_all_cells_once(self):
        """This function propagates the constraints from all singletons."""
        for i in range(9):
            for j in range(9):
                self.propagate_cell((i, j))

    def full_propagation(self, to_propagate=None):
        """Iteratively propagates from all singleton cells, and from all
        newly discovered singleton cells, until no more propagation is possible.
        @param to_propagate: sets of cells from where to propagate.  If None, propagates
            from all singleton cells. 
        @return: nothing.
        """
        if to_propagate is None:
            to_propagate = {(i, j) for i in range(9) for j in range(9)}        
        while (len(to_propagate) != 0):
            a = to_propagate.pop()
            b = self.propagate_cell(a)
            to_propagate = to_propagate.union(b)

    def done(self):
        """Checks whether an instance of Sudoku is solved."""
        for i in range(9):
            for j in range(9):
                if len(self.m[i][j]) > 1:
                    return False
        return True

    def search(self, new_cell=None):
        """Tries to solve a Sudoku instance."""
        to_propagate = None if new_cell is None else {new_cell}
        self.full_propagation(to_propagate=to_propagate)
        if self.done():
            return self # We are a solution
        # We need to search.  Picks a cell with as few candidates as possible.
        candidates = [(len(self.m[i][j]), i, j)
                    for i in range(9) for j in range(9) if len(self.m[i][j]) > 1]
        _, i, j = min(candidates)
        values = self.m[i][j]
        # values contains the list of values we need to try for cell i, j.
        # print("Searching values", values, "for cell", i, j)
        for x in values:
            # print("Trying value", x)
            sd = Sudoku(self)
            sd.m[i][j] = {x}
            try:
                # If we find a solution, we return it.
                return sd.search(new_cell=(i, j))
            except Unsolvable:
                # Go to next value.
                pass
        # All values have been tried, apparently with no success.
        raise Unsolvable()

    def betterSearch(self, new_cell=None):
        """Tries to solve a Sudoku instance. Better than search() by using where can it go algorithm"""
        to_propagate = None if new_cell is None else {new_cell}
        self.full_propagation_with_where_can_it_go(to_propagate=to_propagate)
        if self.done():
            return self # We are a solution
        # We need to search.  Picks a cell with as few candidates as possible.
        candidates = [(len(self.m[i][j]), i, j)
                    for i in range(9) for j in range(9) if len(self.m[i][j]) > 1]
        _, i, j = min(candidates)
        values = self.m[i][j]
        # values contains the list of values we need to try for cell i, j.
        # print("Searching values", values, "for cell", i, j)
        for x in values:
            # print("Trying value", x)
            sd = Sudoku(self)
            sd.m[i][j] = {x}
            try:
                # If we find a solution, we return it.
                return sd.search(new_cell=(i, j))
            except Unsolvable:
                # Go to next value.
                pass
        # All values have been tried, apparently with no success.
        raise Unsolvable()

    def solve(self, do_print=True):
        """Wrapper function, calls self and shows the solution if any."""
        try:
            r = self.betterSearch() 
            if do_print:
                print("We found a solution:")
                r.show()
                return r
        except Unsolvable:
            if do_print:
                print("The problem has no solutions")

    def where_can_it_go(self):
        """Sets some cell values according to the where can it go
        heuristics, by examining all rows, colums, and blocks."""
        newly_singleton = set()

        #all rows
        for i in range(9):
            a = occurs_once_in_sets(self.m[i])
            if (len(a) != 0):
                for y in a:
                    for j in range(9):
                        if (y in self.m[i][j] and len(self.m[i][j]) > 1):
                            newly_singleton.add((i,j))
                            self.m[i][j] = set()
                            self.m[i][j].add(y)
        #all Columns

        for j in range(9):
            a = []
            for i in range(9):
                a.append(self.m[i][j])
                b = occurs_once_in_sets(a)

            if (len(b) != 0):
                for y in b:
                    for i in range(9):
                        if (y in self.m[i][j] and len(self.m[i][j]) > 1):
                            newly_singleton.add((i,j))
                            self.m[i][j] = set()
                            self.m[i][j].add(y)

        #all boxes
        ii = 0
        jj = 0
        for x in range(9):
            a = []
            i = 0
            j = 0
            
            if (jj > 8):
                ii += 3
                jj = 0
            for y in range(9):
                if (j > 2):
                    j = 0
                    i += 1
                a.append(self.m[i+ii][j+jj])
                j += 1
            b = occurs_once_in_sets(a)
            if (len(b) != 0):
                for k in b:
                    i = 0
                    j = 0
                    for z in range(9):
                        if (j > 2):
                            j = 0
                            i += 1
                        if (k in self.m[i+ii][j+jj] and len(self.m[i+ii][j+jj]) > 1):
                            newly_singleton.add((i+ii,j+jj))
                            self.m[i+ii][j+jj] = set()
                            self.m[i+ii][j+jj].add(k)
                        j += 1
            jj += 3


        # Returns the list of newly-singleton cells.
        return newly_singleton

    def full_propagation_with_where_can_it_go(self, to_propagate=None):
        """Iteratively propagates from all singleton cells, and from all
        newly discovered singleton cells, until no more propagation is possible."""
        if to_propagate is None:
            to_propagate = {(i, j) for i in range(9) for j in range(9)}
        while len(to_propagate) > 0:
            # Full propagation code
            while (len(to_propagate) > 0):
                a = to_propagate.pop()
                b = self.propagate_cell(a)
                to_propagate = to_propagate.union(b)
            # Now we check whether there is any other propagation that we can
            # get from the where can it go rule.
            to_propagate = self.where_can_it_go()

# Helper Functions
def getel(s):
    """Returns the unique element in a singleton set (or list)."""
    assert len(s) == 1
    return list(s)[0]

def occurs_once_in_sets(set_sequence):
    """Returns the elements that occur only once in the sequence of sets set_sequence.
    The elements are returned as a set."""
    occuronce = set()
    deleted = set()
    for setx in set_sequence:
        for sety in setx:
            if (sety in occuronce):
                deleted.add(sety)
                occuronce.remove(sety)
            elif (sety not in deleted):
                occuronce.add(sety)
    return occuronce

# Unique Exception, means Sudoku is unsolvable
class Unsolvable(Exception):
    pass