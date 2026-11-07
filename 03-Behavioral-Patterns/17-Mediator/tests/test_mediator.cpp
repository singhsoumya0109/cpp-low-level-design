#include <cassert>
#include <iostream>
#include <string>

class Mediator;

class Component {
    Mediator* med_;
public:
    explicit Component(Mediator* m) : med_(m) {}
    void trigger();
};

class Mediator {
public:
    int event_count = 0;
    void notify() { ++event_count; }
};

void Component::trigger() { med_->notify(); }

int main() {
    std::cout << "[TEST] Running Mediator tests...\n";
    Mediator m;
    Component c(&m);
    c.trigger();
    assert(m.event_count == 1);
    std::cout << "[TEST] All Mediator tests PASSED!\n";
    return 0;
}
