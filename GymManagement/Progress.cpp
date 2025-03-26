#include "Progress.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Member.h"

void Member::saveProgress(const std::string& date, const std::string& progress) {
    std::string filename = username + "_progress.csv";
    std::ofstream outFile(filename, std::ios::app); // Open file in append mode

    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }

    outFile << date << "," << progress << "\n";
    outFile.close();
    std::cout << "Progress saved successfully!\n";
}

void Progress::trackProgress(const std::string& username, double weight, double bmi, const std::string& achievement) {
    std::ofstream outFile(username + "_progress.csv", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }

    outFile << weight << "," << bmi << "," << achievement << "\n";
    outFile.close();
    std::cout << "Progress tracked successfully!\n";
}

void Progress::viewProgress(const std::string& username) {
    std::ifstream inFile(username + "_progress.csv");
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file for reading.\n";
        return;
    }

    std::string line;
    std::cout << "\n===== PROGRESS =====\n";
    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        double weight, bmi;
        std::string achievement;
        ss >> weight;
        ss.ignore();
        ss >> bmi;
        ss.ignore();
        std::getline(ss, achievement, ',');

        std::cout << "Weight: " << weight << " kg\n";
        std::cout << "BMI: " << bmi << "\n";
        std::cout << "Achievement: " << achievement << "\n";
        std::cout << "------------------------\n";
    }

    inFile.close();
}