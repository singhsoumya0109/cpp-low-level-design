/**
 * @file test_singleton.cpp
 * @brief Unit tests for Singleton pattern ensuring thread safety and unique identity.
 */

#include <cassert>
#include <iostream>
#include <thread>
#include <vector>

class TestService {
private:
    int counter_{0};
    TestService() = default;

public:
    TestService(const TestService&) = delete;
    TestService& operator=(const TestService&) = delete;

    static TestService& getInstance() {
        static TestService instance;
        return instance;
    }

    void increment() { ++counter_; }
    int getCounter() const { return counter_; }
};

int main() {
    std::cout << "[TEST] Running Singleton Tests...\n";

    // Test 1: Identity Check
    TestService& s1 = TestService::getInstance();
    TestService& s2 = TestService::getInstance();
    assert(&s1 == &s2 && "Singleton instances must share the exact same memory address!");
    std::cout << "  ✓ Test 1 Passed: Single memory identity verified.\n";

    // Test 2: Multithreaded Concurrency Check
    constexpr int NUM_THREADS = 50;
    std::vector<std::thread> workers;
    std::vector<TestService*> recordedAddresses(NUM_THREADS, nullptr);

    for (int i = 0; i < NUM_THREADS; ++i) {
        workers.emplace_back([i, &recordedAddresses]() {
            recordedAddresses[i] = &TestService::getInstance();
        });
    }

    for (auto& w : workers) {
        w.join();
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        assert(recordedAddresses[i] == &s1 && "Concurrent call yielded an invalid instance address!");
    }
    std::cout << "  ✓ Test 2 Passed: 50 concurrent threads obtained identical singleton instance.\n";

    std::cout << "[SUCCESS] All Singleton tests passed successfully!\n";
    return 0;
}

