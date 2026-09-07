#ifndef BOOKING_CPP
#define BOOKING_CPP
#include <memory>
#include <string>
#include <vector>
#include "Customer.cpp"
#include "ShowSeat.cpp"
#include "Payment.cpp"
using namespace std;

enum BookingStatus { PENDING, CONFIRMED, FAILED, CANCELLED };

string bookingStatusToString(BookingStatus status) {
    switch (status) {
        case PENDING: return "PENDING";
        case CONFIRMED: return "CONFIRMED";
        case FAILED: return "FAILED";
        default: return "CANCELLED";
    }
}

// Single Responsibility: Booking stores booking state and controls its status.
class Booking {
private:
    static int nextBookingId;
    int bookingId;
    Customer* customer;                 // Association: customer exists independently.
    vector<ShowSeat*> seats;            // Aggregation: Show owns the actual ShowSeats.
    unique_ptr<Payment> payment;        // Composition: payment belongs to this booking.
    double totalAmount;
    BookingStatus status;

public:
    Booking(Customer* customer, vector<ShowSeat*> seats,
            unique_ptr<Payment> payment, double totalAmount)
        : bookingId(nextBookingId++),
          customer(customer),
          seats(seats),
          payment(move(payment)),
          totalAmount(totalAmount),
          status(PENDING) {}

    // Compile-time polymorphism: overloaded constructor with no-payment form.
    Booking(Customer* customer, vector<ShowSeat*> seats, double totalAmount)
        : bookingId(nextBookingId++),
          customer(customer),
          seats(seats),
          payment(nullptr),
          totalAmount(totalAmount),
          status(PENDING) {}

    void confirm() { status = CONFIRMED; }
    void fail() { status = FAILED; }

    void cancel() {
        if (status != CONFIRMED) return;
        for (ShowSeat* seat : seats) {
            seat->releaseSeat();
        }
        status = CANCELLED;
    }

    int getBookingId() const { return bookingId; }
    Customer* getCustomer() const { return customer; }
    const vector<ShowSeat*>& getSeats() const { return seats; }
    Payment* getPayment() const { return payment.get(); }
    double getTotalAmount() const { return totalAmount; }
    BookingStatus getStatus() const { return status; }
    string getStatusString() const { return bookingStatusToString(status); }
};

int Booking::nextBookingId = 1001;

#endif
