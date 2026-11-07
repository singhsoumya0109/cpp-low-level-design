#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

class Book;
class Electronics;

class ICartVisitor {
public:
    virtual ~ICartVisitor() = default;
    virtual void visit(const Book& b) = 0;
    virtual void visit(const Electronics& e) = 0;
};

class ICartItem {
public:
    virtual ~ICartItem() = default;
    virtual void accept(ICartVisitor& v) const = 0;
};

class Book : public ICartItem {
    double price_;
public:
    explicit Book(double p) : price_(p) {}
    double price() const { return price_; }
    void accept(ICartVisitor& v) const override { v.visit(*this); }
};

class Electronics : public ICartItem {
    double price_;
public:
    explicit Electronics(double p) : price_(p) {}
    double price() const { return price_; }
    void accept(ICartVisitor& v) const override { v.visit(*this); }
};

class TotalPriceVisitor : public ICartVisitor {
    double total_ = 0.0;
public:
    void visit(const Book& b) override { total_ += b.price(); }
    void visit(const Electronics& e) override { total_ += e.price(); }
    double total() const { return total_; }
};

int main() {
    std::vector<std::unique_ptr<ICartItem>> cart;
    cart.push_back(std::make_unique<Book>(25.0));
    cart.push_back(std::make_unique<Electronics>(150.0));

    TotalPriceVisitor calc;
    for (const auto& item : cart) item->accept(calc);

    assert(calc.total() == 175.0);
    std::cout << "Visitor solution verified successfully!\n";
    return 0;
}
