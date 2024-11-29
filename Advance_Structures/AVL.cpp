//
// Created by tonystark on 27-Nov-24.
//

#include "AVL.h"

// Node constructor
template <typename T>
AVLTree<T>::Node::Node(const T& value) :
    data(value), left(nullptr), right(nullptr), height(1) {}

// Custom max function
template <typename T>
T AVLTree<T>::max(const T& a, const T& b) {
    return (a > b) ? a : b;
}

// Get height of a node
template <typename T>
int AVLTree<T>::getHeight(Node* node) {
    return node ? node->height : 0;
}

// Calculate balance factor
template <typename T>
int AVLTree<T>::getBalanceFactor(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Update node height
template <typename T>
void AVLTree<T>::updateHeight(Node* node) {
    if (node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

// Right rotation
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Left rotation
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Balance the tree
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::balance(Node* node) {
    if (!node) return nullptr;

    updateHeight(node);

    int balanceFactor = getBalanceFactor(node);

    // Left Heavy
    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) < 0) {
            // Left-Right Case
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    // Right Heavy
    if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) > 0) {
            // Right-Left Case
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    return node;
}

// Insert a node
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::insertNode(Node* node, const T& value) {
    if (!node) return new Node(value);

    if (value < node->data)
        node->left = insertNode(node->left, value);
    else if (value > node->data)
        node->right = insertNode(node->right, value);
    else
        return node; // Duplicate values not allowed

    return balance(node);
}

// Find minimum node
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::findMinNode(Node* node) {
    while (node->left) node = node->left;
    return node;
}

// Delete a node
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::deleteNode(Node* node, const T& value) {
    if (!node) return nullptr;

    if (value < node->data)
        node->left = deleteNode(node->left, value);
    else if (value > node->data)
        node->right = deleteNode(node->right, value);
    else {
        // Node to delete found
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;

            // No child case
            if (!temp) {
                temp = node;
                node = nullptr;
            }
            else // One child case
                *node = *temp;

            delete temp;
        }
        else {
            // Two children case
            Node* temp = findMinNode(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
    }

    if (!node) return nullptr;
    return balance(node);
}

// Search for a node
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::searchNode(Node* node, const T& value) {
    if (!node || node->data == value) return node;

    if (value < node->data)
        return searchNode(node->left, value);
    else
        return searchNode(node->right, value);
}

// Clear entire tree
template <typename T>
void AVLTree<T>::clearTree(Node* node) {
    if (!node) return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

// Constructor
template <typename T>
AVLTree<T>::AVLTree() : root(nullptr) {}

// Destructor
template <typename T>
AVLTree<T>::~AVLTree() {
    clearTree(root);
}

// Public insert method
template <typename T>
void AVLTree<T>::insert(const T& value) {
    root = insertNode(root, value);
}

// Public remove method
template <typename T>
void AVLTree<T>::remove(const T& value) {
    root = deleteNode(root, value);
}

// Public update method
template <typename T>
bool AVLTree<T>::update(const T& oldValue, const T& newValue) {
    Node* nodeToUpdate = searchNode(root, oldValue);
    if (!nodeToUpdate) return false;

    remove(oldValue);
    insert(newValue);
    return true;
}

// Check if value exists
template <typename T>
bool AVLTree<T>::contains(const T& value) {
    return searchNode(root, value) != nullptr;
}

// Inorder traversal
template <typename T>
void AVLTree<T>::inorderTraversal() {
    inorderTraversalHelper(root);
    cout << endl;
}

// Inorder traversal helper
template <typename T>
void AVLTree<T>::inorderTraversalHelper(Node* node) {
    if (!node) return;
    inorderTraversalHelper(node->left);
    cout << node->data << " ";
    inorderTraversalHelper(node->right);
}
