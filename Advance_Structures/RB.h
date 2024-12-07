//
// Created by muham on 12/7/2024.
//

#ifndef RB_H
#define RB_H


#include<iostream>
#include <filesystem>
#include <fstream>

#include "../STL_STRUCTURES/MyString.h"
#include "../STL_STRUCTURES/MyList.h"
#include "../Utils/file_operations.h"

using namespace std;

enum Color { RED, BLACK };

using namespace std::filesystem;

template<typename T>
struct RedBlack_Node {
    T key;
    MyList<MyString> data;
    Color color;
    path left_child;
    path right_child;
    // node hash
    MyString hash;
    RedBlack_Node() : left_child("NULL"), right_child("NULL"), color(RED), hash("") {}

    friend fstream& operator<<(fstream& file_stream, RedBlack_Node& node) {
        file_stream << node.key << endl;
        file_stream << node.data.get_size() << endl;
        for (int i = 0; i < node.data.get_size(); i++) {
            file_stream << node.data[i];
        }
        if (node.left_child == "NULL" || node.left_child == "") {
            file_stream << "NULL" << endl;
        }
        else {
            file_stream << node.left_child.string() << endl;
        }
        if (node.right_child == "" || node.right_child == "NULL") {
            file_stream << "NULL" << endl;
        }
        else {
            file_stream << node.right_child.string() << endl;
        }
        file_stream << node.hash << endl;
        return file_stream;
    }

    friend fstream& operator>>(fstream& file_stream, RedBlack_Node& node) {
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
        move_pointer_ahead(file_stream);
        file_stream >> node.hash;
        return file_stream;
    }
};

template<typename T>
void write_RedBlack_node(path node_path, RedBlack_Node<T>& node) {
    fstream file;
    open_file(file, node_path, ios::out);
    file << node;
    file.close();
}

template<typename T>
void read_RedBlack_node(path node_path, RedBlack_Node<T>& node) {
    node.data.clear();
    fstream file;
    open_file(file, node_path, ios::in);
    file >> node;
    file.close();
}


template<typename T>
path rightRotate(path y_path, path root) {
    RedBlack_Node<T> y, x, temp;
    read_RedBlack_node(y_path, y);

    read_RedBlack_node(y.left_child, x);

    y.left_child = x.right_child;
    if (x.right_child != "NULL") {
        read_RedBlack_node(x.right_child, temp);
        temp.hash = y.hash;
        write_RedBlack_node(x.right_child, temp);
    }

    x.hash = y.hash;
    if (y.hash == "") {
        root = y.left_child;
    }
    else {
        RedBlack_Node<T> parent;
        path parent_path = y.hash;
        read_RedBlack_node(parent_path, parent);

        if (parent.left_child == y_path)
            parent.left_child = y.left_child;
        else
            parent.right_child = y.left_child;

        write_RedBlack_node(parent_path, parent);
    }

    x.right_child = y_path;
    y.hash = y.left_child;

    write_RedBlack_node(y_path, y);
    write_RedBlack_node(y.left_child, x);

    return y.left_child;
}

template<typename T>
path leftRotate(path x_path, path root) {
    RedBlack_Node<T> x, y, temp;
    read_RedBlack_node(x_path, x);

    if (x.right_child == "NULL")
        return "NULL";
    read_RedBlack_node(x.right_child, y);

    x.right_child = y.left_child;
    if (y.left_child != "NULL")
    {
        read_RedBlack_node(y.left_child, temp);
        temp.hash = x.hash;
        write_RedBlack_node(y.left_child, temp);
    }

    y.hash = x.hash;
    if (x.hash == "")
    {
        root = x.right_child;
    }
    else {
        RedBlack_Node<T> parent;
        path parent_path = x.hash;
        read_RedBlack_node(parent_path, parent);

        if (parent.left_child == x_path)
            parent.left_child = x.right_child;
        else
            parent.right_child = x.right_child;

        write_RedBlack_node(parent_path, parent);
    }

    y.left_child = x_path;
    x.hash = y.left_child;

    write_RedBlack_node(x_path, x);
    write_RedBlack_node(x.right_child, y);

    return x.right_child;
}

