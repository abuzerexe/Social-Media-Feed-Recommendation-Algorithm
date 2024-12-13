#ifndef POSTMANAGEMENT_H
#define POSTMANAGEMENT_H

#include "UserManager.h"
#include "Queue.h"
#include "Post.h"

class PostManagement {
private:
    UserManager& userManager;

public:
    // Constructor taking UserManager reference
    PostManagement(UserManager& um);

    // Add a post for a specific user
    void addPost(int userID, const Post& post);

    // Remove a post for a specific user
    void removePost(int userID);

    // Display posts for a specific user
    void displayPosts(int userID);
};

#endif // POSTMANAGEMENT_H