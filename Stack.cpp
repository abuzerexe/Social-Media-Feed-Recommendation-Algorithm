#include "Stack.h"
#include <iostream>

Stack::Stack() : top(nullptr) {}

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

bool Stack::isEmpty() const {
    return top == nullptr;
}

void Stack::push(const Post& post) {
    Node* newNode = new Node(post);
    
    // New node points to the current top
    newNode->next = top;
    // New node becomes the new top
    top = newNode;
}

void Stack::pop() {
    if (isEmpty()) {
        std::cout << "Stack is empty. Cannot pop." << std::endl;
        return;
    }

    Node* temp = top;
    top = top->next;
    delete temp;
}

Post Stack::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }
    return top->data;
}

void Stack::displayAllPosts() const {
    if (isEmpty()) {
        std::cout << "No posts in the stack." << std::endl;
        return;
    }

    Node* current = top;
    int postCount = 1;
    while (current != nullptr) {
        std::cout << "Post " << postCount++ << ":" << std::endl;
        current->data.displayPostDetails();
        std::cout << std::endl;
        current = current->next;
    }
}
