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

int main() {
    std::cout << "***** Welcome to Synergy *****\n\n";

    std::string username;
    std::cout << "Enter Username (or 'new' to register): ";
    std::cin >> username;

    User user;
    Role userRole;

    if (username == "new") {
        // Call the registration function
        user.registerUser();
        // After registration, prompt for login
        userRole = user.login();
    }
    else {
        // Check if user exists
        if (userExists(username)) {
            std::cout << "Welcome back, " << username << "!\n";
            // Set the username and prompt for password
            std::cout << "Enter Password: ";
            std::string password;
            std::cin >> password;

            // Verify credentials
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

// The original menu functions remain unchanged
void memberMenu(std::string username) {
    Member member(username, 22, "Gold");
    int choice;
    do {
        std::cout << "\nMember Menu:\n1. View Profile\n2. Update Profile\n3. Calculate BMI\n4. View Workout Plan\n5. Make Payment\n6. View Payment Status\n7. Exit\nChoice: ";
        std::cin >> choice;

        if (choice == 1) member.viewDetails();
        else if (choice == 2) member.updateProfile();
        else if (choice == 3) {
            double weight, height;
            std::cout << "Enter weight (kg): "; std::cin >> weight;
            std::cout << "Enter height (m): "; std::cin >> height;
            double bmi = BMI::computeBMI(weight, height);
            std::cout << "Your BMI: " << bmi << "\nCategory: " << BMI::categorizeBMI(bmi)
                << "\nHealth Tip: " << BMI::getHealthTips(bmi) << "\n";
        }
        else if (choice == 4) Workout::viewWorkoutPlan(username);
        else if (choice == 5) Payment::makePayment(username);
        else if (choice == 6) Payment::viewPaymentStatus(username);
    } while (choice != 7);
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
            std::cout << "Enter Membership Type (Gold/Silver/Bronze): "; std::cin >> membership;
            Member newMember(name, age, membership);
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

// Helper function to check if a user exists in the CSV file
bool userExists(const std::string& username) {
    std::ifstream file("users.csv");
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    // Skip header
    std::getline(file, line);

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