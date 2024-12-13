#include "PostManagement.h"
#include <iostream>

PostManagement::PostManagement(UserManager& um) : userManager(um) {}

void PostManagement::addPost(int userID, const Post& post) {
    User* user = userManager.getUserById(userID);
    if (user) {
        user->addPost(post);
    } else {
        std::cout << "User not found." << std::endl;
    }
}

void PostManagement::removePost(int userID) {
    User* user = userManager.getUserById(userID);
    if (user) {
        user->removePost();
    } else {
        std::cout << "User not found." << std::endl;
    }
}

void PostManagement::displayPosts(int userID) {
    User* user = userManager.getUserById(userID);
    if (user) {
        user->displayPosts();
    } else {
        std::cout << "User not found." << std::endl;
    }
}