#include "Workout.h"
#include "Member.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Trainer.h"

// Function to generate a workout plan for a specific user
void Workout::generateWorkoutPlan(const std::string& username) {
    // Read user details from users.csv
    std::ifstream inFile("users.csv");
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open users.csv for reading.\n";
        return;
    }

    std::string line;
    std::getline(inFile, line); // Skip header

    std::string dietPreference, activityLevel;
    bool userFound = false;
    Member member("", "", "", "", 0, "", 0.0, 0.0, "", "", "");

    // Read each line from the file to find the user
    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        std::string uname, password, role, name, gender, membershipType, startDate, endDate;
        int age;
        double height, weight;

        std::getline(ss, uname, ',');
        std::getline(ss, password, ',');
        std::getline(ss, role, ',');
        std::getline(ss, name, ',');
        ss >> age;
        ss.ignore();
        std::getline(ss, gender, ',');
        ss >> height;
        ss.ignore();
        ss >> weight;
        ss.ignore();
        std::getline(ss, dietPreference, ',');
        std::getline(ss, activityLevel, ',');
        std::getline(ss, membershipType, ',');
        std::getline(ss, startDate, ',');
        std::getline(ss, endDate, ',');

        // Check if the current line matches the username
        if (uname == username) {
            userFound = true;
            member = Member(uname, password, role, name, age, gender, height, weight, dietPreference, activityLevel, membershipType);
            member.setStartDate(startDate);
            member.setEndDate(endDate);
            break;
        }
    }

    inFile.close();

    if (!userFound) {
        std::cerr << "Error: User not found in users.csv.\n";
        return;
    }

    // Generate workout plan based on diet preference and activity level
    std::vector<std::string> exercises;
    std::vector<int> sets;
    std::vector<int> reps;
    std::vector<std::string> descriptions;

    // Define workout plans based on activity level
    if (activityLevel == "Sedentary") {
        exercises = { "Walking", "Stretching" };
        sets = { 1, 1 };
        reps = { 30, 10 };
        descriptions = {
            "Walk at a moderate pace for 30 minutes.",
            "Perform stretching exercises for 10 minutes."
        };
    }
    else if (activityLevel == "Lightly Active") {
        exercises = { "Push-ups", "Squats", "Plank" };
        sets = { 2, 2, 2 };
        reps = { 10, 15, 30 };
        descriptions = {
            "Perform push-ups with proper form.",
            "Perform squats with proper form.",
            "Hold plank position for 30 seconds."
        };
    }
    else if (activityLevel == "Moderately Active") {
        exercises = { "Push-ups", "Squats", "Plank", "Lunges" };
        sets = { 3, 3, 3, 3 };
        reps = { 15, 20, 60, 15 };
        descriptions = {
            "Perform push-ups with proper form.",
            "Perform squats with proper form.",
            "Hold plank position for 60 seconds.",
            "Perform lunges with proper form."
        };
    }
    else if (activityLevel == "Very Active") {
        exercises = { "Running", "Burpees", "Deadlifts", "Pull-ups" };
        sets = { 3, 3, 3, 3 };
        reps = { 20, 15, 10, 10 };
        descriptions = {
            "Run at a fast pace for 20 minutes.",
            "Perform burpees with proper form.",
            "Perform deadlifts with proper form.",
            "Perform pull-ups with proper form."
        };
    }
    else if (activityLevel == "Super Active") {
        exercises = { "Sprints", "Clean and Jerk", "Snatch", "Muscle-ups" };
        sets = { 4, 4, 4, 4 };
        reps = { 25, 10, 10, 10 };
        descriptions = {
            "Perform sprints with maximum effort.",
            "Perform clean and jerk with proper form.",
            "Perform snatch with proper form.",
            "Perform muscle-ups with proper form."
        };
    }

    // Write the workout plan to a CSV file
    std::ofstream outFile(username + "_workout.csv");
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }

    outFile << "Exercise,Sets,Reps,Description\n";
    for (size_t i = 0; i < exercises.size(); ++i) {
        outFile << exercises[i] << "," << sets[i] << "," << reps[i] << "," << descriptions[i] << "\n";
    }

    outFile.close();
    std::cout << "Workout plan generated successfully!\n";

    // Set workoutAssigned flag and save member details
    member.setWorkoutAssigned(true);
    member.saveMemberDetails();
}

// Function to view the workout plan for a specific user
void Workout::viewWorkoutPlan(const std::string& username) {
    std::string filename = username + "_workout.csv";
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        std::cerr << "Workout plan has not been assigned yet.\n";
        return;
    }

    std::string line;
    std::getline(inFile, line); // Skip header

    std::cout << "\n===== WORKOUT PLAN =====\n";
    // Read and display each line of the workout plan
    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        std::string exercise, sets, reps, description;
        std::getline(ss, exercise, ',');
        std::getline(ss, sets, ',');
        std::getline(ss, reps, ',');
        std::getline(ss, description, ',');

        std::cout << "Exercise: " << exercise << "\n";
        std::cout << "Sets: " << sets << "\n";
        std::cout << "Reps: " << reps << "\n";
        std::cout << "Description: " << description << "\n";
        std::cout << "------------------------\n";
    }

    inFile.close();
    Trainer trainer;
    trainer.scheduleClass();
}