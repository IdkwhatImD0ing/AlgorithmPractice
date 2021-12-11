#include "path.h"

#include "stack.h"
#include "vertices.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//Definitnion of struct Path, a path of vertices
//
//*vertices, a stack of vertices for path
//Length: current length of path

struct Path {
    Stack *vertices;
    uint32_t length;
};

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p) {
        p->vertices = stack_create(VERTICES + 1);
        stack_push(p->vertices, START_VERTEX);
        p->length = 0;
    }
    return p;
}

void path_delete(Path **p) {
    if (*p) {
        stack_delete(&(*p)->vertices);
        free(*p);
        *p = NULL;
    }
    return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t topOfStack;
    stack_peek(p->vertices, &topOfStack);
    if (graph_edge_weight(G, topOfStack, v) == 0) {
        fprintf(stderr, "Error no edge between 2 vertexes.\n");
        return false;
    } else {
        stack_push(p->vertices, v);
        p->length += graph_edge_weight(G, topOfStack, v);
        return true;
    }
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {

    bool popped = stack_pop(p->vertices, v);

    uint32_t topOfStack;
    stack_peek(p->vertices, &topOfStack);
    if (popped == false) {
        return popped;
    }
    p->length -= graph_edge_weight(G, topOfStack, *v);
    return true;
}

uint32_t path_vertices(Path *p) {
    return (stack_size(p->vertices));
}

uint32_t path_length(Path *p) {
    return (p->length);
}

void path_copy(Path *dst, Path *src) {
    dst->length = src->length;
    stack_copy(dst->vertices, src->vertices);
    return;
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path length: %d\n", p->length);
    fprintf(outfile, "Path: ");
    stack_print(p->vertices, outfile, cities);
    return;
}
