//
// Created by Abdul Muizz on 12/12/2024.
//

#include "UserAnalytics.h"
#include "UserManager.h"
#include "User.h"
#include <vector>
#include <iostream>
using namespace std ;

std::pmr::vector<User> UserAnalytics::getMostActiveUsers() {
        std::pmr::vector<User> mostActiveUsers;
        int maxPosts = 0;

        for (const auto& pair : UserManager::userById) {
                int userId = pair.first;
                User user = pair.second;
                if ( user.getPostQueue().getNumberOfPosts() >= maxPosts ) {
                        mostActiveUsers.clear();
                        maxPosts = user.getPostQueue().getNumberOfPosts() ;
                        mostActiveUsers.push_back(user);
                }
        }

        return mostActiveUsers ;
}

UserAnalytics

