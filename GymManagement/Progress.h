#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class Progress {
public:
    static void trackProgress(const std::string& username,
        double weight,
        double bmi,
        const std::string& achievement);
    static void viewProgress(const std::string& username);

private:
    static std::unordered_map<std::string, std::vector<std::string>> progressEntries;
};