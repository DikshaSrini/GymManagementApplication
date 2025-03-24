#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "User.h"
#include "Member.h"
#include "Trainer.h"
#include "BMI.h"
#include "Workout.h"
#include "Payment.h"

void memberMenu(std::string username);
void trainerMenu(std::string username);
void adminMenu();
bool userExists(const std::string& username);
std::string selectMembershipType();

int main() {
    std::cout << "***** Welcome to SynerGym *****\n\n";

    std::string username;
    std::cout << "Enter Username (or 'new' to register): ";
    std::cin >> username;

    User user;
    Role userRole;

    if (username == "new") {
        user.registerUser();
        userRole = user.login();
    }
    else {
        if (userExists(username)) {
            std::cout << "Welcome back, " << username << "!\n";
            std::cout << "Enter Password: ";
            std::string password;
            std::cin >> password;

            if (user.verifyCredentials(username, password)) {
                std::cout << "Login Successful!\n";
                userRole = user.getUserRole(username);
            }
            else {
                std::cout << "Invalid Credentials!\n";
                userRole = NONE;
            }
        }
        else {
            std::cout << "Username not found. Would you like to register? (y/n): ";
            char choice;
            std::cin >> choice;

            if (choice == 'y' || choice == 'Y') {
                user.registerUser();
                userRole = user.login();
            }
            else {
                std::cout << "Exiting...\n";
                return 0;
            }
        }
    }

    if (userRole == ADMIN) adminMenu();
    else if (userRole == TRAINER) trainerMenu(user.getUsername());
    else if (userRole == MEMBER) memberMenu(user.getUsername());
    else std::cout << "Exiting...\n";

    return 0;
}

// Updated member menu function with membership type selection
void memberMenu(std::string username) {
    // Create member object with full attributes
    Member member(username, "password123", "MEMBER", username, 22, "Female", 1.65, 55.0, "Vegetarian", "Active", "Bronze");

    int choice;
    do {
        std::cout << "\nMember Menu:\n";
        std::cout << "1. Set/Change Membership Type\n";
        std::cout << "2. View Profile\n";
        std::cout << "3. Update Profile\n";
        std::cout << "4. Calculate BMI\n";
        std::cout << "5. View Workout Plan\n";
        std::cout << "6. Make Payment\n";
        std::cout << "7. View Payment Status\n";
        std::cout << "8. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string newMembership = selectMembershipType();
            member.setMembershipType(newMembership);
            std::cout << "Membership type updated to " << newMembership << "!\n";
        }
        else if (choice == 2) member.viewDetails();
        else if (choice == 3) member.updateProfile();
        else if (choice == 4) {
            double weight, height;
            std::cout << "Enter weight (kg): "; std::cin >> weight;
            std::cout << "Enter height (m): "; std::cin >> height;
            double bmi = BMI::computeBMI(weight, height);
            std::cout << "Your BMI: " << bmi << "\nCategory: " << BMI::categorizeBMI(bmi)
                << "\nHealth Tip: " << BMI::getHealthTips(bmi) << "\n";
        }
        else if (choice == 5) Workout::viewWorkoutPlan(username);
        else if (choice == 6) Payment::makePayment(username);
        else if (choice == 7) Payment::viewPaymentStatus(username);
    } while (choice != 8);
}

// Function to handle membership type selection
std::string selectMembershipType() {
    int choice;
    std::string membershipType;

    std::cout << "\nSelect Membership Type:\n";
    std::cout << "1. Bronze (Basic access to gym facilities)\n";
    std::cout << "2. Silver (Bronze + access to group classes)\n";
    std::cout << "3. Gold (Silver + personal trainer sessions)\n";
    std::cout << "4. Platinum (Gold + nutrition counseling and spa access)\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
    case 1: membershipType = "Bronze"; break;
    case 2: membershipType = "Silver"; break;
    case 3: membershipType = "Gold"; break;
    case 4: membershipType = "Platinum"; break;
    default:
        std::cout << "Invalid choice! Setting to Bronze by default.\n";
        membershipType = "Bronze";
    }

    return membershipType;
}

void trainerMenu(std::string username) {
    Trainer trainer(username, "Strength Training");
    int choice;
    do {
        std::cout << "\nTrainer Menu:\n1. Assign Workout Plan\n2. Schedule Class\n3. Exit\nChoice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string memberName;
            std::cout << "Enter Member Name: ";
            std::cin >> memberName;
            Workout::assignWorkoutPlan(memberName);
        }
        else if (choice == 2) trainer.scheduleClass();
    } while (choice != 3);
}

void adminMenu() {
    int choice;
    do {
        std::cout << "\nAdmin Menu:\n1. Add Member\n2. Remove Trainer\n3. Assign Trainer to Member\n4. View Stats\n5. Exit\nChoice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string name, membership;
            int age;
            std::cout << "Enter Member Name: "; std::cin >> name;
            std::cout << "Enter Age: "; std::cin >> age;

            std::cout << "Select membership type for new member:\n";
            membership = selectMembershipType();

            // Create new member with full attributes
            Member newMember(name, "defaultPass", "MEMBER", name, age, "Unspecified", 0.0, 0.0, "None", "Sedentary", membership);
            std::cout << "New Member Added!\n";
        }
        else if (choice == 2) {
            std::string trainerName;
            std::cout << "Enter Trainer Name to Remove: "; std::cin >> trainerName;
            Trainer::removeTrainer();
        }
        else if (choice == 3) {
            std::string memberName;
            std::cout << "Enter Member Name: ";
            std::cin >> memberName;
            Trainer::assignTrainerToMember(memberName);
        }
        else if (choice == 4) {
            std::cout << "Displaying Gym Statistics...\n";
        }
    } while (choice != 5);
}

bool userExists(const std::string& username) {
    std::ifstream file("users.csv");
    if (!file.is_open()) return false;

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string user;
        std::getline(ss, user, ',');

        if (user == username) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}