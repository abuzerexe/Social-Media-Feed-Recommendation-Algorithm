//
// Created by Abdul Muizz on 12/12/2024.
//
#include "UserAnalytics.h"
#include "UserManager.h"
#include "User.h"
#include <vector>
#include "ConnectionsManager.h"
#include <iostream>
using namespace std ;

// Function to get the most active users
std::pmr::vector<User> UserAnalytics::getMostActiveUsers() {
        std::pmr::vector<User> mostActiveUsers;

        for (const auto& pair : UserManager::userById) {
                User user = pair.second;
                if ( user.getPostStack().getNumberOfPosts() >= 5 ) {
                        mostActiveUsers.push_back(user);
                }
        }
        return mostActiveUsers ;
}

// Function to get the most followed users
User UserAnalytics::getInfluentialUsers() {
        User influentialUser;
        ConnectionsManager connectionsManager ;
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
int UserAnalytics::getIsolatedUserCount() {
        ConnectionsManager connectionsManager ;
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



