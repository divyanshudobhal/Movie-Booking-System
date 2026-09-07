#ifndef SCREEN_CPP
#define SCREEN_CPP
#include <vector>
#include "Seat.cpp"
using namespace std;

// Composition: Screen creates/owns its physical Seat objects.
class Screen {
private:
    int screenNumber;
    vector<Seat> seats;

public:
    Screen() : screenNumber(0) {}

    explicit Screen(int screenNumber) {
        this->screenNumber = screenNumber;
    }

    void addSeat(const Seat& seat) { seats.push_back(seat); }
    vector<Seat>& getSeats() { return seats; }
    const vector<Seat>& getSeats() const { return seats; }
    int getScreenNumber() const { return screenNumber; }
};

#endif
