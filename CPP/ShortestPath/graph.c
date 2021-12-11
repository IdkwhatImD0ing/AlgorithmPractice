#include "graph.h"

#include "vertices.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//Definitnion of struct Graph
//
//vertices: amount of vertices on this Graph
//undirected: boolean specifying if graph is undirected
//visited: the vertices that are visited
//matrix, the adjacency matrix for this graph

struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *g = (Graph *) malloc(sizeof(Graph));
    if (g) {
        g->vertices = vertices;
        g->undirected = undirected;
        for (uint32_t i = 0; i < VERTICES; i++) {
            g->visited[i] = false;
        }
        for (uint32_t x = 0; x < VERTICES; x++) {
            for (uint32_t y = 0; y < VERTICES; y++) {
                g->matrix[x][y] = 0;
            }
        }
    }
    return g;
}

bool within_bounds(uint32_t x) {
    if (x < VERTICES) {
        return true;
    }
    return false;
}

void graph_delete(Graph **g) {
    if (*g) {
        free(*g);
        *g = NULL;
    }
    return;
}

uint32_t graph_vertices(Graph *G) {
    return (G->vertices);
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (within_bounds(i) && within_bounds(j)) {
        G->matrix[i][j] = k;
        if (G->undirected) {
            G->matrix[j][i] = k;
        }
        return true;
    }
    return false;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (within_bounds(i) && within_bounds(j)) {
        if (G->matrix[i][j] > 0) {
            return true;
        }
    }
    return false;
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (within_bounds(i) && within_bounds(j)) {
        return (G->matrix[i][j]);
    }
    return (0);
}

bool graph_visited(Graph *G, uint32_t v) {
    return (G->visited[v]);
}

void graph_mark_visited(Graph *G, uint32_t v) {
    if (within_bounds(v)) {
        G->visited[v] = true;
    }
    return;
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (within_bounds(v)) {
        G->visited[v] = false;
    }
    return;
}

void graph_print(Graph *G) {
    for (int i = 0; i < VERTICES; i++) {
        for (int j = 0; j < VERTICES; j++) {
            printf("%d", G->matrix[i][j]);
        }
        printf("\n");
    }
    return;
}
