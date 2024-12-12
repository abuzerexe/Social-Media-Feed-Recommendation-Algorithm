#include "UserManager.h"
#include "User.h"
#include <iostream>
#include <string>
 
using namespace std;

int main() {
    UserManager userManager;

    DoublyLinkedList<string> initialInterests1;
    initialInterests1.pushBack("Technology");
    initialInterests1.pushBack("Gaming");

    DoublyLinkedList<string> initialInterests2;
    initialInterests2.pushBack("Sports");
    initialInterests2.pushBack("Photography");

    DoublyLinkedList<string> initialInterests3;
    initialInterests3.pushBack("Fashion");
    initialInterests3.pushBack("Politics");

    cout << "Adding users...\n\n";
    User user1("Abuzer", "abuzerexe","abouzer381@gmail.com", initialInterests1);
    cout << user1.getUserId()<< endl;
    User user2("MrLongShlong", "MrlongShlong","mrlongshlong@gmail.com", initialInterests2);
    cout<< user2.getUserId()<< endl;
    User user3("MrShortShlong", "MrShortShlong","mrshortshlong@gmail.com", initialInterests3);
    cout<< user3.getUserId()<< endl;

    bool added1 = userManager.addUser(user1);
    bool added2 = userManager.addUser(user2);
    bool added3 = userManager.addUser(user3);

    cout << "User 1 added: " << (added1 ? "Yes" : "No") << endl;
    cout << "User 2 added: " << (added2 ? "Yes" : "No") << endl;
    cout << "User 3 added: " << (added3 ? "Yes" : "No") << endl;

    // Attempt to add a user with a duplicate username
    User user4("az", "abuzerexe","az@gmail.com", initialInterests1);
    bool added4 = userManager.addUser(user4);
    cout << "Duplicate user added: " << (added4 ? "Yes" : "No") << endl;

    user1.addConnection(2);
    user1.addConnection(3);
    // cout<<user1.isConnectedTo(2)<<endl;
    user1.removeConnection(2);
    // cout<<user1.isConnectedTo(2)<<endl;
    cout<<user1.getNumConnections()<<endl;
    // user1.displayUserDetails();

    // List all users
    // cout << "\nListing all users:\n";
    // userManager.listAllUsers();

        // Retrieve a user by ID
    // cout << "\nRetrieving user with ID 2:\n";
    // User* retrievedUser = userManager.getUserById(2);
    // if (retrievedUser) {
    //     retrievedUser->displayUserDetails();
    // } else {
    //     cout << "User not found.\n";
    // }

    // Retrieve a user by username
    // cout << "\nRetrieving user with username :\n";
    // retrievedUser = userManager.getUserByUsername("abuzerexe");
    // if (retrievedUser) {
    //     retrievedUser->displayUserDetails();
    // } else {
    //     cout << "User not found.\n";
    // }

    // // Remove a user by ID
    cout << "\nRemoving user with ID 1:\n";
    bool removed = userManager.removeUser(1);
     cout << " user removed: " << (removed ? "Yes" : "No") << endl;


    // // Attempt to remove a non-existing user
    // cout << "\nRemoving user with ID 99:\n";
    // removed = userManager.removeUser(99);
    // cout << " user removed: " << (removed ? "Yes" : "No") << endl;


    // // List all users again
    // cout << "\nListing all users after removal:\n";
    // userManager.listAllUsers();


   
    return 0;
}

// To run

// del *.obj  # Windows
// g++ -o SocialMediaSimulator main.cpp UserManager.cpp User.cpp AllInterests.cpp 
// ./SocialMediaSimulator
