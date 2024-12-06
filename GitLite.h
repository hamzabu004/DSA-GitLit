//
// Created by hamza on 11/26/2024.
//

#ifndef GITLITE_H
#define GITLITE_H
#include "STL_STRUCTURES/MyString.h"
#include <iostream>
#include <filesystem>

#include "csv_meta.h"
#include "GLOBALS.h"

using std::filesystem::path;

using std::endl;
using std::cout;
using std::cin;

class GitLite {
    struct {
      path tree_root;
      path merkle_root;
      path commit_root;
    } branch_meta;
    struct {
        path repo_name;
        MyList<MyString> branches;
        int current_branch = 0;
    } git_info;
    struct {
        int selected_col;
        int hash;
        int tree_type;
        int btree_order;
        int csv_meta;
    } structure_info;

    // commit structure
    path csv_path;
	MyString title_str = "   ________.__  __  .____    .__  __          \n  /  _____/|__|/  |_|    |   |__|/  |_  ____ \n /   \\  ___|  \\   __\\    |   |  \\   __\\/ __ \\ \n \\    \\_\\  \\  ||  | |    |___|  ||  | \\  ___/ \n  \\______  /__||__| |_______ \\__||__|  \\___  > \n         \\/                 \\/             \\/";

public:
    void welcome();
    void main_menu();
    void init_menu();
    void git_menu();
    void git_init();
    void git_add();
    void git_commit();
    void git_log();
    void git_checkout();
    void git_reset();
    void run();

    // testing
    void fill_initial_csv();
};

#endif //GITLITE_H
