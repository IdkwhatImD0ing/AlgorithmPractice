import numpy as np

class SudokuViaSAT(object):

    def __init__(self, sudoku_string):
        """
        @param sudoku_string: an 81-long digit string: 0 represents an unknown
            digit, and 1..9 represent the respective digit.
        """
        assert len(sudoku_string) > 80
        self.board = np.zeros((9, 9), dtype=np.uint8)
        for i in range(9):
            for j in range(9):
                self.board[i, j] = int(sudoku_string[i * 9 + j])
        self.sat = None # This will be the SAT instance.
        # Perform here any other initialization you think you need.
        # YOUR CODE HERE

    def show(self):
        """Prints out the board."""
        print("+---+---+---+")
        for i in range(9):
            r = '|'
            for j in range(9):
                r += "." if self.board[i, j] == 0 else str(self.board[i, j])
                if (j + 1) % 3 == 0:
                    r += "|"
            print(r)
            if (i + 1) % 3 == 0:
                print("+---+---+---+")

    def _board_to_SAT(self):
        """Translates the currently known state of the board into a list of SAT
        clauses.  Each clause has only one literal, and expresses the fact that a
        given digit is in a given position.  The method returns the list of clauses
        corresponding to all the initially known Sudoku digits."""
        
        list = []
        for i in range(9):
            for j in range(9):
                d = self.board[i][j]
                if (d != 0):
                    clause = []
                    clause.append(encode_variable(d,i,j))
                    list.append(clause)
        return list

    def _to_SAT(self):
        return list(sudoku_rules()) + list(self._board_to_SAT())

    def solve(self, Solver):
        """Solves the Sudoku instance using the given SAT solver
        (e.g., Glucose3, Minisat22).
        @param Solver: a solver, such as Glucose3, Minisat22.
        @returns: False, if the Sudoku problem is not solvable, and True, if it is.
            In the latter case, the solve method also completes self.board,
            using the solution of SAT to complete the board."""
        ps = None
        with Solver() as g:
            sd = SudokuViaSAT(problem)
            for c in sd._to_SAT():
                g.add_clause(c)
            if (g.solve() == False):
                return False
            # Let's get a truth assignment.
            ps = g.get_model()
            for l in ps:
                if l > 0 and decode_variable(l) is not None:
                    d,i,j = decode_variable(l)
                    self.board[i][j] = d
            return True


# Helper functions

def encode_variable(d, i, j):
    """This function creates the variable (the integer) representing the
    fact that digit d appears in position i, j.
    Of course, to obtain the complement variable, you can just negate
    (take the negative) of the returned integer.
    Note that it must be: 1 <= d <= 9, 0 <= i <= 8, 0 <= j <= 8."""
    assert 1 <= d <= 9
    assert 0 <= i < 9
    assert 0 <= j < 9
    # The int() below seems useless, but it is not.  If d is a numpy.uint8,
    # as an element of the board is, this int() ensures that the generated
    # literal is a normal Python integer, as the SAT solvers expect.
    return int(d * 100 + i * 10 + j)

def decode_variable(p):
    """Given an integer constructed as by _create_prediate above,
    returns the tuple (d, i, j), where d is the digit, and i, j are
    the cells where the digit is.  Returns None if the integer is out of
    range.
    Note that it must be: 1 <= d <= 9, 0 <= i <= 8, 0 <= j <= 8.
    If this does not hold, return None.
    Also return None if p is not in the range from 100, to 988 (the
    highest and lowest values that p can assume)."""
    if (p > 998 or p < 100):
        return None
    d = p // 100
    i = (p - d*100) // 10
    j = (p - d*100 - i*10)
    return int(d,i,j)

def every_cell_contains_at_least_one_digit():
    """Returns a list of clauses, stating that every cell must contain
    at least one digit."""
    list = []
    for i in range(9):
        for j in range(9):
            clause = []
            for x in range(10):
                if (x != 0):
                    clause.append(encode_variable(x,i,j))
            list.append(clause)
    return list 

def every_cell_contains_at_most_one_digit():
    """Returns a list of clauses, stating that every cell contains
    at most one digit."""
    list = []
    for i in range(9):
        for j in range(9):
            for x in range(10):
                for y in range (10):
                    if (x != 0 and y != 0 and x != y):
                        clause = []
                        clause.append(-encode_variable(x,i,j))
                        clause.append(-encode_variable(y,i,j))
                        list.append(clause)
    return list

def no_identical_digits_in_same_row():
    """Returns a list of clauses, stating that if a digit appears
    in a cell, the same digit cannot appear elsewhere in the
    same row, column, or 3x3 square."""
    list = []
    for i in range(9): # For Every row
        for x in range(10): #for numbers 1-9 inclusive
            if (x != 0):
                for j in range(9):
                    for jd in range(9):
                        if (j != jd):
                            clause = []
                            clause.append(-encode_variable(x,i,j))
                            clause.append(-encode_variable(x,i,jd))
                            list.append(clause)
    return list

def no_identical_digits_in_same_block():
    """Returns a list of clauses, stating that if a digit appears
    in a cell, the same digit cannot appear elsewhere in the
    same row, column, or 3x3 square."""
    bigi = 0
    bigj = 0
    list = []
    for big in range(9):# The 9 big boxes
        if (bigj > 2):
            bigj = 0
            bigi += 1

        for x in range(10): # 9 numbers
            if (x != 0):# dont do for number 0
                smalli = 0
                smallj = 0
                for small in range(9): # for each box in the the small 9 boxes
                    if (smallj > 2):
                            smallj = 0
                            smalli += 1

                    smallid = 0
                    smalljd = 0
                    for smalld in range(9): # gotta propagate to other boxes EXCEPT the current box
                        if (smalljd > 2):
                            smalljd = 0
                            smallid += 1
                        
                        if (smalli != smallid or smallj != smalljd): # all 8 boxes except originating box
                            clauses = []
                            clauses.append(-encode_variable(x,smalli + (bigi * 3),smallj + (bigj * 3)))
                            clauses.append(-encode_variable(x,smallid + (bigi * 3),smalljd + (bigj * 3)))
                            list.append(clauses)
                        
                        smalljd += 1


                    smallj += 1
        bigj +=1


    return list

# Rules for sudoku
def sudoku_rules():
    clauses = []
    clauses.extend(every_cell_contains_at_least_one_digit())
    clauses.extend(every_cell_contains_at_most_one_digit())
    clauses.extend(no_identical_digits_in_same_row())
    clauses.extend(no_identical_digits_in_same_column())
    clauses.extend(no_identical_digits_in_same_block())
    return clauses

