//
// Created by hamza on 11/28/2024.
//

#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>

using std::cout;
using std::endl;



template <typename T>
struct TreeNode {
    T data;
    TreeNode* next;
};

template <typename T>
class MyList {
    TreeNode<T>* head;
    TreeNode<T>* tail;
    int size;
public:
    // insert, remove, print, search, size, empty, clear
    MyList(): head(nullptr), tail(nullptr), size(0) {}
    void insert(T data) {
        TreeNode* new_node = new TreeNode;
        new_node->data = data;
        new_node->next = nullptr;
        if (head == nullptr) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        size++;
    }
    void remove_element(T data) {
        if (head == nullptr) {
            throw std::underflow_error("List is empty");
        }
        TreeNode* temp = head;
        TreeNode* prev = nullptr;
        while (temp != nullptr) {
            if (temp->data == data) {
                if (prev == nullptr) {
                    head = temp->next;
                } else {
                    prev->next = temp->next;
                }
                delete temp;
                size--;
                return;
            }
            prev = temp;
            temp = temp->next;
        }

    }
    void print() {
        TreeNode* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    T& operator[] (int index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        TreeNode* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }
    int get_size() {
        return size;
    }
};



#endif //MYLIST_H
