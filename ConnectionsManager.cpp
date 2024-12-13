#include "ConnectionsManager.h"
#include "User.h"
#include "DoublyLinkedList.h"
#include <set>
using namespace std;

// Constructor to initialize the connections linked list
ConnectionsManager::ConnectionsManager() {
    connections = DoublyLinkedList<pair<int, int>>();
}

// Function to add a connection between two user IDs
void ConnectionsManager::addConnection(int userID1, int userID2) {
    // Check if the connection already exists
    if (areConnected(userID1, userID2)) {
        cout << "Connection already exists." << endl;
        return;
    }

    // Add the connection to the linked list
    connections.pushBack(make_pair(userID1, userID2));
    cout << "Connection added successfully." << endl;
}

// Function to check if a connection exists between two user IDs
bool ConnectionsManager::areConnected(int userID1, int userID2) {
    // Iterate through the connections to find a match
    for (auto connection : connections) {
        if ((connection.first == userID1 && connection.second == userID2) ||
            (connection.first == userID2 && connection.second == userID1)) {
            return true;
        }
    }
    return false;
}

// Function to remove a connection between two user IDs
void ConnectionsManager::removeConnection(int userID1, int userID2) {
    // Check if the connection exists
    if (areConnected(userID1, userID2)) {
        // Iterate through the connections to find and remove the match
        for (auto connection : connections) {
            if ((connection.first == userID1 && connection.second == userID2) ||
                (connection.first == userID2 && connection.second == userID1)) {
                connections.deleteByValue(connection);
                cout << "Connection removed successfully." << endl;
                return;
            }
        }
    } else {
        cout << "Connection not found." << endl;
    }
}

// Function to display all connections
void ConnectionsManager::displayConnections() {
    cout << "Displaying all connections:" << endl;
    for (auto connection : connections) {
        cout << connection.first << " <--> " << connection.second << endl;
    }
}

// Function to get all connections for a specific user ID, ensuring no duplicates
vector<int> ConnectionsManager::getConnectionsByUser(int userId) {
    set<int> userConnectionsSet; // Use a set to ensure no duplicates
    for (auto connection : connections) {
        if (connection.first == userId) {
            userConnectionsSet.insert(connection.second);
        } else if (connection.second == userId) {
            userConnectionsSet.insert(connection.first);
        }
    }
    // Convert the set to a vector and return
    return vector<int>(userConnectionsSet.begin(), userConnectionsSet.end());
}