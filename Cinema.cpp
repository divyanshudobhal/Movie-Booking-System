#ifndef CINEMA_CPP
#define CINEMA_CPP
#include <vector>
#include <string>
#include "Screen.cpp"
using namespace std;

// Composition: Cinema owns its Screen objects.
class Cinema {
private:
    string name;
    vector<Screen> screens;

public:
    Cinema() {}

    explicit Cinema(string name) {
        this->name = name;
    }

    void addScreen(const Screen& screen) { screens.push_back(screen); }

    vector<Screen>& getScreens() { return screens; }
    const vector<Screen>& getScreens() const { return screens; }

    string getName() const { return name; }

    Screen* findScreen(int screenNumber) {
        for (Screen& screen : screens) {
            if (screen.getScreenNumber() == screenNumber) {
                return &screen;
            }
        }
        return nullptr;
    }
};

#endif
