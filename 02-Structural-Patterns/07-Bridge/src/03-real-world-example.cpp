// 03-real-world-example.cpp: Messaging Service and Channel Bridge
#include <iostream>
#include <memory>
#include <string_view>

class IMessageSender {
public:
    virtual ~IMessageSender() = default;
    virtual void send(std::string_view msg) const = 0;
};

class EmailSender : public IMessageSender {
public:
    void send(std::string_view msg) const override { std::cout << "[Email Sender] " << msg << "\n"; }
};

class SmsSender : public IMessageSender {
public:
    void send(std::string_view msg) const override { std::cout << "[SMS Sender] " << msg << "\n"; }
};

class Message {
protected:
    std::shared_ptr<IMessageSender> sender_;
public:
    explicit Message(std::shared_ptr<IMessageSender> sender) : sender_(std::move(sender)) {}
    virtual ~Message() = default;
    virtual void dispatch(std::string_view text) const = 0;
};

class UrgentMessage : public Message {
public:
    explicit UrgentMessage(std::shared_ptr<IMessageSender> s) : Message(std::move(s)) {}
    void dispatch(std::string_view text) const override {
        std::cout << "[URGENT PRIORITY] ";
        sender_->send(text);
    }
};

int main() {
    auto email = std::make_shared<EmailSender>();
    UrgentMessage msg(email);
    msg.dispatch("Server temperature critical!");
    return 0;
}
