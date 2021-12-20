import networkx as nx # Library for displaying graphs.
import matplotlib.pyplot as plt

class Graph(object):

    def __init__(self, vertices=None, edges=None):
        self.s = {u: set() for u in vertices or []}
        for u, v in (edges or []):
            self.add_edge((u, v))

    def show(self):
        g = nx.DiGraph()
        g.add_nodes_from(self.s.keys())
        g.add_edges_from([(u, v) for u in self.s for v in self.s[u]])
        nx.draw(g, with_labels=True)

    def add_vertex(self, v):
        if v not in self.s:
            self.s[v] = set()

    def add_edge(self, e):
        u, v = e
        self.add_vertex(u)
        self.add_vertex(v)
        self.s[u].add(v)

    @property
    def vertices(self):
        return set(self.s.keys())

    @property
    def edges(self):
        return {(u, v) for u, d in self.s.items() for v in d}

    def successors(self, u):
        """Returns the set of successors of vertex u"""
        return self.s[u]

    def __eq__(self, other):
        """We need to define graph equality."""
        if self.vertices != other.vertices:
            return False
        for v, d in self.s.items():
            if d != other.s[v]:
                return False
        return True

    def __repr__(self):
        r = "Graph:"
        for v in self.vertices:
            r += "\n %r : %r" % (v, self.s.get(v))
        return r

    def show(self):
        g = nx.DiGraph()
        g.add_nodes_from(self.vertices)
        g.add_edges_from([(u, v) for u in self.vertices for v in self.s[u]])
        nx.draw(g, with_labels=True)

    def add_vertex(self, v):
        self.vertices.add(v)
        # We must be careful not to overwrite the successor relation
        # in case v might already be present in the graph.
        self.s[v] = self.s.get(v, set())

    def add_edge(self, e):
        """Adds an edge e = (u, v) between two vertices u, v.  If the
        two vertices are not already in the graph, adds them."""
        u, v = e
        self.vertices.update({u, v})
        # Initializes the successor function if needed.
        self.s[u] = self.s.get(u, set()) | {v}
        self.s[v] = self.s.get(v, set())

    def successors(self, u):
        """Returns the set of successors of a vertex u"""
        return self.s[u]

    def reachable(self, v):
        """Returns the set of vertices reachable from an initial vertex v."""
        vopen = {v}
        vclosed = set()
        while len(vopen) > 0:
            u = vopen.pop()
            vclosed.add(u)
            vopen.update(self.s[u] - vclosed)
        return vclosed

    def __and__(self, g):
        """Returns the intersection of the current graph with a
        specified graph g."""
        return Graph(vertices=self.vertices & g.vertices,
                     edges=self.edges & g.edges)

    def induced(self, vertex_set):
        """Returns the subgraph induced by the set of vertices vertex_set."""
        common_vertices = vertex_set & self.vertices
        gg = Graph(vertices = common_vertices)
        for v in common_vertices:
            gg.s[v] = self.s[v] & common_vertices
        gg._check()
        return gg

    def __or__(self, g):
        a = g.vertices
        print(self.vertices)
        print(self.edges)
        b = g.edges
        """Returns the union of the current graph, and of the graph g."""
        for i in range(len(a)):
            self.add_vertex(a.pop())
            print(self.vertices)
        for j in range(len(b)):
            self.add_edge(b.pop())
            print(self.edges)
        return(Graph(vertices=self.vertices, edges=self.edges))

    @property
    def is_tree(self):
        """Returns True iff the graph is a tree."""
        inputs = set()
        for e in (self.edges):
            u, v = e
            if (v in inputs):
                return False
            else:
                inputs.add(v)
        if (len(self.vertices) == 0):
            return True
        numRoots = 0
        for x in (self.vertices):
            
            print(x)
            print(self.reachable(x))
            if (len(self.reachable(x)) == len(self.vertices)):
                numRoots += 1
        if (numRoots == 1):
            return True


