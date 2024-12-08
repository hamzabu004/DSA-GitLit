//
// Created by hamza on 11/26/2024.
//

#include "GitLite.h"

#include <thread>

#include "GLOBALS.h"
#include "Advance_Structures/AVL.h"
#include "Utils/file_operations.h"

void GitLite::welcome() {
    cout << title_str << endl;

    cout << "Welcome to GitLite\n";
    cout << "Enter repo name: ";
    cin >> git_info.repo_name;

    git_init();
    // main_menu();


}

void GitLite::print_tree() {
    // print colum names
    for (int i = 0; i < structure_info.col_names.get_size(); i++) {
        // same line with width of 20
        cout << setw(20) ;
        cout << structure_info.col_names[i] << setfill(' ');


    }
    cout << endl;
    if (structure_info.tree_type == tree_type::AVL) {
        AVL::print_avl_tree<MyString>(branch_meta.tree_root);
    }
    else if (structure_info.tree_type == tree_type::RBT) {
        // RBT::print_rbt_tree();
    }
    else if (structure_info.tree_type == tree_type::BTree) {
        // BTree::print_btree_tree();
    }
}

void GitLite::search_tree() {
    MyString search_key;
    cout << "Enter key to search: ";
    std::cin.ignore();
    cin >> search_key;
    if (structure_info.tree_type == tree_type::AVL) {
        path key_node = AVL::search_avl(branch_meta.tree_root, search_key);
        if (key_node == "NULL") {
            cout << "Key not found\n";
            return;
        }
        else {
            prettyPrint(structure_info.col_names);
            AVL_NODE<MyString> node;
            AVL::read_avl_node(key_node, node);
            for (int i = 0; i < node.data.get_size(); i++) {
                prettyPrint(node.data[i]);
            }
        }
    }
    else if (structure_info.tree_type == tree_type::RBT) {
        // RBT::search_rbt_tree();
    }
    else if (structure_info.tree_type == tree_type::BTree) {
        // BTree::search_btree_tree();
    }
}

void GitLite::insert_tree() {
    if (structure_info.tree_type == tree_type::AVL) {
        AVL_NODE<MyString> new_node;
        new_node.key = "NULL";
        new_node.height = 0;
        new_node.left_child = "NULL";
        new_node.right_child = "NULL";
        MyString data;
        // read all fields
        std::cin.ignore();
        for (int i = 0; i < structure_info.num_cols; i++) {
            MyString field;
            // comma for all except first
            if (i != 0) {
                data.insert_char(',');
            }

            cout << "Enter " << structure_info.col_names[i] << ": ";

            cin >> field;

            data += field;
            // set key field
            if (i == structure_info.selected_col) {
                new_node.key = field;
            }
            // data.insert(field);
        }
        new_node.data.insert(data);
        branch_meta.tree_root = AVL::insert_avl_node(new_node, branch_meta.tree_root);
    }
    else if (structure_info.tree_type == tree_type::RBT) {
        // RBT::insert_rbt_tree();
    }
    else if (structure_info.tree_type == tree_type::BTree) {
        // BTree::insert_btree_tree();
    }
}

void GitLite::update_tree() {
    cout << "Enter key to update: ";
    MyString search_key;
    std::cin.ignore();
    cin >> search_key;

    // search for key
    if (structure_info.tree_type == tree_type::AVL) {
        path key_node = AVL::search_avl(branch_meta.tree_root, search_key);
        if (key_node == "NULL") {
            cout << "Key not found\n";
            return;
        }
        else {
            AVL_NODE<MyString> node;
            AVL::read_avl_node(key_node, node);
            prettyPrint(structure_info.col_names);
            for (int i = 0; i < node.data.get_size(); i++) {
                prettyPrint(node.data[i]);
            }

            // select field
            int col;
            cout << "Enter column number to update: ";
            cin >> col;


            // ask for which row to update
            int row = 0;
            cout << "Enter row number to update (" << 0  << "-"<< node.data.get_size() - 1  << "). -1 for all : ";
            cin >> row;

            // get new field value
            MyString new_data;
            cin.ignore();
            cout << "Enter new value: ";
            cin >> new_data;


            // for all row
            if (row == -1) {
                for (int i = 0; i < node.data.get_size(); i++) {
                    update_row(node.data[i], new_data, col);
                }
            }
            else {
                update_row(node.data[row], new_data, col);
            }

            // write to disk
            AVL::write_avl_node(key_node, node);
        }
    }
    else if (structure_info.tree_type == tree_type::RBT) {
        // RBT::update_rbt_tree();
    }
    else if (structure_info.tree_type == tree_type::BTree) {
        // BTree::update_btree_tree();
    }
}


void GitLite::tree_menu() {
    while (true) {
        system("clear");
        cout << title_str << endl;
        cout << "###Tree Menu###\n";
        cout << "1. Print Tree\n";
        cout << "2. Search Tree\n";
        cout << "3. Insert into Tree\n";
        cout << "4. Update into Tree\n";
        cout << "5. Delete from Tree\n";
        cout << "6. Back\n";

        int choice;
        cout << " => ";
        cin >> choice;

        switch (choice) {
            case 1:
                print_tree();
                break;
            case 2:
                search_tree();
                break;
            case 3:
                insert_tree();
                break;
            case 4:
                update_tree();
                    break;
            case 5:
                // delete_tree();
                    break;
            case 6:
                return;
        }
    }
}

void GitLite::main_menu() {
    while (true) {
        system("clear");
        cout << title_str << endl;
        cout << "###Main Menu###\n";
        cout << "Current Branch: " << git_info.branches[git_info.current_branch]
            // << "is uncommit changes\n" << is_stage_empty() ? "No" : "Yes"
        << endl;
        cout << "1. Git Menu\n";
        cout << "2. Tree Menu\n";
        cout << "3. Exit\n";

        int choice;
        cout << " => ";
        cin >> choice;

        switch (choice) {
            case 1:
                git_menu();
                break;
            case 2:
                tree_menu();
                break;
            case 3:
                return;
        }
    }
}

void GitLite::git_menu() {
    // git menu
    // merge, branch, commit, log, checkout
    while (true) {
        system("clear");
        cout << title_str << endl;
        cout << "###Git Menu###\n";
        cout << "Current Branch: " << git_info.branches[git_info.current_branch] << endl;
        cout << "1. New Branch\n";
        cout << "2. List Branch\n";
        cout << "3. Commit\n";
        cout << "4. Log\n";
        cout << "5. Checkout\n";
        cout << "6. Merge\n";
        cout << "7. Exit\n";

        int choice;
        cout << " => ";
        cin >> choice;

        switch (choice) {
            case 1:
                git_new_branch();
            break;
            case 2:
                git_list_branches();
                    break;
            case 3:
                // git_commit();
                    break;
            case 4:
                // git_log();
                    break;
            case 5:
                git_checkout();
                    break;
            case 6:
                // git_merge();
                    break;
                break;
            case 7:
                return;
        }
    }
}

void GitLite::initial_data_collection() {
    cout << "Enter full csv path: ";
    cin >> csv_path;
    if (!std::filesystem::exists(csv_path)) {
        cout << "File not found\n";
        throw std::runtime_error("File not found");
    }

    structure_info.col_names = get_columns(csv_path);
    structure_info.num_cols = structure_info.col_names.get_size();
    cout << "Columns: " << endl;

    for (int i = 0; i < structure_info.num_cols; i++) {
        cout << i << ". " << structure_info.col_names[i] << endl;
    }

    cout << "Select Column(0-indexed): ";
    cin >> structure_info.selected_col;

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
