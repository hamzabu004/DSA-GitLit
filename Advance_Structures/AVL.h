//
// Created by tonystark on 27-Nov-24.
//

#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <filesystem>
#include <fstream>

#include "CSV.h"
#include "../STL_STRUCTURES/MyList.h"

using namespace std;
using namespace std::filesystem;


template<typename T>
struct AVL_NODE {
    T key;
    MyList<csv_row> data;
    filesystem::path left_child;
    filesystem::path right_child;
    int height;
    // node hash
    MyString hash;
    AVL_NODE(): left_child(""), right_child(""), height(0), hash("") {}
    friend fstream& operator<<(fstream &file_stream,  AVL_NODE &node) {
        file_stream << node.key << endl;
        file_stream << node.data.get_size() << endl;
        for (int i = 0; i < node.data.get_size(); i++) {
            file_stream << node.data[i];
        }
        file_stream << node.left_child << endl;
        file_stream << node.right_child << endl;
        file_stream << node.height << endl;
        file_stream << node.hash << endl;
        return file_stream;
    }
};


template<typename T>
filesystem::path insert_avl_node(AVL_NODE<T> &node, filesystem::path root_path) {

    fstream file(root_path, ios::in);

    if (root_path == "") {
        cout << "File not found\n inferring that first node of tree...\n";
        // create file.
        filesystem::path node_path = root_path / node.key;
        file.open(node_path, ios::out);
        file << node;
        file.close();
        return node_path;
    }
    else if (!file.is_open()) {
        cout << "Error opening file\n";
        return root_path;
    }
    return root_path;
}

template<typename U>
auto insert_avl(TreeNode<U> * root, U data) {
    if (!root) {
        return new TreeNode<U>(data);
    }
    if(root->id > data) {
        root->left = insert_avl(root->left, data);
    } else if (root->id < data) {
        root->right = insert_avl(root->right, data);
    }
    root = balance_tree(root);
    root->height = tree_height(root);
    return root;
}



#endif //AVL_H
