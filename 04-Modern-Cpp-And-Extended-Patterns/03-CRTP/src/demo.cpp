#include <iostream>
#include <string>
#include <chrono>

// CRTP Mixin 1: Static Polymorphism Interface
template <typename Derived>
class Shape {
public:
    void draw() const {
        // Compile-time static dispatch: no vtable pointer indirection!
        static_cast<const Derived*>(this)->draw_impl();
    }
    double area() const {
        return static_cast<const Derived*>(this)->area_impl();
    }
};

class Circle : public Shape<Circle> {
public:
    explicit Circle(double r) : radius_(r) {}
    void draw_impl() const {
        std::cout << "[CRTP] Drawing Circle with radius: " << radius_ << "\n";
    }
    double area_impl() const {
        return 3.141592653589793 * radius_ * radius_;
    }
private:
    double radius_;
};

class Square : public Shape<Square> {
public:
    explicit Square(double s) : side_(s) {}
    void draw_impl() const {
        std::cout << "[CRTP] Drawing Square with side: " << side_ << "\n";
    }
    double area_impl() const {
        return side_ * side_;
    }
private:
    double side_;
};

// CRTP Mixin 2: Object Counting
template <typename Derived>
class InstanceCounter {
public:
    static size_t live_count() noexcept { return count_; }
protected:
    InstanceCounter() { ++count_; }
    InstanceCounter(const InstanceCounter&) { ++count_; }
    ~InstanceCounter() { --count_; }
private:
    inline static size_t count_ = 0;
};

class HeavyResource : public InstanceCounter<HeavyResource> {
public:
    std::string id;
    explicit HeavyResource(std::string s) : id(std::move(s)) {}
};

int main() {
    std::cout << "=== Modern C++ CRTP (Static Polymorphism) Demo ===\n";
    Circle c(5.0);
    Square s(4.0);

    c.draw();
    std::cout << "Circle Area: " << c.area() << "\n";

    s.draw();
    std::cout << "Square Area: " << s.area() << "\n";

    {
        HeavyResource r1("Res1");
        HeavyResource r2("Res2");
        std::cout << "Live HeavyResources: " << HeavyResource::live_count() << "\n";
    }
    std::cout << "Live HeavyResources after scope: " << HeavyResource::live_count() << "\n";

    return 0;
}
