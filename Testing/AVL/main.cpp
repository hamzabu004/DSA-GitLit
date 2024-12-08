//
// Created by ht on 12/4/24.
//

#include "../../Advance_Structures/AVL.h"

path insert_avl() {
    // current time
    path csv_path = "data.csv";
     // path csv_path = "/media/ht/01DB003D88B96CA0/Sem3/Data/Project/dataset20.csv";
    fstream file(csv_path, ios::in);

    AVL::parents_folder = "master";
    // ignore columns
    char temp[10000];
    // ignore first line of columns
    file.getline(temp, 10000);
    path parent = "master/tree";
    std::filesystem::path avl_tree = "NULL";
    int i = 0;
    while (!file.eof() && temp[0] != '\n') {

            AVL_NODE<MyString> new_node;

        file.getline(temp, 10000);
        if (temp[0] == '\0') break;
        MyString row = temp;
        // cout << row << endl;
        new_node.data.insert(row);
        new_node.key = get_column(row, 1);
        // cout << "Inserting node " << i++ << endl;
        avl_tree = AVL::insert_avl_node(new_node, avl_tree);
    }
    cout << endl << "end of teh world" << endl;
    return avl_tree;
}

// int main() {
//     std::ios::sync_with_stdio(false);
//
//     auto start = std::chrono::high_resolution_clock::now();
//
//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> duration = end - start;
//     std::cout << "Time taken by insert_avl: " << duration.count()/60 << " Minutes" << std::endl;
//
//     return 0;
// }

int main() {
    AVL::parents_folder = "master";

    path root = insert_avl();
    AVL::print_avl_tree<MyString>(root);
    MyString key = "62";
    root = AVL::delete_avl_node(root, key);
    cout << "After deletion" << endl;
    AVL::print_avl_tree<MyString>(root);
    cout << root;
    return 0;
}