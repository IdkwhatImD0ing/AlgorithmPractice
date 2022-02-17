#include "avlt.h"
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

AVLT ::AVLT() // Taken from Professor Sesh's code
{
  root = NULL;
}

int AVLT ::max(int x, int y)
{ // Simple maximum function
  if (x > y)
  {
    return x;
  }
  return y;
}

Node *AVLT ::insert(string str)
{
  root = insert(root, str);
  return root;
}

Node *AVLT ::insert(Node *start, string str) // Base code taken from Professor's code
{
  Node *to_insert = new Node(str);
  if (root == NULL)
  {
    root = to_insert;
    root->height = 1;
    root->subtreeSize = 1;
    return (root);
  }
  else
  {
    return (insert(start, to_insert));
  }
}

Node *AVLT ::insert(Node *start, Node *to_insert) // Base code taken from Professor's code
{
  if (start == NULL)
  {
    start = to_insert; // Base case if no node
    return start;
  }
  if (to_insert->key < start->key)
  {
    // cout << "Left Insert \n";
    start->left = insert(start->left, to_insert); // Go left node if key is smaller that the start node
  }
  else if (to_insert->key > start->key)
  { // Go right if larger
    // cout << "Right Insert \n";
    start->right = insert(start->right, to_insert);
  }
  else
  {
    return start; // This is if to_insert key is equal to start-key which is not allowed, just return the start node without doing anything
  }

  setHeight(start);  // This sets the height recursively starting from the parent of the inserted node
  setSubTree(start); // This sets the subtree recursively starting from the parent of the inserted node

  int balance = getBalance(start); // Checks balance of node

  if (balance < -1 && to_insert->key > start->right->key)
  { // Balance < 1 means left is smaller than right, this is the right right case because the new node was inserted right of right child
    // cout << "Right Right\n" << flush;
    start = leftRotate(start); // If the inserted node was larger than the right child of parent and parent is smaller than right child, that means right child can be used as new base
  }

  else if (balance > 1 && to_insert->key < start->left->key)
  { // Balance > 1 means left side is larger than right side, this is left left case because the new node key is less than the left chi
    // cout << "Left Left\n" << flush;
    start = rightRotate(start); // Since parent is larger than child and the inserted node is smaller than child, child can be new parent node
  }

  else if (balance < -1 && to_insert->key < start->right->key)
  { // This is the right left case, the new node was inserted under the right child, but left because it was smaller than the right key
    // cout << "Right Left\n" << flush;

    start->right = rightRotate(start->right); // First we do a right rotate to ensure that the subtree is turned into a right right
    start = leftRotate(start);                // Continue left rotating due to being right right case
  }

  else if (balance > 1 && to_insert->key > start->left->key)
  { // This is left right case because the the inserted node was smaller than parent but the inserted node is larger than the left child
    // cout << "Left Right\n" << flush;
    start->left = leftRotate(start->left); // First left rotate to make it a left left case
    start = rightRotate(start);            // Then continue right rotating
  }

  return (start); // Returns the root of the subtree
}

Node *AVLT ::rightRotate(Node *start)
{
  Node *leftChild = start->left; // The left child of start
  Node *originalParent = NULL;
  Node *leftRight = leftChild->right; // Right child of left child of start

  if (start->parent != NULL)
  {                                 // Check for parent
    originalParent = start->parent; // Store the original parent node in original parent
  }

  leftChild->right = start;  // Rotate the left child and the original root
  start->parent = leftChild; // New Parent after rotating

  start->left = leftRight;
  if (leftRight != NULL)
  {
    leftRight->parent = start; // Set parent to original root which is now right child of the left child of the original root
  }

  setSubTree(start);     // First recalculate subtree size for start since it is now child
  setSubTree(leftChild); // Recalculate subtree sizes for leftChild after since it is parent
  setHeight(start);      // Recalculate height for start
  setHeight(leftChild);  // Recalculate height for new root

  // NOTE TO SELF: THIS WAS WHAT WAS BREAKING MY CODE AND SPENT 8 HOURS DOING SAME WITH LEFT ROTATE
  // I ALREADY SET ALL THE PARENT STUFF IN MY INSERT CODE SO I DIDNT NEED TO DO THIS
  // WASTED 8 HOURS HOLY FUCK
  if (originalParent != NULL)
  { // Do if there was a parent of start
    leftChild->parent = originalParent;
    // if(leftChild->key > leftChild->parent->key){ //Sets children of parents
    //   leftChild->parent->right = leftChild;
    // }
    // else{
    //   leftChild->parent->left = leftChild;
    // }
    // setHeight(leftChild->parent); //Sets the height of the parent
    // setSubTree(leftChild->parent);
  }

  return leftChild; // This is the new root
}

