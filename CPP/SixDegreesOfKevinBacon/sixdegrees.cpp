#include <iostream>
#include "graph.h"
#include "linkedlist.h"
#include <sstream>
#include <fstream>
#include <cstring>
#include <vector>
#include <bits/stdc++.h>
#include <unordered_map>
#include <stack>

using namespace std;

int main(int argc, char** argv){
  
  ifstream input;
  ofstream output;
  
  unordered_map<int, string> actorMap; //Map for int/string for actors
  unordered_map<string, int> reverseActorMap; //Reverse of actor map
  unordered_map<int, LinkedList*> movieMap; //Map for each actor and the movies they are in
  
  input.open("cleaned_movielist.txt", ios::in); //Source file
  string inputString;
  vector<string> parsedStrings; //Parsed from input
  
  int actorIndex = 0; //Current free index
  string actorOne;
  string actorTwo;
  
  stack<Double*> newStack; //Stack for storing edges
  
  while(getline(input, inputString)){
    istringstream ss(inputString);
    string word;
    parsedStrings.clear();
    while(ss >> word){
      parsedStrings.push_back(word); //Parses all the words into the vector
    }
    
    for(unsigned int x = 1; x < parsedStrings.size(); x++){ //For each string in input except first one
      actorOne = parsedStrings.at(x); //First actor is x
      if(reverseActorMap.find(actorOne) == reverseActorMap.end()){//If this actor is not in the map yet
        LinkedList *newList = new LinkedList(); //New Linked List for movies
        movieMap.insert({actorIndex, newList}); //Insert current movie
        reverseActorMap.insert({actorOne, actorIndex});//Insert into reverseMap
        actorMap.insert({actorIndex, actorOne}); //Insert to Actormap
        actorIndex++; //Increment index of actor
      }
      LinkedList *thisList = movieMap.at(reverseActorMap.at(actorOne)); //Gets the linkedlist of movies for the actor
      thisList->insert(parsedStrings[0]); //Adds current movie to the linkedlist of movies for that actor
      
      for(unsigned int y = x+1; y < parsedStrings.size(); y++){//Do the same for the first loop but starting from index x+1
        actorTwo = parsedStrings.at(y);
        if(reverseActorMap.find(actorTwo) == reverseActorMap.end()){
          LinkedList *newList = new LinkedList();
          movieMap.insert({actorIndex, newList});
          reverseActorMap.insert({actorTwo, actorIndex});
          actorMap.insert({actorIndex, actorTwo});
          actorIndex++;
        }
        Double *to_add = new Double;
        to_add->actorOne = reverseActorMap.at(actorOne);
        to_add->actorTwo = reverseActorMap.at(actorTwo);
        newStack.push(to_add); //Add the edge between the two actors to the stack
        
      }
    }
  }
  
  input.close();

  Graph myGraph(actorMap.size()); //Creates graph with size of actor
  while(!newStack.empty()){//While the edge stack is not empty add edge to graph
    myGraph.addEdge(newStack.top());//Memory issues
    delete(newStack.top());
    newStack.pop();
  }
  
  //myGraph.print();
  
  input.open(argv[1]);
  output.open(argv[2]);
  stack<int> myStack; //This will be path from start to finish
  
  while(getline(input, inputString)){
    istringstream ss(inputString);
    string word;
    parsedStrings.clear();
    while(ss >> word){
      parsedStrings.push_back(word); //Parses all the words into the vector
    }
    
    actorOne = parsedStrings[0];
    actorTwo = parsedStrings[1];
    
    if(reverseActorMap.find(actorOne) == reverseActorMap.end()  //Base case where one of the actors is not in the source
      || reverseActorMap.find(actorTwo) == reverseActorMap.end()){
      output << "Not present\n";
      continue;
    }
    
    if(actorOne.compare(actorTwo) == 0){ //2nd Base case where actors are equal
      output << actorOne << "\n";
      continue;
    }
    
    int one = reverseActorMap.find(actorOne)->second;
    int two = reverseActorMap.find(actorTwo)->second;
    myStack = myGraph.bfs(one,two);
    if(myStack.size() == 0 || myStack.size() == 1){ //Third base case where stack of path is 1 or 0
      output << "Not present\n";
      continue;
    }
    
    int curr;
    string name;
    while(!myStack.empty()){
      curr = myStack.top(); //Current actor is stack pop
      myStack.pop();
      output << actorMap.at(curr);//Get the string of the actor and print it
      if(!myStack.empty()){
        output << " -(";
        LinkedList *one = movieMap.at(curr); //First actor linkedlist
        LinkedList *two = movieMap.at(myStack.top());//Next actor linkedlist
        Node *myNode = one->findSame(two); //Find a movie that both actors appeared in
        name = myNode->data;
        output << name << ")- ";
      }
      
    }
    output << "\n";
  }
  
}

