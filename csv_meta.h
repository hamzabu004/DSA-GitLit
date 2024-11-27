//
// Created by hamza on 11/27/2024.
//

#ifndef CSV_META_H
#define CSV_META_H
#include <filesystem>

#include "STL_STRUCTURES/MyString.h"


struct CSV_META {
    std::filesystem::path filename;
    int columns;
    // array of selected cols


};

#endif //CSV_META_H
