//
// Created by tonystark on 27-Nov-24.
//

#ifndef AVL_H
#define AVL_H


#include <filesystem>
#include <fstream>


#include "../STL_STRUCTURES/MyList.h"
#include "../Utils/file_operations.h"


using namespace std;
using namespace std::filesystem;

template<typename T>
struct AVL_NODE {

    T key;
    MyList<MyString> data;
    path left_child;
    path right_child;
    int height;
    AVL_NODE(): left_child("NULL"), right_child("NULL"), height(0) {}

    friend fstream& operator<<(fstream &file_stream,  AVL_NODE &node) {
        file_stream << node.key << endl;
        file_stream << node.data.get_size() << endl;
        for (int i = 0; i < node.data.get_size(); i++) {
            file_stream << node.data[i];
        }

        file_stream << node.left_child << endl;
        file_stream << node.right_child << endl;

        file_stream << node.height << endl;
        return file_stream;
    }

    friend fstream& operator>>(fstream &file_stream, AVL_NODE &node) {
        file_stream >> node.key;
        int size;
        file_stream >> size;
        move_pointer_ahead(file_stream);
        for (int i = 0; i < size; i++) {
            MyString row;
            file_stream >> row;
            node.data.insert(row);
        }
        string left, right;
        file_stream >> node.left_child;
        file_stream >> node.right_child;
        file_stream >> node.height;
        move_pointer_ahead(file_stream);
        return file_stream;
    }
};



class AVL {
public:
    static path parents_folder;
    static void write_avl_node(path node_path, AVL_NODE<MyString> &node) {
        fstream file;
        open_file(file, AVL::parents_folder / node_path, ios::out);
        file << node;
        file.close();
    }


    static void read_avl_node(path node_path, AVL_NODE<MyString> &node) {
        node.data.clear();
        fstream file;
        open_file(file, AVL::parents_folder / node_path, ios::in);
        file >> node;
        file.close();
    }




    static int tree_height(filesystem::path root) {
        if (root == "NULL") return -1;

        int right = -1;
        int left  = -1;
        AVL_NODE<MyString> curr_node;
        // need right height
        fstream file;
        read_avl_node(root, curr_node);

        path right_child = curr_node.right_child;
        path left_child = curr_node.left_child;


        if (left_child != "NULL") {
            read_avl_node(left_child, curr_node);
            left = curr_node.height;
        }
        if (right_child != "NULL") {
            read_avl_node(right_child, curr_node);
            right = curr_node.height;
        }

        return max(left, right ) + 1;
    }


    static int node_height(path root) {
        if (root == "NULL") return -1;
        AVL_NODE<MyString> curr_node;
        read_avl_node(root, curr_node);
        return curr_node.height;
    }

    static int tree_height(AVL_NODE<MyString>& node) {
        int right = -1;
        int left  = -1;

        path right_child = node.right_child;
        path left_child = node.left_child;

        if (left_child != "NULL") {
            left = node_height(left_child);
        }
        if (right_child != "NULL") {
            right = node_height(right_child);
        }

        return max(left, right ) + 1;
    }


    static short get_balance_factor(path root) {
        AVL_NODE<MyString> curr_node;
        fstream file;
        read_avl_node(root, curr_node);
        path left_child = curr_node.left_child;
        path right_child = curr_node.right_child;
        return (tree_height(right_child) - tree_height(left_child));
    }

    static path right_rotate(path root) {
        // root's left becomes new_root
        // root's left's right becomes root's left
        AVL_NODE<MyString> curr_node;
        AVL_NODE<MyString> left_ram;
        read_avl_node(root, curr_node);
        // this will act as root

        // auto temp = root->left;
        path root_left_child = curr_node.left_child;

        // temp->right = root;
        read_avl_node(root_left_child, left_ram);

        path root_left_right_child = left_ram.right_child;
        curr_node.left_child = root_left_right_child;
        curr_node.height = max(node_height(root_left_right_child) + 1, curr_node.height);
        write_avl_node(root, curr_node);

        left_ram.right_child = root;
        left_ram.height = max(node_height(root) + 1, left_ram.height);
        write_avl_node(root_left_child, left_ram);

        return root_left_child;
    }

    static path left_rotate(path root) {
        AVL_NODE<MyString> curr_node;
        AVL_NODE<MyString> right_ram;
        read_avl_node(root, curr_node);

        // auto* temp = root->right;
        path root_right_child = curr_node.right_child;

        // temp->left = root;
        read_avl_node(root_right_child, right_ram);

        path root_right_left_child = right_ram.left_child;
        curr_node.right_child = root_right_left_child;
        curr_node.height = max(node_height(root_right_left_child) + 1, curr_node.height);
        write_avl_node(root, curr_node);

        right_ram.left_child = root;
        right_ram.height = max(node_height(root) + 1, right_ram.height);
        write_avl_node(root_right_child, right_ram);

        return root_right_child;

    }

