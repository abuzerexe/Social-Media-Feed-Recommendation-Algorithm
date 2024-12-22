#ifndef FEEDGENERATOR_H
#define FEEDGENERATOR_H

#include <queue>
#include <vector>
#include <random>
#include "UserManager.h"
#include "ConnectionsManager.h"
#include "Post.h"

class FeedGenerator {
public:
    FeedGenerator(UserManager& um, ConnectionsManager& cm);
    std::priority_queue<Post> generateFeed(int userID);

private:
    UserManager& userManager;
    ConnectionsManager& connectionsManager;

    static constexpr double INTEREST_WEIGHT = 0.6;
    static constexpr double IMPORTANCE_WEIGHT = 0.4;

    // Helper methods
    std::vector<Post> getRandomPosts();
    std::vector<Post> getConnectionPosts(int userID);
    std::priority_queue<Post> matchPostsToInterests(const std::vector<Post>& posts, const DoublyLinkedList<string>& userInterests);

    double calculatePostScore(const Post& post, const DoublyLinkedList<string>& userInterests);
    double calculateInterestScore(const Post& post, const DoublyLinkedList<string>& userInterests);
};

#endif // FEEDGENERATOR_H