#include <iostream>
#include <memory>
#include <string>

// Abstract logging interface
class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void log(const std::string& message) = 0;
    virtual bool is_null() const noexcept { return false; }
};

// Real production logger
class ConsoleLogger : public ILogger {
public:
    void log(const std::string& message) override {
        std::cout << "[LOG]: " << message << "\n";
    }
};

// Null Object: safe no-op implementation
class NullLogger : public ILogger {
public:
    void log(const std::string&) override {
        // Deliberate no-op: eliminates nullptr checks across client code
    }
    bool is_null() const noexcept override { return true; }

    static std::shared_ptr<NullLogger> instance() {
        static auto instance = std::make_shared<NullLogger>();
        return instance;
    }
};

class PaymentGateway {
    std::shared_ptr<ILogger> logger_;
public:
    explicit PaymentGateway(std::shared_ptr<ILogger> logger = nullptr) {
        // Default to NullLogger if nullptr is supplied
        logger_ = logger ? logger : NullLogger::instance();
    }

    void process(double amount) {
        logger_->log("Processing payment of $" + std::to_string(amount));
        std::cout << "Payment processed: $" << amount << "\n";
        logger_->log("Payment complete.");
    }
};

int main() {
    std::cout << "=== Modern C++ Null Object Pattern Demo ===\n";
    std::cout << "1. With ConsoleLogger:\n";
    PaymentGateway gw1(std::make_shared<ConsoleLogger>());
    gw1.process(100.0);

    std::cout << "\n2. With NullLogger (no logging output, no null checks):\n";
    PaymentGateway gw2(nullptr);
    gw2.process(250.0);
    return 0;
}
