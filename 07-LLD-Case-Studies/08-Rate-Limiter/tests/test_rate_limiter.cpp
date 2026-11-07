#include <cassert>
#include <iostream>

class SimpleLimiter {
    int max_;
    int cur_ = 0;
public:
    explicit SimpleLimiter(int m) : max_(m) {}
    bool allow() {
        if (cur_ < max_) { ++cur_; return true; }
        return false;
    }
    void reset() { cur_ = 0; }
};

int main() {
    std::cout << "[TEST] Running Rate Limiter tests...\n";
    SimpleLimiter l(2);
    assert(l.allow());
    assert(l.allow());
    assert(!l.allow()); // Exceeded
    l.reset();
    assert(l.allow());
    std::cout << "[TEST] All Rate Limiter tests PASSED!\n";
    return 0;
}
