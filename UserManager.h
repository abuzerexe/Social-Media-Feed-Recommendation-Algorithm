#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <unordered_map>
#include "User.h" 
using namespace std;

class UserManager {

private:
    unordered_map<int, User> userById;        // userId -> User object
    unordered_map<string, int> userByUserName; // username -> userId

public:
    // Adds a user to the manager, ensuring unique username
    bool addUser(User& user);

    // Removes a user by their ID
    bool removeUser(int userId);

    // Checks if a username exists
    bool userExistsByUsername(string username);

    // Retrieves a user by their ID
    User* getUserById(int userId);

    // Retrieves a user by their username
    User* getUserByUsername(string username);

    // Lists all users 
    void listAllUsers();
};

#endif // USERMANAGER_H
