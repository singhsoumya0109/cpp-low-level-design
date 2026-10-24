#include <cassert>
#include <iostream>
#include <memory>

class ITarget { public: virtual ~ITarget() = default; virtual int request() const = 0; };
class Adaptee { public: int specificRequest() const { return 42; } };
class Adapter : public ITarget {
    std::unique_ptr<Adaptee> a_;
public:
    explicit Adapter(std::unique_ptr<Adaptee> a) : a_(std::move(a)) {}
    int request() const override { return a_->specificRequest(); }
};

int main() {
    auto target = std::make_unique<Adapter>(std::make_unique<Adaptee>());
    assert(target->request() == 42);
    std::cout << "[TEST] ✓ Adapter unit test passed!\n";
    return 0;
}
