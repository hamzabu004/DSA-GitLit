//
// Created by ht on 12/6/24.
//

#include <iostream>
#include "../../GitLite.h"



int main() {
    GitLite git;
    git.fill_initial_csv();
    git.git_init();
    MyString data = "INSERT\nname,age,gender\nhamza,23,male\nali,22,male\n";
    git.staging_area.operations += data;
    git.staging_area.write_meta(git.git_info.repo_name / git.git_info.branches[git.git_info.current_branch]);
    git.staging_area.operations += data;
    git.staging_area.write_meta(git.git_info.repo_name / git.git_info.branches[git.git_info.current_branch]);

    git.git_commit();
//
//    git.main_menu();
    // cout << get_current_date_time();
    return 0;
}