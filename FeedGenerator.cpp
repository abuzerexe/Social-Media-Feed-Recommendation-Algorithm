#include "FeedGenerator.h"
#include <algorithm>

using namespace std;

FeedGenerator::FeedGenerator(UserManager& um, ConnectionsManager& cm)
    : userManager(um), connectionsManager(cm) {}

priority_queue<Post> FeedGenerator::generateFeed(int userID) {
    User* user = userManager.getUserById(userID);
    if (!user) {
        return priority_queue<Post>();
    }

    // First, get posts from direct connections
    vector<Post> connectionPosts = getConnectionPosts(userID);
    priority_queue<Post> feedQueue;

    // Use a vector to keep track of added posts
    vector<Post> addedPosts;

    // Get user interests
    DoublyLinkedList<string> userInterests = user->getUserInterests();

    // Process connection posts first (these get priority)
    for (const Post& post : connectionPosts) {
        double score = calculatePostScore(post, userInterests);
        // Boost score for connection posts
        Post scoredPost = post;
        scoredPost.interestMatchScore = static_cast<int>(score * 150); // 50% boost for connection posts
        feedQueue.push(scoredPost);
        addedPosts.push_back(post);
    }

    // Then process random posts (for discovery)
    vector<Post> randomPosts = getRandomPosts();
    for (const Post& post : randomPosts) {
        // Check if post is already added (from connections)
        bool isDuplicate = false;
        for (const Post& addedPost : addedPosts) {
            if (post == addedPost) {
                isDuplicate = true;
                break;
            }
        }

        if (!isDuplicate) {
            double score = calculatePostScore(post, userInterests);
            Post scoredPost = post;
            scoredPost.interestMatchScore = static_cast<int>(score * 100);
            feedQueue.push(scoredPost);
            addedPosts.push_back(post);
        }
    }

    return feedQueue;
}

vector<Post> FeedGenerator::getRandomPosts() {
    vector<Post> allPosts;

    for (auto& userPair : userManager.userById) {
        PostLinkedList& userPosts = userPair.second.getPostList();
        PostLinkedList::Node* current = userPosts.head;
        while (current != nullptr) {
            allPosts.push_back(current->data);
            current = current->next;
        }
    }

    auto rng = std::default_random_engine{std::random_device{}()};
    shuffle(allPosts.begin(), allPosts.end(), rng);

    int maxPosts = min(50, static_cast<int>(allPosts.size()));
    return vector<Post>(allPosts.begin(), allPosts.begin() + maxPosts);
}

vector<Post> FeedGenerator::getConnectionPosts(int userID) {
    vector<Post> connectionPosts;
    vector<int> userConnections = connectionsManager.getConnectionsByUser(userID);

    for (int connectionID : userConnections) {
        User* connectionUser = userManager.getUserById(connectionID);
        if (connectionUser) {
            PostLinkedList& userPosts = connectionUser->getPostList();
            PostLinkedList::Node* current = userPosts.head;
            while (current != nullptr) {
                connectionPosts.push_back(current->data);
                current = current->next;
            }
        }
    }

    return connectionPosts;
}

priority_queue<Post> FeedGenerator::matchPostsToInterests(
    const vector<Post>& posts,
    const DoublyLinkedList<string>& userInterests
) {
    priority_queue<Post> matchedPosts;

    for (Post post : posts) {
        int matchScore = 0;

        DoublyLinkedList<string>::Node* current = userInterests.head;
        while (current != nullptr) {
            if (find(post.tags.begin(), post.tags.end(), current->data) != post.tags.end()) {
                matchScore++;
            }
            current = current->next;
        }

        if (matchScore > 0) {
            post.interestMatchScore = matchScore;
            matchedPosts.push(post);
        }
    }

    return matchedPosts;
}

double FeedGenerator::calculatePostScore(const Post& post, const DoublyLinkedList<string>& userInterests) {
    double interestScore = calculateInterestScore(post, userInterests);
    double normalizedImportance = static_cast<double>(post.getImportance()) / 10.0;

    // Combine scores with weights
    return (interestScore * INTEREST_WEIGHT) +
           (normalizedImportance * IMPORTANCE_WEIGHT);
}

double FeedGenerator::calculateInterestScore(const Post& post, const DoublyLinkedList<string>& userInterests) {
    int matchCount = 0;
    int totalInterests = 0;

    DoublyLinkedList<string>::Node* current = userInterests.head;
    while (current != nullptr) {
        totalInterests++;
        if (find(post.tags.begin(), post.tags.end(), current->data) != post.tags.end()) {
            matchCount++;
        }
        current = current->next;
    }

    return totalInterests > 0 ? static_cast<double>(matchCount) / totalInterests : 0.0;
}