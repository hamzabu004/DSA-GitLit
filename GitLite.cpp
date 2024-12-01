//
// Created by hamza on 11/26/2024.
//

#include "GitLite.h"

#include "GLOBALS.h"
#include "Utils/file_operations.h"

void GitLite::welcome() {
    cout << title_str << endl;

    cout << "Welcome to GitLite\n";
    cout << "Enter full csv path: ";
    path csv_path;
    cin >> structure_info.csv_meta.filename;
    if (!std::filesystem::exists(structure_info.csv_meta.filename)) {
        cout << "File not found\n";
        throw std::runtime_error("File not found");
    }

    structure_info.csv_meta.col_names = get_columns(structure_info.csv_meta.filename);

    int col_len;
    cout << "Enter number of columns: ";
    cin >> col_len;

    cout << "Enter column index (seperated by space): \n";
    for (int i = 0; i < col_len; i++) {
        int col;
        cin >> col;
        if (col < 0 || col >= structure_info.csv_meta.col_names.get_size()) {
            cout << "Invalid column index\n";
            i--;
            continue;
        }
        structure_info.csv_meta.selected_cols.insert(col);
    }

    cout << "Enter preferred tree type (0 for AVL, 1 for Red-Black, 2 for Btree): ";
    cin >> structure_info.tree;
    if (structure_info.tree == tree_type::BTree) {
        cout << "Enter Btree order: ";
        cin >> tree_info.btree_order;
    }
    else if (structure_info.tree != tree_type::AVL && structure_info.tree != tree_type::RBT) {
        cout << "Invalid tree type. Selecting default_tree\n";
        structure_info.tree = tree_type::AVL;
    }

    cout << "Enter preferred hash type (0 for custom hash, 1 for SHA256): ";
    cin >> structure_info.hash;
    if (structure_info.hash != hash_type::I_HASH && structure_info.hash != hash_type::SHA256) {
        cout << "Invalid hash type. Selecting default_hash\n";
        structure_info.hash = hash_type::SHA256;
    }

    // create csv_meta object
    structure_info.csv_meta.col_names = get_columns(structure_info.csv_meta.filename);
    cout << "Columns: " << structure_info.csv_meta.col_names << endl;
    // read and print specific columns

}

void GitLite::run() {
    welcome();
}
