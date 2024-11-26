cmake_minimum_required(VERSION 3.29)
project(Gtest_Proj)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/7927f8e93d2cc7788229ab446179fdfda15e75e4.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        Gtest_Proj
        main.cpp
        ../../STL_STRUCTURES/MyString.h
)
target_link_libraries(
        Gtest_Proj
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Gtest_Proj)