//
// Created by ht on 11/30/24.
//

#include <gtest/gtest.h>
#include <filesystem>
#include "../GLOBALS.h"
#include "../Advance_Structures/AVL.h"
/*
TEST(AVL, INSERTROOTNODE) {

    csv_row rows[1];
    AVL_NODE<MyString> new_node;
    std::filesystem::path avl_tree = "NULL";
    rows[0].name = "John Doe";
    rows[0].age = 30;
    rows[0].gender = gender::Male;
    rows[0].blood_group = blood_group::A_P;
    rows[0].medical_condition = "Healthy";
    rows[0].date = "2024-11-30";
    rows[0].doctor = "Dr. Smith";
    rows[0].hospital = "General Hospital";
    rows[0].insurance_provider = "HealthCare Inc.";
    rows[0].billing_sum = 1234.56;
    rows[0].room_no = 101;
    rows[0].admission_type = admission_type::Elective;
    rows[0].discharge_date = "2024-12-05";
    rows[0].medication = "None";
    rows[0].test_result = test_results::Normal;


    avl_tree = insert_avl_node(new_node, avl_tree);
    cout << avl_tree << endl;
}

TEST(AVL, ReadNode) {
    csv_row rows[2];
    rows[0].name = "John Doe";
    rows[0].age = 30;
    rows[0].gender = gender::Male;
    rows[0].blood_group = blood_group::A_P;
    rows[0].medical_condition = "Healthy";
    rows[0].date = "2024-11-30";
    rows[0].doctor = "Dr. Smith";
    rows[0].hospital = "General Hospital";
    rows[0].insurance_provider = "HealthCare Inc.";
    rows[0].billing_sum = 1234.56;
    rows[0].room_no = 101;
    rows[0].admission_type = admission_type::Elective;
    rows[0].discharge_date = "2024-12-05";
    rows[0].medication = "None";
    rows[0].test_result = test_results::Normal;

    rows[1].name = "Jane Doe";
    rows[1].age = 25;
    rows[1].gender = gender::Female;
    rows[1].blood_group = blood_group::B_N;
    rows[1].medical_condition = "Minor Cold";
    rows[1].date = "2024-12-01";
    rows[1].doctor = "Dr. Adams";
    rows[1].hospital = "City Hospital";
    rows[1].insurance_provider = "Wellness Corp.";
    rows[1].billing_sum = 567.89;
    rows[1].room_no = 202;
    rows[1].admission_type = admission_type::Emergency;
    rows[1].discharge_date = "2024-12-03";
    rows[1].medication = "Cold Medicine";
    rows[1].test_result = test_results::Normal;

    std::filesystem::path avl_tree = "NULL";
    for (int i = 0; i < 2; i++) {
        AVL_NODE<MyString> new_node;
        new_node.key = rows[i].name;
        new_node.data.insert(rows[i]);
        new_node.hash = "HASH";
        avl_tree = insert_avl_node(new_node, avl_tree);
    }


}
*/


TEST(CSV, READEVERYROW) {
    path csv_path = "/media/ht/01DB003D88B96CA0/Sem3/Data/Project/healthcare_dataset.csv";
    // path csv_path = "/media/ht/01DB003D88B96CA0/Sem3/Data/Project/dataset20.csv";
    fstream file(csv_path, ios::in);

    // ignore columns
    char temp[10000];
    // ignore first line of columns
    file.getline(temp, 10000);
    path parent = "master/tree";
    std::filesystem::path avl_tree = parent;

    while (!file.eof() && temp[0] != '\n') {
        AVL_NODE<MyString> new_node;
        csv_row row;
        file.getline(temp, 10000);
        if (temp[0] == '\0') break;
        map_str_row_to_csv_row(temp, row);
        // cout << row << endl;
        new_node.data.insert(row);
        new_node.key = row.name;
        new_node.hash = "HASH";
        new_node.left_child = parents_folder;
        new_node.right_child = parents_folder;

        avl_tree = insert_avl_node(new_node, avl_tree);
    }
    cout << endl << avl_tree << endl << "end of teh world";
}

// TEST(AVL, inorder) {
//     print_avl_tree<MyString>("danny smith");
// }
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
