#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class IMessageSender {
public:
    virtual ~IMessageSender() = default;
    virtual void send_raw(const std::string& msg) = 0;
};

class MockSender : public IMessageSender {
public:
    std::vector<std::string> sent;
    void send_raw(const std::string& msg) override {
        sent.push_back(msg);
    }
};

class Message {
protected:
    std::shared_ptr<IMessageSender> sender_;
public:
    explicit Message(std::shared_ptr<IMessageSender> s) : sender_(std::move(s)) {}
    virtual ~Message() = default;
    virtual void send(const std::string& body) = 0;
};

class NormalMessage : public Message {
public:
    using Message::Message;
    void send(const std::string& body) override {
        sender_->send_raw("[NORMAL] " + body);
    }
};

class UrgentMessage : public Message {
public:
    using Message::Message;
    void send(const std::string& body) override {
        sender_->send_raw("[URGENT] " + body);
    }
};

int main() {
    auto mock = std::make_shared<MockSender>();
    NormalMessage m1(mock);
    UrgentMessage m2(mock);

    m1.send("Server online");
    m2.send("High load detected");

    assert(mock->sent.size() == 2);
    assert(mock->sent[0] == "[NORMAL] Server online");
    assert(mock->sent[1] == "[URGENT] High load detected");

    std::cout << "Bridge solution verified successfully!\n";
    return 0;
}
