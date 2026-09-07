#ifndef PAYMENTTYPE_CPP
#define PAYMENTTYPE_CPP
#include <memory>
#include <string>
#include "UpiPayment.cpp"
#include "CardPayment.cpp"
#include "CashPayment.cpp"
using namespace std;

enum PaymentMethod { UPI = 1, CARD = 2, CASH = 3 };

// Factory responsibility is isolated here; BookingService depends only on Payment.
unique_ptr<Payment> createPayment(PaymentMethod method, const string& paymentData) {
    if (method == UPI) {
        return make_unique<UpiPayment>(paymentData);
    }
    if (method == CARD) {
        return make_unique<CardPayment>(paymentData);
    }
    return make_unique<CashPayment>();
}

#endif
