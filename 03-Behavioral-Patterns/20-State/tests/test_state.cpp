#include <cassert>
#include <iostream>
#include <memory>

class StateContext;

class State {
public:
    virtual ~State() = default;
    virtual int action(StateContext& ctx) = 0;
};

class StateContext {
    std::unique_ptr<State> s_;
public:
    explicit StateContext(std::unique_ptr<State> s) : s_(std::move(s)) {}
    void set_state(std::unique_ptr<State> s) { s_ = std::move(s); }
    int do_action() { return s_->action(*this); }
};

class ConcreteState : public State {
public:
    int action(StateContext&) override { return 42; }
};

int main() {
    std::cout << "[TEST] Running State tests...\n";
    StateContext ctx(std::make_unique<ConcreteState>());
    assert(ctx.do_action() == 42);
    std::cout << "[TEST] All State tests PASSED!\n";
    return 0;
}
