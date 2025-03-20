#include "Workout.h"
std::string Workout::getWorkoutPlan(int level) {
    return level == 1 ? "Beginner Plan" : "Advanced Plan";
}