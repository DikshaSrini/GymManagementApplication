#include "Member.h"

Member::Member(std::string n, int a, std::string m) : name(n), age(a), membershipType(m) {}

void Member::updateProfile() {
    std::cout << "Enter new membership type: ";
    std::cin >> membershipType;
    std::cout << "Profile Updated!\n";
}

void Member::viewDetails() {
    std::cout << "Name: " << name << "\nAge: " << age << "\nMembership: " << membershipType << "\n";
}
