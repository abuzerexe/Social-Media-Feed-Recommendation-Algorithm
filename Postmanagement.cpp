#include "PostManagement.h"
#include <iostream>

using namespace std;

PostManagement::PostManagement(UserManager& um) : userManager(um) {}

void PostManagement::addPost(int userID, const Post& post) {
    User* user = userManager.getUserById(userID);
    if (user) {
        user->addPost(post);
    } else {
        cout << "User not found." << endl;
    }
}

void PostManagement::removePost(int userID) {
    User* user = userManager.getUserById(userID);
    if (user) {
        user->removePost();
    } else {
        cout << "User not found." << endl;
    }
}

void PostManagement::displayPosts(int userID) {
    User* user = userManager.getUserById(userID);
    if (user) {
        user->displayPosts();
    } else {
        cout << "User not found." << endl;
    }
}