#ifndef GRAPH_H
#define GRAPH_H
#include <queue>
#include <vector>
#include <stack>

using namespace std;

struct Double{
  public:
    int actorOne, actorTwo;
};

class Graph{
  private:
    vector<vector<int>> adjList;
    int graphSize;
  public:
    Graph(int);
    void addEdge(int, int);
    void addEdge(Double*);
    bool getEdge(int, int);
    stack<int> bfs(int, int);
    void deleteGraph();
    void print();
    int min(int[]);
};

#endif