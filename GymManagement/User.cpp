#include "User.h"

std::string User::loggedInUsername = "";

std::unordered_map<std::string, std::pair<std::string, Role>> users = {
    {"admin", {"admin123", ADMIN}},
    {"trainer1", {"trainer123", TRAINER}},
    {"member1", {"member123", MEMBER}}
};

Role User::login() {
    std::string usernameInput, passwordInput;
    std::cout << "Enter Username: ";
    std::cin >> usernameInput;
    std::cout << "Enter Password: ";
    std::cin >> passwordInput;  

    if (users.count(usernameInput) && users[usernameInput].first == passwordInput) {
        std::cout << "Login Successful!\n";
        loggedInUsername = usernameInput;
        return users[usernameInput].second;
    }
    else {
        std::cout << "Invalid Credentials!\n";
        return NONE;
    }
}

std::string User::getUsername() {
    return loggedInUsername;
}
