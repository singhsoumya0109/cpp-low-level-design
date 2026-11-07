#include <cassert>
#include <iostream>
#include <memory>
#include <string>

class IButton {
public:
    virtual ~IButton() = default;
    virtual std::string render() const = 0;
};

class ICheckbox {
public:
    virtual ~ICheckbox() = default;
    virtual std::string render() const = 0;
};

class WindowsButton : public IButton {
public:
    std::string render() const override { return "[Windows Button]"; }
};

class WindowsCheckbox : public ICheckbox {
public:
    std::string render() const override { return "[Windows Checkbox]"; }
};

class MacButton : public IButton {
public:
    std::string render() const override { return "[Mac Button]"; }
};

class MacCheckbox : public ICheckbox {
public:
    std::string render() const override { return "[Mac Checkbox]"; }
};

class IUIFactory {
public:
    virtual ~IUIFactory() = default;
    virtual std::unique_ptr<IButton> create_button() const = 0;
    virtual std::unique_ptr<ICheckbox> create_checkbox() const = 0;
};

class WindowsUIFactory : public IUIFactory {
public:
    std::unique_ptr<IButton> create_button() const override {
        return std::make_unique<WindowsButton>();
    }
    std::unique_ptr<ICheckbox> create_checkbox() const override {
        return std::make_unique<WindowsCheckbox>();
    }
};

class MacUIFactory : public IUIFactory {
public:
    std::unique_ptr<IButton> create_button() const override {
        return std::make_unique<MacButton>();
    }
    std::unique_ptr<ICheckbox> create_checkbox() const override {
        return std::make_unique<MacCheckbox>();
    }
};

int main() {
    auto win_factory = std::make_unique<WindowsUIFactory>();
    auto mac_factory = std::make_unique<MacUIFactory>();

    auto wb = win_factory->create_button();
    auto wc = win_factory->create_checkbox();
    assert(wb->render() == "[Windows Button]");
    assert(wc->render() == "[Windows Checkbox]");

    auto mb = mac_factory->create_button();
    auto mc = mac_factory->create_checkbox();
    assert(mb->render() == "[Mac Button]");
    assert(mc->render() == "[Mac Checkbox]");

    std::cout << "Abstract Factory solution verified successfully!\n";
    return 0;
}
