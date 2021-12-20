# Graphs

## Data structure

Given that our main use for graphs is to answer reachability-type questions, a better idea is to store the edges via a dictionary that associates with each vertex the set of successors of the vertex. The vertices will simply be the keys of the dictionary. This is very similar to an adjacency list.

## Algorithms

### Reachability

The algorithm keeps two sets of vertices:

- The set of open vertices: these are the vertices that are known to be reachable, and whose successors have not yet been explored.
- The set of closed vertices: these are the vertices that are known to be reachable, and whose successors we have already explored.

Intially, the set of open vertices contains only the starting vertex, and the set of closed vertices is empty, as we have completed no exploration. Repeatedly, we pick an open vertex, we move it to the closed set, and we put all its successor vertices -- except those that are closed already -- in the open set. The algorithm continues until there are no more open vertices; at that point, the set of reachable vertices is equal to the closed vertices.

### Union and Intersection

For a graph so that, for  G1=(V1,E1)  and  G2=(V2,E2) , with  G1  represented by `g1` in code and  G2  represented by `g2`,

`g1 | g2`

returns the graph G(12)=(V1 ∪ V2, E1 ∪ E2) having as vertices the union of the vertices of G1 and G2, and as edges the union of the edges of G1 and G2.

Using the above example, 

`g1 & g2` 

returns the Intersection of graphs g1 and g2.

### Induced

Given a graph  G=(V,E)  and a set of vertices  U , we return the graph with set of vertices  V∩U  and set of edges  E∩(V∩U×V∩U) . This is the portion of the original graph that only involves vertices in V.

The function `induced(set)` returns the subgraph induced by a specified set of vertices.

### Is Tree

A tree is a graph (V,E) with two special properties:

- Every vertex has at most one incoming edge.
- Either there are no vertices, or there is a vertex with no incoming edges, called the root, from which all other vertices are reachable.

The property `is_tree` returns whether the graphs ia tree or not.