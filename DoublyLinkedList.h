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
};

#include "DoublyLinkedList.tpp" // Include the template implementation

#endif // DOUBLY_LINKED_LIST_H
