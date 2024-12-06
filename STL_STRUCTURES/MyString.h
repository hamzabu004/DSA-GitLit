//
// Created by hamza on 11/26/2024.
//

#ifndef MYSTRING_H
#define MYSTRING_H
#include <ostream>
#include <cstring>
#include <filesystem>

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
    int length() const {
        return len;
    }

    void insert_char(char c, int pos = -1) {
        if (pos == -1) {
            pos = len;
        }

        char* new_str = new char[len + 2];
        for (int i = 0; i < pos; i++) {
            new_str[i] = str[i];
        }
        new_str[pos] = c;
        for (int i = pos; i < len; i++) {
            new_str[i + 1] = str[i];
        }
        new_str[len + 1] = '\0';
        delete[] str;
        str = new_str;
        len++;
    }
    void to_upper() {
        for (int i = 0; i < len; i++) {
            if (str[i] >= 'a' && str[i] <= 'z') {
                str[i] -= 32;
            }
        }
    }
    void to_lower() {
        for (int i = 0; i < len; i++) {
            if (str[i] >= 'A' && str[i] <= 'Z') {
                str[i] += 32;
            }
        }
    }
    char* c_str() const {
        return str;
    }
    int size() const {
        return len;
    }

    MyString& operator=(const MyString& s) {
        if (this == &s) return *this;
        delete[] str;
        len = s.len;
        str = new char[len + 1];
        strcpy(str, s.str);
        return *this;
    }
    char& operator[](int i) {
        return str[i];
    }

    // comparisons
    bool operator==(const MyString &s) const {
        if (len != s.len) return false;
        return strcmp(str, s.str) == 0;
    }
    bool operator!=(const MyString &s) const {
        return !(*this == s);
    }
    bool operator<(const MyString &s) const {
        return strcmp(str, s.str) < 0;
    }
    bool operator>(const MyString &s) const {
        return strcmp(str, s.str) > 0;
    }
    bool operator<(const char* s) const {
        return strcmp(str, s) < 0;
    }
    bool operator>(const char* s) const {
        return strcmp(str, s) > 0;
    }

    ~MyString() {
        delete[] str;
    }
    friend std::ostream& operator<<(std::ostream& os, const MyString& s) {
        os << s.str;
        return os;
    }



    friend std::filesystem::__cxx11::path operator/(const std::filesystem::path &p, const MyString& s) {
        return p / s.str;
    }

    friend std::istream& operator>>(std::istream& is, MyString& s) {
        char temp[200];
        is.getline(temp, 200);
        s = temp;
        return is;
    }


};


#endif //MYSTRING_H
