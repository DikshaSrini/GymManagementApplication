#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector> 
#include <ctime>

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
    std::string startDate;
    std::string endDate;

    std::string getCurrentDate();
    std::string calculateEndDate(const std::string& startDate);

    void saveMemberDetails();

public:
    Member(std::string uname, std::string pwd, std::string r, std::string n, int a,
        std::string g, double h, double w, std::string dp, std::string al, std::string mType);

    void setMembershipType(const std::string& mType);
    std::string getMembershipType() const;

    void setStartDate(const std::string& start);
    std::string getStartDate() const;

    void setEndDate(const std::string& end);
    std::string getEndDate() const;

    // Add these getters
    double getHeight() const { return height; }
    double getWeight() const { return weight; }

    void updateProfile();
    void viewDetails();

    static std::vector<Member> loadAllMembers();
};

#endif