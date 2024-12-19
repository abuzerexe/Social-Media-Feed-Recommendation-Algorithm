#include "Post.h"
#include <iostream>
#include <iomanip>

Post::Post() : content(""), type(""), importance(0), timestamp(std::time(nullptr)), interestMatchScore(0) {}

Post::Post(const std::string& content, const std::string& type, int importance)
    : content(content), type(type), importance(importance),
      timestamp(std::time(nullptr)), interestMatchScore(0) {}

void Post::setContent(const std::string& content) {
    this->content = content;
}

void Post::setType(const std::string& type) {
    this->type = type;
}

void Post::setImportance(int importance) {
    this->importance = importance;
}

std::string Post::getContent() const {
    return content;
}

std::string Post::getType() const {
    return type;
}

int Post::getImportance() const {
    return importance;
}

time_t Post::getTimestamp() const {
    return timestamp;
}

void Post::addTag(const std::string& tag) {
    tags.push_back(tag);
}

void Post::displayPostDetails() const {
    std::cout << "Post Details:" << std::endl;
    std::cout << "Content: " << content << std::endl;
    std::cout << "Type: " << type << std::endl;
    std::cout << "Importance: " << importance << std::endl;

    // Display tags
    std::cout << "Tags: ";
    for (const auto& tag : tags) {
        std::cout << tag << " ";
    }
    std::cout << std::endl;

    // Convert timestamp to readable format
    char buffer[26];
    // ctime_s(buffer, sizeof(buffer), &timestamp);
    std::cout << "Timestamp: " << buffer;

    // Display interest match score
    std::cout << "Interest Match Score: " << interestMatchScore << std::endl;
}

// Overloaded comparison operators for priority queue
// Prioritize by interest match score first, then by importance
bool Post::operator<(const Post& other) const {
    // For max-heap priority queue, we want higher scores to be considered "smaller"
    if (interestMatchScore == other.interestMatchScore) {
        return importance < other.importance;
    }
    return interestMatchScore < other.interestMatchScore;
}

bool Post::operator>(const Post& other) const {
    // Complementary to the < operator
    if (interestMatchScore == other.interestMatchScore) {
        return importance > other.importance;
    }
    return interestMatchScore > other.interestMatchScore;
}