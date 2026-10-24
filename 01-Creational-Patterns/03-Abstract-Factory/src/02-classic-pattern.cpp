// 02-classic-pattern.cpp: Families of UI widgets via Abstract Factory
#include <iostream>
#include <memory>

class IButton { public: virtual ~IButton() = default; virtual void render() const = 0; };
class ICheckbox { public: virtual ~ICheckbox() = default; virtual void render() const = 0; };

class WinButton : public IButton { public: void render() const override { std::cout << "[Windows] Button\n"; } };
class WinCheckbox : public ICheckbox { public: void render() const override { std::cout << "[Windows] Checkbox\n"; } };

class MacButton : public IButton { public: void render() const override { std::cout << "[Mac] Button\n"; } };
class MacCheckbox : public ICheckbox { public: void render() const override { std::cout << "[Mac] Checkbox\n"; } };

class IUIFactory {
public:
    virtual ~IUIFactory() = default;
    virtual std::unique_ptr<IButton> createButton() const = 0;
    virtual std::unique_ptr<ICheckbox> createCheckbox() const = 0;
};

class WinFactory : public IUIFactory {
public:
    std::unique_ptr<IButton> createButton() const override { return std::make_unique<WinButton>(); }
    std::unique_ptr<ICheckbox> createCheckbox() const override { return std::make_unique<WinCheckbox>(); }
};

class MacFactory : public IUIFactory {
public:
    std::unique_ptr<IButton> createButton() const override { return std::make_unique<MacButton>(); }
    std::unique_ptr<ICheckbox> createCheckbox() const override { return std::make_unique<MacCheckbox>(); }
};

int main() {
    std::unique_ptr<IUIFactory> factory = std::make_unique<MacFactory>();
    auto btn = factory->createButton();
    auto chk = factory->createCheckbox();
    btn->render();
    chk->render();
    return 0;
}
