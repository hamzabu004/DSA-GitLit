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
public:
    // commit_struct staging_area
    struct {
        path branch_name = "NULL";
        path tree_root = "NULL";
        path merkle_root = "NULL";
        path commit_root = "NULL";
        MyList<path> commits;

        void write_meta(path repo) {
            std::fstream file;
            open_file(file, repo / branch_name / "branch_meta", ios::out);
            file << branch_name << endl;
            file << tree_root << endl;
            file << merkle_root << endl;
            file << commit_root << endl;
            file << commits.get_size() << endl;
            for (int i = 0; i < commits.get_size(); i++) {
                file << commits[i] << endl;
            }
            file.close();
        }
        void read_meta(path repo, path branch) {
            std::fstream file;
            open_file(file, repo / branch / "branch_meta", ios::in);
            file >> branch_name;
            file >> tree_root;
            file >> merkle_root;
            file >> commit_root;
            int size;
            file >> size;
            for (int i = 0; i < size; i++) {
                path commit;
                file >> commit;
                commits.insert(commit);
            }

            file.close();
        }
    } branch_meta;

    struct {
        MyString message = "";
        // timestamp
        path timestamp;
        MyString changes;

        void write_meta(path repo, path branch) {
            timestamp = get_current_date_time();
            std::fstream file;
            open_file(file, repo / branch / "commit" / timestamp, ios::out);
            file << message << endl;
            file << timestamp << endl;
            file << changes << endl;
            file.close();
        }
        void read_meta(path repo, path branch, path commit) {
            changes = "";
            std::fstream file;
            open_file(file, repo / branch / "commit" / commit, ios::in);
            file >> message;
            file >> timestamp;

            char line[1000];
            file.getline(line, 1000);
            while (!file.eof()) {
                changes += line;
                changes += "\n";
                file.getline(line, 1000);
            }
            file.close();
        }

    } commit;

    struct {
        path repo_name;
        MyList<path> branches;
        int current_branch = 0;

        void add_branch(path branch_name) {
            branches.insert(branch_name);
            write_meta();
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

    // commit related

    void add_commit(path commit) {
        if (branch_meta.commits.get_size() == 0) {
            branch_meta.commit_root = commit;
        }
        branch_meta.commits.insert(commit);
        branch_meta.write_meta(git_info.repo_name);
    }

    struct {
        int num_cols;
        MyList<MyString> col_names;
        int selected_col;
        int tree_type;
        int btree_order;
        int hash;

        void write_meta(path repo) {
            std::fstream file;
            open_file(file, repo / "structure_meta", ios::out);
            file << num_cols << endl;
            for (int i = 0; i < col_names.get_size(); i++) {
                file << col_names[i] << endl;
            }
            file << selected_col << endl;
            file << tree_type << endl;
            file << btree_order << endl;
            file << hash;
            file.close();
        }

        void read_meta(path repo) {
            std::fstream file;
            open_file(file, repo / "structure_meta", ios::in);
            file >> num_cols;
            file.get();
            for (int i = 0; i < num_cols; i++) {
                MyString col_name;
                file >> col_name;
                col_names.insert(col_name);
            }
            file >> selected_col;
            file >> tree_type;
            file >> btree_order;
            file >> hash;
            file.close();
        }
    } structure_info;

    struct {
        MyString operations = "";

        void insert(const MyString& data) {
            operations += "INSERT\n";
            operations += data;
            operations += "\n";
        }
        void update(MyString data) {
            operations += "UPDATE\n";
            operations += data;
            operations += "\n";
        }
        void remove(MyString data) {
            operations += "REMOVE\n";
            operations += data;
            operations += "\n";
        }

        void write_meta(const path& parent) {
            std::fstream file;
            open_file(file, parent / "staging_area", ios::out);
            file << operations << endl;
            file.close();
        }
        void read_meta(path repo, path branch) {
            std::fstream file;
            open_file(file, repo / branch / "staging_area", ios::in);
            int size;
            file >> size;
            for (int i = 0; i < size; i++) {
                MyString operation;
                // read line by lien till end
                char line[1000];
                file.getline(line, 1000);
                while (!file.eof() ) {
                    operation += line;
                    operation += "\n";
                    file.getline(line, 1000);
                }
            }
            file.close();
        }

        void clear(path repo, path branch) {
            // clear staging file
            std::fstream file;
            open_file(file, repo / branch / "staging_area", ios::out);
            file.clear();
            file.close();
            operations = "";
        }
    } staging_area;

    // commit structure
    path csv_path;

public:
    void welcome();

    void print_tree();

    void search_tree();

    void insert_tree();

    void delete_tree();

    void update_tree();

    void tree_menu();

    void main_menu();
    void init_menu();
    void git_menu();

    void initial_data_collection();

    void git_init();
    void git_list_branches();
    // related to commit
    void git_commit();
    void git_log();
    void git_checkout();
    void git_new_branch();

    void run();

    // testing
    void fill_initial_csv();

    void fill_initial_csv_exisiting(path repo_name);

    void load_csv_into_tree();

    void generate_merkle();

    void append_stage(MyString);
};

#endif //GITLITE_H
