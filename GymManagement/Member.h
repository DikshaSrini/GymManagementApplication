#ifndef MEMBER_H
#define MEMBER_H

#include <string>

class Member {
private:
    std::string username;
    std::string password;
    std::string role;
    std::string name;
    int age;
    std::string gender;
    double height;
    double weight;
    std::string dietPreference;
    std::string activityLevel;
    std::string membershipType;

    void loadMemberDetails();
    void saveMemberDetails();

public:
    Member(std::string uname, std::string pwd, std::string r, std::string n, int a,
        std::string g, double h, double w, std::string dp, std::string al, std::string mType);

    void setMembershipType(const std::string& mType);  // Move this to public
    std::string getMembershipType() const;  // Getter function

    void updateProfile();
    void viewDetails();
};

#endif
