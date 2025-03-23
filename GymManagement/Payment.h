#pragma once

#include <iostream>
#include <unordered_map>

class Payment {
public:
    static void makePayment(std::string memberName);
    static void viewPaymentStatus(std::string memberName);
};


