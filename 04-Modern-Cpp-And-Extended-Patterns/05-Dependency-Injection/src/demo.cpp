#include <iostream>
#include <memory>
#include <string>
#include <utility>

// Abstract dependency
class INotificationService {
public:
    virtual ~INotificationService() = default;
    virtual void send_notification(const std::string& recipient, const std::string& msg) = 0;
};

// Concrete production service
class EmailNotificationService : public INotificationService {
public:
    void send_notification(const std::string& recipient, const std::string& msg) override {
        std::cout << "[Email Service] Sending to " << recipient << ": " << msg << "\n";
    }
};

// Abstract repository dependency
class IUserRepository {
public:
    virtual ~IUserRepository() = default;
    virtual std::string get_user_email(int user_id) = 0;
};

class SQLUserRepository : public IUserRepository {
public:
    std::string get_user_email(int user_id) override {
        return "user" + std::to_string(user_id) + "@company.com";
    }
};

// Business service with constructor injection
class UserService {
public:
    UserService(std::shared_ptr<IUserRepository> repo, 
                std::shared_ptr<INotificationService> notifier)
        : repo_(std::move(repo)), notifier_(std::move(notifier)) {}

    void alert_user(int user_id, const std::string& alert_msg) {
        std::string email = repo_->get_user_email(user_id);
        notifier_->send_notification(email, alert_msg);
    }

private:
    std::shared_ptr<IUserRepository> repo_;
    std::shared_ptr<INotificationService> notifier_;
};

int main() {
    std::cout << "=== Modern C++ Dependency Injection Demo ===\n";
    auto repo = std::make_shared<SQLUserRepository>();
    auto notifier = std::make_shared<EmailNotificationService>();

    UserService svc(repo, notifier);
    svc.alert_user(101, "Your security password was changed.");
    return 0;
}
