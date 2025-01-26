
# Social Media Feed Generation Algorithm

## Project Overview

This project was developed as semester project for my Data Structures(DS) course.

It is a console based project. 

If you have added a GUI to this project, please drop a pull request.



## Features


- **User and Connection Management**: Users are assigned unique IDs, and their profiles and interests are managed. Users are stored in a hashmap with unique usernames. Connections between users are managed to drive feed content.
- **Content Relevance**: Posts are prioritized based on their relevance to user interests, connections, and engagement.
- **Real-Time Updates**: The system adapts and updates feeds dynamically based on user activities and interactions.
- **All-Interest Management**: Users can select and manage their interests, which are used to filter relevant posts.
- **Feed Generation**: A priority-based feed generation system ranks posts based on relevance and recency.
- **User Analytics**: Track and analyze user activity, identifying the most active users and top influencers.


## Functionality

- **User Management**: Handles user registration and updates, ensuring each user has a unique identifier and set of interests.
- **Feed Generation**: Generates personalized feeds by considering the user’s interests, connections, and interactions.
- **Connection Management**: Manages the relationships between users and dynamically updates the feed as new connections are made or removed.
- **Post Creation and Handling**: Users can create and manage posts that will be added to the feed based on their relevance.
- **User Analytics**: Provides insights into user activity and engagement, identifying influencers and key users.

## Data Structures Used

- **Doubly Linked List Template**: For storing and managing user interests and connections.
- **Hashmap (unordered_map)**: Used to manage user profiles, ensuring efficient lookup and management.
- **Priority Queue**: For ranking posts based on their relevance and engagement score.
- **Custom Linked List for post (PostLinkedList)**: Used to manage posts, ensuring quick addition and deletion operations.
- **Graph**: For representing and managing user connections, allowing efficient traversal and analysis of social networks.
- **Vector**: Used to store dynamic collections of data such as user interests, post data, and analytics, supporting efficient access and resizing.


## Code Explanation

The project is divided into several classes that handle different aspects of the social media feed system:

- **User Class**: Manages individual user profiles and their interests.
- **UserManager Class**: Handles registration and retrieval of users.
- **ConnectionManager Class**: Manages connections between users, influencing the feed generation.
- **FeedGenerator Class**: Creates personalized feeds by ranking posts based on relevance.
- **Post Management**: Organizes posts and ensures they are properly ranked and displayed in the feed.

## Tech Stack

- **Programming Language**: C++
- **IDE**: CLion, Visual Studio
- **Version Control**: Git, GitHub
- **Build System**: CMake

## How the Components Work Together

The components work together seamlessly:

1. **User Management**: The `UserManager` creates and manages user profiles stored in hashmaps, ensuring each user has a unique ID and interests.
2. **Connection Management**: `ConnectionManager` tracks user connections and feeds relevant content based on interactions.
3. **Feed Generation**: The `FeedGenerator` uses priority queues to rank posts and create personalized user feeds.
4. **Post Management**: Posts are created and managed via the `Post` and `PostLinkedList` classes to ensure they are accurately displayed in the feed.
5. **User Analytics**: The `UserAnalytics` class tracks activity trends and identifies top influencers.



## Credits

This project was developed in collaboration with:

- **Muhammad Abuzer Zia** [@abuzerexe](https://github.com/abuzerexe)
- **Muhammad Abdullah** [@taciturn2021](https://github.com/taciturn2021)
- **Muhammad Siraj** [@muhammadsirajdev](https://github.com/muhammadsirajdev)
- **Abdul Muizz** [a-muizz28](https://github.com/a-muizz28)
