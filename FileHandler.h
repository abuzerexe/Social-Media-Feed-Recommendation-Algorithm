#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "User.h"
#include "Post.h"
#include "UserManager.h"
#include "ConnectionsManager.h"

class FileHandler {
public:
    // Constructor taking references to UserManager and ConnectionsManager
    FileHandler(UserManager& userManager, ConnectionsManager& connectionManager);

    // Load sample users from a file
    bool loadSampleUsers(const std::string& filename);

    // Load sample posts from a file
    bool loadSamplePosts(const std::string& filename);

    // Load sample connections from a file
    bool loadSampleConnections(const std::string& filename);

    // Save current users to a file
    bool saveUsers(const std::string& filename);

    // Save current posts to a file
    bool savePosts(const std::string& filename);

    // Save current connections to a file
    bool saveConnections(const std::string& filename);

private:
    UserManager& userManager;
    ConnectionsManager& connectionManager;

    // Helper method to trim whitespace
    std::string trim(const std::string& str);

    // Validate input data
    bool validateUserData(const std::vector<std::string>& userData);
    bool validatePostData(const std::vector<std::string>& postData);
    bool validateConnectionData(const std::vector<std::string>& connectionData);
};

#endif // FILE_HANDLER_H