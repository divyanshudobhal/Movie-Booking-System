#ifndef MAINMENU_CPP
#define MAINMENU_CPP
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>
#include "Cinema.cpp"
#include "Movie.cpp"
#include "Show.cpp"
#include "Customer.cpp"
#include "BookingService.cpp"
#include "PaymentType.cpp"
using namespace std;

// Association: MainMenu uses BookingService; neither owns the other.
// The menu is responsible only for console interaction and input validation.
class MainMenu {
private:
    Cinema cinema;
    vector<Movie> movies;
    vector<Show> shows;
    vector<unique_ptr<Customer>> customers;
    vector<unique_ptr<Booking>> bookings;
    BookingService bookingService;

    int readInt(const string& prompt) const {
        while (true) {
            cout << prompt;
            int value;
            if (cin >> value) {
                return value;
            }
            if (cin.eof()) {
                return 0;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
        }
    }

    string readText(const string& prompt) const {
        cout << prompt;
        string value;
        cin >> ws;
        getline(cin, value);
        return value;
    }

    void setupData() {
        cinema = Cinema("PVR Cineplex");

        Screen screen1(1);
        for (int seatNumber = 1; seatNumber <= 10; ++seatNumber) {
            SeatType type = SILVER;
            if (seatNumber <= 2) type = PLATINUM;
            else if (seatNumber <= 6) type = GOLD;
            screen1.addSeat(Seat(seatNumber, type));
        }
        cinema.addScreen(screen1);

        movies.emplace_back("Interstellar", "English", 169);
        movies.emplace_back("Dangal", "Hindi", 161);

        Screen* screen = cinema.findScreen(1);
        shows.emplace_back(&movies[0], screen, "6:00 PM");
        shows.emplace_back(&movies[1], screen, "9:00 PM");
    }

    void listMovies() const {
        cout << "\n--- Movies Currently Playing ---\n";
        for (size_t index = 0; index < movies.size(); ++index) {
            cout << "[" << index + 1 << "] "
                 << movies[index].getTitle() << " | "
                 << movies[index].getLanguage() << " | "
                 << movies[index].getDuration() << " min\n";
        }
    }

    void listShowsForMovie(const Movie* movie) const {
        cout << "\n--- Shows for " << movie->getTitle() << " ---\n";
        bool found = false;
        for (const Show& show : shows) {
            if (show.getMovie() == movie) {
                found = true;
                cout << "Show " << show.getShowId()
                     << " | Screen " << show.getScreen()->getScreenNumber()
                     << " | " << show.getStartTime() << "\n";
            }
        }
        if (!found) cout << "No shows available.\n";
    }

    Show* findShowById(int showId) {
        for (Show& show : shows) {
            if (show.getShowId() == showId) return &show;
        }
        return nullptr;
    }

    Booking* findBookingById(int bookingId) {
        for (auto& booking : bookings) {
            if (booking->getBookingId() == bookingId) return booking.get();
        }
        return nullptr;
    }

    Customer* createCustomer() {
        string name = readText("Enter customer name: ");
        if (name.empty()) {
            cout << "Customer name cannot be empty.\n";
            return nullptr;
        }

        string phone = readText("Enter customer phone: ");
        if (phone.empty()) {
            cout << "Customer phone cannot be empty.\n";
            return nullptr;
        }

        customers.push_back(make_unique<Customer>(name, phone));
        return customers.back().get();
    }

    unique_ptr<Payment> selectPayment() const {
        cout << "\nPayment method: 1.UPI  2.Card  3.Cash\n";
        int choice = readInt("Choose payment method: ");

        if (choice == UPI) {
            string upiId = readText("Enter UPI ID (use fail@upi for failure demo): ");
            if (upiId.empty()) {
                cout << "UPI ID cannot be empty.\n";
                return nullptr;
            }
            return createPayment(UPI, upiId);
        }

        if (choice == CARD) {
            string card = readText("Enter masked card (use FAIL for failure demo): ");
            if (card.empty()) {
                cout << "Card details cannot be empty.\n";
                return nullptr;
            }
            return createPayment(CARD, card);
        }

        if (choice == CASH) {
            return createPayment(CASH, "CASH");
        }

        cout << "Invalid payment method. Booking not started.\n";
        return nullptr;
    }

    // F1: list all movies currently playing.
    void handleListMovies() const {
        listMovies();
    }

    // F2: list shows (screen + start time) for a chosen movie.
    void handleListShows() const {
        listMovies();
        int movieChoice = readInt("Choose movie number: ");
        if (movieChoice < 1 || movieChoice > static_cast<int>(movies.size())) {
            cout << "Invalid movie selection.\n";
            return;
        }
        listShowsForMovie(&movies[movieChoice - 1]);
    }

    // F3: display AVAILABLE / BOOKED status for one show.
    void handleDisplaySeats() {
        int showId = readInt("Enter show ID: ");
        Show* show = findShowById(showId);
        if (show == nullptr) {
            cout << "Invalid show ID.\n";
            return;
        }

        cout << "\n" << show->getMovie()->getTitle()
             << " | Screen " << show->getScreen()->getScreenNumber()
             << " | " << show->getStartTime() << "\n";
        show->displaySeats();
    }

    // F4-F7: validate seats, calculate price, pay, confirm and print ticket.
    void handleBookSeats() {
        int showId = readInt("Enter show ID: ");
        Show* show = findShowById(showId);
        if (show == nullptr) {
            cout << "Invalid show ID.\n";
            return;
        }

        int seatCount = readInt("Enter number of seats to book: ");
        if (seatCount <= 0) {
            cout << "Number of seats must be at least 1.\n";
            return;
        }

        vector<int> seatNumbers;
        for (int index = 0; index < seatCount; ++index) {
            seatNumbers.push_back(readInt("Enter seat number " + to_string(index + 1) + ": "));
        }

        Customer* customer = createCustomer();
        if (customer == nullptr) return;

        unique_ptr<Payment> payment = selectPayment();
        if (payment == nullptr) return;

        unique_ptr<Booking> booking = bookingService.bookTicket(
            *show, customer, seatNumbers, move(payment));

        if (booking != nullptr) {
            cout << "Booking created with ID BK" << booking->getBookingId()
                 << " and status " << booking->getStatusString() << ".\n";
            bookings.push_back(move(booking));
        }
    }

    // F8: cancel a confirmed booking and release its seats.
    void handleCancelBooking() {
        int bookingId = readInt("Enter booking ID (without BK): ");
        Booking* booking = findBookingById(bookingId);
        if (booking == nullptr) {
            cout << "Booking not found.\n";
            return;
        }
        bookingService.cancelBooking(*booking);
    }

    void displayMenu() const {
        cout << "\n========== MOVIE TICKET BOOKING ==========\n";
        cout << "1. List Movies\n";
        cout << "2. List Shows for a Movie\n";
        cout << "3. Display Seats for a Show\n";
        cout << "4. Book Seats\n";
        cout << "5. Cancel Booking\n";
        cout << "0. Exit\n";
    }

public:
    MainMenu() {
        setupData();
    }

    void run() {
        bool running = true;
        while (running) {
            displayMenu();
            int choice = readInt("Choose: ");
            switch (choice) {
                case 1: handleListMovies(); break;
                case 2: handleListShows(); break;
                case 3: handleDisplaySeats(); break;
                case 4: handleBookSeats(); break;
                case 5: handleCancelBooking(); break;
                case 0: running = false; break;
                default: cout << "Invalid menu choice. Please try again.\n";
            }
        }
        cout << "Thank you for using the Movie Ticket Booking System.\n";
    }
};

#endif
