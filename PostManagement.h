#ifndef POSTMANAGEMENT_H
#define POSTMANAGEMENT_H

#include "UserManager.h"
#include "PostLinkList.h"
#include "Post.h"

class PostManagement {
private:
    UserManager& userManager;

public:
  
    PostManagement(UserManager& um);

    void addPost(int userID, const Post& post);

    void removePost(int userID);

    void displayPosts(int userID);
};

#endif // POSTMANAGEMENT_H
