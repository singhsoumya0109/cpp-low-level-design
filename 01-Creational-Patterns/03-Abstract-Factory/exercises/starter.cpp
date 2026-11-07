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

// TODO: Implement WindowsButton, WindowsCheckbox, MacButton, MacCheckbox
// TODO: Implement IUIFactory with createButton() and createCheckbox()
// TODO: Implement WindowsUIFactory and MacUIFactory

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
