//
// Created by hamza on 11/27/2024.
//

#ifndef CSV_META_H
#define CSV_META_H
#include <filesystem>

#include "STL_STRUCTURES/MyString.h"
// #include "STL_STRUCTURES/MYList.h"


struct CSV_META {
    std::filesystem::path filename;
    int columns;
    // MyList<int> col_names; // array of col names
    // array of selected cols


};

#endif //CSV_META_H
