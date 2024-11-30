//
// Created by tonystark on 27-Nov-24.
//

#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <filesystem>

#include "CSV.h"
#include "../STL_STRUCTURES/MyList.h"

using namespace std;
using namespace std::filesystem;


template<typename T>
struct AVL_NODE {
    T key;
    MyList<csv_row> data;
    filesystem::path left_child;
    filesystem::path right_child;
    int height;
    // node hash
    MyString hash;
};



#endif //AVL_H
