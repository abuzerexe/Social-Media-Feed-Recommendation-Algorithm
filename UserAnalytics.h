//
// Created by Abdul Muizz on 12/12/2024.
//

#ifndef USERANALYTICS_H
#define USERANALYTICS_H
#include <vector>
#include "User.h"
using namespace std ;


class UserAnalytics {

public:

    std::pmr::vector<User> getMostActiveUsers();
    User getInfluentialUsers();
    int getIsolatedUserCount() ;

};



#endif //USERANALYTICS_H
