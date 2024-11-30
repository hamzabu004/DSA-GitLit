//
// Created by ht on 11/30/24.
//


#include <gtest/gtest.h>
#include <filesystem>
#include "../Advance_Structures/CSV.h"
#include "../GLOBALS.h"
#include "../Advance_Structures/AVL.h"


TEST(AVL, INSERTROOTNODE) {
    csv_row rows[1];
    AVL_NODE<MyString> new_node;
    std::filesystem::path avl_tree = "";
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
    new_node.data.insert(rows[0]);
    new_node.key = rows[0].name;
    new_node.hash = "hash";


    avl_tree = insert_avl_node(new_node, avl_tree);
    cout << avl_tree << endl;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
