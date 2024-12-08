//
// Created by hamza on 11/26/2024.
//

#include "GitLite.h"

#include <thread>

#include "GLOBALS.h"
#include "Advance_Structures/AVL.h"
#include "Advance_Structures/Merkel.h"
#include "Utils/file_operations.h"

void title_printer() {
    MyList<MyString> title_str;
    title_str.insert( "   ________.__  __");
    title_str.insert("  .____    .__  __          \n");
    title_str.insert("  /  _____/|__|/  |_");
    title_str.insert("|    |   |__|/  |    ---\n");
    title_str.insert(" /   \\  ___|  \\   __\\");
    title_str.insert("    |   |  \\   __\\/ __ \\ \n");
    title_str.insert(" \\    \\_\\  \\  ||  | ");
    title_str.insert("|    |___|  ||  | \\  ___/ \n");
    title_str.insert("  \\______  /__||__| ");
    title_str.insert("|_______ \\__||__|  \\___  > \n");
    title_str.insert("         \\/                 ");
    title_str.insert("\\/             \\/\n");

    for (int i = 0; i < title_str.get_size(); i++) {
        cout << GIT_COLOR;
        cout << title_str[i];
        i++;
        cout << LITE_COLOR;
        cout << title_str[i];

    }
    cout << RESET;
    cout << endl;

}

void GitLite::welcome() {
    title_printer();

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

        staging_area.operations += "INSERT\n";
        staging_area.operations += data;
        staging_area.operations += "\n";
        // write to disk
        staging_area.write_meta(git_info.repo_name / git_info.branches[git_info.current_branch]);

        branch_meta.tree_root = AVL::insert_avl_node(new_node, branch_meta.tree_root);
        branch_meta.write_meta(git_info.repo_name);
    }
    else if (structure_info.tree_type == tree_type::RBT) {
        // RBT::insert_rbt_tree();
    }
    else if (structure_info.tree_type == tree_type::BTree) {
        // BTree::insert_btree_tree();
    }
}

void GitLite::delete_tree() {
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


            // ask for which row to delete
            int row = 0;
            cout << "Enter row number to delete (" << 0  << "-"<< node.data.get_size() - 1  << "). -1 for all : ";
            cin >> row;

            staging_area.operations += "DELETE\n";

            if (row == -1 || node.data.get_size() == 1) {



                branch_meta.tree_root = AVL::delete_avl_node(branch_meta.tree_root, search_key);
                for (int i = 0; i < node.data.get_size(); i++) {
                    staging_area.operations += node.data[i];
                    staging_area.operations += "\n";
                }

                // write to disk the change in tree
                branch_meta.write_meta(git_info.repo_name);

            }
            else {
                // staging sht
                staging_area.operations += node.data[row];
                staging_area.operations += "\n";
                staging_area.write_meta(git_info.repo_name / git_info.branches[git_info.current_branch]);
                // staging end
                node.data.remove(row);
                AVL::write_avl_node(key_node, node);
            }

            // saving the staging area to disk
            staging_area.write_meta(git_info.repo_name / git_info.branches[git_info.current_branch]);

        }
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
            cout << "Enter new value: ";
            cin.ignore();
            cin >> new_data;

            MyString staging_data = "UPDATE\n";


            // for all row
            if (row == -1) {
                for (int i = 0; i < node.data.get_size(); i++) {
                    staging_data += node.data[i];
                    update_row(node.data[i], new_data, col);
                }
            }
            else {
                staging_data += node.data[row];
                update_row(node.data[row], new_data, col);

            }

            staging_area.operations += staging_data;
            staging_area.operations += "\n";
            staging_area.write_meta(git_info.repo_name / git_info.branches[git_info.current_branch]);

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
        title_printer();
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
                delete_tree();
                    break;
            case 6:
                return;
        }
    }
}