Node *AVLT ::leftRotate(Node *start)
{
  Node *rightChild = start->right; // This is the right child of start
  Node *originalParent = NULL;
  Node *rightLeft = rightChild->left; // This is the left child of the right child

  if (start->parent != NULL)
  { // If start has a parent, save that in original parent
    originalParent = start->parent;
  }

  rightChild->left = start;   // start is now a child of right child
  start->parent = rightChild; // Set parent of start to right child

  start->right = rightLeft; // Set start right to rightLeft, even if null
  if (rightLeft != NULL)
  {                            // If its not null
    rightLeft->parent = start; // Point back to parent
  }

  setSubTree(start);      // Same as right rotate
  setHeight(start);       // Sets the height of start then the new root
  setSubTree(rightChild); // new subtree size
  setHeight(rightChild);  // New Height

  if (originalParent != NULL)
  {
    rightChild->parent = originalParent;
    //  if(rightChild->key > rightChild->parent->key){ //Sets the children of parents
    //    rightChild->parent->right = rightChild;
    // }
    //  else if(rightChild->key < rightChild->parent->key){
    //    rightChild->parent->left = rightChild;
    //  }
    //  setHeight(rightChild->parent); //Sets height of parent of start
    //	setSubTree(rightChild->parent);
  }

  return rightChild;
}

void AVLT ::increaseSubTree(Node *start)
{ // This function increases the subtree size of all parent nodes starting from start
  if (start == NULL)
  {         // Use only after inserting, reason this is a seperate method because this needs to increase subtree up to root,
    return; // wheras insert is only starting from a subtree of root, not root itself
  }
  start->subtreeSize = start->subtreeSize + 1;
  increaseSubTree(start->parent);
}

int AVLT ::range(string str1, string str2)
{
  return (root->subtreeSize - findLeft(root, str1) - findRight(root, str2));
}

int AVLT ::range(Node *start, string str1, string str2)
{
  int toRemove = 0;

  if (start == NULL)
  { // Most basic case, dont recurse anymore if at leaf
    return 0;
  }
  if (start->key < str1 || start->key > str2)
  { // Remove this node if its not in range, could be leaf or intermediate node
    toRemove++;
  }

  if (start->key <= str1)
  { // Second base case, if the node is lower to str1, everything smaller than it wont count
    if (start->left != NULL)
    {
      return toRemove + start->left->subtreeSize + range(start->right, str1, str2); // Add the left subtree to be removed, keep iterating down
    }
  }
  else if (start->key >= str2)
  { // Third base case, if the node is larger  str2, everything larger than it wont count
    if (start->right != NULL)
    {
      return toRemove + start->right->subtreeSize + range(start->left, str1, str2); // Add the right subtree to be removed, keep iterating down
    }
  }
  else
  {
    return range(start->left, str1, str2) + range(start->right, str1, str2); // Do this otherwise, this is the recursion part
  }

  return (toRemove);
}