template<typename T>
filesystem::path fix_insertion(filesystem::path root_path, filesystem::path z_path,
      path root) {
    RedBlack_Node<T> z, parent, grandparent, uncle;

    while (true) {
        read_RedBlack_node(z_path, z);

        if (z.hash == "NULL") break;
        read_RedBlack_node(z.hash, parent);

        if (parent.color == BLACK) break;

        filesystem::path gp_path = parent.hash;
        if (gp_path == "NULL") break;
        read_RedBlack_node(gp_path, grandparent);

        if (parent.hash == grandparent.left_child) {
            filesystem::path uncle_path = grandparent.right_child;
            if (uncle_path != "NULL")
                read_RedBlack_node(uncle_path, uncle);

            if (uncle_path != "NULL" && uncle.color == RED) {
                parent.color = BLACK;
                uncle.color = BLACK;
                grandparent.color = RED;
                z_path = gp_path;
            }
            else {
                if (z_path == parent.right_child) {
                    z_path = parent.hash;
                    leftRotate<MyString>(z_path, root);
                }

                read_RedBlack_node(z_path, z);
                read_RedBlack_node(z.hash, parent);
                parent.color = BLACK;
                grandparent.color = RED;
                rightRotate<MyString>(gp_path, root);
            }
        }
        else {
            filesystem::path uncle_path = grandparent.left_child;
            if (uncle_path != "NULL")
                read_RedBlack_node(uncle_path, uncle);

            if (uncle_path != "NULL" && uncle.color == RED) {
                parent.color = BLACK;
                uncle.color = BLACK;
                grandparent.color = RED;
                z_path = gp_path;
            }
            else {
                if (z_path == parent.left_child) {
                    z_path = parent.hash;
                    rightRotate<T>(z_path, root);
                }

                read_RedBlack_node(z_path, z);
                read_RedBlack_node(z.hash, parent);
                parent.color = BLACK;
                grandparent.color = RED;
                leftRotate<T>(gp_path, root);
            }
        }
    }

    read_RedBlack_node(root_path, z);
    z.color = BLACK;
    write_RedBlack_node(root_path, z);

    return root_path;
}

template<typename T>
filesystem::path insert_redblack_node(RedBlack_Node<T>& z, filesystem::path root_path) {
    // Node paths
    filesystem::path y_path = "NULL";
    filesystem::path x_path = root_path;

    // Traverse the tree to find the correct position for the new node
    while (x_path != "NULL") {
        RedBlack_Node<T> x;
        read_RedBlack_node(x_path, x);
        y_path = x_path;

        if (z.key < x.key)
            x_path = x.left_child;
        else
            x_path = x.right_child;
    }

    z.hash = y_path;

    if (y_path == "NULL") {
        root_path = filesystem::path(std::to_string(z.key));
        write_RedBlack_node(root_path, z);
    }
    else {
        RedBlack_Node<T> y;
        read_RedBlack_node(y_path, y);

        if (z.key < y.key)
            y.left_child = filesystem::path(std::to_string(z.key));
        else
            y.right_child = filesystem::path(std::to_string(z.key));

        write_RedBlack_node(y_path, y);

        // Write the new node
        filesystem::path z_path = filesystem::path(std::to_string(z.key));
        write_RedBlack_node(z_path, z);
    }

    root_path = fix_insertion(root_path, filesystem::path(std::to_string(z.key)));
    return root_path;
}

bool isBlack(const filesystem::path& node_path) {
    if (node_path == "NULL") {
        return true; // Treat null nodes as black.
    }

    RedBlack_Node<MyString> node;
    read_RedBlack_node<MyString>(node_path, node);
    return node.color == BLACK;


    // Handle error case if needed.
    std::cout << "Error reading node from path: " << node_path << std::endl;
    return false;
}

