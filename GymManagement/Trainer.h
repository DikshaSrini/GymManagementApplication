#ifndef TRAINER_H
#define TRAINER_H
#include <string>
class Trainer {
private:
    std::string name;
    std::string specialty;
public:
    Trainer(std::string name, std::string specialty);
    std::string getSpecialty();
};
#endif