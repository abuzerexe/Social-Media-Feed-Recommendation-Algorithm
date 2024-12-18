#ifndef FEEDGENERATOR_H
#define FEEDGENERATOR_H

#include <queue>
#include <vector>
#include "UserManager.h"
#include "ConnectionsManager.h"
#include "Post.h"

class FeedGenerator {
public:
    // Constructor taking references to UserManager and ConnectionsManager
    FeedGenerator(UserManager& um, ConnectionsManager& cm);

    // Generate feed for a specific user
    std::priority_queue<Post> generateFeed(int userID);

private:
    // References to UserManager and ConnectionsManager
    UserManager& userManager;
    ConnectionsManager& connectionsManager;

    // Helper method to get posts from random users
    std::vector<Post> getRandomPosts();

    // Helper method to get posts from user's connections
    std::vector<Post> getConnectionPosts(int userID);

    // Helper method to match posts with user's interests
    std::priority_queue<Post> matchPostsToInterests(const std::vector<Post>& posts, const DoublyLinkedList<string>& userInterests);
};

#endif // FEEDGENERATOR_H