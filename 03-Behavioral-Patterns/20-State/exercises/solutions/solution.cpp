#include <cassert>
#include <iostream>
#include <memory>
#include <string>

class VendingMachine;

class IVendingState {
public:
    virtual ~IVendingState() = default;
    virtual bool insert_coin(VendingMachine& vm) = 0;
    virtual bool press_button(VendingMachine& vm) = 0;
    virtual std::string name() const = 0;
};

class VendingMachine {
    std::unique_ptr<IVendingState> state_;
    int items_ = 5;
public:
    explicit VendingMachine(std::unique_ptr<IVendingState> s);
    void change_state(std::unique_ptr<IVendingState> s) { state_ = std::move(s); }
    bool insert_coin() { return state_->insert_coin(*this); }
    bool press_button() { return state_->press_button(*this); }
    void decrement_item() { if (items_ > 0) --items_; }
    int items() const { return items_; }
    std::string state_name() const { return state_->name(); }
};

class IdleState : public IVendingState {
public:
    bool insert_coin(VendingMachine& vm) override;
    bool press_button(VendingMachine&) override { return false; }
    std::string name() const override { return "IDLE"; }
};

class HasCoinState : public IVendingState {
public:
    bool insert_coin(VendingMachine&) override { return false; } // Already has coin
    bool press_button(VendingMachine& vm) override {
        vm.decrement_item();
        vm.change_state(std::make_unique<IdleState>());
        return true;
    }
    std::string name() const override { return "HAS_COIN"; }
};

bool IdleState::insert_coin(VendingMachine& vm) {
    if (vm.items() > 0) {
        vm.change_state(std::make_unique<HasCoinState>());
        return true;
    }
    return false;
}

VendingMachine::VendingMachine(std::unique_ptr<IVendingState> s) : state_(std::move(s)) {}

int main() {
    VendingMachine vm(std::make_unique<IdleState>());
    assert(vm.state_name() == "IDLE");

    bool coin_inserted = vm.insert_coin();
    assert(coin_inserted == true);
    assert(vm.state_name() == "HAS_COIN");

    bool dispensed = vm.press_button();
    assert(dispensed == true);
    assert(vm.state_name() == "IDLE");
    assert(vm.items() == 4);

    std::cout << "State solution verified successfully!\n";
    return 0;
}
