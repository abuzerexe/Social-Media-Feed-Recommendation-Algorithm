//
// Created by Abdul Muizz on 22/12/2024.
//

#include "PriorityQueue.h"
#include "User.h"
#include <iostream>


PriorityQueue::Node::Node(User user, int p) : user(user) , priority(p), next(nullptr) {}

PriorityQueue::PriorityQueue() : start(nullptr), end(nullptr) {}

void PriorityQueue::enqueueUser(User& user) {
    Node* newNode = new Node(user , user.getPostCount());
    if (start == nullptr) {
        start = end = newNode;
    } else {
        if (newNode->priority > start->priority) {
            newNode->next = start;
            start = newNode;
        } else {
            Node* current = start;
            while (current->next != nullptr && current->next->priority >= newNode->priority) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
            if (newNode->next == nullptr) {
                end = newNode;
            }
        }
    }
}

User PriorityQueue::dequeueUser() {
    if (start == nullptr) {
        std::cout << "Queue is empty!" << std::endl;
        return User();
    }
    Node* temp = start;
    start = start->next;
    User user = temp->user;

    delete temp;
    return user;
}

void PriorityQueue::display() const {
    if (start == nullptr) {
        std::cout << "Queue is empty!" << std::endl;
        return;
    }
    Node* current = start;
    while (current != nullptr) {
        std::cout << "User ID: " << current->user.getUserId() << " Priority: " << current->priority << std::endl;
        current = current->next;
    }
}

bool PriorityQueue::isEmpty() const {
    return start == nullptr;
}

int PriorityQueue::size() const {
    int count = 0;
    Node* current = start;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

