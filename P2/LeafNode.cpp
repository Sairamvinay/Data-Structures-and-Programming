#include <iostream>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"
#include "math.h"

using namespace std;

void bubbleSort(int* VALS,int count){
  for (int i=0;i<count;i++){
    for (int j=0; j<(count - 1); j++){
      if (VALS[j] > VALS[j+1]){
        int val = VALS[j];
        VALS[j] = VALS[j+1];
        VALS[j+1] = val;
      }
    }
  }
}


LeafNode* LeafNode::split(int value){

    LeafNode *next = new LeafNode(leafSize,parent,this,rightSibling);
    next->setLeftSibling(this);
    next->setRightSibling(rightSibling);
    next->setParent(parent);
    if (rightSibling){
      
      rightSibling->setLeftSibling(next);
    
    }

    setRightSibling(next);
    setLeftSibling(leftSibling);
    int startPos;

    if ((count + 1) % 2 == 0){

      startPos = floor((count + 1) /2);

    }

    else{

      startPos = count / 2;
    }
    
    for (int k=startPos ; k < count ; k++){
      next->values[next->getCount()] = values[k];
      (next->count)++;
      
    }


  if (value<values[count-1]){

    
    values[count-1] = value;
    bubbleSort(values,count);
    next->values[next->getCount()] = values[count-1];
    //bubbleSort(parent->keys,parent->getCount());
    (next->count)++;
  }

  

  else{
    next->values[next->getCount()] = value;
    //bubbleSort(parent->keys,parent->getCount());
    next->count++;
  }
  

    
    bubbleSort(next->values,next->getCount());
    bubbleSort(values,count);
    count = floor((count+1)/2);
    if (parent)
      parent->updateKeys();
    return next;
}

LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()



int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
  // students must write this



   if ((count < leafSize)){
    
   
    values[count] = value;
    count++;
   bubbleSort(values,count);
  
   if (parent)
    parent->updateKeys();
  }
 


 else if ((leftSibling) &&(leftSibling->getCount() < leafSize)){ //left space


    if (value > values[0]){
      int move = values[0];
      for (int i=0;i<(count-1);i++){
        values[i] = values[i+1];
      }
      
      values[count-1] = value;
      leftSibling->insert(move);
      bubbleSort(values,count);
      if (((LeafNode*)leftSibling)->parent)
        ((LeafNode*)leftSibling)->parent->updateKeys();
    }

    else{
      leftSibling->insert(value);
      if (((LeafNode*)leftSibling)->parent)
          ((LeafNode*)leftSibling)->parent->updateKeys();
    }   
      
}


else if ((rightSibling) && (rightSibling->getCount() < leafSize)){ //right space
    
   
    LeafNode* rs = (LeafNode*) rightSibling;
    if ((value < rs->values[0]) && (value<values[count-1])){


      int move = values[count - 1];

      for (int i=0;i<count;i++){
        values[i+1] = values[i];
      }
      
      values[0] = value;
      rightSibling->insert(move);
      bubbleSort(values,count);
      if (((LeafNode*)rightSibling)->parent)
        ((LeafNode*)rightSibling)->parent->updateKeys();
    }

    else{
    rightSibling->insert(value);
    if (((LeafNode*)rightSibling)->parent)
      ((LeafNode*)rightSibling)->parent->updateKeys();
    }
  
}

else{    //SPLIT
    
    return split(value);
  }

 
  
  return NULL; // to avoid warnings for now.
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()


