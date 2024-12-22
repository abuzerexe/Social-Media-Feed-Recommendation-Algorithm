//
// Created by Abdul Muizz on 22/12/2024.
//

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <queue>

#include "User.h"


class PriorityQueue {

    struct Node {
        User user;
        int priority;
        Node* next;

        Node(User user, int p);
    };

    Node* start ;
    Node* end ;

public:

    PriorityQueue() ;
    void enqueueUser(User& user);
    User dequeueUser();
    void display() const;
    bool isEmpty() const;
    int size() const;


};



#endif //PRIORITYQUEUE_H
