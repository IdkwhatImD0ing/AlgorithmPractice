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

    def apply_assignment(self, assignment):
        """Applies the assignment to every clause, simplifying it.
        If a clause is false, the whole problem is unsatisfiable,
        and we return False.  If a clause is True, it does not need
        to be included."""

        newClauses = set()
        for x in self.clauses:
            if (x.istrue or (isinstance(x.simplify(assignment),bool) and x.simplify(assignment)== True)): # If clause is true or simpplify is true
                continue
            elif (x.isfalse): # If Clause is false return false
                return False
            else:
                newClauses.add(x.simplify(assignment)) # Else include the simplified clause
        return SAT(newClauses) # Create new SAT

    def solve(self):
        """Solves a SAT instance.
        First, it checks whether the instance is false (in which case
        it returns False) or true (in which case it returns an empty
        assignment).
        If neither of these applies, generates a list of candidate
        assignments, and for each of them, applies them to the current SAT
        instance, generating a new SAT instance, and solves it.
        If the new SAT instance has a solution, merges it with the assignment,
        and returns it.  If it has no solution, tries the next candidate
        assignment.  If no candidate assignment works, returns False, as
        the SAT problem cannot be satisfied."""
        # Answer based on TA's given pseudocode
        answer = set()
        def recursive(self):
            if (self.isfalse):
                return False
            elif (self.istrue):
                return set()
            newAssignments = self.generate_candidate_assignments()
            for x in newAssignments:
                a = self.apply_assignment(x)
                answer.add(x)
                return(recursive(self.apply_assignment(x)))

        if(recursive(self) != False):
            return(answer)
        return False

    def verify_assignment(self, assignment):
        assert not has_pos_and_neg(assignment), "The assignment is inconsistent"
        s = self
        for i in assignment:
            s = s.apply_assignment(i)
            if s.istrue:
                return True
            if s.isfalse:
                return False
        return False

def has_pos_and_neg(l):
    return len(set(l)) > len({abs(x) for x in l})