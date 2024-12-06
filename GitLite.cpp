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
    cin >> csv_path;
    if (!std::filesystem::exists(csv_path)) {
        cout << "File not found\n";
        throw std::runtime_error("File not found");
    }

    cout << "Enter repo name: ";
    cin >> git_info.repo_name;

    MyList<MyString> columns = get_columns(csv_path);
    cout << "Columns: " << endl;

    for (int i = 0; i < columns.get_size(); i++) {
        cout << i << ". " << columns[i] << endl;
    }

    cout << "Select Column(0-indexed): ";
    cin >> structure_info.selected_col;

    cout << "Enter preferred tree type (0 for AVL, 1 for Red-Black, 2 for Btree): ";
    cin >> structure_info.tree_type;
    if (structure_info.tree_type == tree_type::BTree) {
        cout << "Enter Btree order: ";
        cin >> structure_info.btree_order;
    }
    else if (structure_info.tree_type != tree_type::AVL && structure_info.tree_type != tree_type::RBT) {
        cout << "Invalid tree type. Selecting default_tree\n";
        structure_info.btree_order = tree_type::AVL;
    }

    cout << "Enter preferred hash type (0 for custom hash, 1 for SHA256): ";
    cin >> structure_info.hash;
    if (structure_info.hash != hash_type::I_HASH && structure_info.hash != hash_type::SHA256) {
        cout << "Invalid hash type. Selecting default_hash\n";
        structure_info.hash = hash_type::SHA256;
    }
    git_init();
    // main_menu();


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
                //git_menu();
                break;
            case 2:
                // tree_menu();
                break;
            case 3:
                return;
        }
    }
}

void GitLite::git_init() {
    // check for existing repo
    if (std::filesystem::exists(git_info.repo_name)) {
        cout << "Repo already exists\n";
        // load repo

        return;
    }
    // create folder for repo
    std::filesystem::create_directory(git_info.repo_name);
    // create master branch
    git_info.branches.insert("master");
    git_info.current_branch = 0;

    std::filesystem::create_directory(git_info.repo_name / git_info.branches[0]);
    // tree folder
    std::filesystem::create_directory(git_info.repo_name / git_info.branches[0] / "tree");
    // commit folder
    std::filesystem::create_directory(git_info.repo_name / git_info.branches[0] / "commit");
    // merkle folder
    std::filesystem::create_directory(git_info.repo_name / git_info.branches[0] / "merkle");

    // read op will only read from ram
    // write op will write to disk
    // yet to decide structure of files

}

void GitLite::run() {
    welcome();
}

void GitLite::fill_initial_csv() {
    structure_info.tree_type = tree_type::AVL;
    structure_info.hash = hash_type::SHA256;
    structure_info.btree_order = 0;
    git_info.repo_name = "test_repo";
    structure_info.selected_col = 0;
    csv_path = "data.csv";
}
