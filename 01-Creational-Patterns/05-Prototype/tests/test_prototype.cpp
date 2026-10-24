#include <cassert>
#include <iostream>
#include <memory>

class IPrototype {
public:
    virtual ~IPrototype() = default;
    virtual std::unique_ptr<IPrototype> clone() const = 0;
    virtual int getVal() const = 0;
};

class Number : public IPrototype {
    int val_;
public:
    explicit Number(int v) : val_(v) {}
    std::unique_ptr<IPrototype> clone() const override { return std::make_unique<Number>(*this); }
    int getVal() const override { return val_; }
};

int main() {
    std::unique_ptr<IPrototype> orig = std::make_unique<Number>(42);
    auto cl = orig->clone();
    assert(cl != nullptr);
    assert(cl != orig);
    assert(cl->getVal() == 42);
    std::cout << "[TEST] ✓ Prototype test passed!\n";
    return 0;
}
