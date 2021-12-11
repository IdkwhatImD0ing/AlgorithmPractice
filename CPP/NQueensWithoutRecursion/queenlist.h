//filename queenList.h
//
//Header file for queenList

#include <string>
#include <vector>
using namespace std;

struct Queen
{
  int posX;
  int posY;
};

class QueenList{
  private:
    vector<Queen> container;
    
  public:
    QueenList(int); //Constructor
    Queen getQueen(int);
    Queen getQueenColumn(int);
    void addQueen(Queen);
    void addQueen(int, int);
    void removeQueen(int, int);
    void changeQueenX(Queen, int);
    void changeQueenY(Queen, int);
    bool contains(int, int);
    bool containsColumn(int);
    bool isSafe(int, int);
    int getCurrentQueens();
    bool isSolution();
    QueenList cloneList();
    void sortList();
    vector<QueenList> solve();
    string print();
    string printResult();
    int mySize;
    int currentColumn;
};