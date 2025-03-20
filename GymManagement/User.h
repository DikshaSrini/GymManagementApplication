#ifndef USER_H
#define USER_H
#include <string>
class User {
private:
    std::string username;
    std::string password;
public:
    User(std::string uname, std::string pass);
    bool authenticate(std::string uname, std::string pass);
};
#endif