//
// Created by ht on 12/5/24.
//

#include "../../Utils/hasher.h"
#include "../../Advance_Structures/Merkel.h"


int main() {

    std::filesystem::path root_file_path = "DBMS";
    std::filesystem::path merkleFolder = "/home/ht/CLionProjects/DSA-GitLit/Testing/Hashing/cmake-build-debug/hana/merkle";
    std::filesystem::path avlBasePath = "/home/ht/CLionProjects/DSA-GitLit/cmake-build-debug/hana/master/tree";

    // Ensure the Merkle folder exists
    if (!std::filesystem::exists(merkleFolder)) {
        std::filesystem::create_directories(merkleFolder);
    }

    MerkleTree merkleTree(avlBasePath);
    MyString rootHash = merkleTree.buildMerkle(root_file_path, merkleFolder);

    std::cout << std::endl << "Root Hash: " << rootHash << std::endl;

    return 0;
}