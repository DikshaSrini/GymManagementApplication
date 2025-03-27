#include "Statistics.h"
#include "BMI.h"
#include <iostream>
#include <map>

// Function to display statistics of gym members
void Statistics::displayStats(const std::vector<Member>& members) {
    int totalMembers = members.size(); // Get the total number of members
    std::map<std::string, int> bmiCategories = { // Initialize BMI categories
        {"Underweight", 0},
        {"Normal weight", 0},
        {"Overweight", 0},
        {"Obese", 0}
    };

    double totalBMI = 0; // Variable to store the sum of all BMIs
    int validCount = 0; // Counter for valid BMI entries

    std::cout << "\n===== GYM STATISTICS =====\n";
    std::cout << "Total Members: " << totalMembers << std::endl;

    // Iterate through each member to compute and categorize BMI
    for (const auto& member : members) {
        double bmi = BMI::computeBMI(member.getWeight(), member.getHeight()); // Compute BMI

        if (bmi > 0) {  // Check if BMI is valid
            totalBMI += bmi; // Add BMI to total
            validCount++; // Increment valid BMI count

            std::string category = BMI::categorizeBMI(bmi); // Categorize BMI
            bmiCategories[category]++; // Increment the corresponding category count
        }
    }

    // Calculate average BMI
    double avgBMI = (validCount > 0) ? (totalBMI / validCount) : 0;

    std::cout << "\nBMI Category Distribution:\n";
    // Display the distribution of BMI categories
    for (const auto& entry : bmiCategories) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }

    // Display the average BMI of all members
    std::cout << "\nAverage BMI of all members: " << avgBMI << std::endl;
    std::cout << "===========================\n";
}