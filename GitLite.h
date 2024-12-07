//
// Created by hamza on 11/26/2024.
//

#ifndef GITLITE_H
#define GITLITE_H
#include "STL_STRUCTURES/MyString.h"
#include "STL_STRUCTURES/MyList.h"
#include <iostream>
#include <filesystem>
#include <fstream>

#include "GLOBALS.h"
#include "Utils/file_operations.h"

using std::filesystem::path;

using std::endl;
using std::cout;
using std::cin;

class GitLite {
    // commit_struct staging_area

    struct {
        path branch_name = "NULL";
        path tree_root = "NULL";
        path merkle_root = "NULL";
        path commit_root = "NULL";

        void write_meta(path repo) {
            std::fstream file;
            open_file(file, repo / branch_name / "branch_meta", ios::out);
            file << branch_name << endl;
            file << tree_root << endl;
            file << merkle_root << endl;
            file << commit_root;
            file.close();
        }
        void read_meta(path repo, path branch) {
            std::fstream file;
            open_file(file, repo / branch / "branch_meta", ios::in);
            file >> branch_name;
            file >> tree_root;
            file >> merkle_root;
            file >> commit_root;
            file.close();
        }
    } branch_meta;

    struct {
        path repo_name;
        MyList<path> branches;
        int current_branch = 0;

        void add_branch(path branch_name) {
            branches.insert(branch_name);
        }
        void write_meta() {
            std::fstream file;
            open_file(file, repo_name / "git_meta", ios::out);
            file << repo_name << endl;
            file << branches.get_size() << endl;
            for (int i = 0; i < branches.get_size(); i++) {
                file << branches[i] << endl;
            }
            file << current_branch;
            file.close();
        }
        void read_meta() {
            std::fstream file;
            open_file(file, repo_name / "git_meta", ios::in);
            file >> repo_name;
            int size;
            file >> size;
            // move_pointer_ahead(file);
            for (int i = 0; i < size; i++) {
                path branch;
                file >> branch;
                branches.insert(branch);
            }
            file >> current_branch;
            file.close();
        }
    } git_info;

    struct {
        int selected_col;
        int tree_type;
        int btree_order;
        int hash;

        void write_meta(path repo) {
            std::fstream file;
            open_file(file, repo / "structure_meta", ios::out);
            file << selected_col << endl;
            file << tree_type << endl;
            file << btree_order << endl;
            file << hash;
            file.close();
        }


        void read_meta(path repo) {
            std::fstream file;
            open_file(file, repo / "structure_meta", ios::in);
            file >> selected_col;
            file >> tree_type;
            file >> btree_order;
            file >> hash;
            file.close();
        }
    } structure_info;

    // commit structure
    path csv_path;
	MyString title_str = "   ________.__  __  .____    .__  __          \n  /  _____/|__|/  |_|    |   |__|/  |_  ____ \n /   \\  ___|  \\   __\\    |   |  \\   __\\/ __ \\ \n \\    \\_\\  \\  ||  | |    |___|  ||  | \\  ___/ \n  \\______  /__||__| |_______ \\__||__|  \\___  > \n         \\/                 \\/             \\/";

public:
    void welcome();

    void print_tree();

    void tree_menu();

    void main_menu();
    void init_menu();
    void git_menu();
    void git_init();
    void git_add();
    void git_commit();
    void git_log();
    void git_checkout();
    void git_reset();
    void git_new_branch();

    void run();

    // testing
    void fill_initial_csv();

    void load_csv_into_tree();
};

#endif //GITLITE_H
