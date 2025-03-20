#ifndef TRAINER_H
#define TRAINER_H

#include <iostream>
#include <vector>
#include <unordered_map>

class Trainer {
private:
    std::string name;
    std::string specialty;
    std::unordered_map<std::string, std::vector<std::string>> memberWorkouts;  // Stores workout plans per member

public:
    Trainer(std::string n, std::string s);

    std::string getSpecialty();
    void assignWorkoutPlan();
    void scheduleClass();
    void viewAssignedWorkouts();
};

#endif
