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