template <typename T>
filesystem::path transplant(filesystem::path u_path, filesystem::path v_path, path root_path) {
    if (u_path == "NULL") {
        return v_path;
    }

    RedBlack_Node<T> u, v;
    read_RedBlack_node(u_path, u);
    if (v_path != "NULL")
        read_RedBlack_node(v_path, v);

    if (u.hash == "NULL") {
        root_path = v_path;
    }
    else {
        RedBlack_Node<T> parent;
        read_RedBlack_node(u.hash, parent);

        if (u_path == parent.left_child) {
            parent.left_child = v_path;
        }
        else {
            parent.right_child = v_path;
        }

        write_RedBlack_node(u.hash, parent);
    }

    if (v_path != "NULL") {
        v.hash = u.hash;
        write_RedBlack_node(v_path, v);
    }

    return v_path;
}

template <typename T>
filesystem::path minimum(filesystem::path x_path) {
    RedBlack_Node<T> x;
    while (x_path != "NULL")
    {
        read_RedBlack_node(x_path, x);
        if (x.left_child == "NULL")
            break;
        x_path = x.left_child;
    }
    return x_path;
}

template <typename T>
void updateHeightsUpwards(filesystem::path node_path) {
    while (node_path != "NULL")
    {
        RedBlack_Node<T> node;
        read_RedBlack_node(node_path, node);

        int left_height = getNodeHeight<T>(node.left_child);
        int right_height = getNodeHeight<T>(node.right_child);

        node.height = max(left_height, right_height) + 1;
        write_RedBlack_node(node_path, node);

        node_path = node.hash;
    }
}


template <typename T>
void fixDeletion(filesystem::path x_path, path root_path) {
    while (x_path != root_path && (x_path == "NULL" || isBlack<T>(x_path))) {
        RedBlack_Node<T> x, parent, w;

        if (x_path != "NULL") read_RedBlack_node(x_path, x);
        if (x.hash != "NULL") read_RedBlack_node(x.hash, parent);

        filesystem::path w_path = (x_path == parent.left_child) ? parent.right_child : parent.left_child;
        if (w_path != "NULL") read_RedBlack_node(w_path, w);

        if (w_path != "NULL" && w.color == RED) {
            w.color = BLACK;
            parent.color = RED;

            if (x_path == parent.left_child) {
                leftRotate<T>(parent.hash);
            }
            else {
                rightRotate<T>(parent.hash);
            }

            w_path = (x_path == parent.left_child) ? parent.right_child : parent.left_child;
            if (w_path != "NULL") read_RedBlack_node(w_path, w);
        }

        if (isBlack<T>(w.left_child) && isBlack<T>(w.right_child)) {
            w.color = RED;
            write_RedBlack_node(w_path, w);
            x_path = parent.hash;
        }
        else {
            if (x_path == parent.left_child && isBlack<T>(w.right_child)) {
                if (w.left_child != "NULL") {
                    RedBlack_Node<T> w_left;
                    read_RedBlack_node(w.left_child, w_left);
                    w_left.color = BLACK;
                    write_RedBlack_node(w.left_child, w_left);
                }

                w.color = RED;
                rightRotate<T>(w_path);
                w_path = parent.right_child;
            }
            else if (x_path == parent.right_child && isBlack<T>(w.left_child)) {
                if (w.right_child != "NULL") {
                    RedBlack_Node<T> w_right;
                    read_RedBlack_node(w.right_child, w_right);
                    w_right.color = BLACK;
                    write_RedBlack_node(w.right_child, w_right);
                }

                w.color = RED;
                leftRotate<T>(w_path);
                w_path = parent.left_child;
            }

            if (w_path != "NULL") {
                read_RedBlack_node(w_path, w);
                w.color = parent.color;
                write_RedBlack_node(w_path, w);
            }

            parent.color = BLACK;
            write_RedBlack_node(parent.hash, parent);

            if (x_path == parent.left_child && w.right_child != "NULL") {
                RedBlack_Node<T> w_right;
                read_RedBlack_node(w.right_child, w_right);
                w_right.color = BLACK;
                write_RedBlack_node(w.right_child, w_right);
            }
            else if (x_path == parent.right_child && w.left_child != "NULL") {
                RedBlack_Node<T> w_left;
                read_RedBlack_node(w.left_child, w_left);
                w_left.color = BLACK;
                write_RedBlack_node(w.left_child, w_left);
            }

            if (x_path == parent.left_child) {
                leftRotate<T>(parent.hash);
            }
            else {
                rightRotate<T>(parent.hash);
            }

            x_path = root_path;
        }
    }

    if (x_path != "NULL") {
        RedBlack_Node<T> x;
        read_RedBlack_node(x_path, x);
        x.color = BLACK;
        write_RedBlack_node(x_path, x);
    }
}

