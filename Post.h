#ifndef POST_H
#define POST_H

#include <string>
#include <ctime>

class Post {
private:
    std::string content;
    std::string type;
    int importance;
    time_t timestamp;

public:
    // Constructors
    Post();
    Post(const std::string& content, const std::string& type, int importance);

    // Setters
    void setContent(const std::string& content);
    void setType(const std::string& type);
    void setImportance(int importance);

    // Getters
    std::string getContent() const;
    std::string getType() const;
    int getImportance() const;
    time_t getTimestamp() const;

    // Display method
    void displayPostDetails() const;
};

#endif // POST_H