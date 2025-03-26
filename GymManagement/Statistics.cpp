#include "Statistics.h"
#include "BMI.h"
#include <iostream>
#include <map>

void Statistics::displayStats(const std::vector<Member>& members) {
    int totalMembers = members.size();
    std::map<std::string, int> bmiCategories = {
        {"Underweight", 0},
        {"Normal weight", 0},
        {"Overweight", 0},
        {"Obese", 0}
    };

    double totalBMI = 0;
    int validCount = 0;

    std::cout << "\n===== GYM STATISTICS =====\n";
    std::cout << "Total Members: " << totalMembers << std::endl;

    for (const auto& member : members) {
        double bmi = BMI::computeBMI(member.getWeight(), member.getHeight());

        if (bmi > 0) {  
            totalBMI += bmi;
            validCount++;

            std::string category = BMI::categorizeBMI(bmi);
            bmiCategories[category]++;
        }
    }

    double avgBMI = (validCount > 0) ? (totalBMI / validCount) : 0;

    std::cout << "\nBMI Category Distribution:\n";
    for (const auto& entry : bmiCategories) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }

    std::cout << "\nAverage BMI of all members: " << avgBMI << std::endl;
    std::cout << "===========================\n";
}
