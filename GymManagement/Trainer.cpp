#include "Trainer.h"
#include <string>

Trainer::Trainer(std::string n, std::string s) : name(n), specialty(s) {}

std::string Trainer::getSpecialty() { return specialty; }

void Trainer::assignWorkoutPlan() {
    std::string memberName, workout;
    std::cout << "Enter Member Name: ";
    std::cin >> memberName;
    std::cout << "Enter Workout Plan for " << memberName << ": ";
    std::cin.ignore();
    std::getline(std::cin, workout);

    memberWorkouts[memberName].push_back(workout);
    std::cout << "Workout Plan Assigned to " << memberName << " successfully!\n";
}

void Trainer::scheduleClass() {
    std::string date, time, topic;
    std::cout << "Enter Class Date (YYYY-MM-DD): ";
    std::cin >> date;
    std::cout << "Enter Class Time (HH:MM): ";
    std::cin >> time;
    std::cout << "Enter Class Topic: ";
    std::cin.ignore();
    std::getline(std::cin, topic);

    std::cout << "Class on '" << topic << "' scheduled on " << date << " at " << time << ".\n";
}

void Trainer::viewAssignedWorkouts() {
    std::cout << "Workout Plans Assigned:\n";
    for (const auto& entry : memberWorkouts) {
        std::cout << "Member: " << entry.first << "\nWorkouts:\n";
        for (const auto& workout : entry.second) {
            std::cout << "- " << workout << "\n";
        }
    }
}
