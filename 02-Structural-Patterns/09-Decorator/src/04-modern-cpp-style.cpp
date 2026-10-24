// 04-modern-cpp-style.cpp: Template Mixin Decorators (Compile-time zero overhead)
#include <iostream>

struct BasePrinter {
    void print() const { std::cout << "Hello World"; }
};

template <typename Base>
struct BoldDecorator : Base {
    void print() const {
        std::cout << "<b>";
        Base::print();
        std::cout << "</b>";
    }
};

int main() {
    BoldDecorator<BasePrinter> p;
    p.print();
    std::cout << "\n";
    return 0;
}
