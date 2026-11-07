#include <iostream>
#include <memory>
#include <string>

class IPaymentStrategy {
public:
    virtual ~IPaymentStrategy() = default;
    virtual bool pay(double amount) = 0;
};

// TODO: Implement CreditCardPayment, PayPalPayment, ShoppingCart

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
