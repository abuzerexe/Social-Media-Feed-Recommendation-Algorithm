//
// Created by Abdul Muizz on 12/12/2024.
//

#ifndef USERANALYTICS_H
#define USERANALYTICS_H
#include <vector>

#include "ConnectionsManager.h"
#include "User.h"
using namespace std ;


class UserAnalytics {

public:

    std::vector<User> getMostActiveUsers();
    User getInfluentialUser();
    int getIsolatedUserCount(ConnectionsManager connectionsManager); ;

};



#endif //USERANALYTICS_H
