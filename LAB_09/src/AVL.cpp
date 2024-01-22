#include "AVL.h"
#include <iostream>
#include <algorithm>

using namespace std;

template <class T>
AVL<T>::AVL()           //constructor
{
   root=NULL; //giving starting value of root pointer
}

template <class T>
AVL<T>::~AVL()              //destructor
{
    delete_tree(root);
}

template <class T>
void AVL<T>::delete_tree(Node* r)               //delete tree
{
    if(root!=NULL)
    {
        delete_tree(r->left);
        delete_tree(r->right);
        delete r;
    }
}

template <class T>
void AVL<T>::singleLeftRotation(Node*& k2) {
    Node* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;

    // Update heights
    k2->height = 1 + std::max(height(k2->left), height(k2->right));
    k1->height = 1 + std::max(height(k1->left), height(k1->right));

    k2 = k1;
}

template <class T>
void AVL<T>::singleRightRotation(Node*& k2) {
    Node* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    // Update heights
    k2->height = 1 + std::max(height(k2->left), height(k2->right));
    k1->height = 1 + std::max(height(k1->left), height(k1->right));

    k2 = k1;
}

template <class T>
void AVL<T>::doubleLeftRotation(Node*& k3)          //DLR=SLR+SRR
{
    singleLeftRotation(k3->left);
    singleRightRotation(k3->left);
}

template <class T>
void AVL<T>::doubleRightRotation(Node*& k3)         //DRR=SRR+SLR
{
    singleRightRotation(k3->right);
    singleLeftRotation(k3->right);
}

template <class T>
void AVL<T>::insert(const T x)      //ADT function of insert
{
    insert(x,root);
}

template <class T>
void AVL<T>::insert(const T x, Node*& t)    //insertion core function
{
    if(t==NULL)         //insert node
    {
        t=new Node(x,t);    //create at node at end
    }
    else
    {
        if(x<t->element)        //insert at left
        {
            insert(x,t->left);
            if (std::abs(height(t->left) - height(t->right)) > 1)  //check AVL tree property
            {
                if(x<t->left->element)                  //check left-left insertion
                    singleRightRotation(t);
                else
                    doubleLeftRotation(t);                 //for right of left insertion
            }
        }
        else
        {
            if(x>t->element)            //insert at right
            {
                insert(x,t->right);
                if(std::abs(height(t->left) - height(t->right)>1))           //check AVL tree property
                {
                    if(x<t->right->element)                        //check right-right insertion
                        singleLeftRotation(t);
                    else
                        doubleRightRotation(t);                     //for left of right insertion
                }
            }
        }
    }
}

template <class T>
int AVL<T>::height(Node* t) const {
    if (t == nullptr) {
        return 0; // Height of an empty tree is 0
    } else {
        int leftHeight = height(t->left);
        int rightHeight = height(t->right);
        return 1 + std::max(leftHeight, rightHeight);
    }
}

template <class T>
bool AVL<T>::empty()  const           //check if the tree is empty
{
    if(root==NULL)
        return true;
    else
        return false;
}

template <class T>
bool AVL<T>::search(const T x)              //searching in AVL
{
    if(root==NULL)
    {
        return false;
    }
    else
    {
        Node* curr=root;
        int flag=0;
       while(curr!=NULL)
       {
           if(x==curr->element)
            return true;
           if(x<curr->element)
           {
               curr=curr->left;
           }
           else{
                if(x>curr->element)
                {
                    curr=curr->right;
                }
           }
       }
       return false;
    }
}

template <class T>
void AVL<T>::remove(const T x) {
    remove(x, root);
}

template <class T>
void AVL<T>::remove(const T x, Node*& t) {
    if (t == nullptr) {
        // Node not found, do nothing
        return;
    }

    if (x < t->element) {
        // Node to be deleted is in the left subtree
        remove(x, t->left);
    } else if (x > t->element) {
        // Node to be deleted is in the right subtree
        remove(x, t->right);
    } else {
        // Node to be deleted found
        if (t->left != nullptr && t->right != nullptr) {
            // Node has two children
            // Find the successor by traversing to the leftmost node in the right subtree
            Node* successorParent = t;
            Node* successor = t->right;
            while (successor->left != nullptr) {
                successorParent = successor;
                successor = successor->left;
            }

            // Replace the node with the successor and remove the successor
            t->element = successor->element;
            remove(successor->element, successorParent->right);
        } else {
            // Node has at most one child
            Node* temp = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete temp;
        }
    }

    // Update height
    if (t != nullptr) {
        t->height = 1 + std::max(height(t->left), height(t->right));

        // Check balance and perform rotations
        int balance = height(t->left) - height(t->right);

        if (balance > 1) {
            if (height(t->left->left) >= height(t->left->right)) {
                singleRightRotation(t);
            } else {
                doubleRightRotation(t);
            }
        } else if (balance < -1) {
            if (height(t->right->right) >= height(t->right->left)) {
                singleLeftRotation(t);
            } else {
                doubleLeftRotation(t);
            }
        }
    }
}

template <class T>
void AVL<T>::print()
{
    print(root);
}

template <class T>
void AVL<T>::print(Node* r)
{
    if (r != NULL)
    {
        print(r->left);
        cout << " " << r->element;
        print(r->right);
    }
}
