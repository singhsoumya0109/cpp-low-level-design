#include <cassert>
#include <iostream>
#include <memory>
#include <string>

class IWidget { public: virtual ~IWidget() = default; virtual std::string id() const = 0; };
class AWidget : public IWidget { public: std::string id() const override { return "A"; } };
class BWidget : public IWidget { public: std::string id() const override { return "B"; } };

class IFactory { public: virtual ~IFactory() = default; virtual std::unique_ptr<IWidget> create() const = 0; };
class AFactory : public IFactory { public: std::unique_ptr<IWidget> create() const override { return std::make_unique<AWidget>(); } };

int main() {
    AFactory f;
    auto w = f.create();
    assert(w->id() == "A");
    std::cout << "[TEST] ✓ Abstract Factory test passed!\n";
    return 0;
}
