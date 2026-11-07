#include <iostream>
#include <functional>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

// Modern C++17 Type-Safe Central Event Bus Mediator
class EventBus {
    using Callback = std::function<void(const void*)>;
    std::unordered_map<std::type_index, std::vector<Callback>> subscribers_;
public:
    template <typename EventType>
    void subscribe(std::function<void(const EventType&)> handler) {
        subscribers_[std::type_index(typeid(EventType))].push_back([handler](const void* evt_ptr) {
            handler(*static_cast<const EventType*>(evt_ptr));
        });
    }

    template <typename EventType>
    void publish(const EventType& event) {
        auto it = subscribers_.find(std::type_index(typeid(EventType)));
        if (it != subscribers_.end()) {
            for (const auto& cb : it->second) {
                cb(&event);
            }
        }
    }
};

struct UserRegisteredEvent { std::string email; };
struct OrderPlacedEvent { int order_id; double amount; };

int main() {
    EventBus bus;

    // Subscriber 1: Email service
    bus.subscribe<UserRegisteredEvent>([](const UserRegisteredEvent& evt) {
        std::cout << "[EmailService] Sending welcome email to " << evt.email << "\n";
    });

    // Subscriber 2: Analytics service
    bus.subscribe<OrderPlacedEvent>([](const OrderPlacedEvent& evt) {
        std::cout << "[Analytics] Tracked Order #" << evt.order_id << " ($" << evt.amount << ")\n";
    });

    bus.publish(UserRegisteredEvent{"alice@example.com"});
    bus.publish(OrderPlacedEvent{1042, 89.99});
    return 0;
}
