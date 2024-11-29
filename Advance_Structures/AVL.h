//
// Created by tonystark on 27-Nov-24.
//

#ifndef AVL_H
#define AVL_H

#include <iostream>

using namespace std;

template <typename T>
class AVLTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;

        Node(const T& value);
    };

    Node* root;

    int getHeight(Node* node);
    int getBalanceFactor(Node* node);
    void updateHeight(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* node);
    Node* insertNode(Node* node, const T& value);
    Node* findMinNode(Node* node);
    Node* deleteNode(Node* node, const T& value);
    Node* searchNode(Node* node, const T& value);
    void clearTree(Node* node);
    void inorderTraversalHelper(Node* node);

    // Custom max function to replace std::max
    T max(const T& a, const T& b);

public:
    AVLTree();
    ~AVLTree();

    void insert(const T& value);
    void remove(const T& value);
    bool update(const T& oldValue, const T& newValue);
    bool contains(const T& value);
    void inorderTraversal();
};

#endif //AVL_H
