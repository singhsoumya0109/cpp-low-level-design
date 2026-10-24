/**
 * @file 01-naive-approach.cpp
 * @brief Demonstrates the classic flawed C++98 Singleton anti-pattern.
 *
 * Flaws:
 * 1. Data race: Multiple threads can call getInstance() concurrently, resulting in multiple objects.
 * 2. Memory leak: 'new' is called without corresponding 'delete'. Destructor is never run.
 */

#include <iostream>
#include <thread>
#include <vector>

class NaiveSingleton {
private:
    static NaiveSingleton* instance_;
    int value_{0};

    NaiveSingleton() {
        std::cout << "[NaiveSingleton] Constructor invoked!\n";
    }

public:
    // Flawed lazy instantiation
    static NaiveSingleton* getInstance() {
        if (instance_ == nullptr) {
            // Simulated delay to trigger race conditions
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            instance_ = new NaiveSingleton();
        }
        return instance_;
    }

    void setValue(int v) { value_ = v; }
    int getValue() const { return value_; }
};

NaiveSingleton* NaiveSingleton::instance_ = nullptr;

int main() {
    std::cout << "=== Running Naive Singleton (Thread Race Demo) ===\n";

    std::vector<std::thread> threads;
    std::vector<NaiveSingleton*> instances(5, nullptr);

    // Launch 5 threads concurrently calling getInstance()
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([i, &instances]() {
            instances[i] = NaiveSingleton::getInstance();
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "\nInstance memory addresses across threads:\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread " << i << " instance address: " << instances[i] << '\n';
    }

    std::cout << "\nNotice: Multiple constructors were called and multiple distinct addresses exist!\n";
    std::cout << "This proves the race condition in the naive approach.\n";
    return 0;
}

