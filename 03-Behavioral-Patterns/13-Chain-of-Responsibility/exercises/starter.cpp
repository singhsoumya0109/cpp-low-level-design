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
    void set_next(std::shared_ptr<Approver> n) { next_ = std::move(n); }
    virtual bool approve(const ExpenseRequest& req) = 0;
};

// TODO: Implement Manager, Director, VP approvers

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
