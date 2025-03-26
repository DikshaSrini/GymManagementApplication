#include "Trainer.h"
#include "string"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

// Create an unordered map to store trainers with their names as keys
std::unordered_map<std::string, Trainer> trainers;

// Constructor for the Trainer class
Trainer::Trainer(std::string name, std::string specialization)
    : name(name), specialization(specialization) {
}

// Function to view trainer details
void Trainer::viewDetails() {
    std::cout << "Trainer: " << name << " | Specialization: " << specialization << "\n";
}

// Function to update trainer details
void Trainer::updateDetails() {
    std::cout << "Enter new specialization: ";
    std::cin.ignore();
    std::getline(std::cin, specialization);
    std::cout << "Trainer details updated!\n";
}

// Function to add a new trainer
void Trainer::addTrainer() {
    std::string name, specialization;
    std::cout << "Enter Trainer Name: ";
    std::cin >> name;
    std::cout << "Enter Specialization: ";
    std::cin.ignore();
    std::getline(std::cin, specialization);

    // Add the new trainer to the map
    trainers[name] = Trainer(name, specialization);
    std::cout << "Trainer " << name << " added successfully!\n";
}

// Function to remove a trainer
void Trainer::removeTrainer() {
    std::string name;
    std::cout << "Enter Trainer Name to remove: ";
    std::cin >> name;

    // Remove the trainer from the map if found
    if (trainers.erase(name))
        std::cout << "Trainer " << name << " removed successfully!\n";
    else
        std::cout << "Trainer not found!\n";
}

// Function to assign a trainer to a member
void Trainer::assignTrainerToMember(std::string memberName) {
    std::string trainerName;
    std::cout << "Enter Trainer Name to assign to " << memberName << ": ";
    std::cin >> trainerName;

    // Check if the trainer exists in the map
    if (trainers.count(trainerName))
        std::cout << "Trainer " << trainerName << " assigned to Member " << memberName << "!\n";
    else
        std::cout << "Trainer not found!\n";
}

// Function to schedule a class
void Trainer::scheduleClass() {
    std::string date, time;
    std::cout << "Enter class date (YYYY-MM-DD): ";
    std::cin >> date;
    std::cout << "Enter class time (HH:MM): ";
    std::cin >> time;

    std::cout << "Class scheduled on " << date << " at " << time << " by Trainer " << name << ".\n";
}

void Trainer::viewMemberProgress(const std::string& memberUsername) const {
    std::string filename = memberUsername + "_progress.csv";
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for reading.\n";
        return;
    }

    std::string line;
    std::cout << "\n===== PROGRESS FOR " << memberUsername << " =====\n";
    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        std::string date, weight, description;
        std::getline(ss, date, ',');
        std::getline(ss, weight, ',');
        std::getline(ss, description, ',');

        std::cout << "Date: " << date << "\n";
        std::cout << "Weight: " << weight << " kg\n";
        std::cout << "Description: " << description << "\n";
        std::cout << "------------------------\n";
    }

    inFile.close();
    std::cout << "Debug: Finished reading progress for " << memberUsername << "\n";
}