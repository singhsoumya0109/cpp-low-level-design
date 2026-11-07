#include <cassert>
#include <iostream>
#include <memory>

class IExpr {
public:
    virtual ~IExpr() = default;
    virtual int evaluate() const = 0;
};

class ConstVal : public IExpr {
    int v_;
public:
    explicit ConstVal(int v) : v_(v) {}
    int evaluate() const override { return v_; }
};

class Multiply : public IExpr {
    std::unique_ptr<IExpr> l_, r_;
public:
    Multiply(std::unique_ptr<IExpr> l, std::unique_ptr<IExpr> r) : l_(std::move(l)), r_(std::move(r)) {}
    int evaluate() const override { return l_->evaluate() * r_->evaluate(); }
};

int main() {
    std::cout << "[TEST] Running Interpreter tests...\n";
    auto expr = std::make_unique<Multiply>(std::make_unique<ConstVal>(6), std::make_unique<ConstVal>(7));
    assert(expr->evaluate() == 42);
    std::cout << "[TEST] All Interpreter tests PASSED!\n";
    return 0;
}
