/**
 * @file 03-real-world-example.cpp
 * @brief Real-world Application: Centralized Thread-Safe Logger Singleton.
 *
 * Demonstrates a production scenario where multiple subsystem threads write logs
 * to a centralized output stream without interleaving lines.
 */

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <string_view>
#include <thread>
#include <vector>

enum class LogLevel { INFO, WARNING, ERROR };

class Logger {
private:
    std::mutex logMutex_;

    Logger() {
        std::cout << "[Logger Initialized]\n";
    }

    std::string_view levelToString(LogLevel level) const {
        switch (level) {
            case LogLevel::INFO:    return "INFO";
            case LogLevel::WARNING: return "WARN";
            case LogLevel::ERROR:   return "ERROR";
        }
        return "UNKNOWN";
    }

public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(LogLevel level, std::string_view message) {
        // Protect concurrent writes to std::cout
        std::lock_guard<std::mutex> lock(logMutex_);

        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);
        auto tm = *std::localtime(&time_t_now);

        std::cout << "[" << std::put_time(&tm, "%H:%M:%S") << "] "
                  << "[" << levelToString(level) << "] "
                  << "[Thread " << std::this_thread::get_id() << "] "
                  << message << '\n';
    }
};

void paymentWorker() {
    Logger::getInstance().log(LogLevel::INFO, "Payment worker started processing order #1001");
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    Logger::getInstance().log(LogLevel::INFO, "Payment captured successfully via Stripe");
}

void notificationWorker() {
    Logger::getInstance().log(LogLevel::INFO, "Notification worker sending push receipt...");
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    Logger::getInstance().log(LogLevel::WARNING, "Push notification delivery delayed by 50ms");
}

int main() {
    std::cout << "=== Running Real-World Centralized Logger Singleton ===\n";

    std::thread t1(paymentWorker);
    std::thread t2(notificationWorker);

    t1.join();
    t2.join();

    Logger::getInstance().log(LogLevel::INFO, "All workers completed cleanly.");
    return 0;
}

