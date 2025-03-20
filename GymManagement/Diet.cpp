#include "Diet.h"
std::string Diet::suggestDiet(int calories) {
    return calories > 2000 ? "High Protein Diet" : "Low Carb Diet";
}