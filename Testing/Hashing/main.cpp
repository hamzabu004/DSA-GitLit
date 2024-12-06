//
// Created by ht on 12/5/24.
//

#include "../../Utils/hasher.h"


int main() {
    MyString s = "hello";
    MyString hash = sha256(s);
    std::cout << hash << std::endl;
    return 0;
}