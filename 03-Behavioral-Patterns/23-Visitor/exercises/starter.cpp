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

// TODO: Implement Book, Electronics, and TotalPriceVisitor

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