int AVLT ::findLeft(Node *start, string str1)
{
  int toRemove = 0; // Initialize 0
  if (start == NULL)
  { // First base case
    return 0;
  }
  if (start->left == NULL && start->right == NULL && start->key < str1)
  { // Second base case
    return 1;
  }

  if (start->key == str1)
  { // Third base case
    if (start->left != NULL)
    {
      return start->left->subtreeSize;
    }
  }

  if (start->key < str1)
  {               // First time value of node is less than lower bound
    toRemove = 1; // Gotta add this to the number of out of bound lists
    if (start->left != NULL)
    { // If there is a left child
      if (start->right != NULL)
      {                                                                              // If there is a right child
        return (toRemove + start->left->subtreeSize + findLeft(start->right, str1)); // Remove the left subtree because its out of bounds, while the right may be in bounds
      }
      return (toRemove + start->left->subtreeSize); // No right child, all left nodes will be out of bounds
    }

    if (start->right != NULL)
    { // If no left child but yes right child, will have to iterate through to see if there are any out of bounds
      return (toRemove + findLeft(start->right, str1));
    }
  }

  if (start->key > str1)
  { // Since current node is in bounds, keep going left
    return findLeft(start->left, str1);
  }

  return 0; // This is only for if the first node checked is lower than str1, and has no parents
}

int AVLT ::findRight(Node *start, string str1)
{
  int toRemove = 0;
  if (start == NULL)
  { // One Base case
    return 0;
  }
  if (start->right == NULL && start->left == NULL && start->key > str1)
  { // Second base case
    return 1;
  }
  if (start->key == str1)
  { // Third base case
    if (start->right != NULL)
    {
      return start->right->subtreeSize;
    }
  }

  if (start->key > str1)
  {               // This is supposed to be the first node where value is higher than the current bound
    toRemove = 1; // This node is over so it should also be removed
    if (start->right != NULL)
    { // If there is right child
      if (start->left != NULL)
      {
        return (toRemove + start->right->subtreeSize + findRight(start->left, str1)); // Everything to the right is larger, but left node could have stuff that is in bounds
      }
      return (toRemove + start->right->subtreeSize); // Everything to the right is larger but no left node
    }
    if (start->left != NULL)
    { // This is if there is no right child but there is left which can be in bounds
      return (toRemove + findRight(start->left, str1));
    }
  }

  if (start->key < str1)
  { // Since current node value is still lower than the higher bound, keep going right
    return findRight(start->right, str1);
  }

  return 0;
}

int AVLT ::getBalance(Node *parent)
{
  if (parent == NULL)
  {
    return 0;
  }
  else if (parent->left == NULL)
  {
    return (0 - parent->right->height);
  }
  else if (parent->right == NULL)
  {
    return (parent->left->height - 0);
  }
  else
  {
    return (parent->left->height - parent->right->height); // This is the balance check for rotations
  }
}

void AVLT ::setHeight(Node *start)
{
  if (start->right == NULL && start->left == NULL)
  {
    start->height = 1;
  }
  else if (start->left == NULL)
  { // Height logic, height of highest child + 1
    start->height = start->right->height + 1;
  }
  else if (start->right == NULL)
  {
    start->height = start->left->height + 1;
  }
  else
  {
    start->height = max(start->left->height, start->right->height) + 1;
  }
}

void AVLT ::setSubTree(Node *start)
{
  if (start->right == NULL && start->left == NULL)
  {
    start->subtreeSize = 1;
  }
  else if (start->left == NULL)
  {
    start->subtreeSize = start->right->subtreeSize + 1;
  }
  else if (start->right == NULL)
  {
    start->subtreeSize = start->left->subtreeSize + 1;
  }
  else
  {
    start->subtreeSize = start->left->subtreeSize + start->right->subtreeSize + 1;
  }
}

Node *AVLT ::find(string str)
{
  return (find(root, str));
}

Node *AVLT ::find(Node *start, string str)
{
  if (start == NULL)
  {
    return NULL;
  }
  if (str == start->key)
  {
    return start;
  }
  else if (str > start->key)
  {
    return (find(start->right, str));
  }
  else
  {
    return (find(start->left, str));
  }
}

void AVLT ::printTree()
{
  printTree(root, 0);
}

void AVLT ::printTree(Node *start, int space)
{ // Print debugging code taken from GFG
  if (start == NULL)
  {
    return;
  }
  space += 4;

  printTree(start->right, space);
  cout << endl;
  for (int i = 4; i < space; i++)
  {
    cout << " ";
  }
  cout << start->key << " Height " << start->height << " Subtree " << start->subtreeSize << "\n";

  printTree(start->left, space);
}
