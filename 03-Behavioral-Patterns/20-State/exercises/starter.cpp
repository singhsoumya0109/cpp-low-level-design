#include <iostream>
#include <memory>
#include <string>

class VendingMachine;

class IVendingState {
public:
    virtual ~IVendingState() = default;
    virtual void insert_coin(VendingMachine&) = 0;
    virtual void press_button(VendingMachine&) = 0;
};

// TODO: Implement IdleState, HasCoinState, DispensingState

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
