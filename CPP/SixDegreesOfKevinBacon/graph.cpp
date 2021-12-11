#include "graph.h"
#include <queue>
#include <algorithm>
#include <iostream>
#include <stack>


using namespace std;

Graph :: Graph(int size){
  graphSize = size;
  for(int i = 0; i < size; i++){ //Create a vector of vectors. Size of the vector will be graph size;
    vector<int> vec;
    adjList.push_back(vec);
  }
}

void Graph :: addEdge(int x, int y){ //Adds an edge to values actors x and y
  if(getEdge(x, y)){
    return;
  }
  adjList[x].push_back(y);
  adjList[y].push_back(x);
}

void Graph :: addEdge(Double *value){// Wrapper class to add edge given a double
  addEdge(value->actorOne, value->actorTwo);
}

bool Graph :: getEdge(int x, int y){ //Checks to see if there is an edge between actors x and y
  if(find(adjList[x].begin(), adjList[x].end(), y) != adjList[x].end()){ //Iterates through the adjList[x] vector for y
    return true;
  }
  return false;
}


stack<int> Graph :: bfs(int start, int end){ //Does bfs on the graph and returns stack of ints for the path, top is start and bottom is end
  bool visited[graphSize]; //Total number of actors
  int previousNode[graphSize]; //Total number of actors
  
  for(int i = 0; i < graphSize; i ++){
    visited[i] = false; //Set each one to false to signify not visited
    previousNode[i] = -1; //Set each one to -1 to signify no previous node
  }
  
  queue<int> queued; //Bfs Queue
  stack<int> answer; //Answer queue
  
  visited[start] = true; //set start node to visited
  queued.push(start); //Push start onto the queue
  
  int current; //Represents current actor
  while(!queued.empty()){
    current = queued.front();
    queued.pop();
    if(current == end){
      break;
    }
    //Iterate through all possible edges
    for(unsigned int i = 0; i< adjList[current].size(); i++){
      if(!visited[adjList[current][i]]){ //If this actor isnt visited yet
        visited[adjList[current][i]] = true;
        queued.push(adjList[current][i]);
        previousNode[adjList[current][i]] = current;
      }
    }
  }
  
  
  int path = end; //Start of path will be end actor
  while(previousNode[path] >= 0){ //If there is a previous path
    answer.push(path); //Push previous actor onto stack
    path = previousNode[path]; //Set current actor to the previous one
  }
  answer.push(start); //Push the start onto the stack
  
  return answer; //Return the stack of actors representing the path
  

}


void Graph :: deleteGraph(){
  return;
}

void Graph :: print(){//Debug function
  for(int i = 0; i < graphSize; i++){
    for(unsigned int j = 0; j < adjList[i].size(); j++){
      cout << adjList[i][j] << " ";
    }
    cout << "\n";
  }
}





