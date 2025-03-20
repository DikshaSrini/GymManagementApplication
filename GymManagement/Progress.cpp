#include "Progress.h"
#include <string>

std::string Progress::trackProgress(int weeks) {
    return "Tracking progress for " + std::to_string(weeks) + " weeks";
}