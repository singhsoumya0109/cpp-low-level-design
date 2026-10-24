#include <cassert>
#include <iostream>
#include <memory>

class IItem { public: virtual ~IItem() = default; virtual int val() const = 0; };
class SimpleItem : public IItem { public: int val() const override { return 10; } };
class BonusDecorator : public IItem {
    std::unique_ptr<IItem> item_;
public:
    explicit BonusDecorator(std::unique_ptr<IItem> i) : item_(std::move(i)) {}
    int val() const override { return item_->val() + 5; }
};

int main() {
    auto item = std::make_unique<BonusDecorator>(std::make_unique<SimpleItem>());
    assert(item->val() == 15);
    std::cout << "[TEST] ✓ Decorator unit test passed!\n";
    return 0;
}
