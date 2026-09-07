#ifndef TICKETPRINTER_CPP
#define TICKETPRINTER_CPP
#include <iomanip>
#include <iostream>
#include "Booking.cpp"
#include "Show.cpp"
using namespace std;

// Single Responsibility: this class formats and prints tickets only.
class TicketPrinter {
public:
    void printTicket(const Booking& booking, const Show& show) const {
        cout << "\n================ TICKET ================\n";
        cout << "Booking ID : BK" << booking.getBookingId() << "\n";
        cout << "Customer   : " << booking.getCustomer()->getName() << "\n";
        cout << "Movie      : " << show.getMovie()->getTitle() << "\n";
        cout << "Screen     : " << show.getScreen()->getScreenNumber() << "\n";
        cout << "Time       : " << show.getStartTime() << "\n";
        cout << "Seats      : ";
        for (ShowSeat* seat : booking.getSeats()) {
            cout << seat->getSeatNumber() << " ";
        }
        cout << "\n";
        cout << "Amount     : Rs." << fixed << setprecision(2)
             << booking.getTotalAmount() << "\n";
        cout << "Payment    : " << booking.getPayment()->getMethodName() << "\n";
        cout << "Status     : " << booking.getStatusString() << "\n";
        cout << "=========================================\n";
    }
};

#endif
