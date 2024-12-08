cmake_minimum_required(VERSION 3.29)
project(Hashing_MAIN)

set(CMAKE_CXX_STANDARD 20)
find_package(OpenSSL REQUIRED)

add_executable(Hashing_MAIN
        main.cpp
        ../../GLOBALS.h
        ../../Utils/file_operations.h
        ../../STL_STRUCTURES/MyList.h

        ../../Advance_Structures/AVL.h
        ../../Advance_Structures/Merkel.h
        ../../STL_STRUCTURES/MyString.h
        ../../Utils/hasher.h

)

target_link_libraries(Hashing_MAIN OpenSSL::SSL)