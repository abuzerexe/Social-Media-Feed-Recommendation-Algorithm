#include "AllInterests.h"
#include <iostream>
using namespace std;


vector<string> allInterests = {
    "Technology", "Music", "Sports", "Gaming", "Travel", 
    "Cooking", "Fitness", "Art", "Books", "Movies",
    "Science", "Education", "Photography", "Fashion", 
    "Nature", "Programming", "Entrepreneurship", "Politics"
};

void displayAllInterests() {
    cout << "Available Interests:\n";
    for (int i = 0; i < allInterests.size(); ++i) {
        cout << i + 1 << ". " << allInterests[i] << "\n";
    }
}
