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
    new_node.data.insert(rows[0]);
    new_node.key = rows[0].name;
    new_node.hash = "hash";

    avl_tree = insert_avl_node(new_node, avl_tree);
    cout << avl_tree << endl;
}
*/
TEST(AVL, ReadNode) {
    csv_row rows[1];
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

    std::filesystem::path avl_tree = "John Doe";
    fstream file(avl_tree, ios::in);
    AVL_NODE<MyString> node;
    file >> node;
    ASSERT_EQ(node.key, rows[0].name);
    ASSERT_EQ(node.data[0].name, rows[0].name);
    ASSERT_EQ(node.data[0].age, rows[0].age);
    ASSERT_EQ(node.data[0].gender, rows[0].gender);
    ASSERT_EQ(node.data[0].blood_group, rows[0].blood_group);
    ASSERT_EQ(node.data[0].medical_condition, rows[0].medical_condition);
    ASSERT_EQ(node.data[0].date, rows[0].date);
    ASSERT_EQ(node.data[0].doctor, rows[0].doctor);
    ASSERT_EQ(node.data[0].hospital, rows[0].hospital);
    ASSERT_EQ(node.data[0].insurance_provider, rows[0].insurance_provider);
    ASSERT_EQ(node.data[0].billing_sum, rows[0].billing_sum);
    ASSERT_EQ(node.data[0].room_no, rows[0].room_no);
    ASSERT_EQ(node.data[0].admission_type, rows[0].admission_type);
    ASSERT_EQ(node.data[0].discharge_date, rows[0].discharge_date);
    ASSERT_EQ(node.data[0].medication, rows[0].medication);
    ASSERT_EQ(node.data[0].test_result, rows[0].test_result);
    ASSERT_EQ(node.hash, "hash");

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
