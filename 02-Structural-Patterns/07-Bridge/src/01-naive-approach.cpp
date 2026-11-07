#include <iostream>

// Naive Approach: Combinatorial class explosion
// 2 Abstractions (NormalMessage, UrgentMessage) x 2 Implementations (SMS, Email) = 4 classes!
class NormalSMSMessage {
public:
    void send(const std::string& text) {
        std::cout << "[SMS] Normal: " << text << "\n";
    }
};

class UrgentSMSMessage {
public:
    void send(const std::string& text) {
        std::cout << "[SMS] URGENT: " << text << "\n";
    }
};

class NormalEmailMessage {
public:
    void send(const std::string& text) {
        std::cout << "[Email] Normal: " << text << "\n";
    }
};

class UrgentEmailMessage {
public:
    void send(const std::string& text) {
        std::cout << "[Email] URGENT: " << text << "\n";
    }
};

int main() {
    NormalSMSMessage m1;
    m1.send("System update");

    UrgentEmailMessage m2;
    m2.send("Database connection lost!");
    return 0;
}
