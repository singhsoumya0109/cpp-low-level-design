// 03-real-world-example.cpp: Payment Gateway Adapter (Square vs Stripe)
#include <iostream>
#include <memory>

class IPaymentGateway {
public:
    virtual ~IPaymentGateway() = default;
    virtual void processPayment(double amount) const = 0;
};

class ThirdPartyStripeSDK {
public:
    void makeStripeCharge(double cents) const {
        std::cout << "Stripe charged: " << cents << " cents.\n";
    }
};

class StripeAdapter : public IPaymentGateway {
private:
    std::unique_ptr<ThirdPartyStripeSDK> sdk_;
public:
    explicit StripeAdapter(std::unique_ptr<ThirdPartyStripeSDK> sdk) : sdk_(std::move(sdk)) {}
    void processPayment(double amount) const override {
        sdk_->makeStripeCharge(amount * 100.0);
    }
};

int main() {
    std::unique_ptr<IPaymentGateway> pg = std::make_unique<StripeAdapter>(std::make_unique<ThirdPartyStripeSDK>());
    pg->processPayment(49.99);
    return 0;
}
