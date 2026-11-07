#include <cassert>
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

class ITransaction {
public:
    virtual ~ITransaction() = default;
    virtual bool execute() = 0;
    virtual void undo() = 0;
};

class DepositTransaction : public ITransaction {
    BankAccount& account_;
    double amount_;
public:
    DepositTransaction(BankAccount& acct, double amt) : account_(acct), amount_(amt) {}
    bool execute() override {
        account_.deposit(amount_);
        return true;
    }
    void undo() override {
        account_.withdraw(amount_);
    }
};

class WithdrawTransaction : public ITransaction {
    BankAccount& account_;
    double amount_;
    bool succeeded_ = false;
public:
    WithdrawTransaction(BankAccount& acct, double amt) : account_(acct), amount_(amt) {}
    bool execute() override {
        succeeded_ = account_.withdraw(amount_);
        return succeeded_;
    }
    void undo() override {
        if (succeeded_) {
            account_.deposit(amount_);
        }
    }
};

int main() {
    BankAccount account;
    std::vector<std::unique_ptr<ITransaction>> history;

    auto t1 = std::make_unique<DepositTransaction>(account, 100.0);
    t1->execute();
    history.push_back(std::move(t1));
    assert(account.get_balance() == 100.0);

    auto t2 = std::make_unique<WithdrawTransaction>(account, 40.0);
    t2->execute();
    history.push_back(std::move(t2));
    assert(account.get_balance() == 60.0);

    // Rollback last transaction
    history.back()->undo();
    history.pop_back();
    assert(account.get_balance() == 100.0);

    std::cout << "Command solution verified successfully!\n";
    return 0;
}
