// ConnectionsManager.cpp

#include "ConnectionsManager.h"
#include <iostream>
#include <algorithm>
#include <set>
#include <stdexcept>
#include <map>
using namespace std;

// Constructor
ConnectionsManager::ConnectionsManager() {
    connections = DoublyLinkedList<pair<int, int>>();
}

// Helper method to validate user IDs
bool ConnectionsManager::validateUserIds(int userID1, int userID2) const {
    if (userID1 < 0 || userID2 < 0) {
        return false;
    }

    if (userID1 == userID2) {
        return false;
    }

    return true;
}

// Helper method for consistent ID ordering
void ConnectionsManager::sortUserIds(int& id1, int& id2) const {
    if (id1 > id2) {
        swap(id1, id2);
    }
}

// Add connection with validation
void ConnectionsManager::addConnection(int userID1, int userID2) {
    if (!validateUserIds(userID1, userID2)) {
        throw invalid_argument("Invalid user IDs provided");
    }

    sortUserIds(userID1, userID2);

    if (areConnected(userID1, userID2)) {
        throw runtime_error("Connection already exists");
    }

    connections.pushBack(make_pair(userID1, userID2));
}

// Remove connection with error handling
void ConnectionsManager::removeConnection(int userID1, int userID2) {
    if (!validateUserIds(userID1, userID2)) {
        throw invalid_argument("Invalid user IDs provided");
    }

    sortUserIds(userID1, userID2);

    for (const auto& connection : connections) {
        if (connection.first == userID1 && connection.second == userID2) {
            connections.deleteByValue(connection);
            return;
        }
    }

    throw runtime_error("Connection not found");
}

// Check if users are connected
bool ConnectionsManager::areConnected(int userID1, int userID2) {
    if (!validateUserIds(userID1, userID2)) {
        return false;
    }

    sortUserIds(userID1, userID2);

    for (const auto& connection : connections) {
        if (connection.first == userID1 && connection.second == userID2) {
            return true;
        }
    }
    return false;
}

// Get all connections for a user
vector<int> ConnectionsManager::getConnectionsByUser(int userId) {
    if (userId < 0) {
        throw invalid_argument("Invalid user ID");
    }

    set<int> userConnectionsSet;
    for (const auto& connection : connections) {
        if (connection.first == userId) {
            userConnectionsSet.insert(connection.second);
        } else if (connection.second == userId) {
            userConnectionsSet.insert(connection.first);
        }
    }

    return vector<int>(userConnectionsSet.begin(), userConnectionsSet.end());
}

// Get mutual connections
map<int, vector<int>> ConnectionsManager::getPotentialFriendSuggestions(int userId) {
    if (userId < 0) {
        throw invalid_argument("Invalid user ID");
    }

    map<int, vector<int>> potentialFriends;  // potential friend ID -> [mutual friend IDs]

    // Get user's direct connections
    vector<int> userConnections = getConnectionsByUser(userId);

    // For each of user's friends, get their friends
    for (int friendId : userConnections) {
        vector<int> friendConnections = getConnectionsByUser(friendId);

        // Check each friend-of-friend
        for (int potentialFriendId : friendConnections) {
            // Skip if this is the main user or already a direct connection
            if (potentialFriendId == userId ||
                find(userConnections.begin(), userConnections.end(), potentialFriendId) != userConnections.end()) {
                continue;
                }

            // Add to potential friends map
            potentialFriends[potentialFriendId].push_back(friendId);
        }
    }

    return potentialFriends;
}

// Get connection count
int ConnectionsManager::getUserConnectionCount(int userId) {
    if (userId < 0) {
        throw invalid_argument("Invalid user ID");
    }

    return getConnectionsByUser(userId).size();
}

// Display all connections
void ConnectionsManager::displayConnections()  {
    if (connections.isEmpty()) {
        cout << "No connections exist in the network." << endl;
        return;
    }

    cout << "\nCurrent Network Connections:" << endl;
    cout << "-------------------------" << endl;

    for (const auto& connection : connections) {
        cout << "User " << connection.first
             << " <--> User " << connection.second << endl;
    }
    cout << "-------------------------" << endl;
}