#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <vector>

class Member {
private:
    std::string name;
    int age;
    std::string membershipType;

public:
    Member(std::string n, int a, std::string m);
    void updateProfile();
    void viewDetails();
};

#endif
