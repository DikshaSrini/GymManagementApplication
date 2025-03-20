#ifndef BMI_H
#define BMI_H
#include <string>
class BMI {
public:
    static double computeBMI(double weight, double height);
    static std::string categorizeBMI(double bmi);
    static std::string getHealthTips(double bmi);
};
#endif

#include "BMI.h"
#include <string>

double BMI::computeBMI(double weight, double height) {
    if (weight <= 0 || height <= 0) return -1;
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
