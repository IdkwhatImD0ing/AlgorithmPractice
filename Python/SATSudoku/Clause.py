class Clause(object):

    def __init__(self, clause):
        """Initializes a clause.  Here, the input clause is either a list or set
        of integers, or is an instance of Clause; in the latter case, a shallow
        copy is made, so that one can modify this clause without modifying the
        original clause.
        Store the list of literals as a frozenset."""
        if isinstance(clause, Clause):
            # We use frozenset here, so that clauses are not modifiable.
            # This ensures that two equal clauses always have the same hash,
            # due also to our definition of the __hash__ method.
            self.literals = frozenset(clause.literals)
        else:
            for i in clause:
                # Sanity check.
                assert isinstance(i, int), "Not an integer: %r" % i
            self.literals = frozenset(clause)

    def __repr__(self):
        return repr(self.literals)

    def __eq__(self, other):
        return self.literals == other.literals

    def __hash__(self):
        """This will be used to be able to have sets of clauses,
        with clause equality defined on the equality of their literal sets."""
        return hash(self.literals)

    def __len__(self):
        return len(self.literals)

    @property
    def istrue(self):
        """A clause is true if it contains both a predicate and its complement."""
        return has_pos_and_neg(self.literals)

    @property
    def isfalse(self):
        """A clause is false if and only if it is empty."""
        return len(self.literals) == 0

    def simplify(self, i):
        """Computes the result simplify the clause according to the
        truth assignment i."""
        if i in self.literals:
            return True
        if -i in self.literals:
            return Clause(self.literals - {-i})
        return self

def has_pos_and_neg(l):
    return len(set(l)) > len({abs(x) for x in l})