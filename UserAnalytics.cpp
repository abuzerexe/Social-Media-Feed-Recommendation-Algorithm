//
// Created by Abdul Muizz on 12/12/2024.
//
#include "UserAnalytics.h"
#include "UserManager.h"
#include "User.h"
#include <vector>
#include "ConnectionsManager.h"
#include <iostream>
#include <queue>

#include "PriorityQueue.h"
using namespace std ;

std::vector<User> UserAnalytics::getMostActiveUsers() {
        vector<User> mostActiveUsers;
        PriorityQueue pq;


        if (UserManager::userById.empty()) {
                cout << "No users found.\n";
                return mostActiveUsers;
        }

        for (const auto& pair : UserManager::userById) {
                User user = pair.second;
                pq.enqueueUser(user); ;
        }

        int count = 0;
        while (!pq.isEmpty() && count < 5) {
                mostActiveUsers.push_back(pq.dequeueUser());
                count++;
        }

        return mostActiveUsers;
}

// Function to get the most followed users
User UserAnalytics::getInfluentialUser(ConnectionsManager connectionsManager) {
        User influentialUser;
        int maxFollowers = 0;

        for ( const auto& pair : UserManager::userById ) {
                User user = pair.second;
                int connections = connectionsManager.getConnectionsByUser(user.getUserId()).size();

                if ( connections >= maxFollowers ) {
                        maxFollowers = connections;
                        influentialUser = user;
                }
        }

        return influentialUser ;

}

// Function to get the number of isolated users
int UserAnalytics::getIsolatedUserCount(ConnectionsManager connectionsManager) {
        int isolatedUserCount = 0;

        for ( const auto& pair : UserManager::userById ) {
                User user = pair.second;
                int connections = connectionsManager.getConnectionsByUser(user.getUserId()).size();

                if ( connections == 0 ) {
                        isolatedUserCount++;
                }
        }

        return isolatedUserCount ;
}



