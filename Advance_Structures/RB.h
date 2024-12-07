#include <iostream>
using namespace std;

enum Color { RED, BLACK };

template <typename T>
struct Node {
    T data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(T value)
        : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};


template <typename T>
class RedBlackTree {

    Node<T>* root;

    void leftRotate(Node<T>* x) {
        Node<T>* y = x->right;
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node<T>* y) {
        Node<T>* x = y->left;
        y->left = x->right;
        if (x->right) x->right->parent = y;
        x->parent = y->parent;
        if (!y->parent)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    void fixInsertion(Node<T>* z) {
        while (z->parent && z->parent->color == RED) {
            Node<T>* gp = z->parent->parent;
            if (z->parent == gp->left) {
                Node<T>* y = gp->right;
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    gp->color = RED;
                    z = gp;
                }
                else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    gp->color = RED;
                    rightRotate(gp);
                }
            }
            else {
                Node<T>* y = gp->left;
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    gp->color = RED;
                    z = gp;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    gp->color = RED;
                    leftRotate(gp);
                }
            }
        }
        root->color = BLACK;
    }

    void transplant(Node<T>* u, Node<T>* v) {
        if (!u->parent)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v) v->parent = u->parent;
    }

    Node<T>* minimum(Node<T>* x) {
        while (x->left) x = x->left;
        return x;
    }

    void fixDeletion(Node<T>* x) {
        while (x != root && (!x || x->color == BLACK)) {
            Node<T>* w = (x == x->parent->left) ? x->parent->right : x->parent->left;
            if (!w) break;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                if (x == x->parent->left)
                    leftRotate(x->parent);
                else
                    rightRotate(x->parent);
                w = (x == x->parent->left) ? x->parent->right : x->parent->left;
            }

            if ((!w->left || w->left->color == BLACK) &&
                (!w->right || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (x == x->parent->left && (!w->right || w->right->color == BLACK)) {
                    if (w->left) w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                else if (x == x->parent->right && (!w->left || w->left->color == BLACK)) {
                    if (w->right) w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (x == x->parent->left && w->right) w->right->color = BLACK;
                else if (x == x->parent->right && w->left) w->left->color = BLACK;

                if (x == x->parent->left)
                    leftRotate(x->parent);
                else
                    rightRotate(x->parent);

                x = root;
            }
        }

        if (x) x->color = BLACK;
    }

    void updateHeightsUpwards(Node<T>* node) {
        while (node) {
            node = node->parent;
        }
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(T value) {
        Node<T>* z = new Node<T>(value);
        Node<T>* y = nullptr;
        Node<T>* x = root;

        while (x) {
            y = x;
            if (z->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;
        if (!y)
            root = z;
        else if (z->data < y->data)
            y->left = z;
        else
            y->right = z;

        fixInsertion(z);
    }

    void deleteNode(T value) {
        Node<T>* z = root;

        while (z && z->data != value) {
            if (value < z->data)
                z = z->left;
            else
                z = z->right;
        }

        if (!z) {
            cout << "Value " << value << " not found in the tree." << endl;
            return;
        }

        Node<T>* y = z;
        Color y_original_color = y->color;
        Node<T>* x = nullptr;

        if (!z->left) {
            x = z->right;
            transplant(z, z->right);
        }
        else if (!z->right) {
            x = z->left;
            transplant(z, z->left);
        }
        else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                if (x) x->parent = y;
            }
            else {
                transplant(y, y->right);
                y->right = z->right;
                if (y->right) y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            if (y->left) y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (y_original_color == BLACK && x)
            fixDeletion(x);

        if (x && x->parent)
            updateHeightsUpwards(x->parent);
    }

    void inorder(Node<T>* node) const {
        if (node) {
            inorder(node->left);
            cout << node->data << " ";
            if (node->color == 0)
                cout << "Red" << endl;
            else
                cout << "Black" << endl;
            inorder(node->right);
        }
    }

    void preorder(Node<T>* node) const {
        if (node) {
            cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(Node<T>* node) const {
        if (node) {
            postorder(node->left);
            postorder(node->right);
            cout << node->data << " ";
        }
    }

    void inorderTraversal() const {
        inorder(root);
        cout << endl;
        postorder(root);
        cout << endl;
        preorder(root);
        cout << endl;
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
       // tree.inorder();
    }
    tree.inorderTraversal();

    int value;
    cout << "Enter the value to be deleted: ";
    cin >> value;
    tree.deleteNode(value);
    tree.inorderTraversal();

    return 0;
}