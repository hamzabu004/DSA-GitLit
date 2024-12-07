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
#include <iomanip>

using std::fstream;
using namespace std::filesystem;

using std::ios;
using std::string;
using std::getline;
using std::left;
using std::setfill;
using std::setw;


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

inline MyList<MyString> get_columns(MyString row) {

    MyList<MyString> columns;
    int i = 0;
    while (row[i] != '\0') {
        MyString col_name;
        while (row[i] != ',' && row[i] != '\0') {
            col_name.insert_char(row[i]);
            i++;
        }
        columns.insert(col_name);
        i++;
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

inline void move_pointer_ahead(fstream& file) {
    move_pointer_ahead(file, 1);
}

inline MyString get_column(MyString row, int col) {
    MyString column;
    int i = 0;
    int j = 0;
    while (row[i] != '\0') {
        if (row[i] == ',') {
            j++;
            i++;
            continue;
        }
        if (j == col) {
            column.insert_char(row[i]);
        }
        i++;
    }
    return column;
}



inline void prettyPrint(MyString row) {
    const int columnWidth = 20;

    MyList<MyString> fields = get_columns(row);
    for (int i = 0; i < fields.get_size(); i++) {

        cout << setw(20);
        cout << fields[i] << setfill(' ');;
    }
    cout << " ";

    cout << endl;
}

inline void prettyPrint(MyList<MyString> fields) {
    const int columnWidth = 20;
    for (int i = 0; i < fields.get_size(); i++) {

        cout << setw(20);
        cout << fields[i] << setfill(' ');;
    }
    cout << " ";

    cout << endl;
}

inline MyString get_str_row(MyList<MyString> fields) {
    MyString row;
    for (int i = 0; i < fields.get_size(); i++) {
        row += fields[i];
        if (i != fields.get_size() - 1) {
            row += ",";
        }
    }
    return row;
}

inline void update_row(MyString& row, MyString updated_val, int col_num) {
    int i = 0;
    int j = 0;
    MyString new_row;
    while (row[i] != '\0') {
        if (row[i] == ',') {
            j++;
            i++;
            continue;
        }
        if (j == col_num) {
            new_row += updated_val;
            i += updated_val.size();
        }
        else {
            new_row.insert_char(row[i]);
        }
        i++;
    }
    file << new_row;
}









#endif //FILE_OPERATIONS_H
