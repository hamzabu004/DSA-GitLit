//
// Created by hamza on 11/26/2024.
//


#include <iostream>
#include <gtest/gtest.h>

TEST(CalculatorTest, HandlesAddition) {
    EXPECT_EQ(5, 5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}