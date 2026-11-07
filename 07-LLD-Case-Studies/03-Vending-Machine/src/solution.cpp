#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

struct Product {
    std::string name;
    double price;
    int quantity;
};

class VendingMachine {
    std::unordered_map<std::string, Product> inventory_;
    double inserted_balance_ = 0.0;

public:
    void add_product(const std::string& code, std::string name, double price, int qty) {
        inventory_[code] = Product{std::move(name), price, qty};
    }

    void insert_money(double amount) {
        inserted_balance_ += amount;
        std::cout << "[Vending] Inserted: $" << amount << " | Total balance: $" << inserted_balance_ << "\n";
    }

    bool select_product(const std::string& code) {
        auto it = inventory_.find(code);
        if (it == inventory_.end()) {
            std::cout << "[Vending] Invalid selection\n";
            return false;
        }
        Product& p = it->second;
        if (p.quantity <= 0) {
            std::cout << "[Vending] Out of stock: " << p.name << "\n";
            return false;
        }
        if (inserted_balance_ < p.price) {
            std::cout << "[Vending] Insufficient funds. Needs: $" << p.price << "\n";
            return false;
        }

        p.quantity--;
        inserted_balance_ -= p.price;
        std::cout << "[Vending] Dispensed: " << p.name << "\n";
        return true;
    }

    double refund() {
        double change = inserted_balance_;
        inserted_balance_ = 0.0;
        std::cout << "[Vending] Refunded: $" << change << "\n";
        return change;
    }

    double current_balance() const { return inserted_balance_; }
};

int main() {
    std::cout << "=== Vending Machine Simulation ===\n";
    VendingMachine vm;
    vm.add_product("A1", "Soda", 1.50, 2);
    vm.add_product("B2", "Chips", 1.00, 5);

    vm.insert_money(1.00);
    vm.select_product("A1"); // Not enough
    vm.insert_money(1.00);
    vm.select_product("A1"); // Dispensed
    vm.refund();
    return 0;
}
