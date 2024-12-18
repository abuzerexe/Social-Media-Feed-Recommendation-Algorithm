#ifndef FEEDGENERATOR_H
#define FEEDGENERATOR_H

#include <queue>
#include "UserManager.h"
#include "ConnectionsManager.h"
#include "Post.h"

class FeedGenerator {
public:
    FeedGenerator(UserManager& um, ConnectionsManager& cm);
    std::priority_queue<Post> generateFeed(int userID);

private:
    UserManager& userManager;
    ConnectionsManager& connectionsManager;
};

#endif // FEEDGENERATOR_H