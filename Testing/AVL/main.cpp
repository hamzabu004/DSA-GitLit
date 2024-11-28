//
// Created by hamza on 11/26/2024.
//


#include <iostream>
#include "../../STL_STRUCTURES/MyList.h"
#include "../../STL_STRUCTURES/MyString.h"
#include <gtest/gtest.h>

TEST(ListTest, InsertTest) {
    MyList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    EXPECT_EQ(list.get_size(), 5);
}

TEST(ListTest, RemoveTest) {
    MyList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    list.remove_element(3);
    EXPECT_EQ(list.get_size(), 4);
}

TEST(ListTest, RemoveTest2) {
    MyList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    list.remove_element(1);
    EXPECT_EQ(list.get_size(), 4);
}

TEST(ListTest, elemnet_verficaton) {
    MyList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    list.remove_element(3);
    list.remove_element(1);
    // check if 1 and 3 are removed
    for (int i = 1; i < list.get_size(); i++) {
        EXPECT_NE(list[i], 1);
        EXPECT_NE(list[i], 3);
    }
    int &i = list[0];
    i = 5;
    // check for other elements
    EXPECT_EQ(list[0], 5);
    EXPECT_EQ(list[1], 4);
    EXPECT_EQ(list[2], 5);
    // EXPECT_EQ(list[3], 0);

}


TEST(StringTest, StringTest) {
    MyString s = "Hello";
    MyString s2 = s;
    s2.insert_char('!');
    EXPECT_NE(s2, s);

}


TEST(StringTest, StringTest2) {
    MyString s = "Hello";
    MyString s2 = s;
    s2.insert_char('!');
    s2.to_upper();
    s = "HELLO";
    ASSERT_FALSE(s2 < s);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}