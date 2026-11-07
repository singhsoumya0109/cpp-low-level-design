#include <cassert>
#include <iostream>

template <typename Derived>
class Shape {
public:
    double area() const { return static_cast<const Derived*>(this)->area_impl(); }
};

class Rectangle : public Shape<Rectangle> {
    double w_, h_;
public:
    Rectangle(double w, double h) : w_(w), h_(h) {}
    double area_impl() const { return w_ * h_; }
};

template <typename Derived>
class Counter {
public:
    static size_t count() { return c_; }
protected:
    Counter() { ++c_; }
    Counter(const Counter&) { ++c_; }
    ~Counter() { --c_; }
private:
    inline static size_t c_ = 0;
};

class Node : public Counter<Node> {};

int main() {
    std::cout << "[TEST] Running CRTP tests...\n";

    // Test static dispatch
    Rectangle rect(4.0, 5.0);
    assert(rect.area() == 20.0);

    // Test instance counter
    assert(Node::count() == 0);
    {
        Node n1;
        Node n2;
        assert(Node::count() == 2);
    }
    assert(Node::count() == 0);

    std::cout << "[TEST] All CRTP tests PASSED!\n";
    return 0;
}
