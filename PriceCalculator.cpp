#ifndef PRICECALCULATOR_CPP
#define PRICECALCULATOR_CPP
#include <vector>
#include "ShowSeat.cpp"
using namespace std;

// Single Responsibility: this class performs only booking price calculation.
class PriceCalculator {
private:
    static constexpr double SILVER_PRICE = 150.0;
    static constexpr double GOLD_PRICE = 250.0;
    static constexpr double PLATINUM_PRICE = 400.0;

public:
    double priceForSeatType(SeatType type) const {
        if (type == SILVER) return SILVER_PRICE;
        if (type == GOLD) return GOLD_PRICE;
        return PLATINUM_PRICE;
    }

    double calculateTotal(const vector<ShowSeat*>& seats) const {
        double total = 0.0;
        for (ShowSeat* seat : seats) {
            total += priceForSeatType(seat->getSeatType());
        }
        return total;
    }
};

#endif
