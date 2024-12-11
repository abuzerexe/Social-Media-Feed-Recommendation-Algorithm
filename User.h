#ifndef USER_H
#define USER_H

#include <string>
#include "DoublyLinkedList.h"

class User {
private:
    int userId;
    string userName;
    std::string name;
    std::string email;
    DoublyLinkedList<std::string> interests;
    DoublyLinkedList<int> connections;

    static int userCounter; // Static counter for generating unique user IDs

public:
     User();
    User(std::string name, std::string username ,std::string email, DoublyLinkedList<std::string> interests);

    // Setters
    void setName(string name);
    void setUserName(string userName);
    void setUserEmail(string email);
    void setUserInterests(DoublyLinkedList<string> interests);

    // Getters
    int getUserId();
    string getname();
    string getUserName();
    string getUserEmail();
    DoublyLinkedList<string> getUserInterests();
    DoublyLinkedList<int> getUserConnections();

    // Methods for interests
    bool hasInterest(std::string interest);
    void addInterests();
    void updateInterests();
    void removeInterests();

    // Methods for connections
    void addConnection(int userId);
    void removeConnection(int userId);
    bool isConnectedTo(int userId);
    int getNumConnections();

    // Display methods
    void displayUserDetails();
    void displayUserInterests();
};

#endif // USER_H
