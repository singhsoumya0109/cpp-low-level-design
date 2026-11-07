#include <iostream>
#include <string>

// Naive Approach: Giant monolithic if-else block for handling requests.
// Violates Open/Closed Principle: adding new check modifies this function.
enum class LogLevel { INFO, WARNING, ERROR, CRITICAL };

void log_message(LogLevel level, const std::string& msg) {
    if (level == LogLevel::INFO) {
        std::cout << "[CONSOLE INFO]: " << msg << "\n";
    } else if (level == LogLevel::WARNING) {
        std::cout << "[CONSOLE WARN]: " << msg << "\n";
        std::cout << "[FILE LOG]: " << msg << "\n";
    } else if (level == LogLevel::ERROR) {
        std::cout << "[CONSOLE ERROR]: " << msg << "\n";
        std::cout << "[FILE LOG]: " << msg << "\n";
        std::cout << "[EMAIL ALERT]: " << msg << "\n";
    } else if (level == LogLevel::CRITICAL) {
        std::cout << "[CONSOLE CRITICAL]: " << msg << "\n";
        std::cout << "[PAGERDUTY ALERT]: Waking on-call! " << msg << "\n";
    }
}

int main() {
    log_message(LogLevel::INFO, "System started");
    log_message(LogLevel::CRITICAL, "Database connection dropped!");
    return 0;
}
