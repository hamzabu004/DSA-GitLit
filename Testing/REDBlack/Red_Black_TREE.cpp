
//
// Created by muham on 11/26/2024.
//

#include <iostream>
using namespace std;

template<typename T>
struct Node {
    T value;
    Node* left;
    Node* right;
    Node* parent;

    bool isBlack;  /*it will keep track of color*/

    int height;

    Node(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr),
        isBlack(false), height(0) {}  /*is black is false because new nodes are inserted with red color*/
};

template<typename T>

class RedBlackTree {
private:
    Node<T>* root;

    int getHeight(Node<T>* node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    void updateHeight(Node<T>* node)
    {
        if (node)
        {
            node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        }
    }


    int getBalanceFactor(Node<T>* node)
    {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }


    Node<T>* rotateLeft(Node<T>* node)
    {
        Node<T>* newRoot = nullptr;
        if(node && node->right)
             newRoot = node->right;
        if(newRoot)
        node->right = newRoot->left;
        if (newRoot && newRoot->left)
            newRoot->left->parent = node;
        if(node && newRoot)
        newRoot->parent = node->parent;
        if (node && node->parent == nullptr)
            root = newRoot;
        else if (node && node->parent && node == node->parent->left)
            node->parent->left = newRoot;
        else
        {
            if(node && node->parent)
            node->parent->right = newRoot;
        }
        if(newRoot)
        newRoot->left = node;
        if(node)
        node->parent = newRoot;

        updateHeight(node);
        updateHeight(newRoot);
        if (newRoot->parent) {
            updateHeight(newRoot->parent);
        }


        return newRoot;
    }


    Node<T>* rotateRight(Node<T>* node)
    {
        Node<T>* newRoot = node->left;
        node->left = newRoot->right;
        if (newRoot->right) newRoot->right->parent = node;

        newRoot->parent = node->parent;
        if (node->parent == nullptr)
            root = newRoot;
        else if (node == node->parent->left)
            node->parent->left = newRoot;
        else
        {
            node->parent->right = newRoot;
        }
        newRoot->right = node;
        node->parent = newRoot;

        updateHeight(node);
        updateHeight(newRoot);
        if (newRoot->parent) {
            updateHeight(newRoot->parent);
        }


        return newRoot;
    }

    void reBalance(Node<T>* node)
    {
        updateHeight(node);
        int balanceFactor = getBalanceFactor(node);

        /*left is heavy so we check its left subtree now*/
        if (balanceFactor > 1)
        {
            /*if left subtree gives neg val it means right is heavy of that subtree
             so we do double rotate*/
            if (getBalanceFactor(node->left) < 0)
            {
                rotateLeft(node->left);
            }

            /*since left is heavy this rotation is done nonetheless*/
            rotateRight(node);
        }

        /*as neg value is shows right is heavy*/
        else if (balanceFactor < -1)
        {
            /*if right subtree is positive means at right subtree left is hevay so
             double rotate*/
            if (getBalanceFactor(node->right) > 0)
            {
                rotateRight(node->right);
            }
            /*is to be done in both cases*/
            rotateLeft(node);
        }
    }

    void fixRedBlackProperties(Node<T>* node)
    {
        while (node != root && node->parent && !node->parent->isBlack)
        {
            Node<T>* parent = node->parent;
            Node<T>* grandparent = parent->parent;
            Node<T>* uncle = nullptr;
            if(grandparent)
                uncle = (parent == grandparent->left) ? grandparent->right : grandparent->left;


            if (uncle && !uncle->isBlack)
            {
                parent->isBlack = true;
                uncle->isBlack = true;
                grandparent->isBlack = false;
                node = grandparent;
            }
            else
            {
                if (grandparent != nullptr && parent == grandparent->left )
                {
                    if (node == parent->right)
                    {
                        rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rotateRight(grandparent);
                }
                else
                {
                    if (node == parent->left)
                    {
                        rotateRight(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rotateLeft(grandparent);
                }
                if(node && parent)
                parent->isBlack = true;

                if(node && parent && grandparent)
                grandparent->isBlack = false;
                break;
            }
        }
        root->isBlack = true;
    }

    void swapSubtree(Node<T>* oldSub, Node<T>* newSub) {
        //  we  replace the old node with the new one

        if (oldSub->parent == nullptr) {
            // If old one is root, then make new one the root
            root = newSub;
        } else if (oldSub == oldSub->parent->left) {
            // check if old one is left child and update that
            oldSub->parent->left = newSub;
        } else {
            oldSub->parent->right = newSub;
        }

        if (newSub != nullptr) {
            // also we set the parent of the new one
            newSub->parent = oldSub->parent;
        }

    }



    Node<T>* insert(Node<T>* current, Node<T>* newNode) {
        if (current == nullptr)
            return newNode;

        if (newNode->value < current->value)
        {
            current->left = insert(current->left, newNode);
            current->left->parent = current;
        }
        else if (newNode->value > current->value)
        {
            current->right = insert(current->right, newNode);
            current->right->parent = current;
        }
        else if (newNode->value == current->value) {
            cout << "Value already exists.." << endl;
            return current;
        }

        reBalance(current);
        return current;
    }

    Node<T>* predecessor(Node<T>* current) {
        if (current == nullptr)
            return nullptr;
        if (current->left == nullptr)
            return nullptr;
        current = current->left;
        while (current->right != nullptr)
            current = current->right;
        return current;
    }

    Node<T>* successor(Node<T>* current) {
        if (current == nullptr)
            return nullptr;
        if (current->right == nullptr)
            return nullptr;
        current = current->right;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

      void fixDeletion(Node<T>* node) {
        while (node != root && (node == nullptr || node->isBlack)) {
            if (node == node->parent->left) {
                Node<T>* sibling = node->parent->right;
                if (!sibling->isBlack) {  // Sibling is red
                    sibling->isBlack = true;
                    node->parent->isBlack = false;
                    rotateLeft(node->parent);
                    sibling = node->parent->right;
                }
                if ((sibling->left == nullptr || sibling->left->isBlack) &&
                    (sibling->right == nullptr || sibling->right->isBlack)) {  // Both sibling children are black
                    sibling->isBlack = false;
                    node = node->parent;
                } else {
                    if (sibling->right == nullptr || sibling->right->isBlack) {  // Sibling right child is black
                        if (sibling->left)
                            sibling->left->isBlack = true;
                        sibling->isBlack = false;
                        rotateRight(sibling);
                        sibling = node->parent->right;
                    }
                    sibling->isBlack = node->parent->isBlack;  //  Sibling right child is red
                    node->parent->isBlack = true;
                    if (sibling->right)
                        sibling->right->isBlack = true;
                    rotateLeft(node->parent);
                    node = root;
                }
            } else {
                Node<T>* sibling = node->parent->left;
                if (!sibling->isBlack) {  // Sibling is red
                    sibling->isBlack = true;
                    node->parent->isBlack = false;
                    rotateRight(node->parent);
                    sibling = node->parent->left;
                }
                if ((sibling->left == nullptr || sibling->left->isBlack) &&
                    (sibling->right == nullptr || sibling->right->isBlack)) {  // Both sibling children are black
                    sibling->isBlack = false;
                    node = node->parent;
                } else {
                    if (sibling->left == nullptr || sibling->left->isBlack) {  //  Sibling left child is black
                        if (sibling->right)
                            sibling->right->isBlack = true;
                        sibling->isBlack = false;
                        rotateLeft(sibling);
                        sibling = node->parent->left;
                    }
                    sibling->isBlack = node->parent->isBlack;  //  Sibling left child is red
                    node->parent->isBlack = true;
                    if (sibling->left)
                        sibling->left->isBlack = true;
                    rotateRight(node->parent);
                    node = root;
                }
            }
        }
        if (node)
            node->isBlack = true;
    }

    Node<T>* deleteNode(Node<T>* node, int value) {
        Node<T>* current = node;
        while (current != nullptr && current->value != value) {
            if (value < current->value)
                current = current->left;
            else
                current = current->right;
        }
        if (current == nullptr) {
            cout << "Value not found in the tree." << endl;
            return node;
        }

        Node<T>* temp = current;
        Node<T>* temp2 = nullptr;
        bool tempOrigionalColor = temp->isBlack;

        if (current->left == nullptr) {
            temp2 = current->right;
            swapSubtree(current, current->right);
        } else if (current->right == nullptr) {
            temp2 = current->left;
            swapSubtree(current, current->left);
        } else {
            temp = successor(current);
            tempOrigionalColor = temp->isBlack;
            temp2 = temp->right;
            if (temp->parent == current) {
                if (temp2)
                    temp2->parent = temp;
            } else {
                swapSubtree(temp, temp->right);
                temp->right = current->right;
                if (temp->right)
                    temp->right->parent = temp;
            }
            swapSubtree(current, temp);
            temp->left = current->left;
            if (temp->left)
                temp->left->parent = temp;
            temp->isBlack = current->isBlack;
        }

        delete current;
        if (tempOrigionalColor)
            fixDeletion(temp2);
        return root;
    }



public:
    RedBlackTree() : root(nullptr)
    {}

    void insert(int value)
    {
        Node<T>* newNode = new Node<T>(value);
        root = insert(root, newNode);
        fixRedBlackProperties(newNode);
    }

    void remove(int val)
    {
        this->root = deleteNode(this->root, val);
    }

    void inorder(Node<T>* node)
    {
        if (node == nullptr)
            return;
        inorder(node->left);
        cout << "Value: " << node->value << "  Color: "  << ((node->isBlack) ? " Black " : " Red   ")  << "  Height: " << node->height << endl;
        inorder(node->right);
    }

    void display()
    {
        inorder(root);
        cout << endl;
        preorder(root);
        cout << endl;
        postorder(root);
        cout << endl;
    }

    void preorder(Node<T>* node)
    {
        if (node == nullptr)
            return;
        cout << node->value << '\t';
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node<T>* node) {
        if (node == nullptr)
            return;
        postorder(node->left);
        postorder(node->right);
        cout << node->value << '\t';
    }

};

int main()
{
    RedBlackTree<int> tree;

    int elements, val;

    cout << "Enter the number of elements: ";
    cin >> elements;

    for (int i = 0; i < elements; i++)
    {
        cout << "Enter Element No. " << i + 1 << " : ";
        cin >> val;
        tree.insert(val);
    }
    tree.display();

    int value;
    cout << "Enter the value to be deleted: ";
    cin >> value;
    tree.remove(value);
    tree.display();

    return 0;
}
