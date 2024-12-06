//
// Created by tonystark on 27-Nov-24.
//

#ifndef AVL_H
#define AVL_H


#include <filesystem>
#include <fstream>

#include "CSV.h"
#include "../Utils/file_operations.h"



#include "../STL_STRUCTURES/MyList.h"



using namespace std;
using namespace std::filesystem;

inline path parents_folder = "master/tree";

template<typename T>
struct AVL_NODE {

    T key;
    MyList<csv_row> data;
    path left_child;
    path right_child;
    int height;
    // node hash
    MyString hash;
    AVL_NODE(): left_child("NULL"), right_child("NULL"), height(0), hash("") {}

    friend fstream& operator<<(fstream &file_stream,  AVL_NODE &node) {
        file_stream << node.key << endl;
        file_stream << node.data.get_size() << endl;
        for (int i = 0; i < node.data.get_size(); i++) {
            file_stream << node.data[i];
        }
        if (node.left_child == parents_folder || node.left_child == "NULL") {
            file_stream << parents_folder << endl;
        } else {
            file_stream << node.left_child << endl;
        }
        if (node.right_child == parents_folder || node.right_child == "NULL") {
            file_stream << parents_folder << endl;
        } else {
            file_stream << node.right_child << endl;
        }
        file_stream << node.height << endl;
        file_stream << node.hash << endl;
        return file_stream;
    }

    friend fstream& operator>>(fstream &file_stream, AVL_NODE &node) {
        file_stream >> node.key;
        int size;
        file_stream >> size;
        move_pointer_ahead(file_stream);
        for (int i = 0; i < size; i++) {
            csv_row row;
            file_stream >> row;
            node.data.insert(row);
        }
        string left, right;
        file_stream >> node.left_child;
        file_stream >> node.right_child;
        file_stream >> node.height;
        move_pointer_ahead(file_stream);
        file_stream >> node.hash;
        return file_stream;
    }
};




template<typename T>
void write_avl_node(path node_path, AVL_NODE<T> &node) {
    fstream file;
    open_file(file, node_path, ios::out);
    file << node;
    file.close();
}

template<typename T>
void read_avl_node(path node_path, AVL_NODE<T> &node) {
    node.data.clear();
    fstream file;
    open_file(file, node_path, ios::in);
    file >> node;
    file.close();
}



template <typename T>
inline int tree_height(filesystem::path root) {
    if (root == parents_folder) return -1;

    int right = -1;
    int left  = -1;
    AVL_NODE<T> curr_node;
    // need right height
    fstream file;
    read_avl_node<T>(root, curr_node);

    path right_child = curr_node.right_child;
    path left_child = curr_node.left_child;


    if (left_child != parents_folder) {
        read_avl_node<T>(left_child, curr_node);
        left = curr_node.height;
    }
    if (right_child != parents_folder) {
        read_avl_node<T>(right_child, curr_node);
        right = curr_node.height;
    }

    return max(left, right ) + 1;
}

template <typename T>
inline int node_height(path root) {
    if (root == parents_folder) return -1;
    AVL_NODE<T> curr_node;
    read_avl_node<MyString>(root, curr_node);
    return curr_node.height;
}

template <typename T>
inline int tree_height(AVL_NODE<T>& node) {
    int right = -1;
    int left  = -1;

    path right_child = node.right_child;
    path left_child = node.left_child;

    if (left_child != parents_folder) {
        AVL_NODE<T> curr_node;
        read_avl_node<T>(left_child, curr_node);
        left = curr_node.height;
    }
    if (right_child != parents_folder) {
        AVL_NODE<T> curr_node;
        read_avl_node<T>(right_child, curr_node);
        right = curr_node.height;
    }

    return max(left, right ) + 1;
}

template <typename T>
short get_balance_factor(path root) {
    AVL_NODE<T> curr_node;
    fstream file;
    read_avl_node<T>(root, curr_node);
    path left_child = curr_node.left_child;
    path right_child = curr_node.right_child;
    return (tree_height<T>(right_child) - tree_height<T>(left_child));
}

template<typename T>
path right_rotate(path root) {
    // root's left becomes new_root
    // root's left's right becomes root's left
    AVL_NODE<T> curr_node;
    AVL_NODE<T> left_ram;
    read_avl_node<T>(root, curr_node);
    // this will act as root

    // auto temp = root->left;
    path root_left_child = curr_node.left_child;

    // temp->right = root;
    read_avl_node<T>(root_left_child, left_ram);

    path root_left_right_child = left_ram.right_child;
    curr_node.left_child = root_left_right_child;
    curr_node.height = max(node_height<T>(root_left_right_child) + 1, curr_node.height);
    write_avl_node<T>(root, curr_node);

    left_ram.right_child = root;
    left_ram.height = max(node_height<T>(root) + 1, left_ram.height);
    write_avl_node<T>(root_left_child, left_ram);

    return root_left_child;
}

template<typename T>
path left_rotate(path root) {
    AVL_NODE<T> curr_node;
    AVL_NODE<T> right_ram;
    read_avl_node<T>(root, curr_node);

    // auto* temp = root->right;
    path root_right_child = curr_node.right_child;

    // temp->left = root;
    read_avl_node<T>(root_right_child, right_ram);

    path root_right_left_child = right_ram.left_child;
    curr_node.right_child = root_right_left_child;
    curr_node.height = max(node_height<T>(root_right_left_child) + 1, curr_node.height);
    write_avl_node<T>(root, curr_node);

    right_ram.left_child = root;
    right_ram.height = max(node_height<T>(root) + 1, right_ram.height);
    write_avl_node<T>(root_right_child, right_ram);

    return root_right_child;

}

