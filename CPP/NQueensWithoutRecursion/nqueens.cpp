//filename: nqueens.cpp
//
//Main wrapper for queenList
//
//
//
//
//
//
//
//

#include <iostream>
#include "queenlist.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

int main(int argc, char** argv){

  ifstream input;
  ofstream output;
  
  input.open(argv[1]);
  output.open(argv[2]);
  vector<int> inputInteger;
  string line;
  int x;
  
  while(getline(input, line)){
    istringstream str(line);
    while(str >> x){
      inputInteger.push_back(x);
    }
    QueenList newList(inputInteger.at(0));
    for(unsigned int x = 1; x < inputInteger.size(); x=x+2){
      newList.addQueen(inputInteger.at(x), inputInteger.at(x+1));
    }
    vector<QueenList> solutions = newList.solve();
    
    if(solutions.size() == 0){
      output << "No solution \n";
    }
    else{
      solutions.at(0).sortList();
      output << solutions.at(0).print();
    }
    inputInteger.clear();
  }
  
  input.close();
  output.close();
  return 1;
  
}