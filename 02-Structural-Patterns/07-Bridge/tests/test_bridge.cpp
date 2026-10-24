#include <cassert>
#include <iostream>
#include <memory>

class IDevice { public: virtual ~IDevice() = default; virtual bool isEnabled() const = 0; virtual void enable() = 0; };
class TV : public IDevice {
    bool on_{false};
public:
    bool isEnabled() const override { return on_; }
    void enable() override { on_ = true; }
};

class Remote {
protected:
    std::shared_ptr<IDevice> device_;
public:
    explicit Remote(std::shared_ptr<IDevice> d) : device_(std::move(d)) {}
    void togglePower() { device_->enable(); }
};

int main() {
    auto tv = std::make_shared<TV>();
    Remote remote(tv);
    assert(!tv->isEnabled());
    remote.togglePower();
    assert(tv->isEnabled());
    std::cout << "[TEST] ✓ Bridge unit test passed!\n";
    return 0;
}
