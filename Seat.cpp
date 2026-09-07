#ifndef SEAT_CPP
#define SEAT_CPP
#include <string>
using namespace std;

enum SeatType { SILVER, GOLD, PLATINUM };

string seatTypeToString(SeatType type) {
    switch (type) {
        case SILVER: return "SILVER";
        case GOLD: return "GOLD";
        default: return "PLATINUM";
    }
}

// Encapsulation: a Seat only stores the identity/type of one physical seat.
class Seat {
private:
    int seatNumber;
    SeatType type;

public:
    Seat() : seatNumber(0), type(SILVER) {}

    Seat(int seatNumber, SeatType type) {
        this->seatNumber = seatNumber;
        this->type = type;
    }

    int getSeatNumber() const { return seatNumber; }
    SeatType getType() const { return type; }
};

#endif
