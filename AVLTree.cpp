//Joseph Timm
//CS3100
//Project 4 - AVL Tree
//this file contains the actual functions of the AVLTree and its nodes

#include "AVLTree.h"

AVLTree:: AVLTree(): 
    root(nullptr),
    size(0)
{}

bool AVLTree::insert(int key, string value){
    return insertHelper(root, key, value);
}

bool AVLTree::insertHelper(treeNode*& current, int key, string value){
 if (!current){ //when current is nullptr change it to the new node
        treeNode* newNode = new treeNode(key, value); 
        current=newNode;
        size++; //adjust size
        return true;
    } else if(current->key == key){ //make sure no dupes. CANT HAVE THIS BE FIRST BECAUSE SEG FAULT
        return false;
    } else if (key < current->key){ //if key is smaller go left
        insertHelper(current->leftChild, key, value);
    } else if (key > current->key){ //if key is bigger go right
        insertHelper(current->rightChild, key, value);
    } 
    this->checkBalance(current);
    current->height=max(getNodeHeight(current->leftChild), getNodeHeight(current->rightChild)) + 1;
}

int AVLTree:: getNodeHeight(treeNode* node){
    if (node==nullptr){
        return -1;
    } else return node->height;
}

void AVLTree:: checkBalance(treeNode*& current){
    int balance;
    if (current->leftChild==nullptr && current->rightChild==nullptr){ //if leaf node balance is 0
        balance = 0;
        return; //return so none of the following ifs will also be checked
    } else if (current->leftChild==nullptr){
      balance = (-1 - current->rightChild->height);
      this->findRotation(balance, current);
    } else if (current->rightChild==nullptr){
        balance = (current->leftChild->height + 1); //+1 because it is - -1 which is equal to +1
        this->findRotation(balance, current);
    } else {
        balance = (current->leftChild->height - current->rightChild->height);
       this->findRotation(balance, current);
    }
    return;
} 

 void AVLTree:: findRotation(int balance, treeNode*& current){ //remember balance is equal to the potential problem nodes balance
    if (balance<=1 && balance >=-1){ //if in balance youre done
        return;
    } else if (balance>=2 && current->leftChild->rotationHelper() >=1){
         this->SRR(current);
    } else if (balance <=-1 && current->rightChild->rotationHelper() <=-1){
         this->SLR(current);
    } else if (balance >=2 &&  current->leftChild->rotationHelper() <=-1){ //double right
         this->SLR(current->leftChild);
        this->SRR(current);
    } else if (balance <=-2 && current->rightChild->rotationHelper() >=1){ //double left
         this->SRR(current->rightChild);
         this->SLR(current);
    }
} 

int AVLTree:: treeNode:: rotationHelper(){
    int balance;
    if (leftChild==nullptr && rightChild==nullptr){ //if leaf node balance is 0
        return 0; //return so none of the following ifs will also be checked
    } else if (leftChild==nullptr){
      balance = (-1 - rightChild->height);
    } else if (rightChild==nullptr){
        balance = (leftChild->height + 1); //+1 because it is - -1 which is equal to +1
    } else {
        balance = (leftChild->height - rightChild->height);  
    }
    return balance;;
}

void AVLTree:: SRR(treeNode*& problem){  
    treeNode* hook = problem->leftChild;
    treeNode* temp = hook->rightChild;
    hook->rightChild=problem;
    problem->leftChild=temp;
    if (problem == this->root){ 
        root=hook;
    }
    //readjust the problem before it is changed to point to the hook node in the next line
    problem->height=max(getNodeHeight(problem->leftChild), getNodeHeight(problem->rightChild)) + 1; 
    problem=hook;
    //now readjust the hook height since its moved to its new spot 
    hook->height=max(getNodeHeight(hook->leftChild), getNodeHeight(hook->rightChild)) + 1; 
}

