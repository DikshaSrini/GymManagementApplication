#include "Progress.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

std::unordered_map<std::string, std::vector<std::string>> Progress::progressEntries;

void Progress::trackProgress(const std::string& username, double weight, double bmi, const std::string& achievement)
{
    // Get current timestamp
    std::time_t now = std::time(nullptr);
    std::tm tm;
    localtime_s(&tm, &now);
    std::stringstream timestamp;
    timestamp << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");

    // Create a formatted progress entry
    std::stringstream entry;
    entry << "Timestamp: " << timestamp.str()
        << " | Weight: " << weight << " kg"
        << " | BMI: " << bmi
        << " | Achievement: " << achievement;

    // Store the entry for the specific username
    progressEntries[username].push_back(entry.str());

    std::cout << "Progress tracked successfully!\n";
}

void Progress::viewProgress(const std::string& username) {
    // Check if the user has any progress entries
    auto it = progressEntries.find(username);
    if (it == progressEntries.end() || it->second.empty()) {
        std::cout << "No progress entries found for " << username << ".\n";
        return;
    }

    // Display progress entries for the username
    std::cout << "\n--- Progress Tracking for " << username << " ---\n";
    for (const auto& entry : it->second) {
        std::cout << entry << "\n";
    }
}