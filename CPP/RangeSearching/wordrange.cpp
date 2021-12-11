#include <iostream>
#include "avlt.h"
#include <sstream>
#include <fstream>
#include <cstring>

using namespace std;

int main(int argc, char** argv){ //Code based off my own code from nqueens
  ifstream input;
  ofstream output;
  if(argc < 3){
    throw invalid_argument("Not enough parameters");
  }
  input.open(argv[1]);
  output.open(argv[2]);
  
  string command, second, third;
  char *com, *first;
  
  AVLT myAvlt; //Initialzing the AVLTree
  
  while(getline(input, command)){//Code based off of professors bst io code
    if (command.length() == 0){
      continue;
    }
    com = strdup(command.c_str());
    first = strtok(com, " \t");
    
    
    if(strcmp(first, "i") == 0){
      second = strtok(NULL, " \t");
      myAvlt.insert(second);
    }
    
    else if(strcmp(first, "r") == 0){
      second = strtok(NULL, " \t");
      third = strtok(NULL, " \t");
			output << myAvlt.range(second, third) << "\n";
    }
    else{
      cout << "SOMETHING IS VERY WRONG" << flush;
    }
  }
  //myAvlt.printTree();
  
}