template <typename T>
filesystem::path deleteNode(T value, filesystem::path root_path) {
    if (root_path == "NULL") {
        std::cout << "Tree is empty." << std::endl;
        return root_path;
    }

    RedBlack_Node<T> z;
    if (!read_RedBlack_node(root_path, z)) {
        std::cout << "Error reading the root node." << std::endl;
        return root_path;
    }

    filesystem::path z_path = root_path;
    while (z_path != "NULL" && z.data != value) {
        if (value < z.data)
            z_path = z.left_child;
        else
            z_path = z.right_child;

        if (!read_RedBlack_node(z_path, z)) {
            std::cout << "Value " << value << " not found in the tree." << std::endl;
            return root_path;
        }
    }

    if (z_path == "NULL") {
        std::cout << "Value " << value << " not found in the tree." << std::endl;
        return root_path;
    }

    RedBlack_Node<T> y = z;
    Color y_original_color = y.color;
    filesystem::path x_path = "NULL";
    RedBlack_Node<T> x;

    if (z.left_child == "NULL") {
        x_path = z.right_child;
        transplant(z_path, z.right_child);
    }
    else if (z.right_child == "NULL") {
        x_path = z.left_child;
        transplant(z_path, z.left_child);
    }
    else {
        filesystem::path y_path = minimum(z.right_child);
        if (!read_RedBlack_node(y_path, y)) {
            cout << "Error reading successor node." << endl;
            return root_path;
        }

        y_original_color = y.color;
        x_path = y.right_child;

        if (y.parent == z_path) {
            if (x_path != "NULL") {
                if (!read_RedBlack_node(x_path, x)) {
                   cout << "Error reading x node." << endl;
                    return root_path;
                }
                x.parent = y_path;
                write_RedBlack_node(x_path, x);
            }
        }
        else {
            transplant(y_path, y.right_child);
            y.right_child = z.right_child;
            RedBlack_Node<T> temp;
            if (read_RedBlack_node(y.right_child, temp)) {
                temp.parent = y_path;
                write_RedBlack_node(y.right_child, temp);
            }
        }

        transplant<MyString>(z_path, y_path, root_path);
        y.left_child = z.left_child;
        if (!read_RedBlack_node(y.left_child, x)) {
            x.parent = y_path;
            write_RedBlack_node(y.left_child, x);
        }
        y.color = z.color;
        write_RedBlack_node(y_path, y);
    }

    filesystem::remove(z_path);

    if (y_original_color == BLACK && x_path != "NULL") {
        if (!read_RedBlack_node(x_path, x)) {
            std::cout << "Error reading node x during fix-up." << std::endl;
            return root_path;
        }
        fixDeletion<MyString>(x_path, root_path);
    }

    return root_path;
}








#endif //RB_H
