#include "Post.h"
#include <iostream>
#include <iomanip>

Post::Post() : content(""), type(""), importance(0), timestamp(std::time(nullptr)) {}

Post::Post(const std::string& content, const std::string& type, int importance) 
    : content(content), type(type), importance(importance), timestamp(std::time(nullptr)) {}

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

void Post::displayPostDetails() const {
    std::cout << "Post Details:" << std::endl;
    std::cout << "Content: " << content << std::endl;
    std::cout << "Type: " << type << std::endl;
    std::cout << "Importance: " << importance << std::endl;
    
    // Convert timestamp to readable format
    char buffer[26];
    ctime_s(buffer, sizeof(buffer), &timestamp);
    std::cout << "Timestamp: " << buffer;
}
