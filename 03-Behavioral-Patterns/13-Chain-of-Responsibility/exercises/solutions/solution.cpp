#include <cassert>
#include <iostream>
#include <memory>
#include <string>

struct ExpenseRequest {
    int id;
    double amount;
    std::string purpose;
};

class Approver {
protected:
    std::shared_ptr<Approver> next_;
public:
    virtual ~Approver() = default;
    std::shared_ptr<Approver> set_next(std::shared_ptr<Approver> n) {
        next_ = std::move(n);
        return next_;
    }
    virtual std::string approve(const ExpenseRequest& req) {
        if (next_) return next_->approve(req);
        return "DENIED: Amount $" + std::to_string(req.amount) + " exceeds approval threshold";
    }
};

class Manager : public Approver {
public:
    std::string approve(const ExpenseRequest& req) override {
        if (req.amount <= 1000.0) return "APPROVED_BY_MANAGER";
        return Approver::approve(req);
    }
};

class Director : public Approver {
public:
    std::string approve(const ExpenseRequest& req) override {
        if (req.amount <= 10000.0) return "APPROVED_BY_DIRECTOR";
        return Approver::approve(req);
    }
};

class VP : public Approver {
public:
    std::string approve(const ExpenseRequest& req) override {
        if (req.amount <= 50000.0) return "APPROVED_BY_VP";
        return Approver::approve(req);
    }
};

int main() {
    auto manager = std::make_shared<Manager>();
    auto director = std::make_shared<Director>();
    auto vp = std::make_shared<VP>();

    manager->set_next(director)->set_next(vp);

    assert(manager->approve({1, 500.0, "Office supplies"}) == "APPROVED_BY_MANAGER");
    assert(manager->approve({2, 5000.0, "Team conference"}) == "APPROVED_BY_DIRECTOR");
    assert(manager->approve({3, 25000.0, "Server cluster"}) == "APPROVED_BY_VP");
    assert(manager->approve({4, 100000.0, "Acquisition"}).find("DENIED") != std::string::npos);

    std::cout << "Chain of Responsibility solution verified successfully!\n";
    return 0;
}
