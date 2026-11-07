#include <cassert>
#include <iostream>
#include <string>
#include <vector>

template <typename F>
class ScopeGuard {
public:
    explicit ScopeGuard(F cleanup) : cleanup_(std::move(cleanup)), active_(true) {}
    ~ScopeGuard() { if (active_) cleanup_(); }
    void dismiss() noexcept { active_ = false; }
private:
    F cleanup_;
    bool active_;
};

int main() {
    std::cout << "[TEST] Running RAII and ScopeGuard tests...\n";

    // Test 1: ScopeGuard executes on normal exit
    bool executed = false;
    {
        ScopeGuard g([&]() { executed = true; });
    }
    assert(executed && "ScopeGuard should execute upon leaving scope");

    // Test 2: Dismissed guard does not execute
    bool dismissed_executed = false;
    {
        ScopeGuard g([&]() { dismissed_executed = true; });
        g.dismiss();
    }
    assert(!dismissed_executed && "Dismissed ScopeGuard must not execute");

    // Test 3: ScopeGuard executes during exception stack unwinding
    bool exception_cleanup = false;
    try {
        ScopeGuard g([&]() { exception_cleanup = true; });
        throw std::runtime_error("Simulated failure");
    } catch (...) {
        // Exception caught
    }
    assert(exception_cleanup && "ScopeGuard must execute during exception unwinding");

    std::cout << "[TEST] All RAII tests PASSED!\n";
    return 0;
}
