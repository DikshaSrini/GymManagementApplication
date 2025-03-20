#include <iostream>
#include "User.h"
#include "Trainer.h"
#include "BMI.h"
#include "Workout.h"
#include "Diet.h"
#include "Class.h"
#include "Payment.h"
#include "Progress.h"
#include "Notification.h"

int main() {
    // User authentication
    User user("Diksha", "diksha");
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    if (user.authenticate(username, password)) {
        std::cout << "Login successful!\n";
    }
    else {
        std::cout << "Invalid credentials!\n";
        return 1;
    }

    // Trainer details
    Trainer trainer("Alice", "Strength Training");
    std::cout << "Trainer Specialty: " << trainer.getSpecialty() << "\n";

    // BMI calculation
    double weight, height;
    std::cout << "Enter weight (kg): ";
    std::cin >> weight;
    std::cout << "Enter height (m): ";
    std::cin >> height;
    std::cout << "Your BMI: " << BMI::computeBMI(weight, height) << "\n";

    // Workout plan
    int level;
    std::cout << "Enter workout level (1 for beginner, 2 for advanced): ";
    std::cin >> level;
    std::cout << "Workout Plan: " << Workout::getWorkoutPlan(level) << "\n";

    // Diet suggestion
    int calories;
    std::cout << "Enter daily calorie intake: ";
    std::cin >> calories;
    std::cout << "Diet Suggestion: " << Diet::suggestDiet(calories) << "\n";

    // Class scheduling
    std::string date;
    std::cout << "Enter class date (YYYY-MM-DD): ";
    std::cin >> date;
    std::cout << Class::scheduleClass(date) << "\n";

    // Payment processing
    double amount;
    std::cout << "Enter payment amount: ";
    std::cin >> amount;
    if (Payment::processPayment(amount)) {
        std::cout << "Payment successful!\n";
    }
    else {
        std::cout << "Payment failed!\n";
    }

    // Progress tracking
    int weeks;
    std::cout << "Enter number of weeks for progress tracking: ";
    std::cin >> weeks;
    std::cout << Progress::trackProgress(weeks) << "\n";

    // Sending notification
    std::string message;
    std::cout << "Enter reminder message: ";
    std::cin.ignore();
    std::getline(std::cin, message);
    std::cout << Notification::sendReminder(message) << "\n";

    return 0;
}
