#ifndef DOUBLY_LINKED_LIST_TPP
#define DOUBLY_LINKED_LIST_TPP

#include <iostream>
using namespace std;


template <typename T>
DoublyLinkedList<T>::Node::Node(T value) : data(value), prev(nullptr), next(nullptr) {}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) : head(nullptr), tail(nullptr) {
    Node* current = other.head;
    while (current != nullptr) {
        pushBack(current->data);  
        current = current->next;
    }
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

template <typename T>
void DoublyLinkedList<T>::pushFront(T value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

template <typename T>
void DoublyLinkedList<T>::pushBack(T value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

template <typename T>
void DoublyLinkedList<T>::popFront() {
    if (head == nullptr) {
        cout << "List is empty!" << endl;
        return;
    }
    Node* temp = head;
    head = head->next;
    if (head)
        head->prev = nullptr;
    else
        tail = nullptr;
    delete temp;
}

template <typename T>
void DoublyLinkedList<T>::popBack() {
    if (head == nullptr) {
        cout << "List is empty!" << endl;
        return;
    }
    Node* temp = tail;
    tail = tail->prev;
    if (tail)
        tail->next = nullptr;
    else
        head = nullptr;
    delete temp;
}

template <typename T>
void DoublyLinkedList<T>::displayForward() {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

template <typename T>
void DoublyLinkedList<T>::displayBackward() {
    Node* current = tail;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->prev;
    }
    cout << endl;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty() {
    return head == nullptr;
}

template <typename T>
bool DoublyLinkedList<T>::contains(T value) {
 
 Node * current = head;
    while (current != nullptr)
    {
        if (current->data == value)
        {
            return true;
        }
        
        current = current->next;
    }
 
 return false;
}

template <typename T>
int DoublyLinkedList<T>::size() {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

template <typename T>
typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::find(T value) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value)
            return current;
        current = current->next;
    }
    return nullptr; // Value not found
}

template <typename T>
void DoublyLinkedList<T>::insertAt(int index, T value) {
    if (index < 0 || index > size()) {
        cout << "Invalid index!" << endl;
        return;
    }
    if (index == 0) {
        pushFront(value);
        return;
    }
    if (index == size()) {
        pushBack(value);
        return;
    }
    Node* newNode = new Node(value);
    Node* current = head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    newNode->next = current->next;
    newNode->prev = current;
    current->next->prev = newNode;
    current->next = newNode;
}

template <typename T>
void DoublyLinkedList<T>::deleteByValue(T value) {
    Node* current = find(value);
    if (!current) {
        cout << "Value not found!" << endl;
        return;
    }
    if (current == head) {
        popFront();
        cout << "Removed successfully!\n";
        return;
    }
    if (current == tail) {
        popBack();
        cout << "Removed successfully!\n";
        return;
    }
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    cout << "Removed successfully!\n";
}

#endif // DOUBLY_LINKED_LIST_TPP
