#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class INotificationChannel {
public:
    virtual ~INotificationChannel() = default;
    virtual void send(const std::string& recipient, const std::string& message) = 0;
};

class EmailChannel : public INotificationChannel {
public:
    void send(const std::string& recipient, const std::string& message) override {
        std::cout << "[EMAIL to " << recipient << "] " << message << "\n";
    }
};

class SMSChannel : public INotificationChannel {
public:
    void send(const std::string& recipient, const std::string& message) override {
        std::cout << "[SMS to " << recipient << "] " << message << "\n";
    }
};

class NotificationService {
    std::unordered_map<std::string, std::shared_ptr<INotificationChannel>> channels_;
public:
    void register_channel(const std::string& name, std::shared_ptr<INotificationChannel> ch) {
        channels_[name] = std::move(ch);
    }

    bool notify(const std::string& channel_name, const std::string& recipient, const std::string& msg) {
        auto it = channels_.find(channel_name);
        if (it != channels_.end()) {
            it->second->send(recipient, msg);
            return true;
        }
        return false;
    }
};

int main() {
    std::cout << "=== Notification System Simulation ===\n";
    NotificationService svc;
    svc.register_channel("EMAIL", std::make_shared<EmailChannel>());
    svc.register_channel("SMS", std::make_shared<SMSChannel>());

    svc.notify("EMAIL", "user@corp.com", "Security alert: new login");
    svc.notify("SMS", "+15550199", "Your one-time pass is 4492");
    return 0;
}
