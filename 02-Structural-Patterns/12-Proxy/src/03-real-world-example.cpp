// 03-real-world-example.cpp: Protection Proxy (Access Control)
#include <iostream>
#include <string>

class IBankAccount {
public:
    virtual ~IBankAccount() = default;
    virtual void withdraw(double amount) = 0;
};

class RealAccount : public IBankAccount {
public:
    void withdraw(double amount) override { std::cout << "Withdrew $" << amount << "\n"; }
};

class ProtectionProxy : public IBankAccount {
private:
    RealAccount account_;
    std::string role_;
public:
    explicit ProtectionProxy(std::string role) : role_(std::move(role)) {}
    void withdraw(double amount) override {
        if (role_ != "ADMIN" && role_ != "OWNER") {
            std::cout << "Access Denied: Role '" << role_ << "' not authorized to withdraw.\n";
            return;
        }
        account_.withdraw(amount);
    }
};

int main() {
    ProtectionProxy hacker("GUEST");
    hacker.withdraw(500);

    ProtectionProxy owner("OWNER");
    owner.withdraw(500);
    return 0;
}
