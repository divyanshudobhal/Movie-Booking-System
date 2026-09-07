#ifndef PAYMENT_CPP
#define PAYMENT_CPP
#include <string>
using namespace std;

// Abstraction: Payment defines the contract, not the implementation.
// Interface Segregation: only operations required by the assignment are exposed.
class Payment {
public:
    virtual bool pay(double amount) = 0;
    virtual string getMethodName() const = 0;
    virtual ~Payment() {}
};

#endif
