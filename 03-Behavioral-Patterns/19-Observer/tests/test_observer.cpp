#include <cassert>
#include <iostream>
#include <vector>
#include <memory>

class IListener {
public:
    virtual ~IListener() = default;
    virtual void on_event(int val) = 0;
};

class TestListener : public IListener {
public:
    int count = 0;
    void on_event(int) override { ++count; }
};

int main() {
    std::cout << "[TEST] Running Observer tests...\n";
    auto l = std::make_shared<TestListener>();
    std::vector<std::shared_ptr<IListener>> subs{l};

    for (auto& s : subs) s->on_event(1);
    assert(l->count == 1);

    std::cout << "[TEST] All Observer tests PASSED!\n";
    return 0;
}
