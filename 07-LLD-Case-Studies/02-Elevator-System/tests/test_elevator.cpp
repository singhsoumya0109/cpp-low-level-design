#include <cassert>
#include <iostream>
#include <set>

class Elevator {
    int floor_ = 1;
    std::set<int> targets_;
public:
    void call(int f) { targets_.insert(f); }
    void step() {
        if (!targets_.empty()) {
            floor_ = *targets_.begin();
            targets_.erase(targets_.begin());
        }
    }
    int floor() const { return floor_; }
    bool is_idle() const { return targets_.empty(); }
};

int main() {
    std::cout << "[TEST] Running Elevator tests...\n";
    Elevator e;
    assert(e.floor() == 1);
    assert(e.is_idle());

    e.call(7);
    assert(!e.is_idle());
    e.step();
    assert(e.floor() == 7);
    assert(e.is_idle());

    std::cout << "[TEST] All Elevator tests PASSED!\n";
    return 0;
}
