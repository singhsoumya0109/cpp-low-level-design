// 02-classic-pattern.cpp: Virtual Copy Constructor (clone idiom)
#include <iostream>
#include <memory>
#include <string>

class IShape {
public:
    virtual ~IShape() = default;
    virtual std::unique_ptr<IShape> clone() const = 0; // Virtual Copy Constructor
    virtual void draw() const = 0;
};

class Circle : public IShape {
private:
    double radius_;
public:
    explicit Circle(double r) : radius_(r) {}
    std::unique_ptr<IShape> clone() const override {
        return std::make_unique<Circle>(*this); // Invokes copy ctor
    }
    void draw() const override { std::cout << "Drawing Circle of radius " << radius_ << "\n"; }
};

int main() {
    std::unique_ptr<IShape> original = std::make_unique<Circle>(5.0);
    auto replica = original->clone();
    original->draw();
    replica->draw();
    return 0;
}
