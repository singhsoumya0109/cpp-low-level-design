#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class INotifier {
public:
    virtual ~INotifier() = default;
    virtual void notify(const std::string& msg) = 0;
};

class MockNotifier : public INotifier {
public:
    std::vector<std::string> sent;
    void notify(const std::string& msg) override {
        sent.push_back(msg);
    }
};

class OrderService {
    std::shared_ptr<INotifier> notifier_;
public:
    explicit OrderService(std::shared_ptr<INotifier> n) : notifier_(std::move(n)) {}
    void place_order(int id) {
        notifier_->notify("Order #" + std::to_string(id) + " placed");
    }
};

int main() {
    std::cout << "[TEST] Running Dependency Injection tests...\n";

    auto mock = std::make_shared<MockNotifier>();
    OrderService service(mock);

    service.place_order(505);
    assert(mock->sent.size() == 1);
    assert(mock->sent[0] == "Order #505 placed");

    std::cout << "[TEST] All Dependency Injection tests PASSED!\n";
    return 0;
}