void GitLite::main_menu() {
    while (true) {
        system("clear");
        title_printer();
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
        title_printer();
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
                git_commit();
                    break;
            case 4:
                git_log();
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
    if (structure_info.hash != hash_type::I_HASH && structure_info.hash != hash_type::shA256) {
        cout << "Invalid hash type. Selecting default_hash\n";
        structure_info.hash = hash_type::shA256;
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
        AVL::parents_folder = git_info.repo_name / git_info.branches[0] / "tree";
        return;
    }
    else {
        initial_data_collection();
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

        AVL::parents_folder = git_info.repo_name / git_info.branches[0] / "tree";
        cout << AVL::parents_folder << endl;
        // tree folder
        std::filesystem::create_directory(git_info.repo_name / git_info.branches[0] / "tree");
        // commit folder
        std::filesystem::create_directory(git_info.repo_name / git_info.branches[0] / "commit");
        // merkle folder
        std::filesystem::create_directory(git_info.repo_name / git_info.branches[0] / "merkle");


        // read op will only read from ram
        // write op will write to disk
        // yet to decide structure of files
        load_csv_into_tree();
        generate_merkle();
    }


}

void GitLite::git_list_branches() {
    for (int i = 0; i < git_info.branches.get_size(); i++) {
        cout << 1 + i << ". " << git_info.branches[i] << endl;
    }
}

void GitLite::git_commit() {
    if (staging_area.operations == "") {
        cout << "No changes to commit\n";
        return;
    }
    MyString commit_message;
    cout << "Enter commit message: ";
    cin.ignore();
    string temp;
    getline(cin, temp);
    commit_message = temp.c_str();
    commit.message = commit_message;
    commit.changes = staging_area.operations;
    staging_area.clear(git_info.repo_name, git_info.branches[git_info.current_branch]);
    commit.write_meta(git_info.repo_name, git_info.branches[git_info.current_branch]);
    branch_meta.commits.insert(commit.timestamp);
    branch_meta.write_meta(git_info.repo_name);
    cout << "Commit successful\n";
    cout << "#############################" << endl;
    cout << "Commit ID: " << commit.timestamp << endl;
    cout << "Message: " << commit.message << endl;
    cout << commit.changes;
    cout << "#############################" << endl;
}

void GitLite::git_log() {
    cout << "Total Commits: " << branch_meta.commits.get_size() << endl;
    for (int i = 0; i < branch_meta.commits.get_size(); i++) {
        commit.read_meta(git_info.repo_name, git_info.branches[git_info.current_branch], branch_meta.commits[i]);
        cout << "#############################" << endl;
        cout << "Commit ID: " << commit.timestamp << endl;
        cout << "Message: " << commit.message << endl;
        cout << commit.changes;
        cout << "#############################" << endl;
    }
}

void GitLite::git_checkout() {
    // if staging area is not empty
    // first commit or ignore changes after last commit
    // return;
    git_list_branches();
    cout << "Enter branch number: ";
    int branch_num;
    cin >> branch_num;
    if (branch_num < 1 || branch_num > git_info.branches.get_size()) {
        cout << "Invalid branch number\n";
        return;
    }
    git_info.current_branch = branch_num - 1;
    branch_meta.read_meta(git_info.repo_name, git_info.branches[git_info.current_branch]);

    cout << "Switched to " << git_info.branches[git_info.current_branch] << endl;
    // delay of 1 sec
    std::this_thread::sleep_for(std::chrono::seconds(1));
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
    main_menu();
}

void GitLite::fill_initial_csv() {
    structure_info.tree_type = tree_type::AVL;
    structure_info.hash = hash_type::shA256;
    structure_info.btree_order = 0;
    git_info.repo_name = "test_repo";
    structure_info.selected_col = 0;
    csv_path = "duta.csv";
}

void GitLite::fill_initial_csv_exisiting(path repo_name) {
    structure_info.tree_type = tree_type::AVL;
    structure_info.hash = hash_type::shA256;
    structure_info.btree_order = 0;
    structure_info.selected_col = 0;
    csv_path = "duta.csv";
    git_info.repo_name = repo_name;

}

void GitLite::load_csv_into_tree() {
    if (structure_info.tree_type == tree_type::AVL) {
        branch_meta.tree_root = AVL::insert_avl(csv_path,
            git_info.repo_name / git_info.branches[git_info.current_branch] / "tree",
            structure_info.selected_col);
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


void GitLite::generate_merkle(){
    path root_file_path = git_info.repo_name / git_info.branches[git_info.current_branch] / "tree" / branch_meta.tree_root;

    std::filesystem::path merkleFolder = git_info.repo_name / git_info.branches[git_info.current_branch] / "merkle";
    std::filesystem::path avlBasePath = git_info.repo_name / git_info.branches[git_info.current_branch] / "tree";

    // Ensure the Merkle folder exists
    if (!std::filesystem::exists(merkleFolder)) {
        std::filesystem::create_directories(merkleFolder);
    }

    MerkleTree merkleTree(avlBasePath);
    branch_meta.merkle_root = merkleTree.buildMerkle(root_file_path, merkleFolder).c_str();

    branch_meta.write_meta(git_info.repo_name);
    std::cout << std::endl << "Root Hash: " << branch_meta.merkle_root << std::endl;
}