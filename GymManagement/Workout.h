#pragma once

#include <string>
#include <vector>

class Workout {
public:
    static void generateWorkoutPlan(const std::string& username);
    static void viewWorkoutPlan(const std::string& username);
};

