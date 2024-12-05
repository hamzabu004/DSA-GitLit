//
// Created by ht on 12/5/24.
//

#ifndef HASHER_H
#define HASHER_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>

#include "../STL_STRUCTURES/MyString.h"

MyString sha256(const MyString& str){
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>( hash[i] );
    }
    MyString s = ss.str().c_str();
    return s;
}


#endif //HASHER_H
