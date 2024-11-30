//
// Created by hamza on 11/26/2024.
//

#ifndef GLOBALS_H
#define GLOBALS_H

enum tree_type {
    AVL,
    RBT,
    BTree
};

enum rdt_color {
    RED,
    BLACK
};

enum hash_type {
    I_HASH,
    SHA256
};

// csv data
enum gender {
    Male,
    Female
};

enum blood_group {
    A_N,
    A_P,
    B_N,
    B_P,
    O_N,
    O_P,
    AB_N,
    AB_P
};

enum admission_type {
    Elective,
    Urgent,
    Emergency,
};

MyString blood_group_str[8] = {"A-", "A+", "B-", "B+", "O-", "O+", "AB-",
    "AB+"};


enum test_results {
    Normal,
    Abnormal,
    Inconclusive
};

MyString test_result_str[3] = {"Normal", "Abnormal", "Inconclusive"};




#endif //GLOBALS_H
