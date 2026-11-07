#include <cassert>
#include <iostream>
#include <memory>
#include <string>

class IPaymentStrategy {
public:
    virtual ~IPaymentStrategy() = default;
    virtual std::string pay(double amount) = 0;
};

class CreditCardStrategy : public IPaymentStrategy {
    std::string card_num_;
public:
    explicit CreditCardStrategy(std::string num) : card_num_(std::move(num)) {}
    std::string pay(double amount) override {
        return "CARD " + card_num_ + " PAID $" + std::to_string(amount);
    }
};

class PayPalStrategy : public IPaymentStrategy {
    std::string email_;
public:
    explicit PayPalStrategy(std::string email) : email_(std::move(email)) {}
    std::string pay(double amount) override {
        return "PAYPAL " + email_ + " PAID $" + std::to_string(amount);
    }
};

class CheckoutService {
    std::unique_ptr<IPaymentStrategy> strategy_;
public:
    void set_strategy(std::unique_ptr<IPaymentStrategy> s) { strategy_ = std::move(s); }
    std::string checkout(double amount) {
        if (!strategy_) return "NO_PAYMENT_METHOD";
        return strategy_->pay(amount);
    }
};

int main() {
    CheckoutService svc;
    svc.set_strategy(std::make_unique<CreditCardStrategy>("4111222233334444"));
    std::string r1 = svc.checkout(99.0);
    assert(r1.find("CARD 4111222233334444") != std::string::npos);

    svc.set_strategy(std::make_unique<PayPalStrategy>("buyer@example.com"));
    std::string r2 = svc.checkout(45.0);
    assert(r2.find("PAYPAL buyer@example.com") != std::string::npos);

    std::cout << "Strategy solution verified successfully!\n";
    return 0;
}
