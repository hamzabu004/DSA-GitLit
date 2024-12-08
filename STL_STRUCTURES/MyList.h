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
    TreeNode(const T& data) : data(data), next(nullptr) {}
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
        TreeNode<T>* new_node = new TreeNode<T>(data);
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
    void remove (int index) {
        int i = 0;
        TreeNode<T>* temp = head;

        while (temp) {
            if (i == index) {
                if (temp == head) {
                    head = temp->next;
                    delete temp;
                    size--;
                    return;
                } else {
                    TreeNode<T>* prev = head;
                    while (prev->next != temp) {
                        prev = prev->next;
                    }
                    prev->next = temp->next;
                    delete temp;
                    size--;
                    return;
                }
            }
            i++;
            temp = temp->next;
        }
    }

    void remove_element(T data) {
        if (head == nullptr) {
            throw std::underflow_error("List is empty");
        }
        TreeNode<T>* temp = head;
        TreeNode<T>* prev = nullptr;
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
        TreeNode<T>* temp = head;
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
        TreeNode<T>* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }
     MyList(const MyList& other) : head(nullptr), tail(nullptr), size(0) {
        TreeNode<T>* temp = other.head;
        while (temp != nullptr) {
            insert(temp->data);
            temp = temp->next;
        }
    }


    // Assignment operator
    MyList& operator=(const MyList& other) {
        if (this != &other) {
            clear();
            TreeNode<T>* temp = other.head;
            while (temp != nullptr) {
                insert(temp->data);
                temp = temp->next;
            }
        }
        return *this;
    }

    int get_size() const {
        return size;
    }
    friend std::ostream& operator<<(std::ostream& os, MyList<T>& list) {
        TreeNode<T>* temp = list.head;
        while (temp != nullptr) {
            os << temp->data << " ";
            temp = temp->next;
        }
        os << endl;
        return os;
    }
    void clear() {
        TreeNode<T>* temp = head;
        while (temp != nullptr) {
            TreeNode<T>* next = temp->next;
            delete temp;
            temp = next;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    ~MyList() {
        clear();
    }

};



#endif //MYLIST_H
