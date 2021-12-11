#ifndef LIST_H
#define LIST_H
#include <string>

using namespace std;

struct Node
{
  string data;
  Node *next;
};

class LinkedList
{
  private: 
    Node *head;
  public:
    LinkedList();
    Node *getHead();
    void insert(string);
    Node *find(string);
    Node *findSame(LinkedList*);
};

#endif