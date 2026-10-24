// 04-modern-cpp-style.cpp: PImpl (Pointer to Implementation) idiom as Bridge
#include <iostream>
#include <memory>

class Widget {
private:
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
public:
    Widget();
    ~Widget();
    void draw() const;
};

struct Widget::Impl {
    void draw() const { std::cout << "Drawing Widget via PImpl\n"; }
};

Widget::Widget() : pimpl_(std::make_unique<Impl>()) {}
Widget::~Widget() = default;
void Widget::draw() const { pimpl_->draw(); }

int main() {
    Widget w;
    w.draw();
    return 0;
}
