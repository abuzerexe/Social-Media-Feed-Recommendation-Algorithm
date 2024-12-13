#include "Queue.h"
#include <iostream>

Queue::Queue() : front(nullptr), rear(nullptr) {}

Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

bool Queue::isEmpty() const {
    return front == nullptr;
}

void Queue::enqueue(const Post& post) {
    Node* newNode = new Node(post);
    
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    size++ ;
}

void Queue::dequeue() {
    if (isEmpty()) {
        std::cout << "Queue is empty. Cannot dequeue." << std::endl;
        return;
    }

    Node* temp = front;
    front = front->next;
    delete temp;

    // If queue becomes empty after dequeuing
    if (front == nullptr) {
        rear = nullptr;
    }
    size-- ;
}

Post Queue::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return front->data;
}

void Queue::displayAllPosts() const {
    if (isEmpty()) {
        std::cout << "No posts in the queue." << std::endl;
        return;
    }

    Node* current = front;
    int postCount = 1;
    while (current != nullptr) {
        std::cout << "Post " << postCount++ << ":" << std::endl;
        current->data.displayPostDetails();
        std::cout << std::endl;
        current = current->next;
    }
}

int Queue::getNumberOfPosts() const {
    return size ;
}