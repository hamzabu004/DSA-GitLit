//
// Created by hamza on 11/27/2024.
//

#ifndef CSV_META_H
#define CSV_META_H
#include <filesystem>

#include "STL_STRUCTURES/MyString.h"
#include "STL_STRUCTURES/MYList.h"


struct CSV_META {
    std::filesystem::path filename;
    int columns;
    MyList<MyString> col_names; // array of col names
    MyList<int> selected_cols;



    // array of selected cols


};

#endif //CSV_META_H
