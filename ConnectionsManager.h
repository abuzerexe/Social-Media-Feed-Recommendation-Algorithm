// ConnectionsManager.h
#ifndef CONNECTIONSMANAGER_H
#define CONNECTIONSMANAGER_H

#include <vector>
#include <set>
#include "DoublyLinkedList.h"
#include <map>
using namespace std;

class ConnectionsManager {
public:
    // Constructor
    ConnectionsManager();

    // Core functionality
    void addConnection(int userID1, int userID2);
    bool areConnected(int userID1, int userID2);
    void removeConnection(int userID1, int userID2);

    // Getters
    vector<int> getConnectionsByUser(int userId);
    map<int, vector<int>> getPotentialFriendSuggestions(int userId);
    int getUserConnectionCount(int userId);

    // Utility functions
    void displayConnections();
    bool validateUserIds(int userID1, int userID2) const;

private:
    DoublyLinkedList<pair<int, int>> connections;
    void sortUserIds(int& id1, int& id2) const;
};

#endif //CONNECTIONSMANAGER_H