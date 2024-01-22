#ifndef AVL_H
#define AVL_H

#include <iostream>

using namespace std;

template <class T>
class AVL {
public:
    AVL();
    AVL(const AVL& a);
    ~AVL();
    bool empty() const;
    bool search(const T x);
    void insert(const T x);
    void remove(const T x);
    void print();

private:
    struct Node {
        T element;
        Node* left;
        Node* right;
        int height;

        Node(const T& elem, Node* lt = nullptr, Node* rt = nullptr, int h = 0)
            : element(elem), left(lt), right(rt), height(h) {}
    };

    Node* root;
    int height(Node* t) const;
    void insert(const T x, Node*& t); // recursive function
    void singleLeftRotation(Node*& k2);
    void singleRightRotation(Node*& k2);
    void doubleLeftRotation(Node*& k3);
    void doubleRightRotation(Node*& k3);
    void delete_tree(Node* r);
    void print(Node* r);
    void remove(const T x, Node*& t);
};

#endif // AVL_H
