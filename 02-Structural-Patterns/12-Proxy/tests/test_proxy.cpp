#include <cassert>
#include <iostream>
#include <memory>

class ISubject { public: virtual ~ISubject() = default; virtual int request() = 0; };
class RealSubject : public ISubject { public: int request() override { return 100; } };

class Proxy : public ISubject {
    std::unique_ptr<RealSubject> real_;
    int calls_{0};
public:
    int request() override {
        if (!real_) real_ = std::make_unique<RealSubject>();
        ++calls_;
        return real_->request();
    }
    int getCalls() const { return calls_; }
};

int main() {
    Proxy p;
    assert(p.request() == 100);
    assert(p.request() == 100);
    assert(p.getCalls() == 2);
    std::cout << "[TEST] ✓ Proxy unit test passed!\n";
    return 0;
}
