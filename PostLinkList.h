#ifndef POSTLINKEDLIST_H
#define POSTLINKEDLIST_H

#include "Post.h"

// Node class definition

// PostLinkedList class definition
class PostLinkedList {
private:
    int size ;

public:
    class Node {
    public:
        Post data;
        Node* next;
        Node* prev;

        // Constructor
        Node(const Post& post) : data(post), next(nullptr), prev(nullptr) {}
    };
    Node* head;
    Node* tail;
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

    int getNumberOfPosts() const;

};

#endif // POSTLINKEDLIST_H
