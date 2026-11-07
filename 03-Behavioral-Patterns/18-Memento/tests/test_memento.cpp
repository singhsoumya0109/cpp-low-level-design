#include <cassert>
#include <iostream>

class Counter {
    int val_ = 0;
public:
    struct Snapshot { int v; };
    void inc() { ++val_; }
    Snapshot save() const { return Snapshot{val_}; }
    void restore(Snapshot s) { val_ = s.v; }
    int val() const { return val_; }
};

int main() {
    std::cout << "[TEST] Running Memento tests...\n";
    Counter c;
    c.inc();
    auto snap = c.save();
    c.inc();
    c.inc();
    assert(c.val() == 3);
    c.restore(snap);
    assert(c.val() == 1);
    std::cout << "[TEST] All Memento tests PASSED!\n";
    return 0;
}
