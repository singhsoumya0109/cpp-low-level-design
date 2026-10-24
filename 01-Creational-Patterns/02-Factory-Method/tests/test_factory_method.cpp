#include <cassert>
#include <iostream>
#include <memory>
#include <string>

class IButton {
public:
    virtual ~IButton() = default;
    virtual std::string render() const = 0;
};

class HtmlButton : public IButton {
public:
    std::string render() const override { return "<button>OK</button>"; }
};

class Dialog {
public:
    virtual ~Dialog() = default;
    virtual std::unique_ptr<IButton> createButton() const = 0;
};

class HtmlDialog : public Dialog {
public:
    std::unique_ptr<IButton> createButton() const override {
        return std::make_unique<HtmlButton>();
    }
};

int main() {
    HtmlDialog dlg;
    auto btn = dlg.createButton();
    assert(btn != nullptr);
    assert(btn->render() == "<button>OK</button>");
    std::cout << "[TEST] ✓ Factory Method unit tests passed!\n";
    return 0;
}
