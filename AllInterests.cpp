#include "AllInterests.h"
#include <iostream>
using namespace std;


vector<string> allInterests = {
    // Technology and Programming
    "technology", "programming", "ai", "machine_learning", "blockchain",
    "cybersecurity", "vr", "ar", "cloud", "cryptocurrency",
    "web_development", "mobile_development", "data_science",

    // Creative and Arts
    "art", "photography", "digital_art", "design", "creativity",
    "music", "audio", "production", "writing", "literature",
    "poetry",

    // Health and Wellness
    "sports", "fitness", "nutrition", "health", "wellness",
    "meditation", "psychology", "coaching", "mental_health",

    // Entertainment and Media
    "gaming", "streaming", "esports", "video", "entertainment",

    // Professional Skills
    "business", "analytics", "leadership", "education", "tutorial",
    "development", "security", "networking",

    // Lifestyle
    "cooking", "food", "culture", "lifestyle", "events",

    // Science and Technology
    "science", "computing", "engineering", "electronics",

    // Other Categories
    "review", "portfolio", "collaboration", "news", "ethics"
};

void displayAllInterests() {
    cout << "Available Interests:\n";
    for (int i = 0; i < allInterests.size(); ++i) {
        cout << i + 1 << ". " << allInterests[i] << "\n";
    }
}