//
// Created by ht on 12/5/24.
//

#ifndef HASHER_H
#define HASHER_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <filesystem>
#include <stdexcept>
#include "../STL_STRUCTURES/MyString.h"

using namespace std;
// string hash
MyString sha256(const MyString& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr);
    EVP_DigestUpdate(ctx, str.c_str(), str.size());
    EVP_DigestFinal_ex(ctx, hash, nullptr);
    EVP_MD_CTX_free(ctx);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    MyString s = ss.str().c_str();
    return s;
}

// file hash
MyString file_hash(const std::filesystem::path& file_path) {
    std::ifstream fp(file_path, std::ios::in | std::ios::binary);

    if (!fp.good()) {
        char buffer[256];
        strerror_r(*buffer, reinterpret_cast<char *>(sizeof(buffer)), errno);
        std::ostringstream os;
        os << "Cannot open \"" << file_path << "\": " << buffer << ".";
        throw std::runtime_error(os.str());
    }

    constexpr const std::size_t buffer_size{ 1 << 12 };
    char buffer[buffer_size];

    unsigned char hash[SHA256_DIGEST_LENGTH] = { 0 };
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr);

    while (fp.good()) {
        fp.read(buffer, buffer_size);
        EVP_DigestUpdate(ctx, buffer, fp.gcount());
    }

    EVP_DigestFinal_ex(ctx, hash, nullptr);
    EVP_MD_CTX_free(ctx);
    fp.close();

    std::ostringstream os;
    os << std::hex << std::setfill('0');

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        os << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }

    return os.str().c_str();
}

inline int isntructor_hash(MyString str) {
    int hash = 1;
    for (int i  = 0; i < str.size(); i++) {
        hash *= int(str[i]);
    }
    return hash % 29;
}

#endif //HASHER_H
