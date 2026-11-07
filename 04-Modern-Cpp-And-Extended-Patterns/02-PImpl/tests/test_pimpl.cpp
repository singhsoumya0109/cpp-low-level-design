#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Widget {
public:
    Widget(std::string name, int version);
    ~Widget();
    Widget(Widget&&) noexcept;
    Widget& operator=(Widget&&) noexcept;
    Widget(const Widget&);
    Widget& operator=(const Widget&);

    void add_feature(const std::string& feature);
    size_t feature_count() const;
    const std::string& name() const;

private:
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
};

struct Widget::Impl {
    std::string name;
    int version;
    std::vector<std::string> features;
    Impl(std::string n, int v) : name(std::move(n)), version(v) {}
    std::unique_ptr<Impl> clone() const {
        auto c = std::make_unique<Impl>(name, version);
        c->features = features;
        return c;
    }
};

Widget::Widget(std::string name, int version) : pimpl_(std::make_unique<Impl>(std::move(name), version)) {}
Widget::~Widget() = default;
Widget::Widget(Widget&&) noexcept = default;
Widget& Widget::operator=(Widget&&) noexcept = default;
Widget::Widget(const Widget& other) : pimpl_(other.pimpl_ ? other.pimpl_->clone() : nullptr) {}
Widget& Widget::operator=(const Widget& other) {
    if (this != &other) pimpl_ = other.pimpl_ ? other.pimpl_->clone() : nullptr;
    return *this;
}
void Widget::add_feature(const std::string& f) { if (pimpl_) pimpl_->features.push_back(f); }
size_t Widget::feature_count() const { return pimpl_ ? pimpl_->features.size() : 0; }
const std::string& Widget::name() const { static const std::string e; return pimpl_ ? pimpl_->name : e; }

int main() {
    std::cout << "[TEST] Running PImpl tests...\n";

    Widget w("Table", 1);
    assert(w.name() == "Table");
    assert(w.feature_count() == 0);

    w.add_feature("Sorting");
    assert(w.feature_count() == 1);

    // Deep copy test
    Widget copy = w;
    copy.add_feature("Filtering");
    assert(w.feature_count() == 1);
    assert(copy.feature_count() == 2);

    // Move test
    Widget moved = std::move(w);
    assert(moved.feature_count() == 1);

    std::cout << "[TEST] All PImpl tests PASSED!\n";
    return 0;
}
