//
// Created by ht on 12/6/24.
//

#include <iostream>
#include "../../GitLite.h"

int main() {
    GitLite git;
    git.fill_initial_csv();
    git.git_init();

    git.main_menu();
}