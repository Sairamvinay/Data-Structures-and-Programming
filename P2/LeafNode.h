#ifndef LeafNodeH
#define LeafNodeH

#include "BTreeNode.h"

class LeafNode:public BTreeNode
{
 
public:
  int *values;
  LeafNode(int LSize, InternalNode *p, BTreeNode *left,
    BTreeNode *right);
  int getMinimum() const;
  LeafNode* insert(int value); // returns pointer to new Leaf if splits
  // else NULL
  void print(Queue <BTreeNode*> &queue);
  LeafNode* split(int value);
  //void leftShift(int value);
}; //LeafNode class

void bubbleSort(int* VALS,int count);

#endif
