#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Forward declaration of internal implementation
class Widget {
public:
    Widget(std::string name, int version);
    ~Widget(); // MUST be declared in header, defined where Impl is complete

    // Move semantics
    Widget(Widget&&) noexcept;
    Widget& operator=(Widget&&) noexcept;

    // Deep copy semantics
    Widget(const Widget&);
    Widget& operator=(const Widget&);

    void render() const;
    void add_feature(const std::string& feature);
    size_t feature_count() const;
    const std::string& name() const;

private:
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
};

// Implementation definition (normally in .cpp file)
struct Widget::Impl {
    std::string name;
    int version;
    std::vector<std::string> features;

    Impl(std::string n, int v) : name(std::move(n)), version(v) {}

    std::unique_ptr<Impl> clone() const {
        auto copy = std::make_unique<Impl>(name, version);
        copy->features = features;
        return copy;
    }
};

Widget::Widget(std::string name, int version) 
    : pimpl_(std::make_unique<Impl>(std::move(name), version)) {}

Widget::~Widget() = default;

Widget::Widget(Widget&&) noexcept = default;
Widget& Widget::operator=(Widget&&) noexcept = default;

Widget::Widget(const Widget& other) : pimpl_(other.pimpl_ ? other.pimpl_->clone() : nullptr) {}
Widget& Widget::operator=(const Widget& other) {
    if (this != &other) {
        pimpl_ = other.pimpl_ ? other.pimpl_->clone() : nullptr;
    }
    return *this;
}

void Widget::render() const {
    if (!pimpl_) return;
    std::cout << "[PImpl] Rendering " << pimpl_->name << " v" << pimpl_->version 
              << " with " << pimpl_->features.size() << " features.\n";
}

void Widget::add_feature(const std::string& feature) {
    if (pimpl_) pimpl_->features.push_back(feature);
}

size_t Widget::feature_count() const {
    return pimpl_ ? pimpl_->features.size() : 0;
}

const std::string& Widget::name() const {
    static const std::string empty;
    return pimpl_ ? pimpl_->name : empty;
}

int main() {
    std::cout << "=== Modern C++ PImpl Idiom Demo ===\n";
    Widget w1("DashboardWidget", 2);
    w1.add_feature("Real-time Metrics");
    w1.add_feature("Export to PDF");
    w1.render();

    Widget w2 = w1; // Deep copy via clone
    w2.add_feature("Dark Mode Theme");
    std::cout << "w1 feature count: " << w1.feature_count() << "\n";
    std::cout << "w2 feature count: " << w2.feature_count() << "\n";
    return 0;
}
