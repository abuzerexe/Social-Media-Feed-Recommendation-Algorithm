#include <iostream>
#include <limits>
#include <iomanip>
#include <queue>
#include <map>

#include "UserManager.h"
#include "ConnectionsManager.h"
#include "PostManagement.h"
#include "FeedGenerator.h"
#include "FileHandler.h"
#include "UserAnalytics.h"
#include "AllInterests.h"

using namespace std;

class SocialMediaApp {
private:
    UserManager userManager;
    ConnectionsManager connectionManager;
    PostManagement postManagement;
    FeedGenerator feedGenerator;
    FileHandler fileHandler;
    UserAnalytics userAnalytics;
    User* currentUser;

    // Helper methods
    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void displayHeader(const string& title) {
        cout << "\n========================================\n";
        cout << "           " << title << "\n";
        cout << "========================================\n";
    }

    void displayMenuOption(const string& option, const string& description) {
        cout << setw(2) << option << "  |  " << description << "\n";
    }

    int getIntInput(const string& prompt, int min = 1, int max = INT_MAX) {
        int choice;
        while (true) {
            cout << prompt;
            if (cin >> choice) {
                if (choice >= min && choice <= max) {
                    clearInputBuffer();
                    return choice;
                }
            }
            cout << "Invalid input. Please try again.\n";
            clearInputBuffer();
        }
    }

    string getStringInput(const string& prompt) {
        string input;
        cout << prompt;
        getline(cin, input);
        return input;
    }

    User* selectUser() {
        displayHeader("Select User");
        userManager.listAllUsers();

        if (UserManager::userById.empty()) {
            cout << "No users available. Please add users first.\n";
            return nullptr;
        }

        int userId = getIntInput("Enter User ID to select: ");
        User* selectedUser = userManager.getUserById(userId);

        if (!selectedUser) {
            cout << "User not found.\n";
            return nullptr;
        }

        return selectedUser;
    }
    void displayFeed(priority_queue<Post> feed, int postsPerPage = 5) {
        if (feed.empty()) {
            cout << "\n========================================\n";
            cout << "           No Posts in Feed\n";
            cout << "========================================\n";
            return;
        }

        int totalPosts = feed.size();
        int currentPost = 0;
        int currentPage = 1;
        int totalPages = (totalPosts + postsPerPage - 1) / postsPerPage;

        while (!feed.empty()) {
            cout << "\n========================================\n";
            cout << "           Feed Page " << currentPage << " / " << totalPages << "\n";
            cout << "========================================\n";

            for (int i = 0; i < postsPerPage && !feed.empty(); ++i) {
                Post post = feed.top();
                feed.pop();

                cout << "\n----------------------------------------\n";
                cout << "Post " << ++currentPost << " of " << totalPosts << "\n";
                cout << "----------------------------------------\n";
                cout << "Interest Match Score: " << post.interestMatchScore << "\n";
                cout << "----------------------------------------\n";
                post.displayPostDetails();
                cout << "----------------------------------------\n";
            }

            if (!feed.empty()) {
                cout << "\nPress Enter to see the next page...";
                cin.get();
                currentPage++;
            }
        }

        cout << "\n========================================\n";
        cout << "           End of Feed\n";
        cout << "========================================\n";
    }

public:
    SocialMediaApp()
        : userManager(), connectionManager(), postManagement(userManager), feedGenerator(userManager, connectionManager),
          fileHandler(userManager, connectionManager), currentUser(nullptr) {}

    void run() {
        while (true) {
            displayHeader("Social Media Feed Application");
            if (currentUser) {
                cout << "Current User: " << currentUser->getUserName() << " (ID: " << currentUser->getUserId() << ")\n\n";
            }
            displayMenuOption("1", "User Management");
            displayMenuOption("2", "Connections Management");
            displayMenuOption("3", "Post Management");
            displayMenuOption("4", "Feed Generation");
            displayMenuOption("5", "File Operations");
            displayMenuOption("6", "User Analytics");
            displayMenuOption("7", "Exit");

            int choice = getIntInput("Enter your choice (1-7): ", 1, 7);

            switch (choice) {
                case 1: userManagementMenu(); break;
                case 2: connectionsManagementMenu(); break;
                case 3: postManagementMenu(); break;
                case 4: feedGenerationMenu(); break;
                case 5: fileOperationsMenu(); break;
                case 6: userAnalyticsMenu(); break;
                case 7:
                    cout << "Exiting application. Goodbye!\n";
                    return;
            }
        }
    }

