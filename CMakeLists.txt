cmake_minimum_required(VERSION 3.29)
project(DSA_GitLit)

set(CMAKE_CXX_STANDARD 20)

add_executable(DSA_GitLit main.cpp
        GitLite.cpp
        GitLite.h
        GLOBALS.h
        Utils/file_operations.h
        STL_STRUCTURES/MyList.h
#        Advance_Structures/AVL.cpp
        Advance_Structures/AVL.h
        Advance_Structures/CSV.h
)

