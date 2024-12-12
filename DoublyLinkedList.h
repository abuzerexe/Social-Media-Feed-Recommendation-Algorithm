#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>
using namespace std;

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(T value);
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList<T>& other); 
    ~DoublyLinkedList();

    void pushFront(T value);
    void pushBack(T value);
    void popFront();
    void popBack();
    void displayForward();
    void displayBackward();
    bool isEmpty();
    bool contains(T value);
    int size();
    Node* find(T value);
    void insertAt(int index, T value);
    void deleteByValue(T value);


    // Iterator class for the use of range-based for loops
    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node) : current(node) {}

        Iterator& operator++() {
            if (current) current = current->next;
            return *this;
        }

        T& operator*() {
            return current->data;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};

#include "DoublyLinkedList.tpp" // Include the template implementation

#endif // DOUBLY_LINKED_LIST_H
