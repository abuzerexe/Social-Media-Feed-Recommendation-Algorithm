// FileHandler.cpp
#include "FileHandler.h"
using namespace std;

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
    return userData.size() >= 4;
}

bool FileHandler::validatePostData(const std::vector<std::string>& postData) {
    return postData.size() >= 4;
}

bool FileHandler::validateConnectionData(const std::vector<std::string>& connectionData) {
    return connectionData.size() == 2;
}

bool FileHandler::loadSampleUsers(const std::string& filename) {
    string fixedName = "../users.txt";
    ifstream file(fixedName);
    if (!file.is_open()) {
        cerr << "Error: Could not open users file " << filename << endl;
        return false;
    }

    string line;
    int successCount = 0, errorCount = 0;

    getline(file, line);

    while (getline(file, line)) {
        istringstream ss(line);
        vector<string> userData;
        string field;

        while (getline(ss, field, ',')) {
            userData.push_back(trim(field));
        }

        if (validateUserData(userData)) {
            try {
                DoublyLinkedList<string> interests;
                for (size_t i = 3; i < userData.size(); ++i) {
                    interests.pushBack(userData[i]);
                }

                int userId = stoi(userData[0]);
                User user(userId, userData[1], userData[2], userData[3], interests);

                if (userManager.addUser(user)) {
                    successCount++;
                } else {
                    errorCount++;
                }
            } catch (const exception& e) {
                cerr << "Error processing user: " << e.what() << endl;
                errorCount++;
            }
        } else {
            cerr << "Invalid user data: " << line << endl;
            errorCount++;
        }
    }

    cout << "Users loaded - Success: " << successCount << ", Errors: " << errorCount << endl;

    return successCount > 0;
}

bool FileHandler::loadSamplePosts(const std::string& filename) {
    string fixedName = "../posts.txt";
    ifstream file(fixedName);
    if (!file.is_open()) {
        cerr << "Error: Could not open posts file " << filename << endl;
        return false;
    }

    string line;
    int successCount = 0, errorCount = 0;

    getline(file, line);

    while (getline(file, line)) {
        istringstream ss(line);
        vector<string> postData;
        string field;

        while (getline(ss, field, ',')) {
            postData.push_back(trim(field));
        }

        if (validatePostData(postData)) {
            try {
                int userId = stoi(postData[0]);
                Post post(postData[1], postData[2], stoi(postData[3]));

                for (size_t i = 4; i < postData.size(); ++i) {
                    post.addTag(postData[i]);
                }

                User* user = userManager.getUserById(userId);
                if (user) {
                    user->addPost(post);
                    successCount++;
                } else {
                    cerr << "User not found for post: " << line << endl;
                    errorCount++;
                }
            } catch (const exception& e) {
                cerr << "Error processing post: " << e.what() << endl;
                errorCount++;
            }
        } else {
            cerr << "Invalid post data: " << line << endl;
            errorCount++;
        }
    }

    cout << "Posts loaded - Success: " << successCount << ", Errors: " << errorCount << endl;

    return successCount > 0;
}

bool FileHandler::loadSampleConnections(const std::string& filename) {
    string fixedName = "../connections.txt";
    ifstream file(fixedName);
    if (!file.is_open()) {
        cerr << "Error: Could not open connections file " << filename << endl;
        return false;
    }

    string line;
    int successCount = 0, errorCount = 0;

    getline(file, line);

    while (getline(file, line)) {
        istringstream ss(line);
        vector<string> connectionData;
        string field;

        while (getline(ss, field, ',')) {
            connectionData.push_back(trim(field));
        }

        if (validateConnectionData(connectionData)) {
            try {
                int userId1 = stoi(connectionData[0]);
                int userId2 = stoi(connectionData[1]);

                if (userManager.getUserById(userId1) && userManager.getUserById(userId2)) {
                    connectionManager.addConnection(userId1, userId2);
                    successCount++;
                } else {
                    cerr << "Invalid users for connection: " << line << endl;
                    errorCount++;
                }
            } catch (const exception& e) {
                cerr << "Error processing connection: " << e.what() << endl;
                errorCount++;
            }
        } else {
            cerr << "Invalid connection data: " << line << endl;
            errorCount++;
        }
    }

    cout << "Connections loaded - Success: " << successCount << ", Errors: " << errorCount << endl;

    return successCount > 0;
}