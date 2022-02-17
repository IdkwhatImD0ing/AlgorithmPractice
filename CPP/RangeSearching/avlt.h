#ifndef AVLT_H
#define AVLT_H

#include <string>

using namespace std;

class Node
{
public:
  string key;
  Node *left, *right, *parent;
  int subtreeSize;
  int height;

  Node()
  {
    left = right = parent = NULL;
  }

  Node(string str1)
  {
    key = str1;
    left = right = parent = NULL;
    height = 1;
    subtreeSize = 1;
  }
};

class AVLT
{
private:
  Node *root;

public:
  AVLT();
  int max(int, int);
  Node *insert(string);
  Node *insert(Node *, string);
  Node *insert(Node *, Node *);
  int height(Node *);
  int subtreeSize(Node *);
  Node *rightRotate(Node *);
  Node *leftRotate(Node *);
  void increaseSubTree(Node *);
  int range(string, string);
  int range(Node *, string, string);
  int findLeft(Node *, string);
  int findRight(Node *, string);
  int getBalance(Node *);
  void setHeight(Node *);
  void setSubTree(Node *);
  Node *find(string);
  Node *find(Node *, string);
  void printTree();
  void printTree(Node *, int);
};

#endif