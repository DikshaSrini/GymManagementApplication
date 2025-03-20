#include "User.h"
User::User(std::string uname, std::string pass) : username(uname), password(pass) {}
bool User::authenticate(std::string uname, std::string pass) {
    return username == uname && password == pass;
}