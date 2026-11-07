#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>

class INotification {
public:
    virtual ~INotification() = default;
    virtual std::string send(std::string_view recipient, std::string_view msg) = 0;
};

class EmailNotification : public INotification {
public:
    std::string send(std::string_view recipient, std::string_view msg) override {
        return "EMAIL to " + std::string(recipient) + ": " + std::string(msg);
    }
};

class SMSNotification : public INotification {
public:
    std::string send(std::string_view recipient, std::string_view msg) override {
        return "SMS to " + std::string(recipient) + ": " + std::string(msg);
    }
};

class NotificationCreator {
public:
    virtual ~NotificationCreator() = default;
    virtual std::unique_ptr<INotification> create() const = 0;
    std::string notify(std::string_view recipient, std::string_view msg) const {
        return create()->send(recipient, msg);
    }
};

class EmailCreator : public NotificationCreator {
public:
    std::unique_ptr<INotification> create() const override {
        return std::make_unique<EmailNotification>();
    }
};

class SMSCreator : public NotificationCreator {
public:
    std::unique_ptr<INotification> create() const override {
        return std::make_unique<SMSNotification>();
    }
};

int main() {
    EmailCreator ec;
    SMSCreator sc;

    std::string email_res = ec.notify("user@test.com", "Welcome!");
    std::string sms_res = sc.notify("+1234567890", "Your OTP is 9482");

    assert(email_res == "EMAIL to user@test.com: Welcome!");
    assert(sms_res == "SMS to +1234567890: Your OTP is 9482");

    std::cout << "Factory Method solution verified successfully!\n";
    return 0;
}
