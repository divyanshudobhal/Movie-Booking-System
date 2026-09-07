#ifndef SHOWSEAT_CPP
#define SHOWSEAT_CPP
#include "Seat.cpp"

enum SeatStatus { AVAILABLE, BOOKED };

// Encapsulation: status can change only through bookSeat()/releaseSeat().
class ShowSeat {
private:
    Seat seat;
    SeatStatus status;

public:
    ShowSeat() : status(AVAILABLE) {}

    explicit ShowSeat(const Seat& seat) {
        this->seat = seat;
        this->status = AVAILABLE;
    }

    bool isAvailable() const { return status == AVAILABLE; }
    bool isBooked() const { return status == BOOKED; }

    bool bookSeat() {
        if (isBooked()) {
            return false;
        }
        status = BOOKED;
        return true;
    }

    void releaseSeat() { status = AVAILABLE; }

    int getSeatNumber() const { return seat.getSeatNumber(); }
    SeatType getSeatType() const { return seat.getType(); }
};

#endif
