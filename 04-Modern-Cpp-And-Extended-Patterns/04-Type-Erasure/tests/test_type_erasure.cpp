#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class AnyRenderable {
public:
    template <typename T>
    AnyRenderable(T val) : pimpl_(std::make_unique<Model<T>>(std::move(val))) {}
    std::string render() const { return pimpl_->render(); }
private:
    struct Concept {
        virtual ~Concept() = default;
        virtual std::string render() const = 0;
    };
    template <typename T>
    struct Model : Concept {
        T data_;
        Model(T val) : data_(std::move(val)) {}
        std::string render() const override { return data_.to_str(); }
    };
    std::unique_ptr<Concept> pimpl_;
};

struct IntItem {
    int v;
    std::string to_str() const { return std::to_string(v); }
};

struct StringItem {
    std::string s;
    std::string to_str() const { return s; }
};

int main() {
    std::cout << "[TEST] Running Type Erasure tests...\n";

    std::vector<AnyRenderable> items;
    items.emplace_back(IntItem{42});
    items.emplace_back(StringItem{"test"});

    assert(items[0].render() == "42");
    assert(items[1].render() == "test");

    std::cout << "[TEST] All Type Erasure tests PASSED!\n";
    return 0;
}
