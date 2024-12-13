//
// Created by Muhammad Abdullah on 12/12/2024.
//

#ifndef CONNECTIONSMANAGER_H
#define CONNECTIONSMANAGER_H
using namespace std;
#include <vector>
#include "DoublyLinkedList.h"
class ConnectionsManager {
private:
    DoublyLinkedList<pair<int, int>> connections;
public:
    ConnectionsManager();
    void addConnection(int userID1, int userID2);
    bool areConnected(int userID1, int userID2);
    void removeConnection(int userID1, int userID2);
    vector<int> getConnectionsByUser(int userId);
    void displayConnections();
    void displayMutualConnections();
    void displayUserConnections();
    void displayUserConnections(int userId);
    int getUserConnectionCount(int userId);
};



#endif //CONNECTIONSMANAGER_H