    void userManagementMenu() {
        while (true) {
            displayHeader("User Management");
            displayMenuOption("1", "Add New User");
            displayMenuOption("2", "Remove User");
            displayMenuOption("3", "List All Users");
            displayMenuOption("4", "View User Details");
            displayMenuOption("5", "Update User Interests");
            displayMenuOption("6", "Select Current User");
            displayMenuOption("7", "Back to Main Menu");

            int choice = getIntInput("Enter your choice (1-7): ", 1, 7);

            switch (choice) {
                case 1: {
                    string name = getStringInput("Enter name: ");
                    string username = getStringInput("Enter username: ");
                    string email = getStringInput("Enter email: ");

                    DoublyLinkedList<string> interests;
                    User newUser(name, username, email, interests);
                    newUser.addInterests();

                    if (userManager.addUser(newUser)) {
                        cout << "User added successfully!\n";
                    }
                    break;
                }
                case 2: {
                    User* user = selectUser();
                    if (user) {
                        userManager.removeUser(user->getUserId());
                        if (currentUser == user) currentUser = nullptr;
                    }
                    break;
                }
                case 3:
                    userManager.listAllUsers();
                    break;
                case 4: {
                    User* user = selectUser();
                    if (user) {
                        user->displayUserDetails();
                    }
                    break;
                }
                case 5: {
                    User* user = selectUser();
                    if (user) {
                        user->updateInterests();
                    }
                    break;
                }
                case 6: {
                    currentUser = selectUser();
                    if (currentUser) {
                        cout << "Current user set to: " << currentUser->getUserName() << "\n";
                    }
                    break;
                }
                case 7:
                    return;
            }
        }
    }

    void connectionsManagementMenu() {
        while (true) {
            displayHeader("Connections Management");
            displayMenuOption("1", "Add Connection");
            displayMenuOption("2", "Remove Connection");
            displayMenuOption("3", "View All Connections");
            displayMenuOption("4", "View User's Connections");
            displayMenuOption("5", "View Mutual Connections");
            displayMenuOption("6", "Back to Main Menu");

            int choice = getIntInput("Enter your choice (1-6): ", 1, 6);

            switch (choice) {
                case 1: {
                    try {
                        cout << "Select first user:\n";
                        User* user1 = selectUser();
                        if (!user1) break;

                        cout << "Select second user:\n";
                        User* user2 = selectUser();
                        if (!user2) break;

                        connectionManager.addConnection(user1->getUserId(), user2->getUserId());
                        cout << "Connection added successfully!\n";
                    } catch (const invalid_argument& e) {
                        cout << "Error: " << e.what() << "\n";
                    } catch (const runtime_error& e) {
                        cout << "Error: " << e.what() << "\n";
                    } catch (const exception& e) {
                        cout << "Unexpected error: " << e.what() << "\n";
                    }
                    break;
                }
                case 2: {
                    try {
                        cout << "Select first user:\n";
                        User* user1 = selectUser();
                        if (!user1) break;

                        cout << "Select second user:\n";
                        User* user2 = selectUser();
                        if (!user2) break;

                        connectionManager.removeConnection(user1->getUserId(), user2->getUserId());
                        cout << "Connection removed successfully!\n";
                    } catch (const invalid_argument& e) {
                        cout << "Error: " << e.what() << "\n";
                    } catch (const runtime_error& e) {
                        cout << "Error: " << e.what() << "\n";
                    } catch (const exception& e) {
                        cout << "Unexpected error: " << e.what() << "\n";
                    }
                    break;
                }
                case 3:
                    try {
                        connectionManager.displayConnections();
                    } catch (const exception& e) {
                        cout << "Error displaying connections: " << e.what() << "\n";
                    }
                    break;
                case 4: {
                    try {
                        User* user = selectUser();
                        if (user) {
                            vector<int> connections = connectionManager.getConnectionsByUser(user->getUserId());
                            cout << "Connections for " << user->getUserName() << ":\n";
                            if (connections.empty()) {
                                cout << "No connections found.\n";
                            } else {
                                for (int connId : connections) {
                                    User* connUser = userManager.getUserById(connId);
                                    if (connUser) {
                                        cout << "- " << connUser->getUserName() << " (ID: " << connId << ")\n";
                                    }
                                }
                            }
                        }
                    } catch (const invalid_argument& e) {
                        cout << "Error: " << e.what() << "\n";
                    } catch (const exception& e) {
                        cout << "Unexpected error: " << e.what() << "\n";
                    }
                    break;
                }
                case 5: {
                    try {
                        cout << "Select user to find mutual friend suggestions for:\n";
                        User* mainUser = selectUser();
                        if (!mainUser) break;

                        // Get friend suggestions using the new function
                        map<int,vector<int>> potentialFriends =
                            connectionManager.getPotentialFriendSuggestions(mainUser->getUserId());

                        // Display results
                        cout << "\nPotential Friend Suggestions for " << mainUser->getUserName() << ":\n";
                        if (potentialFriends.empty()) {
                            cout << "No friend suggestions found.\n";
                        } else {
                            for (const auto& suggestion : potentialFriends) {
                                User* suggestedUser = userManager.getUserById(suggestion.first);
                                if (suggestedUser) {
                                    cout << "\n- " << suggestedUser->getUserName()
                                         << " (ID: " << suggestion.first << ")\n";
                                    cout << "  Mutual friends with: ";

                                    // Show through which friends this connection is mutual
                                    bool first = true;
                                    for (int mutualFriendId : suggestion.second) {
                                        User* mutualFriend = userManager.getUserById(mutualFriendId);
                                        if (mutualFriend) {
                                            if (!first) cout << ", ";
                                            cout << mutualFriend->getUserName();
                                            first = false;
                                        }
                                    }
                                    cout << "\n";
                                }
                            }
                        }
                    } catch (const invalid_argument& e) {
                        cout << "Error: " << e.what() << "\n";
                    } catch (const exception& e) {
                        cout << "Unexpected error: " << e.what() << "\n";
                    }
                    break;
                }
                case 6:
                    return;
            }
        }
    }

