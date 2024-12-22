#include "FeedGenerator.h"
#include <algorithm>
#include <random>

using namespace std;

// Constructor
FeedGenerator::FeedGenerator(UserManager& um, ConnectionsManager& cm)
    : userManager(um), connectionsManager(cm) {}

// Generate feed for a specific user
priority_queue<Post> FeedGenerator::generateFeed(int userID) {
    // Get the user
    User* user = userManager.getUserById(userID);
    if (!user) {
        cout << "User not found." << endl;
        return priority_queue<Post>();
    }

    // Get user's interests
    DoublyLinkedList<string> userInterests = user->getUserInterests();

    // Initialize priority queue for feed
    priority_queue<Post> feedQueue;

    // Check if user has connections
    vector<int> userConnections = connectionsManager.getConnectionsByUser(userID);

    if (!userConnections.empty()) {
        // Get posts from connections
        vector<Post> connectionPosts = getConnectionPosts(userID);

        // Match connection posts to user's interests
        feedQueue = matchPostsToInterests(connectionPosts, userInterests);
    }

    // If feed is empty or not enough posts, get random posts
    if (feedQueue.empty()) {
        vector<Post> randomPosts = getRandomPosts();

        // Match random posts to user's interests
        priority_queue<Post> randomPostQueue = matchPostsToInterests(randomPosts, userInterests);

        // If random posts queue is not empty, use it
        if (!randomPostQueue.empty()) {
            feedQueue = randomPostQueue;
        }
    }

    return feedQueue;
}

// Helper method to get posts from random users
vector<Post> FeedGenerator::getRandomPosts() {
    vector<Post> allPosts;

    // Iterate through all users and collect their posts
    for (auto& userPair : userManager.userById) {
        PostLinkedList& userPosts = userPair.second.getPostList();

        // Iterate through user's posts and add to allPosts
        PostLinkedList::Node* current = userPosts.head;
        while (current != nullptr) {
            allPosts.push_back(current->data);
            current = current->next;
        }
    }

    // Shuffle the posts randomly
    random_device rd;
    mt19937 g(rd());
    shuffle(allPosts.begin(), allPosts.end(), g);

    // Return a limited number of random posts (e.g., first 20)
    int maxPosts = min(20, static_cast<int>(allPosts.size()));
    return vector<Post>(allPosts.begin(), allPosts.begin() + maxPosts);
}

// Helper method to get posts from user's connections
vector<Post> FeedGenerator::getConnectionPosts(int userID) {
    vector<Post> connectionPosts;

    // Get user's connections
    vector<int> userConnections = connectionsManager.getConnectionsByUser(userID);

    // Iterate through connections and collect their posts
    for (int connectionID : userConnections) {
        User* connectionUser = userManager.getUserById(connectionID);
        if (connectionUser) {
            PostLinkedList& userPosts = connectionUser->getPostList();

            // Iterate through user's posts and add to connectionPosts
            PostLinkedList::Node* current = userPosts.head;
            while (current != nullptr) {
                connectionPosts.push_back(current->data);
                current = current->next;
            }
        }
    }

    return connectionPosts;
}

// Helper method to match posts to user's interests
priority_queue<Post> FeedGenerator::matchPostsToInterests(
    const vector<Post>& posts,
    const DoublyLinkedList<string>& userInterests
) {
    priority_queue<Post> matchedPosts;

    for (const Post& post : posts) {
        int interestScore = 0;

        // Check each of the user's interests against the post's tags
        DoublyLinkedList<string>::Node* interestNode = userInterests.head;
        while (interestNode != nullptr) {
            if (find(post.tags.begin(), post.tags.end(), interestNode->data) != post.tags.end()) {
                interestScore++;
            }
            interestNode = interestNode->next;
        }

        // If post matches any interests, add to priority queue with score
        if (interestScore > 0) {
            Post scoredPost = post;
            scoredPost.interestMatchScore = interestScore;
            matchedPosts.push(scoredPost);
        }
    }

    return matchedPosts;
}