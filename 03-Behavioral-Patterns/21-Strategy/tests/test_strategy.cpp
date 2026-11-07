#include <cassert>
#include <iostream>
#include <memory>

class IStrategy {
public:
    virtual ~IStrategy() = default;
    virtual int compute(int a, int b) const = 0;
};

class AddStrategy : public IStrategy {
public:
    int compute(int a, int b) const override { return a + b; }
};

int main() {
    std::cout << "[TEST] Running Strategy tests...\n";
    auto s = std::make_unique<AddStrategy>();
    assert(s->compute(10, 20) == 30);
    std::cout << "[TEST] All Strategy tests PASSED!\n";
    return 0;
}
