#include "FileHandler.h"

FileHandler::FileHandler(UserManager& userManager, ConnectionsManager& connectionManager)
    : userManager(userManager), connectionManager(connectionManager) {}

std::string FileHandler::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

bool FileHandler::validateUserData(const std::vector<std::string>& userData) {
    // Check for minimum required user data fields
    return userData.size() >= 4; // Name, Username, Email, Interests
}

bool FileHandler::validatePostData(const std::vector<std::string>& postData) {
    // Check for minimum required post data fields
    return postData.size() >= 4; // UserID, Content, Type, Importance
}

bool FileHandler::validateConnectionData(const std::vector<std::string>& connectionData) {
    // Check for valid connection data
    return connectionData.size() == 2; // UserID1, UserID2
}

bool FileHandler::loadSampleUsers(const std::string& filename) {
    string fixedName = "../users.txt";
    std::ifstream file(fixedName);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open users file " << filename << std::endl;
        return false;
    }

    std::string line;
    int successCount = 0, errorCount = 0;

    // Skip header if exists
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::vector<std::string> userData;
        std::string field;

        while (std::getline(ss, field, ',')) {
            userData.push_back(trim(field));
        }

        if (validateUserData(userData)) {
            try {
                // Create interests list
                DoublyLinkedList<string> interests;
                for (size_t i = 3; i < userData.size(); ++i) {
                    interests.pushBack(userData[i]);
                }

                // Create user
                // Create user
                int userId = std::stoi(userData[0]);  // Convert string ID to integer
                User user(userId, userData[1], userData[2], userData[3], interests);  // Add email parameter
                
                // Add user to UserManager
                if (userManager.addUser(user)) {
                    successCount++;
                } else {
                    errorCount++;
                }
            } catch (const std::exception& e) {
                std::cerr << "Error processing user: " << e.what() << std::endl;
                errorCount++;
            }
        } else {
            std::cerr << "Invalid user data: " << line << std::endl;
            errorCount++;
        }
    }

    std::cout << "Users loaded - Success: " << successCount 
              << ", Errors: " << errorCount << std::endl;

    return successCount > 0;
}

bool FileHandler::loadSamplePosts(const std::string& filename) {
    string fixedName = "../posts.txt";
    std::ifstream file(fixedName);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open posts file " << filename << std::endl;
        return false;
    }

    std::string line;
    int successCount = 0, errorCount = 0;

    // Skip header if exists
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::vector<std::string> postData;
        std::string field;

        while (std::getline(ss, field, ',')) {
            postData.push_back(trim(field));
        }

        if (validatePostData(postData)) {
            try {
                // Convert user ID
                int userId = std::stoi(postData[0]);

                // Create post
                Post post(postData[1], postData[2], std::stoi(postData[3]));

                // Add tags if more fields exist
                for (size_t i = 4; i < postData.size(); ++i) {
                    post.addTag(postData[i]);
                }

                // Add post to user
                User* user = userManager.getUserById(userId);
                if (user) {
                    user->addPost(post);
                    successCount++;
                } else {
                    std::cerr << "User not found for post: " << line << std::endl;
                    errorCount++;
                }
            } catch (const std::exception& e) {
                std::cerr << "Error processing post: " << e.what() << std::endl;
                errorCount++;
            }
        } else {
            std::cerr << "Invalid post data: " << line << std::endl;
            errorCount++;
        }
    }

    std::cout << "Posts loaded - Success: " << successCount 
              << ", Errors: " << errorCount << std::endl;

    return successCount > 0;
}

bool FileHandler::loadSampleConnections(const std::string& filename) {
    string fixedName = "../connections.txt";
    std::ifstream file(fixedName);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open connections file " << filename << std::endl;
        return false;
    }

    std::string line;
    int successCount = 0, errorCount = 0;

    // Skip header if exists
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::vector<std::string> connectionData;
        std::string field;

        while (std::getline(ss, field, ',')) {
            connectionData.push_back(trim(field));
        }

        if (validateConnectionData(connectionData)) {
            try {
                // Convert user IDs
                int userId1 = std::stoi(connectionData[0]);
                int userId2 = std::stoi(connectionData[1]);

                // Add connection
                if (userManager.getUserById(userId1) && userManager.getUserById(userId2)) {
                    connectionManager.addConnection(userId1, userId2);
                    successCount++;
                } else {
                    std::cerr << "Invalid users for connection: " << line << std::endl;
                    errorCount++;
                }
            } catch (const std::exception& e) {
                std::cerr << "Error processing connection: " << e.what() << std::endl;
                errorCount++;
            }
        } else {
            std::cerr << "Invalid connection data: " << line << std::endl;
            errorCount++;
        }
    }

    std::cout << "Connections loaded - Success: " << successCount 
              << ", Errors: " << errorCount << std::endl;

    return successCount > 0;
}

