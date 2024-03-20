//Joseph Timm
//CS3100
//Project 4 - AVL Tree
//this file contains the function delcaration and member data for both the AVL Tree and its nodes

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class AVLTree{
    private:
        //NODE CLASS
        class treeNode{
            public:
                treeNode* leftChild;
                treeNode* rightChild;
                int key;
                string value;
                int height; //height of specific node

                int rotationHelper();
                
                treeNode(int num, string str): leftChild(nullptr), rightChild(nullptr), key(num), value(str), height(0){}
                    //constructor for treeNode
                treeNode(int num, string str, int oldHeight): leftChild(nullptr), rightChild(nullptr), key(num), value(str), height(oldHeight){}
                    //for copy constructor so the height will be added properly since that is adjusted in the inset method which is not utilized by copy constructor
                ~treeNode(){}
                    //destructor for treeNode
        };

        //MEMBER DATA FOR TREE
        treeNode* root;
        int size; //number of nodes in the tree      

    public:
        //CONSTRUCTOR
        AVLTree();
        AVLTree(const AVLTree&);

        //MEMBER FUNCTIONS
            bool insert(int key, string value);
                //insert a new node into the AVL tree. DUPES NOT ALLOWED. Return true if inserted (no dupe) and false if not inserted (dupe found)
                //The time complexity should be O(log2 n)

            int getHeight();
                //return height of the AVLTree
                //The time complexity should be O(1)

            int getSize();
                //return total number of nodes in the AVL Tree
                //The time complexity should be O(1)


            friend ostream& operator<<(ostream& os, const AVLTree& me);
                //print the tree out such that if you tilt your head 90 degrees, the tree would be in order (see assignment for picture)


            bool find(int key, string& value);
                //if the given key is found, return true and place the corresponding value in value. 
                //Otherwise return false (and the value in value can be anything)
                //The time complexity should be O(log2 n).

            vector<string> findRange(int lowkey, int highkey);
                //return a C++ vector of strings containing all of the values in the tree with keys ≥ lowkey and ≤ highkey. 
                // For each key found in the given range, there will be one value in the vector. 
                //If no matching key/value pairs are found, return an empty vector.

            AVLTree& operator=(const AVLTree& s);    

            ~AVLTree();
                //destructor 

            //CUSTOM FUNCTIONS
            void deleteNode(treeNode*& node);

            bool insertHelper(treeNode*& current, int key, string value);

            void inOrderPrint(treeNode* current, ostream& os, int depth) const;

            bool findHelper(int key, string& value, treeNode* current);

            void SRR(treeNode*& problem);

            void SLR(treeNode*& problem);

            treeNode* copyNodes(treeNode* copyFrom, treeNode* copyInto);

            void checkBalance(treeNode*& current);

            void findRotation(int balance, treeNode*& current);

            void rangeHelper(int lowkey, int highkey, vector<string>& rangeList, treeNode* current);

            int getNodeHeight(treeNode* node);

};