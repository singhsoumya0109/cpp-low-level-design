#include <cassert>
#include <iostream>

enum class Status { NEW, PAID, SHIPPED };

class SimpleOrder {
    Status s_ = Status::NEW;
public:
    bool pay() { if (s_ == Status::NEW) { s_ = Status::PAID; return true; } return false; }
    bool ship() { if (s_ == Status::PAID) { s_ = Status::SHIPPED; return true; } return false; }
    Status status() const { return s_; }
};

int main() {
    std::cout << "[TEST] Running Order tests...\n";
    SimpleOrder o;
    assert(o.status() == Status::NEW);
    assert(!o.ship()); // Cannot ship before pay
    assert(o.pay());
    assert(o.ship());
    assert(o.status() == Status::SHIPPED);
    std::cout << "[TEST] All Order tests PASSED!\n";
    return 0;
}
