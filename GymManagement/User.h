#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

enum Role { NONE, ADMIN, TRAINER, MEMBER };

class User {
private:
    static std::string loggedInUsername;

public:
    Role login();
    void registerUser();
    bool verifyCredentials(const std::string& username, const std::string& password);
    Role getUserRole(const std::string& username);
    static std::string getUsername();
};

