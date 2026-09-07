#ifndef CASHPAYMENT_CPP
#define CASHPAYMENT_CPP
#include <iostream>
#include "Payment.cpp"
using namespace std;

// Inheritance + runtime polymorphism: Cash supplies its own pay() implementation.
class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "Collecting cash of Rs." << amount << " ...\n";
        cout << "Cash received. Payment successful.\n";
        return true;
    }

    string getMethodName() const override { return "CASH"; }
};

#endif
