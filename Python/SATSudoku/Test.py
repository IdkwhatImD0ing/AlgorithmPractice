from Clause import Clause
from Sat import SAT

from nose.tools import assert_equal, assert_almost_equal
from nose.tools import assert_true, assert_false
from nose.tools import assert_not_equal

# Tests for Clause.
c = Clause([2, -3, 4])
d = Clause([-3, 2, 4])
e = Clause(c)
assert_equal(c, d)
assert_equal(c, e)

c = Clause([2, 3, 5])
assert_false(c.istrue)
assert_false(c.isfalse)

c = Clause([-2, 5, 2])
assert_true(c.istrue)
assert_false(c.isfalse)

c = Clause([])
assert_false(c.istrue)
assert_true(c.isfalse)

# Simplify Tests
c = Clause([1, 2, -3, 4])
assert_equal(c.simplify(1), True)

c = Clause([1, 2, -3, 4])
# If we assign False to 1 and True to 3, p_1 and p_3 are not useful
# any more to make the clause true.
assert_equal(c.simplify(-4), Clause([1, 2, -3]))

c = Clause([1, 2, -3, 4])
# Left unchanged.
assert_equal(c.simplify(12), c)

# Tests for is_true

s = SAT([[-1,-2,3],[2,-3],[1,-4,2,1]])
assert_false(s.istrue)
s = SAT([])
assert_true(s.istrue)

# Tests for is_false

s = SAT([[-1,-2,3],[2,-3],[1,-4,2,1]])
assert_false(s.isfalse)
s = SAT([])
assert_false(s.isfalse)
s = SAT([[],[2,-3],[1,-4,2,1]])
assert_true(s.isfalse)

# Tests for `generate_candidate_assignments`

s = SAT([[-1,-2,3],[2,-3],[1,-4,2,1]])
assert_equal(set(s.generate_candidate_assignments()), {2, -3})

# Tests for `apply_assignment`

# First, examples in which each clause is simplified and is part of the
# new SAT problem.
s = SAT([[-1, -2, 3], [2, -3], [5, -4, 2, 10]])
t = s.apply_assignment(1)
print(t)
assert_equal(t, SAT([[-2, 3], [2, -3], [5, -4, 2, 10]]))

s = SAT([[2, 3], [4, 2, -3], [2]])
t = s.apply_assignment(-2)
assert_equal(t, SAT([[3], [4, -3], []]))


# More tests for `apply_assignment`

# Second, an example in which some clauses are made True, and hence removed
# from the new SAT problem.
s = SAT([[-1, -2, 3], [2, -3], [5, -4, 2, 10]])
t = s.apply_assignment(-1)
assert_equal(t, SAT([[2, -3], [5, -4, 2, 10]]))

s = SAT([[2, 3, -4], [-1, -3, 5], [-3]])
t = s.apply_assignment(3)
assert_equal(t, SAT([[-1, 5], []]))

# Some solvable problems

s = SAT([[1, 2], [-2, 2, 3], [-3, -2]])
a = s.solve()
print("Assignment:", a)
assert_true(s.verify_assignment(a))

s = SAT([[1, 2], [-2, 3], [-3, 4], [-4, 5], [8, -1]])
a = s.solve()
print("Assignment:", a)
assert_true(s.verify_assignment(a))


s = SAT([[-1, 2], [-2, 3], [-3, 1]])
a = s.solve()
print("Assignment:", a)
assert_true(s.verify_assignment(a))

# Unsolvable problems

s = SAT([[1], [-1, 2], [-2]])
assert_false(s.solve())

s = SAT([[-1, 2], [-2, 3], [-3, -1], [1]])
assert_false(s.solve())

s = SAT([[-1, 2], [-2, 3], [-3, -1], [1], [-4, -3, -2]])
assert_false(s.solve())
