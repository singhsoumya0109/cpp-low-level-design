// 01-naive-approach.cpp: Manual copy without polymorphism
#include <iostream>
#include <string>

class Shape {
public:
    std::string type_;
};

int main() {
    Shape s1;
    s1.type_ = "Circle";
    Shape s2 = s1; // Shallow value copy; doesn't work through polymorphic base pointers!
    std::cout << "Shape: " << s2.type_ << "\n";
    return 0;
}
