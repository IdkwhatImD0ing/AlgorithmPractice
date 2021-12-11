#include "graph.h"
#include "path.h"
#include "stack.h"
#include "variable.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "hvui:o:"
#define BLOCK   4096

int recursions = 0;
bool pathFound = false;

void dfs(Graph *G, uint32_t v, Path *current_path, Path *shortest_path, bool verbose,
    char *cities[], FILE *outfile) {
    recursions += 1;
    graph_mark_visited(G, v);
    for (uint32_t i = 0; i < graph_vertices(G); i++) {
        if (graph_has_edge(G, v, i)) {

            //Check if current path is a hamiltononian path
            if (path_vertices(current_path) == graph_vertices(G) && i == 0) {
                //If no shortest path or current path < shortest path
                path_push_vertex(current_path, i, G);
                if (path_length(shortest_path) == 0
                    || (path_length(current_path) < path_length(shortest_path))) {

                    //Print out shorter hamilton path if verbose printing
                    if (verbose) {
                        path_print(current_path, outfile, cities);
                    }
                    path_copy(shortest_path, current_path);
                    pathFound = true;
                }
                path_pop_vertex(current_path, &i, G);
            }

            if (!graph_visited(G, i) && !pathFound) {
                path_push_vertex(current_path, i, G);
                dfs(G, i, current_path, shortest_path, verbose, cities, outfile);
                path_pop_vertex(current_path, &i, G);
            }

            else if (!graph_visited(G, i)
                     && path_length(current_path) < path_length(shortest_path)) {
                path_push_vertex(current_path, i, G);
                dfs(G, i, current_path, shortest_path, verbose, cities, outfile);
                path_pop_vertex(current_path, &i, G);
            }
        }
    }
    graph_mark_unvisited(G, v);
    return;
}

int main(int argc, char **argv) {
    int32_t opt = 0;
    bool verbose = false;
    bool undirected = false;
    char buffer[BLOCK];
    FILE *infile = stdin;
    FILE *outfile = stdout;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("SYNOPSIS\n");
            printf("  Traveling Salesman Problem using DFS.\n\n");
            printf("USAGE\n");
            printf("  ./tsp [-u] [-v] [-h]  [-i infile] [-o outfile]\n\n");
            printf("OPTIONS \n");
            printf("  -u             Use undirected graph.\n");
            printf("  -v             Enable verbose printing.\n");
            printf("  -h             Program usage and help.\n");
            printf("  -i infile      Input containing graph (default: stdin)\n");
            printf("  -o outfile     Output of computer path (default: stdout)\n");

            return 0;
            break;
        case 'v': verbose = true; break;
        case 'u': undirected = true; break;
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        }
    }
    if (infile == NULL) {
        fprintf(stderr, "Error: failed to open infile.\n");
        return 0;
    }
    if (outfile == NULL) {
        fprintf(stderr, "Error: failed to open outfile.\n");
        fclose(infile);
        return 0;
    }
    uint32_t vertices1;
    fscanf(infile, "%u", &vertices1);

    if (vertices1 > VERTICES) {
        fprintf(stderr, "ERROR: Vertices greater than specified max vertices");
        fclose(infile);
        fclose(outfile);
        return 0;
    } else if (vertices1 == 0 || vertices1 == 1) {
        fprintf(outfile, "There's nowhere to go.\n");
        return 0;
    }
    char *cities[vertices1];
    //Gets rid of empty line after fscanf
    fgets(buffer, BLOCK, infile);

    for (uint32_t x = 0; x < vertices1; x += 1) {
        fgets(buffer, BLOCK, infile);
        cities[x] = strdup(buffer);
        cities[x][strlen(cities[x]) - 1] = '\0';
        
    }

    uint32_t origin;
    uint32_t end;
    uint32_t weight;
    int32_t c;
    //Creates the graph
    Graph *new_graph = graph_create(vertices1, undirected);

    //Iterates through all the paths
    while ((c = fscanf(infile, "%u %u %u\n", &origin, &end, &weight)) != EOF) {
        if (origin > 10000 || end > 10000 || weight > 10000 || c % 3 != 0 || c == 0 ) {
            fprintf(stderr, "Error: malformed edge. \n");
            graph_delete(&new_graph);
            fclose(infile);
            fclose(outfile);
            for (uint32_t x = 0; x < vertices1; x += 1) {
                free(cities[x]);
            }
            return 0;
        }
        graph_add_edge(new_graph, origin, end, weight);
    }

    Path *current_path = path_create();
    Path *shortest_path = path_create();

    dfs(new_graph, START_VERTEX, current_path, shortest_path, verbose, cities, outfile);
    if (path_length(shortest_path) == 0) {
        fprintf(outfile, "No Hamiltonian path found.\n");
    } else {
        path_print(shortest_path, outfile, cities);
    }
    fprintf(outfile, "Total recursive calls: %d\n", recursions);

    //Frees alll the memory that was used.
    fclose(infile);
    fclose(outfile);
    graph_delete(&new_graph);
    path_delete(&current_path);
    path_delete(&shortest_path);
    for (uint32_t x = 0; x < vertices1; x += 1) {
        free(cities[x]);
    }

    return 0;
}
