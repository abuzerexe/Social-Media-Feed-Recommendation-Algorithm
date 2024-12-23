#include "PostLinkList.h"
#include <iostream>
#include <stdexcept>

using namespace std;

PostLinkedList::PostLinkedList() : head(nullptr), tail(nullptr), size(0) {}

PostLinkedList::~PostLinkedList() {
}

bool PostLinkedList::isEmpty() const {
    return head == nullptr;
}

void PostLinkedList::add(const Post& post) {
    Node* newNode = new Node(post);

    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

void PostLinkedList::remove() {
    if (isEmpty()) {
        cout << "List is empty. Cannot remove post." << endl;
        return;
    }

    Node* temp = tail;

    if (head == tail) {
        // Only one node
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    size--;
    delete temp;
}

Post PostLinkedList::peek() const {
    if (isEmpty()) {
        throw runtime_error("List is empty");
    }
    return tail->data;
}

void PostLinkedList::displayAllPosts() const {
    if (isEmpty()) {
        cout << "No posts in the list." << endl;
        return;
    }

    Node* current = head;
    int postCount = 1;
    while (current != nullptr) {
        cout << "Post " << postCount++ << ":" << endl;
        current->data.displayPostDetails();
        cout << endl;
        current = current->next;
    }
}

int PostLinkedList::getNumberOfPosts() const {
    return size;
}