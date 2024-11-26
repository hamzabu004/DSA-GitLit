//
// Created by hamza on 11/26/2024.
//

#ifndef GITLITE_H
#define GITLITE_H
#include "STL_STRUCTURES/MyString.h"
#include <iostream>
#include <filesystem>

using std::filesystem::path;

using std::endl;
using std::cout;

class GitLite {
    path csv_path = "";
	MyString title_str = "   ________.__  __  .____    .__  __          \n  /  _____/|__|/  |_|    |   |__|/  |_  ____ \n /   \\  ___|  \\   __\\    |   |  \\   __\\/ __ \\ \n \\    \\_\\  \\  ||  | |    |___|  ||  | \\  ___/ \n  \\______  /__||__| |_______ \\__||__|  \\___  > \n         \\/                 \\/             \\/";
public:
    void welcome();
    void init_menu();
    void git_menu();
    void git_init();
    void git_add();
    void git_commit();
    void git_log();
    void git_checkout();
    void git_reset();
    void run();

};



#endif //GITLITE_H
