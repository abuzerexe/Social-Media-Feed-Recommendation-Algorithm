#ifndef POSTLINKEDLIST_H
#define POSTLINKEDLIST_H

#include "Post.h"

// Node class definition
class Node {
public:
    Post data;
    Node* next;
    Node* prev;

    // Constructor
    Node(const Post& post) : data(post), next(nullptr), prev(nullptr) {}
};

// PostLinkedList class definition
class PostLinkedList {
private:
    Node* head;
    Node* tail;

public:
    // Constructor
    PostLinkedList();

    // Destructor
    ~PostLinkedList();

   
    bool isEmpty() const;

   
    void add(const Post& post);

    // Remove the most recent post (from the end)
    void remove();

    // Get the most recent post
    Post peek() const;

  
    void displayAllPosts() const;
};

#endif // POSTLINKEDLIST_H
