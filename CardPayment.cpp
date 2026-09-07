#ifndef CARDPAYMENT_CPP
#define CARDPAYMENT_CPP
#include <iostream>
#include <string>
#include "Payment.cpp"
using namespace std;

// Inheritance + runtime polymorphism: Card supplies its own pay() implementation.
class CardPayment : public Payment {
private:
    string maskedCardNumber;

public:
    explicit CardPayment(string maskedCardNumber) {
        this->maskedCardNumber = maskedCardNumber;
    }

    bool pay(double amount) override {
        cout << "Charging Rs." << amount << " to card " << maskedCardNumber << " ...\n";
        if (maskedCardNumber == "FAIL") {
            cout << "Card payment declined.\n";
            return false;
        }
        cout << "Card payment approved.\n";
        return true;
    }

    string getMethodName() const override { return "CARD"; }
};

#endif