template<typename T>
filesystem::path balance_avl(filesystem::path root) {
    short balance_factor = get_balance_factor<T>(root);
    if (abs(balance_factor) > 1 ) {
        AVL_NODE<T> curr_node;
        read_avl_node<T>(root, curr_node);
        switch (balance_factor) {
            case 2: {
                // cout << "Left shift" << endl;
                path right_child = curr_node.right_child;
                if (get_balance_factor<T>(right_child) == -1) {
                    right_child = right_rotate<T>(right_child);
                    curr_node.right_child = right_child.c_str();
                    write_avl_node<T>(root, curr_node);
                }
                root = left_rotate<T>(root).c_str();
                break;
            }
            case -2:{
                path left_child = curr_node.left_child;
                if (get_balance_factor<T>(left_child) == 1) {
                    left_child = left_rotate<T>(left_child);
                    curr_node.left_child = left_child.c_str();
                    write_avl_node<T>(root, curr_node);
                }
                // cout << "Right Shift" << endl;
                root = right_rotate<T>(root).c_str();
                break;
            }
            default: ;
        }

    }
    return root;
}

template<typename T>
filesystem::path insert_avl_node(AVL_NODE<T> &node, filesystem::path root_path) {

    static fstream file;
    if (root_path == parents_folder) {
        // cout << "File not found\n inferring that first node of tree...\n";
        // create file.
        filesystem::path node_path = parents_folder / node.key;
        write_avl_node<T>(node_path, node);
        return node_path;
    }



    AVL_NODE<T> curr_node;
    read_avl_node<T>(root_path, curr_node);
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
        cout << "DUp";
        return root_path;
    }
    curr_node.height = max(node_height<T>(curr_node.left_child), node_height<T>(curr_node.right_child)) + 1;
    write_avl_node<T>(root_path, curr_node);

    short balance_factor = get_balance_factor<T>(root_path);
    if (abs(balance_factor) > 1 ) {
        AVL_NODE<T> curr_node;
        read_avl_node<T>(root_path, curr_node);
        switch (balance_factor) {
            case 2: {
                // cout << "Left shift" << endl;
                path right_child = curr_node.right_child;
                if (get_balance_factor<T>(right_child) == -1) {
                    right_child = right_rotate<T>(right_child);
                    curr_node.right_child = right_child.c_str();
                    write_avl_node<T>(root_path, curr_node);
                }
                root_path = left_rotate<T>(root_path);
                break;
            }
            case -2:{
                path left_child = curr_node.left_child;
                if (get_balance_factor<T>(left_child) == 1) {
                    left_child = left_rotate<T>(left_child);
                    curr_node.left_child = left_child;
                    write_avl_node<T>(root_path, curr_node);
                }
                // cout << "Right Shift" << endl;
                root_path = right_rotate<T>(root_path);
                break;
            }
            default: ;
        }

    }

    return root_path;
}


template<typename T>
void print_avl_tree(path root) {
    if (root == parents_folder) return;
    AVL_NODE<T> curr_node;
    read_avl_node<T>(root, curr_node);
    print_avl_tree<T>(curr_node.left_child);
    cout << curr_node.key << endl;
    print_avl_tree<T>(curr_node.right_child);
}

void map_str_row_to_csv_row(char str_row[], csv_row &row) {

    int i = 0;
    while (str_row[i] != ',') {
        row.name.insert_char(str_row[i]);
        i++;
    }
    row.name.to_lower();
    i++;
    while (str_row[i] != ',') {
        row.age = row.age * 10 + (str_row[i] - '0');
        i++;
    }
    i++;
    while (str_row[i] != ',') {
        row.gender.insert_char(str_row[i]);
        i++;
    }
    i++;
    while (str_row[i] != ',') {
        row.blood_group.insert_char(str_row[i]);
        i++;
    }
    i++;
    while (str_row[i] != ',') {
        row.medical_condition.insert_char(str_row[i]);
        i++;
    }
    i++;
    while (str_row[i] != ',') {
        row.date.insert_char(str_row[i]);
        i++;
    }
    i++;
    while (str_row[i] != ',') {
        row.doctor.insert_char(str_row[i]);
        i++;
    }
    i++;
    while (str_row[i] != ',') {
        row.hospital.insert_char(str_row[i]);
        i++;
    }
    i++;
    while (str_row[i] != ',') {
        row.insurance_provider.insert_char(str_row[i]);
        i++;
    }
    i++;
    bool decimal = false;
    int mul = 10;
    while (str_row[i] != ',') {
        // billing sum is float

        if (str_row[i] == '.') {
            decimal = true;
            i++;
            continue;
        }
        if (decimal) {
            int temp = str_row[i] - '0';
            double temp2 = double(temp) / mul;
            row.billing_sum = row.billing_sum + temp2;
            mul *= 10;
        }
        else {
            row.billing_sum = row.billing_sum * 10 + (str_row[i] - '0');
        }
        i++;
    }
    i++;
    while (str_row[i] != ',') {
        row.room_no = row.room_no * 10 + (str_row[i] - '0');
        i++;
    }
    i++;
    while (str_row[i] != ',') {
        row.admission_type.insert_char(str_row[i]);
        i++;
    }
    i++;
    while (str_row[i] != ',') {
        row.discharge_date.insert_char(str_row[i]);
        i++;
    }
    i++;
    while (str_row[i] != ',') {
        row.medication.insert_char(str_row[i]);
        i++;
    }
    i++;
    while (str_row[i] != '\0') {
        row.test_result.insert_char(str_row[i]);
        i++;
    }
}


#endif //AVL_H
