#ifndef UPIPAYMENT_CPP
#define UPIPAYMENT_CPP
#include <iostream>
#include <string>
#include "Payment.cpp"
using namespace std;

// Inheritance + runtime polymorphism: UPI supplies its own pay() implementation.
class UpiPayment : public Payment {
private:
    string upiId;

public:
    explicit UpiPayment(string upiId) {
        this->upiId = upiId;
    }

    bool pay(double amount) override {
        cout << "Sending Rs." << amount << " via UPI (" << upiId << ") ...\n";
        // Demo rule: the special demo UPI ID forces a failure so the edge case
        // can be demonstrated reliably without random behaviour.
        if (upiId == "fail@upi") {
            cout << "UPI payment failed.\n";
            return false;
        }
        cout << "UPI payment successful.\n";
        return true;
    }

    string getMethodName() const override { return "UPI"; }
};

#endif
