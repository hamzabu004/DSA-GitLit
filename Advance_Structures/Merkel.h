//
// Created by ht on 12/8/24.
//

#ifndef MERKEL_H
#define MERKEL_H


#include "../Utils/hasher.h"
#include <filesystem>
#include "../STL_STRUCTURES/MyList.h"
#include <fstream>
#include <sstream>
#include <openssl/evp.h>

class MerkleNode {
public:
    MyString hash;
    std::filesystem::path file_path;
    std::filesystem::path left_parent_path;
    std::filesystem::path right_parent_path;

    MerkleNode(const MyString& hash, const std::filesystem::path& file_path = "",
        const std::filesystem::path& left_parent_path = "", const std::filesystem::path& right_parent_path = "")
        : hash(hash), file_path(file_path), left_parent_path(left_parent_path), right_parent_path(right_parent_path) {}

};


class MerkleTree {
public:
    MyList<MerkleNode> merkleLeafList;
    std::filesystem::path avlBasePath;

    MerkleTree(const std::filesystem::path& avlBasePath)
        : avlBasePath(avlBasePath) {}

	// Build the list of leaf nodes
    void buildMerkleLeafsList(const std::filesystem::path& root_file_path, const std::filesystem::path& merkleFolder) {
        inOrder(root_file_path, merkleFolder);
    }

    void buildMerkleTree(const std::filesystem::path& merkleFolder) {
        while (merkleLeafList.get_size() > 1) {
            MyList<MerkleNode> newLevel;
            int merkleLeafListSize = merkleLeafList.get_size();
            for (int i = 0; i < merkleLeafListSize-1; i += 1) {
                // Combine the hash of the two nodes
                MyString combinedHash = sha256(merkleLeafList[i].hash + merkleLeafList[i + 1].hash);
                // correct path from merkle folder
                std::filesystem::path currrent_file_path = merkleFolder / combinedHash ;
                // Save the new node in the new level
                newLevel.insert(MerkleNode(combinedHash, currrent_file_path, merkleLeafList[i].file_path, merkleLeafList[i + 1].file_path));
                // Save the new node in the merkle folder
                saveMerkleNode(combinedHash, merkleFolder, "", merkleLeafList[i].file_path, merkleLeafList[i + 1].file_path);
            }
            merkleLeafList = newLevel;
        }
    }

	// Inorder traversal of the AVL tree
    void inOrder(const std::filesystem::path& file_path, const std::filesystem::path& merkleFolder) {
        if (file_path.empty()) return;

        std::ifstream file(file_path);
        if (!file.is_open()) return;

        MyList<MyString> lines;
        char line[1000];
        while (!file.eof()) {
            file.getline(line, 1000);
            lines.insert(line);
        }


        file.close();

        if (lines.get_size() < 5) return;

		// line-3, line-4, line-5 avl file: Save the left and right child paths
        std::filesystem::path left_child_path = avlBasePath / lines[3] ;
        std::filesystem::path right_child_path = avlBasePath / lines[4];

        inOrder(left_child_path, merkleFolder);

		// line-1 avl file: Save the hash of the file
        MyString fileHash = file_hash(file_path);
        merkleLeafList.insert(MerkleNode(fileHash, file_path));
        saveMerkleNode(fileHash, merkleFolder, file_path);

        inOrder(right_child_path, merkleFolder);
    }

    void saveMerkleNode(const MyString& hash, const std::filesystem::path& merkleFolder,
        const std::filesystem::path& filePath = "",
        const std::filesystem::path& leftParentPath = "",
        const std::filesystem::path& rightParentPath = "") {
        std::filesystem::path fileName = merkleFolder / hash ;

        std::ofstream outFile(fileName.generic_string());
        if (!outFile) {
            std::cout << "Failed to create file: " << fileName.generic_string() << std::endl;
            return;
        }
        outFile << hash << std::endl;

		// line-3 merkleNode file: Save the file path if it is a leaf node else save null
        if (!filePath.empty()) {
            outFile << filePath.generic_string() << std::endl;
        }
        else {
            outFile << "null" << std::endl;
        }

        // line-4, line-5 merkleNode file: Save the left and right parent paths
        /*
         if it is a leaf node save null
         if parent nodes are avl files save their path
         if parent nodes are merkle tree file save their path
        */
        outFile << (leftParentPath.empty() ? "null" : leftParentPath.generic_string()) << std::endl;
        outFile << (rightParentPath.empty() ? "null" : rightParentPath.generic_string()) << std::endl;

        outFile.close();
        std::cout << "Created file: " << fileName.generic_string() << std::endl;
    }

	// Build the Merkle tree - combination of the above two functions buildMerkleLeafsList() and buildMerkleTree()
    MyString buildMerkle(const std::filesystem::path& root_file_path, const std::filesystem::path& merkleFolder) {
        buildMerkleLeafsList(root_file_path, merkleFolder);
        buildMerkleTree(merkleFolder);

        if (merkleLeafList.get_size() > 0) {
            return merkleLeafList[0].hash;
        }
        return MyString();
    }
};

#endif //MERKEL_H
