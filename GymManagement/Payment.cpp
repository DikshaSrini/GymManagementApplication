#include "Payment.h"

// Create an unordered map to store payment status with member names as keys
std::unordered_map<std::string, bool> payments;

// Function to make a payment for a member
void Payment::makePayment(std::string memberName) {
    std::cout << memberName << " is making a membership payment...\n";
    // Mark the payment as successful in the map
    payments[memberName] = true;
    std::cout << "Payment successful!\n";
}

// Function to view the payment status of a member
void Payment::viewPaymentStatus(std::string memberName) {
    // Check if the member has made a payment and has an active membership
    if (payments.count(memberName) && payments[memberName])
        std::cout << memberName << " has an active membership.\n";
    else
        std::cout << memberName << " has NOT made a membership payment!\n";
}