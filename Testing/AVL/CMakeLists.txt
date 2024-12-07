cmake_minimum_required(VERSION 3.29)
project(AVL_MAIN)

set(CMAKE_CXX_STANDARD 20)

add_executable(AVL_MAIN
        main.cpp
        ../../GLOBALS.h
        ../../Utils/file_operations.h
        ../../STL_STRUCTURES/MyList.h
        #        Advance_Structures/AVL.cpp
        ../../Advance_Structures/AVL.h
        ../../Advance_Structures/Tree.h

)

