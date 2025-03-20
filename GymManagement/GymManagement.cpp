#include <iostream>
#include "User.h"
#include "Member.h"
#include "Trainer.h"
#include "BMI.h"

void memberMenu(std::string username);
void trainerMenu(std::string username);
void adminMenu();

int main() {
    Role userRole = User::login();  // ? Call static login()

    if (userRole == ADMIN) adminMenu();
    else if (userRole == TRAINER) trainerMenu(User::getUsername());  // ? Use User::getUsername()
    else if (userRole == MEMBER) memberMenu(User::getUsername());    // ? Use User::getUsername()
    else std::cout << "Exiting...\n";

    return 0;
}

void memberMenu(std::string username) {
    Member member(username, 22, "Gold");
    int choice;
    do {
        std::cout << "\nMember Menu:\n1. View Profile\n2. Update Profile\n3. Calculate BMI\n4. Exit\nChoice: ";
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
    } while (choice != 4);
}

void trainerMenu(std::string username) {
    Trainer trainer(username, "Strength Training");
    int choice;
    do {
        std::cout << "\nTrainer Menu:\n1. Assign Workout Plan\n2. Schedule Class\n3. Exit\nChoice: ";
        std::cin >> choice;

        if (choice == 1) trainer.assignWorkoutPlan();
        else if (choice == 2) trainer.scheduleClass();
    } while (choice != 3);
}

void adminMenu() {
    int choice;
    do {
        std::cout << "\nAdmin Menu:\n1. Add Member\n2. Remove Trainer\n3. View Stats\n4. Exit\nChoice: ";
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
            std::cout << "Trainer " << trainerName << " has been removed.\n";
        }
        else if (choice == 3) {
            std::cout << "Displaying Gym Statistics...\n";
            // Implement detailed stats display
        }
    } while (choice != 4);
}
