#include <cassert>
#include <iostream>
#include <unordered_map>
#include <string>

struct Item { double price; int stock; };

class VendingMachine {
    std::unordered_map<std::string, Item> items;
    double bal = 0.0;
public:
    void add(const std::string& code, double price, int stock) { items[code] = {price, stock}; }
    void insert(double amt) { bal += amt; }
    bool buy(const std::string& code) {
        if (items.count(code) && items[code].stock > 0 && bal >= items[code].price) {
            items[code].stock--;
            bal -= items[code].price;
            return true;
        }
        return false;
    }
    double refund() { double r = bal; bal = 0.0; return r; }
};

int main() {
    std::cout << "[TEST] Running Vending Machine tests...\n";
    VendingMachine vm;
    vm.add("C1", 2.0, 1);
    vm.insert(1.0);
    assert(!vm.buy("C1"));
    vm.insert(1.0);
    assert(vm.buy("C1"));
    assert(!vm.buy("C1")); // Stock depleted
    assert(vm.refund() == 0.0);
    std::cout << "[TEST] All Vending Machine tests PASSED!\n";
    return 0;
}
