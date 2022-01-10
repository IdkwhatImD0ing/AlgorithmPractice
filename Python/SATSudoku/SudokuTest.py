from SudokuViaSat import SudokuViaSAT
import pysat
from pysat.solvers import Glucose3

def check_equal(x, y, msg=None):
    if x != y:
        if msg is None:
            print("Error:")
        else:
            print("Error in", msg, ":")
        print("    Your answer was:", x)
        print("    Correct answer: ", y)
    assert x == y, "%r and %r are different" % (x, y)

problem = "000000061350000000400050000020000800000601000000700000000080200600400000007000010"
sd = SudokuViaSAT(problem)
sd.show()

# Testing cell code

def prepare(g):
    for c in every_cell_contains_at_least_one_digit():
        g.add_clause(c)

with Glucose3() as g:
    prepare(g)
    # This can be solved.
    check_equal(g.solve(), True)
    for d in range(1, 10):
        # These clauses state that no digit appears at 4, 5.
        # You can change the coordinates if you like.
        g.add_clause([-encode_variable(d, 4, 5)])
    check_equal(g.solve(), False)

def prepare(g):
    for c in every_cell_contains_at_most_one_digit():
        g.add_clause(c)

with Glucose3() as g:
    prepare(g)
    check_equal(g.solve(), True)
    # This states that both 3 and 4 appear at position 6, 7.
    g.add_clause([encode_variable(3, 6, 7)])
    g.add_clause([encode_variable(4, 6, 7)])
    check_equal(g.solve(), False)

def prepare(g):
    for c in no_identical_digits_in_same_column():
        g.add_clause(c)

with Glucose3() as g:
    prepare(g)
    check_equal(g.solve(), True)
    # This states that 3 appears twice in column 7.
    g.add_clause([encode_variable(3, 5, 7)])
    g.add_clause([encode_variable(3, 2, 7)])
    check_equal(g.solve(), False)

# But rows are not forbidden.
with Glucose3() as g:
    prepare(g)
    g.add_clause([encode_variable(3, 5, 7)])
    g.add_clause([encode_variable(3, 5, 8)])
    check_equal(g.solve(), True)

def prepare(g):
    for c in no_identical_digits_in_same_block():
        g.add_clause(c)

with Glucose3() as g:
    prepare(g)
    check_equal(g.solve(), True)
    # This states that 3 appears twice in top block
    g.add_clause([encode_variable(3, 1, 1)])
    g.add_clause([encode_variable(3, 1, 2)])
    check_equal(g.solve(), False)

# One more test.
with Glucose3() as g:
    prepare(g)
    g.add_clause([encode_variable(3, 1, 1)])
    g.add_clause([encode_variable(3, 2, 1)])
    check_equal(g.solve(), False)

# But different blocks are not forbidden.
with Glucose3() as g:
    prepare(g)
    g.add_clause([encode_variable(3, 1, 1)])
    g.add_clause([encode_variable(3, 5, 8)])
    check_equal(g.solve(), True)

# Creating a sudoku problem
with Glucose3() as g:
    for c in sudoku_rules():
        g.add_clause(c)
    check_equal(g.solve(), True)


problem = "000000061350000000400050000020000800000601000000700000000080200600400000007000010"
sd = SudokuViaSAT(problem)
sd.show()
clauses = sd._board_to_SAT()
check_equal(len(clauses), 17)
check_equal([310] in clauses, True)
check_equal([511] in clauses, True)
check_equal([224] in clauses, False)

# This should print the elements of the board.
for c in sd._board_to_SAT():
    print(c)

# Actualling solving in instance of Sudoku
problem = "000000061350000000400050000020000800000601000000700000000080200600400000007000010"
sd = SudokuViaSAT(problem)
with Glucose3() as g:
    for c in sd._to_SAT():
        g.add_clause(c)
    check_equal(g.solve(), True)

problem = "000000061350000000404050000020000800000601000000700000000080200600400000007000010"
sd = SudokuViaSAT(problem)
with Glucose3() as g:
    for c in sd._to_SAT():
        for j in c:
            g.add_clause(c)
    check_equal(g.solve(), False)

#Solving a sudoku problem
problem = "000000061350000000400050000020000800000601000000700000000080200600400000007000010"
sd = SudokuViaSAT(problem)
sd.show()
sd.solve(Glucose3)
sd.show()

def verify_solution(Solver, sudoku_string):
    sd = SudokuViaSAT(sudoku_string)
    sd.show()
    sd.solve(Solver)
    sd.show()
    # Check that we leave alone the original assignment.
    for i in range(9):
        for j in range(9):
            d = int(sudoku_string[i * 9 + j])
            if d > 0:
                assert sd.board[i, j] == d
    # Check that there is a digit in every cell.
    for i in range(9):
        for j in range(9):
            assert 1 <= sd.board[i, j] <= 9
    # Check the exclusion rules of Sudoku.
    for i in range(9):
        for j in range(9):
            # No repetition in row.
            for ii in range(i + 1, 9):
                assert sd.board[i, j] != sd.board[ii, j]
            # No repetition in column.
            for jj in range(j + 1, 9):
                assert sd.board[i, j] != sd.board[i, jj]
            # No repetition in block
            ci, cj = i // 3, j // 3
            for bi in range(2):
                ii = ci * 3 + bi
                for bj in range(2):
                    jj = cj * 3 + bj
                    if i != ii or j != jj:
                        assert sd.board[i, j] != sd.board[ii, jj]

verify_solution(Glucose3, problem)

# Solving first 100 puzzles
import requests

r = requests.get("https://raw.githubusercontent.com/shadaj/sudoku/master/sudoku17.txt")
puzzles = r.text.split()

for problem in puzzles[:100]:
    verify_solution(Glucose3, problem)