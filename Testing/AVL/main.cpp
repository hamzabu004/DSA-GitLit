//
// Created by ht on 12/4/24.
//

#include "../../Advance_Structures/AVL.h"

MyString get_key(csv_row& row, int selected_col) {
    switch (selected_col) {
        case 0:
            return row.name;
        case 1:
            return to_string(row.age).c_str();
        case 2:
            return row.gender;
        case 3:
            return row.blood_group;
        case 4:
            return row.medical_condition;
        case 5:
            return row.date;
        case 6:
            return row.doctor;
        case 7:
            return row.hospital;
        case 8:
            return row.insurance_provider;
        case 9:
            return to_string(row.billing_sum).c_str();
        case 10:
            return to_string(row.room_no).c_str();
        case 11:
            return row.admission_type;
        case 12:
            return row.discharge_date;
        case 13:
            return row.medication;
        case 14:
            return row.test_result;
        default:
            return "";
    }
}
path insert_avl() {
    // current time
    path csv_path = "data.csv";
    // path csv_path = "/media/ht/01DB003D88B96CA0/Sem3/Data/Project/dataset20.csv";
    fstream file(csv_path, ios::in);

    AVL::parents_folder = "master/tree";
    // ignore columns
    char temp[10000];
    // ignore first line of columns
    file.getline(temp, 10000);
    path parent = "master/tree";
    std::filesystem::path avl_tree = "NULL";
    int i = 0;
    while (!file.eof() && temp[0] != '\n') {

            AVL_NODE<MyString> new_node;
        csv_row row;
        file.getline(temp, 10000);
        if (temp[0] == '\0') break;
        map_str_row_to_csv_row(temp, row);
        // cout << row << endl;
        new_node.data.insert(row);
        new_node.key = get_key(row, 0);
        new_node.hash = "HASH";
        // cout << "Inserting node " << i++ << endl;
        avl_tree = AVL::insert_avl_node(new_node, avl_tree);
    }
    cout << endl << "end of teh world" << endl;
    return avl_tree;
}

// int main() {
//     std::ios::sync_with_stdio(false);
//
//     auto start = std::chrono::high_resolution_clock::now();
//
//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> duration = end - start;
//     std::cout << "Time taken by insert_avl: " << duration.count()/60 << " Minutes" << std::endl;
//
//     return 0;
// }

int main() {

    insert_avl();
    return 0;
}