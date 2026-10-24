// 04-modern-cpp-style.cpp: Template Policy-based Abstract Factory (Zero Virtual Table Overhead)
#include <iostream>

struct ModernWindows {
    static void renderButton() { std::cout << "[Modern Win11] Rounded Fluent Button\n"; }
    static void renderCheckbox() { std::cout << "[Modern Win11] Toggle Switch Checkbox\n"; }
};

struct ModernMac {
    static void renderButton() { std::cout << "[Modern macOS] Aqua Vibrant Button\n"; }
    static void renderCheckbox() { std::cout << "[Modern macOS] Segmented Control Checkbox\n"; }
};

template <typename PlatformPolicy>
class ApplicationView {
public:
    void render() {
        PlatformPolicy::renderButton();
        PlatformPolicy::renderCheckbox();
    }
};

int main() {
    ApplicationView<ModernMac> macApp;
    macApp.render();
    return 0;
}
