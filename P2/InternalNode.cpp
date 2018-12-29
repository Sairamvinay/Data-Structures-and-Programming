#include <iostream>
#include "InternalNode.h"
#include "LeafNode.h"
#include "QueueAr.h"
#include "math.h"

using namespace std;

/*void InternalNode::BubbleSort(){
 

  for (int i=0;i<count;i++){
    for (int j=0; j<(count - 1); j++){
      if (keys[j] > keys[j+1]){
         cout<<keys[j]<<keys[j+1]<<endl;
        BTreeNode* temp = children[j];
        children[j] = children[j+1];
        children[j+1]= temp;
      }
    }
  }
}*/


int InternalNode::findPos(int value){

  int pos;
  for (pos=count-1; pos>=0; pos--){
    
    if (keys[pos]<value){
      
      break;
    }
  }



  return pos+1;
}



void InternalNode::updateKeys(){

  for (int pos=0;pos<count;pos++){
    
    //BTreeNode* child= (BTreeNode*)children[pos];
    //keys[pos]= child->getMinimum(); 
    keys[pos] = children[pos] -> getMinimum();
  }
  //BubbleSort(keys,count);
  if (parent)
    parent->updateKeys();
}

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()


InternalNode* InternalNode::split(BTreeNode *existingNode){

    InternalNode *next = new InternalNode(internalSize,leafSize,parent,this,rightSibling);
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
   //.... 
    for (int k=startPos ; k < count ; k++){
      next->keys[next->getCount()] = keys[k];
      next->children[next->getCount()] = children[k];
      (next->count)++;
      children[k]->setParent(next);

      
    }

count = floor((count+1)/2);
  //children[count-1]->setRightSibling(NULL);
  //children[0]->setLeftSibling(NULL);
  if (existingNode->getMinimum()<getMinimum()){

    insert(existingNode);
    existingNode->setParent(this);
  }

  

  else{
    next->insert(existingNode);
    existingNode->setParent(next);
  }
  
  updateKeys();
  next->updateKeys();

  if (rightSibling)
    ((InternalNode*)rightSibling)->updateKeys();

  if (leftSibling)
    ((InternalNode*)leftSibling)->updateKeys();

  return next;
}




InternalNode* InternalNode::insert(int value)
{
  // students must write this
  //compare with keys
 
    int pos=0;
    for (pos=count-1;pos>0;pos--){
      if ((keys[pos]) <= value)
        break;
    }


      BTreeNode* bt = children[pos];
     
      BTreeNode *tmp = bt->insert(value);
      
  if (!tmp){
        
           updateKeys();
           //BubbleSort();

          return NULL;
          
      }

  else if((count<internalSize)){

        insert(tmp);
        updateKeys();
        // BubbleSort();


        return NULL;
      }
      
  else if ((leftSibling) &&(leftSibling->getCount() < internalSize)){ //left space

    InternalNode* lf  = (InternalNode*) leftSibling;
    if (tmp->getMinimum() > keys[0]){
      BTreeNode* move = children[0];
      for (int i=0;i<(count-1);i++){
        keys[i] = keys[i+1];
        children[i]=children[i+1];

      }
      
      children[count-1] = tmp;
      keys[count-1] = tmp->getMinimum();
      lf->insert(move);
      updateKeys();
      lf->updateKeys();
      move->setParent(lf);
      // BubbleSort();
      if (rightSibling)
        ((InternalNode*)rightSibling)->updateKeys();

    }

    else{
      lf->insert(tmp);
      updateKeys();
      lf->updateKeys();
      tmp->setParent(lf);
      // BubbleSort();
      if (rightSibling)
        ((InternalNode*)rightSibling)->updateKeys();
    }   
      
}


else if ((rightSibling) && (rightSibling->getCount() < internalSize)){ //right space
    
   
  InternalNode* rt = (InternalNode*) rightSibling;
    if ((tmp->getMinimum() < rightSibling->getMinimum()) & (tmp->getMinimum()<getMinimum())){


      BTreeNode* move = children[count - 1];

      for (int i=0;i<count;i++){
        children[i+1] = children[i];
        keys[i+1] = keys[i];
      }
      
      children[0] = tmp;
      keys[0] = tmp->getMinimum();
      rt->insert(move);
      updateKeys();
      rt->updateKeys();
      move->setParent(parent);
       //BubbleSort();
      if (leftSibling)
        ((InternalNode*)leftSibling)->updateKeys();
    }

    else{
    rt->insert(tmp);
    updateKeys();
    rt->updateKeys();
    tmp->setParent(rt);
    // BubbleSort();
    if (leftSibling)
      ((InternalNode*)leftSibling)->updateKeys();
    }
  
}

else{    //SPLIT
    
    return split(tmp);
  }

    updateKeys();
     //BubbleSort();
    return NULL; // to avoid warnings for now.
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
    // students must write this
  children[0] = oldRoot;
  children[1] = node2;
  count = 2;
  keys[0] = oldRoot->getMinimum();
  keys[1] = node2->getMinimum();
  children[0]->setParent(this);
  children[1]->setParent(this);
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *newNode) // from a sibling
{
//look into this
  // students may write this
if (count<internalSize){
  newNode->setParent(this);
  

  updateKeys();
    
  int position = findPos(newNode->getMinimum());
  
  for (int i = count-1;i>=position;i--){
    
    children[i+1] = children[i];
  }

  count++;  
  children[position] =newNode;
  children[position]->setParent(this);
  
  //sort() children in order of mimimum() of children[i]
  //use BubbleSort defined at the top
  
  //BubbleSort();
  updateKeys();
  
}
  
   
} // InternalNode::insert()

void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()


