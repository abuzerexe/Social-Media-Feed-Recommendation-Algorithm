#include <queue>
#include <vector>
#include <algorithm>
#include "FeedGenerator.h"
#include "UserManager.h"
#include "ConnectionsManager.h"
#include "Post.h"

std::priority_queue<Post> FeedGenerator::generateFeed(int userID) {
    std::priority_queue<Post> feed;
    User* user = userManager.getUserById(userID);

    if (!user) {
        std::cout << "User not found." << std::endl;
        return feed;
    }

    std::vector<int> connections = connectionsManager.getConnectionsByUser(userID);
    std::vector<Post> posts;

    if (connections.empty()) {
        for (const auto& pair : UserManager::userById) {
            User* randomUser = userManager.getUserById(pair.first);
            if (randomUser) {
                Stack tempStack = randomUser->getPostStack();
                while (!tempStack.isEmpty()) {
                    posts.push_back(tempStack.peek());
                    tempStack.pop();
                }
            }
        }
    } else {
        // Get posts from connections
        for (int connectionID : connections) {
            User* connection = userManager.getUserById(connectionID);
            if (connection) {
                Stack tempStack = connection->getPostStack();
                while (!tempStack.isEmpty()) {
                    posts.push_back(tempStack.peek());
                    tempStack.pop();
                }
            }
        }
    }

    // Match posts with user's interests
    DoublyLinkedList<std::string> userInterests = user->getUserInterests();
    for (const Post& post : posts) {
        for (const std::string& interest : userInterests) {
            if (post.getContent().find(interest) != std::string::npos) {
                feed.push(post);
                break;
            }
        }
    }

    return feed;
}