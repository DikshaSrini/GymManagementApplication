#include "Workout.h"
#include "string"

// Create an unordered map to store workout plans with member names as keys
std::unordered_map<std::string, std::vector<std::string>> workoutPlans;

// Function to assign a workout plan to a member
void Workout::assignWorkoutPlan(std::string memberName) {
    std::string plan;
    std::cout << "Enter workout plan for " << memberName << ": ";
    std::cin.ignore();
    std::getline(std::cin, plan);

    // Add the workout plan to the member's list of plans
    workoutPlans[memberName].push_back(plan);
    std::cout << "Workout plan added for " << memberName << "!\n";
}

// Function to view the workout plan of a member
void Workout::viewWorkoutPlan(std::string memberName) {
    // Check if the member has any workout plans
    if (workoutPlans.count(memberName)) {
        std::cout << memberName << "'s Workout Plan:\n";
        // Print each workout plan for the member
        for (const auto& plan : workoutPlans[memberName])
            std::cout << "- " << plan << "\n";
    }
    else {
        std::cout << "No workout plan found for " << memberName << "!\n";
    }
}