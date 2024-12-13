#ifndef STACK_H
#define STACK_H

#include "Post.h"

class Node {
public:
    Post data;
    Node* next;

    Node(const Post& post) : data(post), next(nullptr) {}
};

class Stack {
private:
    Node* top;
    int size ;

public:
    // Constructor
    Stack();

    // Destructor
    ~Stack();

    // Check if the stack is empty
    bool isEmpty() const;

    // Add an element to the top of the stack
    void push(const Post& post);

    // Remove the top element
    void pop();

    // Get the top element
    Post peek() const;

    // Display all posts in the stack (most recent first)
    void displayAllPosts() const;

    int getNumberOfPosts() const ;
};

#endif // STACK_H
