//Joseph Timm
//CS3100
//Project 4 - AVL Tree

#include "AVLTree.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
   AVLTree tree;
   tree.insert(6, "six");
   tree.insert(5, "five");
   tree.insert(4, "four");
   tree.insert(7, "seven");
   tree.insert(2, "two");
   tree.insert(9, "nine");
   tree.insert(1, "one");

   vector<string> rangeList = tree.findRange(1, 7);


   for (int i=0; i<rangeList.size(); i++){
       cout << rangeList.at(i) << endl;
   }

//    AVLTree tree2 = tree; //calls copy constructor correctly and makes independent tree

    AVLTree tree2;
    tree2 = tree; //correctly makes new independent tree that has same values/keys

    tree2.insert(20, "twenty");

    cout<< tree2 << endl;

    cout << "here" << endl;

    cout << tree << endl;

    cout << "tree1 size is: " << tree.getSize() << endl; 

    cout << "tree1 height is: " << tree.getHeight() << endl; 

    cout << "tree2 size is: " << tree2.getSize() << endl;

    cout << "tree2 height is: " << tree2.getHeight() << endl;


}