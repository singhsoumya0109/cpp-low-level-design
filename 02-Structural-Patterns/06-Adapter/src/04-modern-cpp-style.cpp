// 04-modern-cpp-style.cpp: Functional Adapter using std::function & lambdas
#include <functional>
#include <iostream>

using ModernPaymentFn = std::function<void(double)>;

class ExternalPaymentAPI {
public:
    void executeExternalTxn(long millicents) const {
        std::cout << "External API transaction: " << millicents << "\n";
    }
};

int main() {
    ExternalPaymentAPI api;
    // Functional adapter without extra classes
    ModernPaymentFn pay = [&api](double amount) {
        api.executeExternalTxn(static_cast<long>(amount * 100000));
    };

    pay(12.50);
    return 0;
}
