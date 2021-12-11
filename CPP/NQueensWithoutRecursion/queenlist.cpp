 //filename: queenList.cpp
//
//Contains the queenList class


#include "queenlist.h"
#include <string>
#include <stack>
#include <vector>
#include <iostream>

using namespace std;


QueenList :: QueenList(int size)
{
  mySize = size; //Size of Board
  currentColumn = 1; //Current Column to place queen
}

Queen QueenList :: getQueen(int position){ //Gets the queen at position in the vector of queens
  return container.at(position);
}

Queen QueenList :: getQueenColumn(int column){ //Gets the queen at specific column
  for(unsigned int i = 0; i < container.size(); i++){
    if(getQueen(i).posX == column){ //Return the queen on the column
      return getQueen(i);
    }
  }
  Queen neverWillBeReturned; //This will never be returned because we will do containsColumn always before this function
  return neverWillBeReturned;
}

void QueenList :: addQueen(Queen newQueen){//Adds a queen to this list
  container.push_back(newQueen);
}

void QueenList :: addQueen(int x, int y){//Makes a queen with the coordinates and adds it to this list
  Queen newQueen;
  newQueen.posX = x;
  newQueen.posY = y;
  addQueen(newQueen);
}

void QueenList :: removeQueen(int x, int y){//Removes the queen with these coordinates
  if(contains(x,y)){
    for(unsigned int i = 0; i < container.size(); i++){
      if(getQueen(i).posX == x && getQueen(i).posY == y){
        container.erase(container.begin() + (i));
      }
    }
  }
}

void QueenList :: changeQueenX(Queen input, int value){ //Change the x value of a queen
  input.posX = value;
}

void QueenList :: changeQueenY(Queen input, int value){ //Change the y value of a queen
  input.posY = value;
}


bool QueenList :: contains(int positionX, int positionY){ //Check if this list contains a queen with the given coordinates
  for(unsigned int i = 0; i < container.size(); i++){
    if(getQueen(i).posX == positionX && getQueen(i).posY == positionY){
      return true;
    }
  }
  return false;
}

bool QueenList :: containsColumn(int column){ //Checks if there is a queen at the given column
  for(unsigned int i = 0; i < container.size(); i++){
    if(getQueen(i).posX == column){
      return true;
    }
  }
  return false;
}

bool QueenList :: isSafe(int positionX, int positionY){ //Check if the tile conflicts with other queens
  
  for (int i = 1; i <= mySize; i++){
    if(contains(positionX, i) && positionY != i){
      return false; //Check if other queen in column but not in the base tile
    }
    if(contains(i, positionY) && positionX != i){
      return false; //Check if other queen in row but not in the base tile
    }
  }
  
  //Checks four diagonals but not including the base tile
  for (int x = positionX - 1, y = positionY - 1; x >= 1 && y >= 1; x--, y--){
    if(contains(x,y)){
      return false;
    }
  }
  
  for (int x = positionX + 1, y = positionY + 1; x <= mySize && y <= mySize ;x++, y++){
    if(contains(x,y)){
      return false;
    }
  }
  
  for (int x = positionX + 1, y = positionY - 1; x <= mySize && y >= 1; x++, y--){
    if(contains(x,y)){
      return false;
    }
  }
  
  for (int x = positionX - 1, y = positionY + 1; x >= 1 && y <= mySize; x--, y++){
    if(contains(x,y)){
      return false;
    }
  }
  
  return true;
}

int QueenList :: getCurrentQueens(){ //Gets the current queens in this list
    return container.size();
}

bool QueenList :: isSolution(){ //Checks if this list is a solution
  if(getCurrentQueens() == mySize){
    return true;
  }
  return false;
}

QueenList QueenList :: cloneList(){ //Clones this list
  QueenList clonedList(mySize);
  for(unsigned int i = 0; i <  container.size(); i ++){
    clonedList.addQueen(getQueen(i));
  }
  return clonedList;
}

void QueenList :: sortList(){ //Bubblesort code from Geeks for geeks
  for(unsigned int i = 0; i < container.size() -1; i++)
    for(unsigned int j = 0; j < container.size() - i - 1; j++){
      if(getQueen(j).posX > getQueen(j + 1).posX){
        swap(container.at(j), container.at(j + 1));
      }
    }
}

vector<QueenList> QueenList :: solve(){ //Solve function
  vector<QueenList> solutions; //Vector of solutions
  for(unsigned int i = 0; i < container.size(); i++){ //Checks if the seeded queens conflicts
    if(isSafe(getQueen(i).posX, getQueen(i).posY) == false){
      return solutions;
    }
  }
   
  stack<class QueenList> recurStack; //Stack for simulating recursion
  QueenList init(mySize), stacktop(mySize);
  init = cloneList(); //Clones the original list
  recurStack.push(init);
  
  while(!recurStack.empty()){
    stacktop = recurStack.top();
    recurStack.pop();
   
    if((stacktop.currentColumn == mySize+1)){ //If the amount of queens in the solution equals the size of the board
      solutions.push_back(stacktop); //This is one solution
      break; //Continue if want to get all solutions, break to just get the first solution
    }
    
    QueenList to_push = stacktop.cloneList(); //Clones the top board
    to_push.currentColumn = stacktop.currentColumn + 1; //Since we are gonna add a queen, on the column, we will increment the column for the next recursion 
    if(stacktop.containsColumn(stacktop.currentColumn)){ //If there is already a queen in this column because of seeded queens, we will not add another queen
      recurStack.push(to_push); //Push the unmodified board
    }
    else{
      for(int i = 1; i <= to_push.mySize; i++){ //Iterate through all possible positions of queens
        if(to_push.isSafe(stacktop.currentColumn, i)){ // If a tile can fit a queen
          to_push.addQueen(stacktop.currentColumn, i); //Add a queen to the board
          recurStack.push(to_push); //Push a copy of the board to the stack
          to_push.removeQueen(stacktop.currentColumn, i); //Remove the queen to look for other positions of queens
        }
      }
    }
  }
  
  
  return solutions; //Return the vector of solutions.
  
}

string QueenList :: print(){ //Prints the queens on this board
  string newString = "";
  for(unsigned int i = 0; i < container.size(); i++){
    newString = newString + to_string(getQueen(i).posX) + " " + to_string(getQueen(i).posY) + " ";
  }
  newString = newString + "\n";
  return newString;
}

string QueenList :: printResult(){ //Print no solution if no solution, else prints the queens on this board
  string newString = "";
  if(!isSolution()){
    newString = newString + "No Solution\n";
  }
  else{
    for(unsigned int i = 0; i < container.size(); i++){
      newString = newString + to_string(getQueen(i).posX) + " " + to_string(getQueen(i).posY) + " ";
    }
    newString = newString + "\n";
  }
  return newString;
}