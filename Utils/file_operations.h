//
// Created by hamza on 11/26/2024.
//

#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H
#include <filesystem>
#include <fstream>
#include <string>

using std::ios;
using std::string;
using std::getline;
#include "../STL_STRUCTURES/MyList.h"
#include "../STL_STRUCTURES/MyString.h"

inline MyList<MyString> get_columns(const std::filesystem::path& csv_path) {
    std::ifstream file(csv_path, ios::in);
    MyList<MyString> columns;
    string line;
    if (file.is_open()) {
        getline(file, line);
        int i = 0;
        while (line[i] != '\0') {
            MyString col_name;
            while (line[i] != ',' && line[i] != '\0') {
                col_name.insert_char(line[i]);
                i++;
            }
            columns.insert(col_name);
            i++;
        }
    }
    else {
        throw std::runtime_error("File not found at extracting columns");
    }
    return columns;
}

// read specified entries for specific columns

#endif //FILE_OPERATIONS_H
