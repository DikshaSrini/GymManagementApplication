#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

class Workout {
public:
    static void assignWorkoutPlan(std::string memberName);
    static void viewWorkoutPlan(std::string memberName);
};

extern std::unordered_map<std::string, std::vector<std::string>> workoutPlans;

