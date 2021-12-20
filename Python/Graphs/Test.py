from Graph import Graph
from nose.tools import assert_equal, assert_true
from nose.tools import assert_false, assert_almost_equal
import random

vertices = list('abcdefghilmnopqrstuvz')

def random_vertices():
    """Returns a set of random vertices."""
    return set(random.choices(vertices, k=12))

def random_edges(vs):
    """Returns a set of random edges, given a set of vertices."""
    vxv = [(u, v) for u in vs for v in vs]
    return set(random.choices(vxv, k=min(len(vxv), 50)))

def random_graph():
    vs = random_vertices()
    e = random_edges(vs)
    return Graph(vertices=vs, edges=e)

# Creating random graphs

for _ in range(100):
    g = Graph()
    vs = random_vertices()
    es = random_edges(vs)
    for e in es:
        g.add_edge(e)

# Graph does not depend on order of adding vertices and edges
for _ in range(100):
    vs = random_vertices()
    es = list(random_edges(vs))
    g1 = Graph(vertices=vs, edges=es)
    g2 = Graph(vertices=vs)
    g3 = Graph(vertices=vs)
    esp = es[:] # Creates a copy.
    random.shuffle(esp)
    for e in es:
        g2.add_edge(e)
    for e in esp:
        g3.add_edge(e)
    assert_equal(g1, g2)
    assert_equal(g1, g3)


### Tests for graph union

# Disjoint graphs.
g1 = Graph(vertices=[1, 3, 2], edges=[(1, 3), (2, 3)])
g2 = Graph(vertices=[4, 5], edges=[(4, 5)])
g = g1 | g2
assert_equal(g.vertices, {1, 2, 3, 4, 5})
assert_true((2, 3) in g.edges)
assert_true((4, 5) in g.edges)
assert_false((1, 4) in g.edges)
g3 = g2 | g1
assert_equal(g, g3)

### More tests for graph union

# Overlapping graphs.
g1 = Graph(vertices=['a', 'b', 'c'], edges=[('a', 'b'), ('b', 'c')])
g2 = Graph(vertices=['b', 'c', 'd', 'e'], edges=[('c', 'd'), ('b', 'c')])
g = g1 | g2
assert_equal(g.vertices, {'a', 'b', 'c', 'd', 'e'})
assert_equal(g.edges, {('a', 'b'), ('b', 'c'), ('c', 'd')})
g3 = g2 | g1
assert_equal(g, g3)

### Even more tests for graph union

# Empty graph.
g1 = Graph(vertices=[1, 3, 2], edges=[(1, 3), (2, 3)])
g2 = Graph()
g = g1 | g2
assert_equal(g, g1)

### Tests for tree. 

g = Graph(vertices=[1, 2, 3], edges=[(1, 2), (1, 3)])
assert_true(g.is_tree)

g = Graph(vertices=[1, 2, 3], edges=[(1, 2), (2, 3), (1, 3)])
assert_false(g.is_tree)

g = Graph(vertices=[1, 2, 3], edges=[(1, 3), (2, 3)])
assert_false(g.is_tree)

g = Graph(vertices=['a', 'b'], edges=[('a', 'b')])
assert_true(g.is_tree)

g = Graph(vertices=['a', 'b'], edges=[('a', 'b'), ('b', 'a')])
assert_false(g.is_tree)

### More tests for `is_tree`

g = Graph()
assert_true(g.is_tree)

g = Graph(vertices=['a', 'b', 'c', 'd'], edges=[('a', 'b'), ('c', 'd')])
assert_false(g.is_tree)

g = Graph(vertices=['a', 'b', 'c', 'd'], edges=[('a', 'b'), ('b', 'c'), ('c', 'd')])
assert_true(g.is_tree)
