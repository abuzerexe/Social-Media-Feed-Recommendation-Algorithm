#include "UserManager.h"
#include <iostream>

std::unordered_map<string, int> UserManager::userByUserName;
std::unordered_map<int, User> UserManager::userById;

bool UserManager::addUser(User& user){

    if (userExistsByUsername(user.getUserName()))
    {
        cout << "\nError: Username "<< user.getUserName() <<" already exists. Please choose a different username. \n";
        return false;
    }

    
   userById[user.getUserId()] = user;
   userByUserName[user.getUserName()] = user.getUserId();


    return true;
}

bool UserManager::removeUser(int userId){

    auto it = userById.find(userId);

    if ( it != userById.end())
    {

        string username = it->second.getUserName();

        userByUserName.erase(username);

        userById.erase(userId);

        cout << "User removed successfully. "<< endl;
        return true;

    }else{

        cout << "No User with such id exists. "<< endl;
        return false;
    }
    
}

User* UserManager::getUserById(int userId){

    auto it = userById.find(userId) ;

    if ( it != userById.end())
    {
        // cout << "User exists. "<< endl;
        return &it->second;
    }else{
        // cout<< "User with id "<< userId << " does not exist. "<< endl;
        return nullptr;
    }
    
}

User* UserManager::getUserByUsername(string username){
    auto it = userByUserName.find(username);

    if ( it != userByUserName.end())
    {
        // cout << "User exists. "<< endl;
        int id = it->second;
        // return &userById.find(id)->second; OR
        return getUserById(id);
    }else{

        return nullptr;
    }
    
}

void UserManager::listAllUsers(){

    if (userById.empty())
    {
        cout << "All Users: \n" << endl;
        return;
    }



    for (auto &pair : userById)
    {
        pair.second.displayUserDetails();
    }

}

bool UserManager::userExistsByUsername(string username){
    return userByUserName.find(username) != userByUserName.end();
}