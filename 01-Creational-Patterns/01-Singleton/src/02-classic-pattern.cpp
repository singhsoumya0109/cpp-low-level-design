/**
 * @file 02-classic-pattern.cpp
 * @brief Standard Thread-Safe Meyers' Singleton in C++17.
 *
 * Guaranteed by C++11/14/17 standard (§6.7) to be thread-safe during static initialization.
 * Zero manual locks, zero memory leaks (automatically destroyed at program exit).
 */

#include <iostream>
#include <thread>
#include <vector>

class MeyersSingleton {
private:
    int counter_{0};

    // Private constructor prevents external instantiation
    MeyersSingleton() {
        std::cout << "[MeyersSingleton] Constructor called exactly once at address: " << this << "\n";
    }

    // Private destructor
    ~MeyersSingleton() {
        std::cout << "[MeyersSingleton] Destructor called automatically at program exit.\n";
    }

public:
    // Delete copy and move constructors/operators
    MeyersSingleton(const MeyersSingleton&) = delete;
    MeyersSingleton& operator=(const MeyersSingleton&) = delete;
    MeyersSingleton(MeyersSingleton&&) = delete;
    MeyersSingleton& operator=(MeyersSingleton&&) = delete;

    // Global point of access
    static MeyersSingleton& getInstance() {
        static MeyersSingleton instance; // Thread-safe local static!
        return instance;
    }

    void increment() { ++counter_; }
    int getCount() const { return counter_; }
};

int main() {
    std::cout << "=== Running Meyers' Thread-Safe Singleton ===\n";

    std::vector<std::thread> threads;
    std::vector<MeyersSingleton*> addresses(5, nullptr);

    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([i, &addresses]() {
            addresses[i] = &MeyersSingleton::getInstance();
            addresses[i]->increment();
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "\nInstance memory addresses across threads:\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread " << i << " instance address: " << addresses[i] << '\n';
    }

    std::cout << "\nAll addresses are identical! Total counter value: "
              << MeyersSingleton::getInstance().getCount() << '\n';
    return 0;
}

