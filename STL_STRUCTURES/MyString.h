//
// Created by hamza on 11/26/2024.
//

#ifndef MYSTRING_H
#define MYSTRING_H
#include <ostream>
#include <cstring>

using std::strlen;

class MyString {
    char* str;
    int len;
public:
    MyString(): str(nullptr), len(0) {}
    MyString(const char* s) {
        len = strlen(s);
        str = new char[len + 1];
        strcpy(str, s);
    }
    MyString(const MyString& s) {
        len = s.len;
        str = new char[len + 1];
        strcpy(str, s.str);
    }
    MyString& operator=(const MyString& s) {
        if (this == &s) return *this;
        delete[] str;
        len = s.len;
        str = new char[len + 1];
        strcpy(str, s.str);
        return *this;
    }
    ~MyString() {
        delete[] str;
    }
    friend std::ostream& operator<<(std::ostream& os, const MyString& s) {
        os << s.str;
        return os;
    }
};


#endif //MYSTRING_H
