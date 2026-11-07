#include <cassert>
#include <iostream>

class ElementA;
class Visitor {
public:
    virtual ~Visitor() = default;
    virtual int visit(const ElementA& a) = 0;
};

class ElementA {
public:
    int val = 99;
    int accept(Visitor& v) const { return v.visit(*this); }
};

class ConcreteVisitor : public Visitor {
public:
    int visit(const ElementA& a) override { return a.val + 1; }
};

int main() {
    std::cout << "[TEST] Running Visitor tests...\n";
    ElementA el;
    ConcreteVisitor v;
    assert(el.accept(v) == 100);
    std::cout << "[TEST] All Visitor tests PASSED!\n";
    return 0;
}
