#include <iostream>
#include "User.h"
#include "Member.h"
#include "Trainer.h"
#include "BMI.h"
#include "Workout.h"
#include "Payment.h"

void memberMenu(std::string username);
void trainerMenu(std::string username);
void adminMenu();

int main() {
    User user;
    Role userRole = user.login();

    if (userRole == ADMIN) adminMenu();
    else if (userRole == TRAINER) trainerMenu(user.getUsername());
    else if (userRole == MEMBER) memberMenu(user.getUsername());
    else std::cout << "Exiting...\n";

    return 0;
}

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
