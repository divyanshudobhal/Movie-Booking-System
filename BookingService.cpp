#ifndef BOOKINGSERVICE_CPP
#define BOOKINGSERVICE_CPP
#include <iostream>
#include <memory>
#include <set>
#include <vector>
#include "Show.cpp"
#include "Customer.cpp"
#include "Payment.cpp"
#include "Booking.cpp"
#include "PriceCalculator.cpp"
#include "TicketPrinter.cpp"
using namespace std;

// Dependency Inversion: BookingService depends on abstract Payment, not UPI/Card/Cash.
// Single Responsibility: it orchestrates the booking use case.
class BookingService {
private:
    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;

    bool validateSeatSelection(Show& show, const vector<int>& seatNumbers,
                               vector<ShowSeat*>& selectedSeats) const {
        if (seatNumbers.empty()) {
            cout << "No seats selected. Booking rejected.\n";
            return false;
        }

        set<int> uniqueSeatNumbers;
        for (int seatNumber : seatNumbers) {
            if (!uniqueSeatNumbers.insert(seatNumber).second) {
                cout << "Seat " << seatNumber
                     << " was selected more than once. Booking rejected.\n";
                return false;
            }

            ShowSeat* seat = show.findShowSeat(seatNumber);
            if (seat == nullptr) {
                cout << "Seat " << seatNumber
                     << " does not exist. Booking rejected.\n";
                return false;
            }

            if (!seat->isAvailable()) {
                cout << "Seat " << seatNumber
                     << " is already BOOKED. Booking rejected.\n";
                return false;
            }

            selectedSeats.push_back(seat);
        }
        return true;
    }

    void releaseSeats(const vector<ShowSeat*>& seats) const {
        for (ShowSeat* seat : seats) {
            seat->releaseSeat();
        }
    }

public:
    unique_ptr<Booking> bookTicket(Show& show, Customer* customer,
                                   const vector<int>& seatNumbers,
                                   unique_ptr<Payment> payment) {
        vector<ShowSeat*> selectedSeats;
        if (!validateSeatSelection(show, seatNumbers, selectedSeats)) {
            return nullptr;
        }

        for (ShowSeat* seat : selectedSeats) {
            seat->bookSeat();
        }

        double total = priceCalculator.calculateTotal(selectedSeats);
        bool isPaid = payment != nullptr && payment->pay(total);

        if (!isPaid) {
            releaseSeats(selectedSeats);
            auto failedBooking = make_unique<Booking>(customer, selectedSeats,
                                                      move(payment), total);
            failedBooking->fail();
            cout << "Booking BK" << failedBooking->getBookingId()
                 << " FAILED. Seats released.\n";
            return failedBooking;
        }

        auto booking = make_unique<Booking>(customer, selectedSeats,
                                            move(payment), total);
        booking->confirm();
        ticketPrinter.printTicket(*booking, show);
        return booking;
    }

    void cancelBooking(Booking& booking) const {
        if (booking.getStatus() != CONFIRMED) {
            cout << "Only CONFIRMED bookings can be cancelled.\n";
            return;
        }

        booking.cancel();
        cout << "Booking BK" << booking.getBookingId()
             << " CANCELLED. Seats released.\n";
    }
};

#endif
