//
// Created by hamza on 11/26/2024.
//

#include "GitLite.h"

#include "GLOBALS.h"
#include "Advance_Structures/AVL.h"
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

void GitLite::print_tree() {
    if (structure_info.tree_type == tree_type::AVL) {
        AVL::print_avl_tree<MyString>(git_info.repo_name / git_info.branches[git_info.current_branch] / "tree");
    }
    else if (structure_info.tree_type == tree_type::RBT) {
        // RBT::print_rbt_tree();
    }
    else if (structure_info.tree_type == tree_type::BTree) {
        // BTree::print_btree_tree();
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
        cout << "4. Delete from Tree\n";
        cout << "5. Back\n";

        int choice;
        cout << " => ";
        cin >> choice;

        switch (choice) {
            case 1:
                print_tree();
                break;
            case 2:
                // search_tree();
                break;
            case 3:
                // insert_tree();
                break;
            case 4:
                // delete_tree();
                break;
            case 5:
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
        cout << "6. Exit\n";

        int choice;
        cout << " => ";
        cin >> choice;

        switch (choice) {
            case 1:
                git_new_branch();
            break;
            case 2:
                // list_branch();
                    break;
            case 3:
                // commit();
                    break;
            case 4:
                // log();
                    break;
            case 5:
                // checkout();
                    break;
            case 6:
                return;
        }
    }
}

void GitLite::git_init() {
    // check for existing repo
    if (std::filesystem::exists(git_info.repo_name)) {
        cout << "Repo already exists\n";
        // load repo, branch, strcuture info
        git_info.read_meta();
        branch_meta.read_meta(git_info.repo_name, git_info.branches[git_info.current_branch]);
        structure_info.read_meta(git_info.repo_name);


        return;
    }
    else {
        load_csv_into_tree();
    }
    // create folder for repo
    std::filesystem::create_directory(git_info.repo_name);
    // create master branch
    git_info.branches.insert("master");
    git_info.current_branch = 0;

    // write meta data to disk
    git_info.write_meta();



    // moving toward branch`s folder
    std::filesystem::create_directory(git_info.repo_name / git_info.branches[0]);
    branch_meta.branch_name = git_info.branches[0];
    branch_meta.write_meta(git_info.repo_name);

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

void GitLite::git_new_branch() {
    cout << "Enter branch name: ";
    path branch_name;
    cin >> branch_name;
    // check if branch already exists
    for (int i = 0; i < git_info.branches.get_size(); i++) {
        if (git_info.branches[i] == branch_name) {
            cout << "Branch already exists\n";
            return;
        }
    }

    git_info.add_branch(branch_name);
    git_info.write_meta();

    // create al necessary dirs
    std::filesystem::create_directory(git_info.repo_name / branch_name);
    std::filesystem::create_directory(git_info.repo_name / branch_name / "tree");
    std::filesystem::create_directory(git_info.repo_name / branch_name / "commit");
    std::filesystem::create_directory(git_info.repo_name / branch_name / "merkle");

    // copy required data only
    std::filesystem::copy(git_info.repo_name / git_info.branches[git_info.current_branch] / "tree",
        git_info.repo_name / branch_name / "tree", std::filesystem::copy_options::recursive);
    std::filesystem::copy(git_info.repo_name / git_info.branches[git_info.current_branch] / "merkle",
        git_info.repo_name / branch_name / "merkle", std::filesystem::copy_options::recursive);

    branch_meta.branch_name = branch_name;
    branch_meta.commit_root = "NULL";
    branch_meta.write_meta(git_info.repo_name);
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

void GitLite::load_csv_into_tree() {
    if (structure_info.tree_type == tree_type::AVL) {
        branch_meta.tree_root = AVL::insert_avl(csv_path,
            git_info.repo_name / git_info.branches[git_info.current_branch] / "tree");
        structure_info.tree_type = tree_type::AVL;

        // sync with disc
        branch_meta.write_meta(git_info.repo_name);
        structure_info.write_meta(git_info.repo_name);
    }
    else if (structure_info.tree_type == tree_type::RBT) {
        // RBT::insert_rbt();
    }
    else if (structure_info.tree_type == tree_type::BTree) {
        // BTree::insert_btree();
    }


}