    static filesystem::path balance_avl(filesystem::path root) {
        short balance_factor = get_balance_factor(root);
        if (abs(balance_factor) > 1 ) {
            AVL_NODE<MyString> curr_node;
            read_avl_node(root, curr_node);
            switch (balance_factor) {
                case 2: {
                    // cout << "Left shift" << endl;
                    path right_child = curr_node.right_child;
                    if (get_balance_factor(right_child) == -1) {
                        right_child = right_rotate(right_child);
                        curr_node.right_child = right_child.c_str();
                        write_avl_node(root, curr_node);
                    }
                    root = left_rotate(root).c_str();
                    break;
                }
                case -2:{
                    path left_child = curr_node.left_child;
                    if (get_balance_factor(left_child) == 1) {
                        left_child = left_rotate(left_child);
                        curr_node.left_child = left_child.c_str();
                        write_avl_node(root, curr_node);
                    }
                    // cout << "Right Shift" << endl;
                    root = right_rotate(root).c_str();
                    break;
                }
                default: ;
            }

        }
        return root;
    }


    static path insert_avl_node(AVL_NODE<MyString> &node, filesystem::path root_path) {

        static fstream file;
        if (root_path == "NULL") {
            // cout << "File not found\n inferring that first node of tree...\n";
            // create file.
            filesystem::path node_path = node.key.c_str();
            write_avl_node(node_path, node);
            return node_path;
        }



        AVL_NODE<MyString> curr_node;
        read_avl_node(root_path, curr_node);
        // read left and right child

        if (curr_node.key > node.key) {
           // move to left
           // update the left child path
            curr_node.left_child = insert_avl_node(node, curr_node.left_child );

        } else if (curr_node.key < node.key) {
            // move to right
            // update the right child path
            curr_node.right_child = insert_avl_node(node, curr_node.right_child);
        }
        else {
            // key already exists
            curr_node.data.insert(node.data[0]);
            write_avl_node(root_path, curr_node);
            return root_path;
        }
        curr_node.height = max(node_height(curr_node.left_child), node_height(curr_node.right_child)) + 1;
        write_avl_node(root_path, curr_node);

        short balance_factor = get_balance_factor(root_path);
        if (abs(balance_factor) > 1 ) {
            AVL_NODE<MyString> curr_node;
            read_avl_node(root_path, curr_node);
            switch (balance_factor) {
                case 2: {
                    // cout << "Left shift" << endl;
                    path right_child = curr_node.right_child;
                    if (get_balance_factor(right_child) == -1) {
                        right_child = right_rotate(right_child);
                        curr_node.right_child = right_child.c_str();
                        write_avl_node(root_path, curr_node);
                    }
                    root_path = left_rotate(root_path);
                    break;
                }
                case -2:{
                    path left_child = curr_node.left_child;
                    if (get_balance_factor(left_child) == 1) {
                        left_child = left_rotate(left_child);
                        curr_node.left_child = left_child;
                        write_avl_node(root_path, curr_node);
                    }
                    // cout << "Right Shift" << endl;
                    root_path = right_rotate
                    (root_path);
                    break;
                }
                default: ;
            }

        }

        return root_path;
    }


    template<typename T>
    static void print_avl_tree(path root) {
        if (root == "NULL") return;
        AVL_NODE<MyString> curr_node;
        read_avl_node(root, curr_node);
        print_avl_tree<T>(curr_node.left_child);
        cout << curr_node.key << endl;
        print_avl_tree<T>(curr_node.right_child);
    }

    static path insert_avl(path csv_path, path parents_folder, int col = 0) {
        fstream file(csv_path, ios::in);
        AVL::parents_folder = parents_folder;
        // ignore columns
        char temp[10000];
        // ignore first line of columns
        file.getline(temp, 10000);
        path parent = "NULL";
        path avl_tree = "NULL";
        int i = 0;
        while (!file.eof() && temp[0] != '\n') {

            AVL_NODE<MyString> new_node;

            file.getline(temp, 10000);
            if (temp[0] == '\0') break;
            MyString row = temp;
            // cout << row << endl;
            new_node.data.insert(row);
            new_node.key = get_column(row, col);
            // cout << "Inserting node " << i++ << endl;
            avl_tree = insert_avl_node(new_node, avl_tree);
        }
        cout << endl << "end of teh world" << endl;
        return avl_tree;
    }


};

path AVL::parents_folder = "";
#endif //AVL_H
