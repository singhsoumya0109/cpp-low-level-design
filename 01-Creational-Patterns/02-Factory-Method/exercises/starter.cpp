#include <iostream>
#include <memory>
#include <string>
#include <string_view>

// Interface
class INotification {
public:
    virtual ~INotification() = default;
    virtual void send(std::string_view recipient, std::string_view msg) = 0;
};

// TODO 1: Implement EmailNotification, SMSNotification, PushNotification
class EmailNotification : public INotification {
public:
    void send(std::string_view recipient, std::string_view msg) override {
        // TODO: Print formatted email dispatch
    }
};

// TODO 2: Implement NotificationCreator base and concrete creators
class NotificationCreator {
public:
    virtual ~NotificationCreator() = default;
    virtual std::unique_ptr<INotification> create() const = 0;
    void notify(std::string_view recipient, std::string_view msg) const {
        auto n = create();
        n->send(recipient, msg);
    }
};

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
