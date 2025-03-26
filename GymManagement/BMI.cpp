#include "BMI.h"
#include <iostream>

double BMI::computeBMI(double weight, double height) {
    std::cout << "Calculating BMI: Weight = " << weight << ", Height = " << height << std::endl;

    if (weight <= 0 || height <= 0) {
        std::cout << "[ERROR] Invalid BMI inputs detected!\n";
        return -1; // Return -1 for invalid cases
    }
    return weight / (height * height);
}

std::string BMI::categorizeBMI(double bmi) {
    if (bmi < 18.5) return "Underweight";
    else if (bmi < 24.9) return "Normal weight";
    else if (bmi < 29.9) return "Overweight";
    else return "Obese";
}

std::string BMI::getHealthTips(double bmi) {
    if (bmi < 18.5) return "Increase calorie intake with healthy foods.";
    else if (bmi < 24.9) return "Maintain a balanced diet and regular exercise.";
    else if (bmi < 29.9) return "Incorporate more physical activity and reduce sugar intake.";
    else return "Consult a professional for a structured weight loss plan.";
}
