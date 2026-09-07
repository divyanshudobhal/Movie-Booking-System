#ifndef SHOW_CPP
#define SHOW_CPP
#include <vector>
#include <string>
#include <iostream>
#include "Movie.cpp"
#include "Screen.cpp"
#include "ShowSeat.cpp"
using namespace std;

// Aggregation: Show refers to an existing Movie and Screen.
// Composition: Show creates and owns one ShowSeat for every Screen seat.
class Show {
private:
    static int nextShowId;
    int showId;
    Movie* movie;
    Screen* screen;
    string startTime;
    vector<ShowSeat> showSeats;

public:
    Show() : showId(0), movie(nullptr), screen(nullptr) {}

    Show(Movie* movie, Screen* screen, string startTime) {
        this->showId = nextShowId++;
        this->movie = movie;
        this->screen = screen;
        this->startTime = startTime;

        if (screen != nullptr) {
            for (const Seat& seat : screen->getSeats()) {
                showSeats.emplace_back(seat);
            }
        }
    }

    int getShowId() const { return showId; }
    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    string getStartTime() const { return startTime; }

    ShowSeat* findShowSeat(int seatNumber) {
        for (ShowSeat& showSeat : showSeats) {
            if (showSeat.getSeatNumber() == seatNumber) {
                return &showSeat;
            }
        }
        return nullptr;
    }

    void displaySeats() const {
        cout << "\nSeat layout ([ ] = AVAILABLE, [X] = BOOKED)\n";
        for (const ShowSeat& showSeat : showSeats) {
            cout << "[" << (showSeat.isAvailable() ? ' ' : 'X') << "] "
                 << "Seat " << showSeat.getSeatNumber()
                 << " - " << seatTypeToString(showSeat.getSeatType()) << "\n";
        }
    }
};

int Show::nextShowId = 1;

#endif
