cmake_minimum_required(VERSION 3.29)
project(Hashing_MAIN)

set(CMAKE_CXX_STANDARD 20)
find_package(OpenSSL REQUIRED)

add_executable(Menu
        main.cpp
        ../../GLOBALS.h
        ../../Utils/file_operations.h
        ../../STL_STRUCTURES/MyList.h
        ../../GitLite.h
        ../../GitLite.cpp

        ../../Advance_Structures/AVL.h

)

target_link_libraries(Menu OpenSSL::SSL)