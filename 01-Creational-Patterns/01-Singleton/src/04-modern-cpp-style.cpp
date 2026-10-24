/**
 * @file 04-modern-cpp-style.cpp
 * @brief Modern C++ Style: std::call_once & Dependency-Injectable Singleton Interface.
 *
 * Solves the #1 interview critique against Singletons: "Singletons make code untestable!"
 * By introducing an abstract interface, clients can be unit-tested with Mock objects,
 * while production uses the real Singleton instance.
 */

#include <iostream>
#include <memory>
#include <mutex>
#include <string>

// 1. Abstract Interface
class IConfigurationService {
public:
    virtual ~IConfigurationService() = default;
    virtual std::string get(const std::string& key) const = 0;
};

// 2. Production Singleton implementing the interface
class ProductionConfig : public IConfigurationService {
private:
    std::string env_{"PRODUCTION"};

    ProductionConfig() = default;

public:
    static ProductionConfig& getInstance() {
        static std::unique_ptr<ProductionConfig> instance;
        static std::once_flag initFlag;

        // Using std::call_once for thread safety
        std::call_once(initFlag, []() {
            instance.reset(new ProductionConfig());
        });

        return *instance;
    }

    std::string get(const std::string& key) const override {
        if (key == "DB_HOST") return "db.prod.internal:5432";
        if (key == "ENV") return env_;
        return "UNKNOWN";
    }
};

// 3. Mock Configuration for Unit Testing (Zero Singleton coupling!)
class MockConfig : public IConfigurationService {
public:
    std::string get(const std::string& key) const override {
        if (key == "DB_HOST") return "localhost:5432_TEST";
        return "TEST_ENV";
    }
};

// 4. Client Service depends on the abstraction, NOT the concrete Singleton
class PaymentService {
private:
    const IConfigurationService& config_;

public:
    // Injects abstraction: can accept ProductionConfig::getInstance() OR MockConfig
    explicit PaymentService(const IConfigurationService& config) : config_(config) {}

    void process() {
        std::cout << "[PaymentService] Connecting to DB: " << config_.get("DB_HOST") << '\n';
    }
};

int main() {
    std::cout << "=== Modern Testable Singleton via Interface Injection ===\n";

    // In Unit Tests:
    std::cout << "--- In Unit Test Environment ---\n";
    MockConfig mockCfg;
    PaymentService testService(mockCfg);
    testService.process();

    // In Production:
    std::cout << "\n--- In Production Environment ---\n";
    PaymentService prodService(ProductionConfig::getInstance());
    prodService.process();

    return 0;
}

