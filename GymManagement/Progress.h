#pragma once

#include <string>
#include <vector>

class Progress {
public:
    static void trackProgress(const std::string& username, double weight, double bmi, const std::string& achievement);
    static void viewProgress(const std::string& username);
};
