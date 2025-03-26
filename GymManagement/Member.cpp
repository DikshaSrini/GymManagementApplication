#include "Member.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

// Constructor
Member::Member(std::string uname, std::string pwd, std::string r, std::string n, int a,
    std::string g, double h, double w, std::string dp, std::string al, std::string mType)
    : username(uname), password(pwd), role(r), name(n), age(a),
    gender(g), height(h), weight(w), dietPreference(dp),
    activityLevel(al), membershipType(mType) {
}

void Member::setMembershipType(const std::string& mType) {
    membershipType = mType;
}

std::string Member::getMembershipType() const {
    return membershipType;
}

// Save member details to CSV
void Member::saveMemberDetails() {
    std::vector<std::string> allMembers;
    bool memberFound = false;
    std::string header;

    std::ifstream inFile("users.csv");
    if (inFile.is_open()) {
        std::getline(inFile, header);
        std::string line;

        while (std::getline(inFile, line)) {
            std::istringstream ss(line);
            std::string uname;
            std::getline(ss, uname, ',');

            if (uname == username) {
                memberFound = true;
            }
            else {
                allMembers.push_back(line);
            }
        }
        inFile.close();
    }
    else {
        header = "Username,Password,Role,Name,Age,Gender,Height,Weight,DietPreference,ActivityLevel";
    }

    std::string updatedMember = username + "," +
        password + "," +
        role + "," +
        name + "," +
        std::to_string(age) + "," +
        gender + "," +
        std::to_string(height) + "," +
        std::to_string(weight) + "," +
        dietPreference + "," +
        activityLevel;

    std::ofstream outFile("users.csv");
    if (!outFile.is_open()) {
        std::cout << "Error: Could not open file for writing.\n";
        return;
    }

    outFile << header << std::endl;
    for (const std::string& member : allMembers) {
        outFile << member << std::endl;
    }
    outFile << updatedMember << std::endl;

    outFile.close();
    std::cout << "Profile saved successfully!\n";
}

// Update profile (Only editable fields)
void Member::updateProfile() {
    int choice;
    bool continueUpdating = true;

    while (continueUpdating) {
        std::cout << "\nUpdate Profile Menu:\n";
        std::cout << "1. Update Age\n";
        std::cout << "2. Update Height (m)\n";
        std::cout << "3. Update Weight (kg)\n";
        std::cout << "4. Update Diet Preference\n";
        std::cout << "5. Update Activity Level\n";
        std::cout << "6. Save and Return\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            std::cout << "Enter new age: ";
            std::cin >> age;
            break;
        case 2:
            std::cout << "Enter new height (m): ";
            std::cin >> height;
            break;
        case 3:
            std::cout << "Enter new weight (kg): ";
            std::cin >> weight;
            break;
        case 4:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            std::cout << "Enter new diet preference: ";
            std::getline(std::cin, dietPreference);
            std::cout << "DEBUG: Diet preference updated to: " << dietPreference << std::endl; // Debugging
            break;

        case 5:
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            std::cout << "Enter new activity level: ";
            std::getline(std::cin, activityLevel);
            std::cout << "DEBUG: Activity level updated to: " << activityLevel << std::endl; // Debugging
            break;

        case 6:
            continueUpdating = false;
            saveMemberDetails();
            break;
        default:
            std::cout << "Invalid choice! Try again.\n";
        }
    }
}

// View profile (Read-only)
void Member::viewDetails() {
    loadAllMembers();

    std::cout << "\n===== MEMBER DETAILS =====" << std::endl;
    std::cout << "Username: " << username << std::endl;
    std::cout << "Password: " << password << std::endl; 
    std::cout << "Role: " << role << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Gender: " << gender << std::endl;
    std::cout << "Height: " << (height > 0 ? std::to_string(height) + " m" : "Not set") << std::endl;
    std::cout << "Weight: " << (weight > 0 ? std::to_string(weight) + " kg" : "Not set") << std::endl;
    std::cout << "Diet Preference: " << (dietPreference.empty() ? "Not set" : dietPreference) << std::endl;
    std::cout << "Activity Level: " << (activityLevel.empty() ? "Not set" : activityLevel) << std::endl;
    std::cout << "=========================" << std::endl;
}

std::vector<Member> Member::loadAllMembers() {
    std::vector<Member> members;
    std::ifstream file("users.csv");

    if (!file.is_open()) {
        std::cerr << "Error: Could not open users.csv\n";
        return members;
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string username, password, role, name, gender, dietPreference, activityLevel, membershipType;
        int age;
        double height, weight;

        std::getline(ss, username, ',');
        std::getline(ss, password, ',');
        std::getline(ss, role, ',');
        std::getline(ss, name, ',');
        ss >> age;
        ss.ignore();
        std::getline(ss, gender, ',');
        ss >> height;
        ss.ignore();
        ss >> weight;
        ss.ignore();
        std::getline(ss, dietPreference, ',');
        std::getline(ss, activityLevel, ',');
        std::getline(ss, membershipType, ',');

        // Validate data
        if (username.empty() || password.empty() || role.empty() || name.empty() || age <= 0 || height <= 0 || weight <= 0) {
            std::cerr << "Invalid data found in CSV file. Skipping entry.\n";
            continue;
        }

        members.emplace_back(username, password, role, name, age, gender, height, weight, dietPreference, activityLevel, membershipType);
    }

    file.close();
    return members;
}



