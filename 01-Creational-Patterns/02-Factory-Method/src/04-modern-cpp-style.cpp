/**
 * @file 04-modern-cpp-style.cpp
 * @brief Modern C++ Style: Parameterized Factory with std::unordered_map of Creator Callables.
 */
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class INotification {
public:
    virtual ~INotification() = default;
    virtual void send(const std::string& message) const = 0;
};

class EmailNotification : public INotification {
public:
    void send(const std::string& msg) const override { std::cout << "[Email] " << msg << "\n"; }
};

class SmsNotification : public INotification {
public:
    void send(const std::string& msg) const override { std::cout << "[SMS] " << msg << "\n"; }
};

// Dynamic Registration Factory in Modern C++
class NotificationFactory {
public:
    using CreatorFn = std::function<std::unique_ptr<INotification>()>;

    static NotificationFactory& instance() {
        static NotificationFactory f;
        return f;
    }

    void registerType(const std::string& type, CreatorFn creator) {
        creators_[type] = std::move(creator);
    }

    std::unique_ptr<INotification> create(const std::string& type) const {
        auto it = creators_.find(type);
        if (it != creators_.end()) {
            return it->second();
        }
        return nullptr;
    }

private:
    std::unordered_map<std::string, CreatorFn> creators_;
};

int main() {
    auto& factory = NotificationFactory::instance();
    factory.registerType("email", [] { return std::make_unique<EmailNotification>(); });
    factory.registerType("sms", [] { return std::make_unique<SmsNotification>(); });

    auto n1 = factory.create("email");
    if (n1) n1->send("Your OTP is 492042");

    auto n2 = factory.create("sms");
    if (n2) n2->send("Server load high");
    return 0;
}
