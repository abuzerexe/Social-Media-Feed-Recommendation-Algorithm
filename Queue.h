#ifndef QUEUE_H
#define QUEUE_H

#include "Post.h"

// Node class definition
class Node {
public:
    Post data;
    Node* next;

    // Constructor
    Node(const Post& post) : data(post), next(nullptr) {}
};

// Queue class definition
class Queue {
private:
    Node* front;
    Node* rear;
    int size = 0;

public:
    // Constructor
    Queue();

    // Destructor
    ~Queue();

    // Check if the queue is empty
    bool isEmpty() const;

    // Add an element to the queue
    void enqueue(const Post& post);

    // Remove an element from the queue
    void dequeue();

    // Get the data at the front of the queue
    Post peek() const;

    // Display all posts in the queue
    void displayAllPosts() const;

    int getNumberOfPosts() const ;

};

#endif // QUEUE_H