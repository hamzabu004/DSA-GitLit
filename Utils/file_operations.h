//
// Created by hamza on 11/26/2024.
//

#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "../STL_STRUCTURES/MyList.h"
#include "../STL_STRUCTURES/MyString.h"

#include <filesystem>
#include <fstream>
#include <string>

using std::fstream;
using namespace std::filesystem;

using std::ios;
using std::string;
using std::getline;


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

//open file funciton
inline bool open_file (fstream& file, std::filesystem::path csv_path, int mode = ios::in)
{
    if(mode == ios::in){
          file.open(csv_path, ios::in | ios::binary);
    }
    else{
        file.open(csv_path, ios::out | ios::binary);
    }
    if (!file.is_open()) {
        cout<<"File not found"<<endl;
        return false;
    }
    return true;
}

inline void move_pointer_ahead(fstream& file, int n = 1) {
    file.seekp(n, ios::cur);
}









#endif //FILE_OPERATIONS_H
