cmake_minimum_required(VERSION 3.28.6)
project(SocialMediaFeed)

set(CMAKE_CXX_STANDARD 20)

add_executable(SocialMediaFeed main.cpp
        AllInterests.cpp
        AllInterests.h
        DoublyLinkedList.h
        DoublyLinkedList.tpp
        User.cpp
        User.h
        UserManager.cpp
        UserManager.h
        ConnectionsManager.cpp
        ConnectionsManager.h
        UserAnalytics.cpp
        UserAnalytics.h
        PostLinkList.cpp
        PostLinkList.h
        FileHandler.cpp
        FileHandler.h
        Post.cpp
        Post.h
        FeedGenerator.cpp
        FeedGenerator.h
        Postmanagement.cpp
        Postmanagement.h
        PriorityQueue.cpp
        PriorityQueue.h
)
