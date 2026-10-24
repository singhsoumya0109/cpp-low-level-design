#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

class IComponent { public: virtual ~IComponent() = default; virtual int count() const = 0; };
class Leaf : public IComponent { public: int count() const override { return 1; } };
class Composite : public IComponent {
    std::vector<std::unique_ptr<IComponent>> children_;
public:
    void add(std::unique_ptr<IComponent> c) { children_.push_back(std::move(c)); }
    int count() const override {
        int sum = 0;
        for (const auto& c : children_) sum += c->count();
        return sum;
    }
};

int main() {
    Composite comp;
    comp.add(std::make_unique<Leaf>());
    comp.add(std::make_unique<Leaf>());
    assert(comp.count() == 2);
    std::cout << "[TEST] ✓ Composite unit test passed!\n";
    return 0;
}
