#include <iostream>
#include <memory>
#include <string>

class IPaymentProcessor {
public:
    virtual ~IPaymentProcessor() = default;
    virtual bool pay(double amount_in_dollars) = 0;
};

class ThirdPartyJsonPayment {
public:
    bool sendPaymentJson(const std::string& json_payload) {
        return true;
    }
};

// TODO: Implement PaymentAdapter that converts dollars to JSON payload and calls ThirdPartyJsonPayment

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
