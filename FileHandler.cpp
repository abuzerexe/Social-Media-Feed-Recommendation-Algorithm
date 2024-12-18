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
    std::ifstream file(filename);
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
                User user(userData[0], userData[1], userData[2], interests);
                
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
    std::ifstream file(filename);
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
    std::ifstream file(filename);
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

bool FileHandler::saveUsers(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for saving users " << filename << std::endl;
        return false;
    }

    // Write header
    file << "Name,Username,Email,Interests\n";

    for (auto& pair : UserManager::userById) {
        User& user = pair.second;
        file << user.getname() << ","
             << user.getUserName() << ","
             << user.getUserEmail() << ",";

        // Write interests
        DoublyLinkedList<string> interests = user.getUserInterests();
        DoublyLinkedList<string>::Node* current = interests.head; // Correct Node type
        bool first = true;
        while (current) {
            if (!first) file << ";";
            file << current->data;
            current = current->next;
            first = false;
        }
        file << "\n";
    }

    std::cout << "Users saved successfully to " << filename << std::endl;
    return true;
}

bool FileHandler::savePosts(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for saving posts " << filename << std::endl;
        return false;
    }

    // Write header
    file << "UserID,Content,Type,Importance,Tags\n";

    for (auto& pair : UserManager::userById) {
        User& user = pair.second; // Remove const qualifier
        PostLinkedList& postList = user.getPostList();

        PostLinkedList::Node* current = postList.head; // Correct Node type
        while (current) {
            file << user.getUserId() << ","
                 << current->data.getContent() << ","
                 << current->data.getType() << ","
                 << current->data.getImportance() << ",";

            // Write tags
            const std::vector<std::string>& tags = current->data.tags;
            for (size_t i = 0; i < tags.size(); ++i) {
                file << tags[i];
                if (i < tags.size() - 1) file << ";";
            }
            file << "\n";

            current = current->next;
        }
    }

    std::cout << "Posts saved successfully to " << filename << std::endl;
    return true;
}

bool FileHandler::saveConnections(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for saving connections " << filename << std::endl;
        return false;
    }

    // Write header
    file << "UserID1,UserID2\n";

    for (const auto& connection : connectionManager.connections) {
        file << connection.first << "," << connection.second << "\n";
    }

    std::cout << "Connections saved successfully to " << filename << std::endl;
    return true;
}