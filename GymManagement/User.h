#ifndef USER_H
#define USER_H

#include <iostream>
#include <unordered_map>

enum Role { NONE, ADMIN, TRAINER, MEMBER };

class User {
private:
    static std::string loggedInUsername;  // Store logged-in user's name

public:
    static Role login();  // Static function for authentication
    static std::string getUsername();  // Returns the logged-in username
};

#endif
