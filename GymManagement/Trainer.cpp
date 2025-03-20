#include "Trainer.h"
Trainer::Trainer(std::string n, std::string s) : name(n), specialty(s) {}
std::string Trainer::getSpecialty() { return specialty; }
