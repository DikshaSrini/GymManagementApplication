#include "BMI.h"
#include <iostream>

// Function to compute BMI based on weight and height
double BMI::computeBMI(double weight, double height) {
    // Output to show the input values
    std::cout << "Calculating BMI: Weight = " << weight << ", Height = " << height << std::endl;

    // Check for invalid input values
    if (weight <= 0 || height <= 0) {
        std::cout << "[ERROR] Invalid BMI inputs detected!\n";
        return -1; // Return -1 for invalid cases
    }
    // Calculate and return BMI
    return weight / (height * height);
}

// Function to categorize BMI into different weight categories
std::string BMI::categorizeBMI(double bmi) {
    if (bmi < 18.5) return "Underweight";
    else if (bmi < 24.9) return "Normal weight";
    else if (bmi < 29.9) return "Overweight";
    else return "Obese";
}

// Function to provide health tips based on BMI category
std::string BMI::getHealthTips(double bmi) {
    if (bmi < 18.5) return "Increase calorie intake with healthy foods.";
    else if (bmi < 24.9) return "Maintain a balanced diet and regular exercise.";
    else if (bmi < 29.9) return "Incorporate more physical activity and reduce sugar intake.";
    else return "Consult a professional for a structured weight loss plan.";
}