#pragma once

#include <iostream>
#include <unordered_map>

class Trainer {
    std::string name, specialization;
public:
    Trainer() {} 
    Trainer(std::string name, std::string specialization);

    void viewDetails();
    void updateDetails();
    static void addTrainer();
    static void removeTrainer();
    static void assignTrainerToMember(std::string memberName);
    void scheduleClass();
};


