//
// Created by ht on 12/4/24.
//

#include "../../Advance_Structures/AVL.h"
#include <chrono>

path insert_avl() {
    // current time
    path csv_path = "/media/ht/01DB003D88B96CA0/Sem3/Data/Project/healthcare_dataset.csv";
    // path csv_path = "/media/ht/01DB003D88B96CA0/Sem3/Data/Project/dataset20.csv";
    fstream file(csv_path, ios::in);

    // ignore columns
    char temp[10000];
    // ignore first line of columns
    file.getline(temp, 10000);
    path parent = "master/tree";
    std::filesystem::path avl_tree = parent;
    int i = 0;
    while (!file.eof() && temp[0] != '\n') {
        AVL_NODE<MyString> new_node;
        csv_row row;
        file.getline(temp, 10000);
        if (temp[0] == '\0') break;
        map_str_row_to_csv_row(temp, row);
        // cout << row << endl;
        new_node.data.insert(row);
        new_node.key = row.name;
        new_node.hash = "HASH";
        new_node.left_child = parents_folder;
        new_node.right_child = parents_folder;
        // cout << "Inserting node " << i++ << endl;
        avl_tree = insert_avl_node(new_node, avl_tree);
    }
    cout << endl << "end of teh world" << endl;
    return avl_tree;
}

int main() {
    std::ios::sync_with_stdio(false);

    auto start = std::chrono::high_resolution_clock::now();
    path avl_tree = insert_avl();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken by insert_avl: " << duration.count()/60 << " Minutes" << std::endl;

    return 0;
}