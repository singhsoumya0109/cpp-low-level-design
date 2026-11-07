#include <iostream>
#include <memory>
#include <string>

class IMessageSender {
public:
    virtual ~IMessageSender() = default;
    virtual void send_raw(const std::string& msg) = 0;
};

class Message {
protected:
    std::shared_ptr<IMessageSender> sender_;
public:
    explicit Message(std::shared_ptr<IMessageSender> s) : sender_(std::move(s)) {}
    virtual ~Message() = default;
    virtual void send(const std::string& body) = 0;
};

// TODO: Implement SmsSender, EmailSender and NormalMessage, EncryptedMessage

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
