#include <iostream>
#include <variant>
#include <vector>
#include <string>

// Modern C++17 Visitor via std::variant and std::visit
struct Circle { double radius; };
struct Rectangle { double width, height; };
struct Triangle { double base, height; };

using Shape = std::variant<Circle, Rectangle, Triangle>;

// In-place visitor pattern using overloaded lambdas
template <class... Ts> struct Overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> Overloaded(Ts...) -> Overloaded<Ts...>;

int main() {
    std::vector<Shape> shapes = {
        Circle{5.0},
        Rectangle{4.0, 6.0},
        Triangle{3.0, 8.0}
    };

    auto area_calculator = Overloaded{
        [](const Circle& c) { return 3.14159 * c.radius * c.radius; },
        [](const Rectangle& r) { return r.width * r.height; },
        [](const Triangle& t) { return 0.5 * t.base * t.height; }
    };

    for (const auto& shape : shapes) {
        double area = std::visit(area_calculator, shape);
        std::cout << "Shape area: " << area << "\n";
    }
    return 0;
}
