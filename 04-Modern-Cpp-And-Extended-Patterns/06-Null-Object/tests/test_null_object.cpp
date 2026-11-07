#include <cassert>
#include <iostream>
#include <memory>
#include <string>

class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void log(const std::string& m) = 0;
    virtual bool is_null() const noexcept = 0;
};

class NullLogger : public ILogger {
public:
    void log(const std::string&) override {}
    bool is_null() const noexcept override { return true; }
};

class RealLogger : public ILogger {
public:
    int log_count = 0;
    void log(const std::string&) override { ++log_count; }
    bool is_null() const noexcept override { return false; }
};

int main() {
    std::cout << "[TEST] Running Null Object tests...\n";

    NullLogger null_log;
    assert(null_log.is_null());
    null_log.log("Ignored message"); // Must not crash

    RealLogger real_log;
    assert(!real_log.is_null());
    real_log.log("Test message");
    assert(real_log.log_count == 1);

    std::cout << "[TEST] All Null Object tests PASSED!\n";
    return 0;
}
