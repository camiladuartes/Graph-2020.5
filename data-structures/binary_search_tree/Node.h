#include <iostream>

using namespace std;

class Node{

   
    private:
        Node *left;
        Node *right;
        int value;

    public:

        Node(int value) {
            this->value = value;
        }

        Node* getLeft() {return this->left;}
        Node* getRight() {return this->right;}
        int getValue() {return this->value;}

        void setLeft(Node *left) {this->left = left;}
        void setRight(Node *right) {this->right = right;}
        void setValue(int value) {this->value = value;}

        bool isLeaf() {return left == NULL && right == NULL;}

};