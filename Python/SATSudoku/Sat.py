from Clause import Clause

class SAT(object):

    def __init__(self, clause_list):
        """clause_list is a list of lists (or better, an iterable of
        iterables), to represent a list or set of clauses."""
        raw_clauses = {Clause(c) for c in clause_list}
        # We do some initial sanity checking.
        # If a clause is empty, then it
        # cannot be satisfied, and the entire problem is False.
        # If a clause is true, it can be dropped.
        self.clauses = set()
        for c in raw_clauses:
            if c.isfalse:
                # Unsatisfiable.
                self.clauses = {c}
                break
            elif c.istrue:
                pass
            else:
                self.clauses.add(c)

    def __repr__(self):
        return repr(self.clauses)

    def __eq__(self, other):
        return self.clauses == other.clauses

    @property
    def istrue(self):
        if len(self.clauses) == 0:
            return True
        return False

    @property
    def isfalse(self):
        for x in self.clauses:
            if x.isfalse:
                return True
        return False

    def generate_candidate_assignments(self):
        """Generates candidate assignments.
        If the SAT problem contains unary clauses (clauses with only
        one literal), then it returns a list of one candidate assignment,
        with the one candidate assignment consisting in the union of
        all the unary clauses.
        If the SAT problem does not contain any unary clause, then picks
        one of its shortest clauses, and return as candidate assignments
        a list of sets, one for each of the literals of the chosen clause."""
        minLength = 10000000000000000
        for x in self.clauses:
            if len(x) < minLength:
                minLength = len(x)

        for x in self.clauses:
            if len(x) == minLength:
                return set(x.literals)