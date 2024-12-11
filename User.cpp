#include <iostream>
#include <string>
#include <vector>
#include "User.h"
#include "DoublyLinkedList.h"
#include "AllInterests.h"
using namespace std;



int User::userCounter = 1; // Initialize the static counter

// Constructor
User::User() {
 this->userId = userCounter++;
}

User::User(string name, string username ,string email, DoublyLinkedList<string> interests) {
    this->name = name;
    this->userName = username;
    this->email = email;
    this->userId = userCounter++;
    this->interests = interests;

}

// Setters

void User::setName(string name) {
    this->name = name;
}

void User::setUserName(string userName) {
    this->userName = userName;
}

void User::setUserEmail(string email) {
    this->email = email;
}

void User::setUserInterests(DoublyLinkedList<string> interests) {
    this->interests = interests;
}

// Getters
int User::getUserId() {
    return userId;
}

string User::getname() {
    return name;
}

string User::getUserName() {
    return userName;
}

string User::getUserEmail() {
    return email;
}

DoublyLinkedList<string> User::getUserInterests() {
    return interests;
}

DoublyLinkedList<int> User::getUserConnections() {
    return connections;
}

// Additional methods

bool User::hasInterest(string interest) {
    return interests.contains(interest);
}

void User::addInterests() {

    displayAllInterests();
    char continueChoice;

    do {
        cout << "Enter the number corresponding to the interest you want to select: ";
        int choice;
        cin >> choice;

        if (choice > 0 && choice <= allInterests.size()) {
            string selectedInterest = allInterests[choice - 1];

            if (interests.contains(selectedInterest)) {
                cout << selectedInterest << " is already in your interest list. " << endl;
            } else {
                interests.pushBack(selectedInterest);
                cout << selectedInterest << " has been added to your interests.\n";
            }
        } else {
            cout << "Invalid choice. Please select a valid number. " << endl;
        }

        do {
            cout << "Do you want to add another interest? (y/n) ";
            cin >> continueChoice;
            cin.ignore();
            continueChoice = tolower(continueChoice);

            if (continueChoice != 'y' && continueChoice != 'n') {
                cout << "Invalid input. Please enter 'y' for yes and 'n' for no.\n ";
            }
        } while (continueChoice != 'y' && continueChoice != 'n');

    } while (continueChoice == 'y');

    cout << "Interests added successfully!\n";
}

void User::removeInterests(){

    string interestToRemove;
    cout << "Enter the name of Interest you want to remove: ";
    getline(cin, interestToRemove);
    interests.deleteByValue(interestToRemove);

}

void User::updateInterests() {
    
    cout << "Do you want to (1) Add or (2) Remove interests? Enter your choice: ";
    
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1)
    {
        addInterests();
    }else if(choice == 2){
        removeInterests();
    }else{
        cout << "Invalid Choice! \n" ;
    }
    
}

void User::addConnection(int userId){

    connections.pushBack(userId);

    cout << "Connected Successfully! \n";
}


void User::removeConnection(int userId){

    if (connections.contains(userId))
    {
        connections.deleteByValue(userId);
        cout << "Connection removed successfully \n"; 

    }else{
        cout << "No such connection. \n";
    }    
}


bool User::isConnectedTo(int userId){

    if (connections.contains(userId))
    {
        return true;

    }else{
        return false;
    }   
}


int User::getNumConnections(){

    return connections.size();

}

void User::displayUserDetails() {
    cout << "User ID: " << getUserId() << endl;
    cout << "Name: " << getname() << endl;
    cout << "Username: " << getUserName() << endl;
    cout << "Email: " << getUserEmail() << endl;
    cout << "Interests: " << endl;
    interests.displayForward();
    cout << "Connections No. : " << getNumConnections()<< endl;
}


void User::displayUserInterests() {
    cout << "Your interests are: " << endl;
    interests.displayForward();
}



