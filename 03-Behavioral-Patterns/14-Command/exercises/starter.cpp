#include <iostream>
#include <memory>
#include <vector>

class BankAccount {
    double balance_ = 0.0;
public:
    void deposit(double amt) { balance_ += amt; }
    bool withdraw(double amt) {
        if (balance_ >= amt) { balance_ -= amt; return true; }
        return false;
    }
    double get_balance() const { return balance_; }
};

// TODO: Implement ITransactionCommand with execute() and undo()
// TODO: Implement DepositTransaction and WithdrawTransaction
// TODO: Implement TransactionInvoker with execute() and undo_last()

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
