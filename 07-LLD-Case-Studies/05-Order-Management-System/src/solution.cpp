#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

enum class OrderStatus { CREATED, PAID, SHIPPED, DELIVERED, CANCELLED };

struct OrderItem {
    std::string item_id;
    int quantity;
    double unit_price;
};

class Order {
    int id_;
    OrderStatus status_ = OrderStatus::CREATED;
    std::vector<OrderItem> items_;

public:
    explicit Order(int id) : id_(id) {}
    void add_item(std::string id, int qty, double price) {
        items_.push_back({std::move(id), qty, price});
    }

    double total_amount() const {
        double total = 0.0;
        for (const auto& item : items_) total += item.quantity * item.unit_price;
        return total;
    }

    bool pay() {
        if (status_ == OrderStatus::CREATED) {
            status_ = OrderStatus::PAID;
            std::cout << "[Order " << id_ << "] Status -> PAID\n";
            return true;
        }
        return false;
    }

    bool ship() {
        if (status_ == OrderStatus::PAID) {
            status_ = OrderStatus::SHIPPED;
            std::cout << "[Order " << id_ << "] Status -> SHIPPED\n";
            return true;
        }
        return false;
    }

    OrderStatus status() const { return status_; }
    int id() const { return id_; }
};

int main() {
    std::cout << "=== Order Management Simulation ===\n";
    Order order(101);
    order.add_item("BOOK-A", 2, 19.99);
    order.add_item("PEN-B", 3, 2.50);

    std::cout << "Total: $" << order.total_amount() << "\n";
    order.pay();
    order.ship();
    return 0;
}
