#ifndef MOVIE_CPP
#define MOVIE_CPP
#include <string>
using namespace std;

// Encapsulation: movie data is private and exposed only through getters.
class Movie {
private:
    string title;
    string language;
    int durationMinutes;

public:
    Movie() : durationMinutes(0) {}

    Movie(string title, string language, int durationMinutes) {
        this->title = title;
        this->language = language;
        this->durationMinutes = durationMinutes;
    }

    string getTitle() const { return title; }
    string getLanguage() const { return language; }
    int getDuration() const { return durationMinutes; }
};

#endif
