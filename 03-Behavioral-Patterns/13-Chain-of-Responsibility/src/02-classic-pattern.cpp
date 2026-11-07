#include <iostream>
#include <memory>
#include <string>

enum class Priority { LOW, MEDIUM, HIGH };

struct Issue {
    int id;
    std::string description;
    Priority priority;
};

class SupportHandler {
protected:
    std::shared_ptr<SupportHandler> next_handler_;
public:
    virtual ~SupportHandler() = default;

    std::shared_ptr<SupportHandler> set_next(std::shared_ptr<SupportHandler> next) {
        next_handler_ = std::move(next);
        return next_handler_;
    }

    virtual void handle(const Issue& issue) {
        if (next_handler_) {
            next_handler_->handle(issue);
        } else {
            std::cout << "[Support] Issue #" << issue.id << " could not be resolved by support chain.\n";
        }
    }
};

class Level1Support : public SupportHandler {
public:
    void handle(const Issue& issue) override {
        if (issue.priority == Priority::LOW) {
            std::cout << "[Level 1 Support] Handled issue #" << issue.id << ": " << issue.description << "\n";
        } else {
            SupportHandler::handle(issue);
        }
    }
};

class Level2Support : public SupportHandler {
public:
    void handle(const Issue& issue) override {
        if (issue.priority == Priority::MEDIUM) {
            std::cout << "[Level 2 Support] Handled issue #" << issue.id << ": " << issue.description << "\n";
        } else {
            SupportHandler::handle(issue);
        }
    }
};

class Level3Support : public SupportHandler {
public:
    void handle(const Issue& issue) override {
        if (issue.priority == Priority::HIGH) {
            std::cout << "[Level 3 Support] Escalated and solved issue #" << issue.id << ": " << issue.description << "\n";
        } else {
            SupportHandler::handle(issue);
        }
    }
};

int main() {
    auto l1 = std::make_shared<Level1Support>();
    auto l2 = std::make_shared<Level2Support>();
    auto l3 = std::make_shared<Level3Support>();

    l1->set_next(l2)->set_next(l3);

    l1->handle({1, "Password reset", Priority::LOW});
    l1->handle({2, "Slow database query", Priority::MEDIUM});
    l1->handle({3, "Data center outage", Priority::HIGH});
    return 0;
}
