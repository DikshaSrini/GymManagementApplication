#ifndef USER_H
#define USER_H

#include <iostream>
#include <unordered_map>
#include <string>

enum Role { NONE, ADMIN, TRAINER, MEMBER };

class User {
private:
    static std::string loggedInUsername;
public:
    static Role login();
    static std::string getUsername();
};

#endif