void AVLTree:: SLR(treeNode*& problem){
    treeNode* hook = problem->rightChild;
    treeNode* temp = hook->leftChild;
    hook->leftChild=problem;
    problem->rightChild=temp;
    if (problem == this->root){
        root=hook;
    }
    //readjust the problem before it is changed to point to the hook node in the next line
    problem->height=max(getNodeHeight(problem->leftChild), getNodeHeight(problem->rightChild)) + 1; 
    problem=hook;
    //now readjust the hook height since its moved to its new spot 
    hook->height=max(getNodeHeight(hook->leftChild), getNodeHeight(hook->rightChild)) + 1; 
}

int AVLTree::getHeight(){
    return root->height;
}

int AVLTree::getSize(){
    return size;
}

ostream& operator<<(ostream& os, const AVLTree& me){
   me.inOrderPrint(me.root, os, 0);
    return os; 
}

void AVLTree:: inOrderPrint(treeNode* current, ostream& os, int depth) const{  //do in order traversal  
    if (current==nullptr){ //base case
        return;
    } else {
        inOrderPrint(current->rightChild, os, depth+1); //go right
        for (int i=0; i<depth * 4; i++){ //print out spaces
            cout << " ";
        }
        cout << current->key << ", " << current->value << endl; //print current
        inOrderPrint(current->leftChild, os, depth+1); //then go left
    }
}

bool AVLTree::find(int key, string& value){
    return findHelper(key, value, root);
}

bool AVLTree:: findHelper(int key, string& value, treeNode* current){
    if (current==nullptr){ //make sure if the current is null it returns false before checking the key as that would cause a seg fault 
        return false;
    } else if (current->key == key){ 
        value=current->value; //key or value?
        return true;
    } else if (key < current->key){ //if key is smaller go left
        findHelper(key, value, current->leftChild);
    } else if (key > current->key){ //if key is bigger go right
        return findHelper(key, value ,current->rightChild);
    } 
}

vector<string> AVLTree::findRange(int lowkey, int highkey){
    vector<string> rangeList;
    rangeHelper(lowkey, highkey, rangeList, root);
    return rangeList;
}

void AVLTree::rangeHelper(int lowkey, int highkey, vector<string>& rangeList, treeNode* current){
    if (current==nullptr){ //base case 
        return;
    } else if (current->key <= highkey && current->key >= lowkey){ //if element is in range, add it to the list 
        rangeList.push_back(current->value);
    }
    rangeHelper(lowkey, highkey, rangeList, current->rightChild);
    rangeHelper(lowkey, highkey, rangeList, current->leftChild);
}

AVLTree &AVLTree:: operator=(const AVLTree& s){
    //use destructor code to clear out tree being called on
    if (root != nullptr) { 
       deleteNode(root);
    }
    delete root; //make sure root is deleted
    root=nullptr;
    size=0;

    //now copy into the tree being called on
    size=s.size;
    root=copyNodes(s.root, root);
}

AVLTree::AVLTree(const AVLTree& other){  
    size = other.size;
    root = copyNodes(other.root, root);
}

AVLTree::treeNode* AVLTree:: copyNodes(treeNode* copyFrom, treeNode* copyInto){
   if(copyFrom){ //if copyFrom is not nullptr then copy its data into a new node
        copyInto=new treeNode(copyFrom->key, copyFrom->value, copyFrom->height);
        copyInto->leftChild=copyNodes(copyFrom->leftChild, copyInto->leftChild);
        copyInto->rightChild=copyNodes(copyFrom->rightChild, copyInto->rightChild);
    }  else {
        return nullptr;
    }
    return copyInto;
} 

AVLTree:: ~AVLTree(){
    if (root != nullptr) {
       deleteNode(root);
    }
    delete root; //make sure root is deleted
    root=nullptr;
    size=0;
}

void AVLTree:: deleteNode(treeNode*& node){ 
    if (node==nullptr) { //Base case
        return;
    } else {
        deleteNode(node->leftChild);
        deleteNode(node->rightChild);   
        delete node; 
    }
}