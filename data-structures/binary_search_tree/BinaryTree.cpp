#include <iostream>
#include "Node.h"

using namespace std;

class BinaryTree{

    private:
        Node *root = NULL;
        

    public:
        
        bool isEmpty() {
            return root == NULL;
        }

        Node* getRoot(){return this->root;}

        void insert(int value) {
            Node *node = new Node(value);
             insert(node);
        }

        

        
        void insert(Node *node) {
        
            if (root == NULL) {
                root = node;
                return;
            }

            Node *parent = root;

            while (true) {
                if (parent->getValue() == node->getValue()) {
                    return;
                }

                if (node->getValue() < parent->getValue()) {
                    if (parent->getLeft() == NULL) {
                        parent->setLeft(node);
                        break;
                    } 
                    else {
                        parent = parent->getLeft();
                        continue;
                    }
                }

                if (parent->getRight() == NULL) {
                    parent->setRight(node);
                    break;
                } 
                else {
                    parent = parent->getRight();
                }
            }
        }

    
        bool search(int key) {
        
            Node *current = root;

            while (current != NULL) {
               
                if (key == current->getValue())  {
                    return true;
                }
                else if (key < current->getValue()) {
                    current = current->getLeft();
                } 
                else {
                    current = current->getRight();
                }
            
            }

            return false;
        }
        
        
        int getSucessorKey(Node *node) {
        
            Node *max = node->getLeft();
            
            while (max->getRight() != NULL) {
                max = max->getRight();
            }
            
            return max->getValue();
        }
        

        
        
        void remove(int key) {
            
            if (root == NULL) {
                return;
            }

            Node *parent  = NULL;
            Node *current = root;

            while (true) {

                if (key > current->getValue()) {
                    if (current->getRight() != NULL) {
                        parent  = current;
                        current = current->getRight();
                    } 
                    else {
                        break;
                    }

                } 
                else if (key < current->getValue()) {
                
                    if (current->getLeft() != NULL) {
                        parent = current;
                        current = current->getLeft();
                    } 
                    else {
                        break;
                    }
                
                }
                else {
                    if (current->isLeaf()) {
                    
                        if (parent == NULL) {
                            root = NULL;
                        } 
                        else if (parent->getLeft() == current) {
                            parent->setLeft(NULL);
                        } 
                        else {
                            parent->setRight(NULL);
                        }
                   
                    } 
                    else if (current->getRight() == NULL) {
                   
                        if (parent == NULL) {
                            root = current->getLeft();
                        } 
                        else if (parent->getLeft() == current) {
                            parent->setLeft(current->getLeft());
                        } 
                        else {
                            parent->setRight(current->getLeft());
                        }
                   
                    } 
                    else if (current->getLeft() == NULL) {
                   
                        if (parent == NULL) {
                            root = current->getRight();
                        } else if (parent->getLeft() == current) {
                            parent->setLeft(current->getRight());
                        } else {
                            parent->setRight(current->getRight());
                        }
                   
                    } 
                    else {
                        int sucessorKey = getSucessorKey(current);
                        remove(sucessorKey);
                        current->setValue(sucessorKey);
                    }
                    break;
                }
           
            }
        }
        


};


int main(){

    BinaryTree *binaryTree = new BinaryTree();

    binaryTree->insert(new Node(12));
    binaryTree->insert(new Node(10));
    binaryTree->insert(new Node(9));

    // 1->true | 0->false
    cout << binaryTree->search(10) << endl;



    return 0;
}