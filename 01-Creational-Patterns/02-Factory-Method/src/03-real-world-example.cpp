/**
 * @file 03-real-world-example.cpp
 * @brief Real-world Application: Cross-Platform Logging Subsystem.
 */
#include <iostream>
#include <memory>
#include <string_view>

class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void log(std::string_view msg) const = 0;
};

class ConsoleLogger : public ILogger {
public:
    void log(std::string_view msg) const override {
        std::cout << "[Console] " << msg << "\n";
    }
};

class FileLogger : public ILogger {
public:
    void log(std::string_view msg) const override {
        std::cout << "[File: app.log] " << msg << "\n";
    }
};

class LoggerFactory {
public:
    virtual ~LoggerFactory() = default;
    virtual std::unique_ptr<ILogger> createLogger() const = 0;
};

class ConsoleLoggerFactory : public LoggerFactory {
public:
    std::unique_ptr<ILogger> createLogger() const override {
        return std::make_unique<ConsoleLogger>();
    }
};

class FileLoggerFactory : public LoggerFactory {
public:
    std::unique_ptr<ILogger> createLogger() const override {
        return std::make_unique<FileLogger>();
    }
};

int main() {
    std::unique_ptr<LoggerFactory> factory = std::make_unique<ConsoleLoggerFactory>();
    auto logger = factory->createLogger();
    logger->log("System initialized.");

    factory = std::make_unique<FileLoggerFactory>();
    logger = factory->createLogger();
    logger->log("Disk write completed.");
    return 0;
}