    void postManagementMenu() {
        while (true) {
            displayHeader("Post Management");
            displayMenuOption("1", "Create New Post");
            displayMenuOption("2", "Remove Post");
            displayMenuOption("3", "View User's Posts");
            displayMenuOption("4", "Back to Main Menu");

            int choice = getIntInput("Enter your choice (1-4): ", 1, 4);

            switch (choice) {
                case 1: {
                    if (!currentUser) {
                        cout << "Please select a current user first.\n";
                        break;
                    }

                    string content = getStringInput("Enter post content: ");
                    string type = getStringInput("Enter post type: ");
                    int importance = getIntInput("Enter importance (1-10): ", 1, 10);

                    Post newPost(content, type, importance);

                    // Add tags
                    char addMoreTags;
                    do {
                        string tag = getStringInput("Enter a tag for the post: ");
                        newPost.addTag(tag);

                        cout << "Add another tag? (y/n): ";
                        cin >> addMoreTags;
                        clearInputBuffer();
                    } while (tolower(addMoreTags) == 'y');

                    currentUser->addPost(newPost);
                    cout << "Post added successfully!\n";
                    break;
                }
                case 2: {
                    User* user = currentUser ? currentUser : selectUser();
                    if (user) {
                        user->removePost();
                    }
                    break;
                }
                case 3: {
                    User* user = currentUser ? currentUser : selectUser();
                    if (user) {
                        user->displayPosts();
                    }
                    break;
                }
                case 4:
                    return;
            }
        }
    }

    void feedGenerationMenu() {
        while (true) {
            displayHeader("Feed Generation");
            displayMenuOption("1", "Generate Feed for Current User");
            displayMenuOption("2", "Generate Feed for Specific User");
            displayMenuOption("3", "Back to Main Menu");

            int choice = getIntInput("Enter your choice (1-3): ", 1, 3);

            switch (choice) {
                case 1: {
                    if (!currentUser) {
                        cout << "Please select a current user first.\n";
                        break;
                    }
                    auto feed = feedGenerator.generateFeed(currentUser->getUserId());
                    displayFeed(feed);
                    break;
                }
                case 2: {
                    User* user = selectUser();
                    if (user) {
                        auto feed = feedGenerator.generateFeed(user->getUserId());
                        displayFeed(feed);
                    }
                    break;
                }
                case 3:
                    return;
            }
        }
    }

    void fileOperationsMenu() {
        while (true) {
            displayHeader("File Operations");
            displayMenuOption("1", "Load Sample Users");
            displayMenuOption("2", "Load Sample Posts");
            displayMenuOption("3", "Load Sample Connections");
            displayMenuOption("4", "Back to Main Menu");

            int choice = getIntInput("Enter your choice (1-7): ", 1, 7);

            switch (choice) {
                case 1: {
                    fileHandler.loadSampleUsers("a");
                    break;
                }
                case 2: {
                    fileHandler.loadSamplePosts("a");
                    break;
                }
                case 3: {
                    fileHandler.loadSampleConnections("a");
                    break;
                }
                case 4:
                    return;
            }
        }
    }

    void userAnalyticsMenu() {
        while (true) {
            displayHeader("User Analytics");
            displayMenuOption("1", "View Most Active Users");
            displayMenuOption("2", "View Most Influential User");
            displayMenuOption("3", "View Number of Isolated Users");
            displayMenuOption("4", "Back to Main Menu");

            int choice = getIntInput("Enter your choice (1-4): ", 1, 4);

            switch (choice) {
                case 1: {
                    vector<User> activeUsers = userAnalytics.getMostActiveUsers();
                    cout << "\nMost Active Users (5+ posts):\n";
                    for ( auto& user : activeUsers) {
                        cout << "- " << user.getUserName()
                                << " (Posts: " << user.getPostCount() << ")\n";
                    }
                    break;
                }
                case 2: {
                    User influentialUser = userAnalytics.getInfluentialUser(connectionManager);
                    cout << "\nMost Influential User: " << influentialUser.getUserName() << "\n";
                    break;
                }
                case 3: {
                    int isolatedUsersCount = userAnalytics.getIsolatedUserCount(connectionManager);
                    cout << "\nNumber of Isolated Users: " << isolatedUsersCount << "\n";
                    break;
                }
                case 4:
                    return;
            }
        }
    }
};

int main() {
    SocialMediaApp app;
    app.run();
    return 0;
}