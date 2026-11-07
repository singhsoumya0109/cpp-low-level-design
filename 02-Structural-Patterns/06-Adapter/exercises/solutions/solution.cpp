#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>

class IPaymentProcessor {
public:
    virtual ~IPaymentProcessor() = default;
    virtual bool pay(double amount_in_dollars) = 0;
};

class ThirdPartyJsonPayment {
public:
    std::string last_payload;
    bool sendPaymentJson(const std::string& json_payload) {
        last_payload = json_payload;
        return true;
    }
};

class PaymentAdapter : public IPaymentProcessor {
public:
    explicit PaymentAdapter(std::shared_ptr<ThirdPartyJsonPayment> adaptee)
        : adaptee_(std::move(adaptee)) {}

    bool pay(double amount_in_dollars) override {
        std::ostringstream ss;
        ss << "{\"amount\":" << amount_in_dollars << ",\"currency\":\"USD\"}";
        return adaptee_->sendPaymentJson(ss.str());
    }

private:
    std::shared_ptr<ThirdPartyJsonPayment> adaptee_;
};

int main() {
    auto third_party = std::make_shared<ThirdPartyJsonPayment>();
    auto adapter = std::make_unique<PaymentAdapter>(third_party);

    bool result = adapter->pay(49.99);
    assert(result == true);
    assert(third_party->last_payload == "{\"amount\":49.99,\"currency\":\"USD\"}");

    std::cout << "Adapter solution verified successfully!\n";
    return 0;
}
