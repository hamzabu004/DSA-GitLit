//
// Created by ht on 12/5/24.
//

#ifndef HASHER_H
#define HASHER_H

#include <iostream>
#include <iomanip>
#include <fstream>
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

// file hash
MyString file_hash(const std::filesystem::path& file_path){
    std::ifstream fp(file_path, std::ios::in | std::ios::binary);

    if (not fp.good()) {
        std::ostringstream os;
        os << "Cannot open \"" << file_path << "\": " << std::strerror(errno) << ".";
        throw std::runtime_error(os.str());
    }

    constexpr const std::size_t buffer_size { 1 << 12 };
    char buffer[buffer_size];

    unsigned char hash[SHA256_DIGEST_LENGTH] = { 0 };

    SHA256_CTX ctx;
    SHA256_Init(&ctx);

    while (fp.good()) {
        fp.read(buffer, buffer_size);
        SHA256_Update(&ctx, buffer, fp.gcount());
    }

    SHA256_Final(hash, &ctx);
    fp.close();

    std::ostringstream os;
    os << std::hex << std::setfill('0');

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        os << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }

    return os.str().c_str();
}


#endif //HASHER_H
