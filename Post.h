#ifndef POST_H
#define POST_H

#include <string>
#include <ctime>
#include <vector>

class Post {
public:
    // Existing constructors
    Post();
    Post(const std::string& content, const std::string& type, int importance);

    // Existing setters and getters
    void setContent(const std::string& content);
    void setType(const std::string& type);
    void setImportance(int importance);

    std::string getContent() const;
    std::string getType() const;
    int getImportance() const;
    time_t getTimestamp() const;

    // New members for feed generation
    std::vector<std::string> tags;
    int interestMatchScore = 0;

    // Method to add tags to the post
    void addTag(const std::string& tag);

    // Display post details
    void displayPostDetails() const;

    // Overloaded comparison operators for priority queue
    bool operator<(const Post& other) const;
    bool operator>(const Post& other) const;

private:
    std::string content;
    std::string type;
    int importance;
    time_t timestamp;
};

#endif // POST_H