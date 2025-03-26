#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <conio.h>
#include <unordered_map>
#include "User.h"
#include "Member.h"
#include "Statistics.h"
#include "Trainer.h"
#include "BMI.h"
#include "Workout.h"
#include "Payment.h"
#include "Progress.h"

void memberMenu(std::string username);
void trainerMenu(std::string username);
bool userExists(const std::string& username);
std::string selectMembershipType();
void adminMenu(std::vector<Member>& members);

std::string getHiddenPassword() {
    std::string password;
    char ch;

    while ((ch = _getch()) != '\r') { // Stop when Enter (Carriage Return) is pressed
        if (ch == '\b') { // Handle backspace
            if (!password.empty()) {
                std::cout << "\b \b";
                password.pop_back();
            }
        }
        else {
            password.push_back(ch);
            std::cout << '*'; // Show * instead of actual characters
        }
    }
    std::cout << std::endl;
    return password;
}

int main() {

    std::vector<Member> members;  // Declare members list

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
        if (username == "admin") {
            std::cout << "Enter Password: ";
            std::string password = getHiddenPassword();;
            if (password == "adminPass") {
                std::cout << "Welcome back, Admin!\n";
                userRole = ADMIN;
            }
            else {
                std::cout << "Invalid Credentials!\n";
                userRole = NONE;
            }
        }
        else if (username == "trainer") {
            std::cout << "Enter Password: ";
            std::string password = getHiddenPassword();
            if (password == "trainerPass") {
                std::cout << "Welcome back, Trainer!\n";
                userRole = TRAINER;
            }
            else {
                std::cout << "Invalid Credentials!\n";
                userRole = NONE;
            }
        }
        else if (userExists(username)) {
            std::cout << "Welcome back, " << username << "!\n";
            std::cout << "Enter Password: ";
            std::string password = getHiddenPassword();

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


    if (userRole == ADMIN) adminMenu(members);
    else if (userRole == TRAINER) trainerMenu(user.getUsername());
    else if (userRole == MEMBER) memberMenu(user.getUsername());
    else std::cout << "Exiting...\n";

    return 0;
}

// Updated member menu function with membership type selection
void memberMenu(std::string username) {
    // Create member object with full attributes
    Member member(username, "diksha", "MEMBER", username, 22, "Female", 1.65, 55.0, "Vegetarian", "Lightly Active", "Bronze");

    int choice;
    do {
        std::cout << "\nMember Menu:\n";
        std::cout << "1. Set/Change Membership Type\n";
        std::cout << "2. View Profile\n";
        std::cout << "3. Update Profile\n";
        std::cout << "4. Calculate BMI\n";
        std::cout << "5. View Workout Plan\n";
        std::cout << "6. Make Payment\n";
        std::cout << "7. View Membership Status\n";
        std::cout << "8. Track Progress\n";
        std::cout << "9. View Progress\n";
        std::cout << "10. Exit\n";
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
            // Fetch stored height and weight
            double weight = member.getWeight();
            double height = member.getHeight();

            if (height > 0 && weight > 0) {
                double bmi = BMI::computeBMI(weight, height);
                std::cout << "Your BMI: " << bmi << "\nCategory: " << BMI::categorizeBMI(bmi)
                    << "\nHealth Tip: " << BMI::getHealthTips(bmi) << "\n";

                // Track progress
                Progress::trackProgress(username, weight, bmi, "BMI calculated");
            }
            else {
                std::cout << "Height or weight information is missing. Please update your profile.\n";
            }
        }
        else if (choice == 5) {
            if (member.isWorkoutAssigned()) {
                Workout::viewWorkoutPlan(username); // Check if workout plan has been assigned
            }
            else {
                std::cout << "Workout plan has not been assigned yet.\n";
            }
        }
        else if (choice == 6) Payment::makePayment(username);
        else if (choice == 7) {
            std::cout << "Membership Start Date: " << member.getStartDate() << "\n";
            std::cout << "Membership End Date: " << member.getEndDate() << "\n";
        }
        else if (choice == 8) {
   
            double weight, bmi;
            std::string achievement;

            std::cout << "Enter current weight (kg): ";
            std::cin >> weight;

            std::cout << "Enter current BMI: ";
            std::cin >> bmi;

            std::cout << "Enter an achievement or note about your progress: ";
            std::cin.ignore(); // Clear input buffer
            std::getline(std::cin, achievement);

            // Track the progress
            Progress::trackProgress(username, weight, bmi, achievement);
        }
        else if (choice == 9) Progress::viewProgress(username);
    } while (choice != 10);
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
            Workout::generateWorkoutPlan(memberName);
            std::cout << "Workout plan assigned to " << memberName << " successfully!\n";
        }
        else if (choice == 2) trainer.scheduleClass();
    } while (choice != 3);
}

void adminMenu(std::vector<Member>& members) {
    int choice;
    do {
        std::cout << "\nAdmin Menu:\n1. Add Member\n2. View Stats\n3. Exit\nChoice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string name, membership;
            int age;
            double height, weight;

            std::cout << "Enter Member Name: "; std::cin >> name;
            std::cout << "Enter Age: "; std::cin >> age;
            std::cout << "Enter Height (m): "; std::cin >> height;
            std::cout << "Enter Weight (kg): "; std::cin >> weight;

            std::cout << "Select membership type for new member:\n";
            membership = selectMembershipType();

            Member newMember(name, "defaultPass", "MEMBER", name, age, "Unspecified", height, weight, "None", "Sedentary", membership);
            members.push_back(newMember);
        }
        else if (choice == 2) {
            std::vector<Member> members = Member::loadAllMembers();  
            Statistics::displayStats(members);
        }
    } while (choice != 3);
}

bool userExists(const std::string& username) {
    std::ifstream file("users.csv");
    if (!file.is_open()) return false;

    std::string line;
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