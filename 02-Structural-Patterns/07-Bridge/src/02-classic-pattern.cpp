// 02-classic-pattern.cpp: Bridge separating Abstraction and Implementation
#include <iostream>
#include <memory>

class IRenderer {
public:
    virtual ~IRenderer() = default;
    virtual void renderCircle(float r) const = 0;
};

class DirectXRenderer : public IRenderer {
public:
    void renderCircle(float r) const override { std::cout << "DirectX circle radius " << r << "\n"; }
};

class OpenGLRenderer : public IRenderer {
public:
    void renderCircle(float r) const override { std::cout << "OpenGL circle radius " << r << "\n"; }
};

class Shape {
protected:
    std::shared_ptr<IRenderer> renderer_;
public:
    explicit Shape(std::shared_ptr<IRenderer> r) : renderer_(std::move(r)) {}
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

class Circle : public Shape {
    float r_;
public:
    Circle(float r, std::shared_ptr<IRenderer> renderer) : Shape(std::move(renderer)), r_(r) {}
    void draw() const override { renderer_->renderCircle(r_); }
};

int main() {
    auto dx = std::make_shared<DirectXRenderer>();
    auto gl = std::make_shared<OpenGLRenderer>();
    Circle c1(5.0f, dx);
    Circle c2(10.0f, gl);
    c1.draw();
    c2.draw();
    return 0;
}
