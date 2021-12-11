#include "linkedlist.h"
#include <string>
#include <bits/stdc++.h>

using namespace std;

//Mostly taken from sesh's linked list implementation

LinkedList :: LinkedList()
{
  head = NULL;
}

void LinkedList :: insert(string val)
{
  Node *to_add = new Node;
  to_add->data = val;
  to_add->next = head;
  head = to_add;
}

Node* LinkedList :: getHead(){ //Get head function
  return head;
}

Node* LinkedList :: find(string val){
  Node *curr = head;
  while(curr!= NULL){
    if(curr->data.compare(val) == 0){
      return curr;
    }
    curr = curr->next;
  }
  
  return NULL;
}

Node* LinkedList :: findSame(LinkedList *other){ //Finds first overlapping string from 2 linkedlists
  
  Node *curr = head; //Current node is head of this Linked List
  
  unordered_set<string> compare; //Set of strings
  
  while(curr!= NULL){
    compare.insert(curr->data); //Add each node in this linkedlist to the set
    curr = curr->next;
  }
  
  curr = other->getHead(); //Gets the head of the other linkedlist
  
  while(curr != NULL){
    if(compare.find(curr->data) != compare.end()){ //See if there is a string matching current node's string in set
      return curr; //Return if there is
    }
    curr = curr->next;
  }
  
  return NULL; //Return NULL is no matching strings
  
  
}