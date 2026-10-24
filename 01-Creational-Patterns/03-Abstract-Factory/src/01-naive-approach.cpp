// 01-naive-approach.cpp: Mixing incompatible UI components
#include <iostream>

class WinButton { public: void paint() { std::cout << "Windows Button\n"; } };
class MacButton { public: void paint() { std::cout << "Mac Button\n"; } };
class WinCheckbox { public: void paint() { std::cout << "Windows Checkbox\n"; } };
class MacCheckbox { public: void paint() { std::cout << "Mac Checkbox\n"; } };

int main() {
    // Anti-pattern: Nothing stops mixing Windows Button with Mac Checkbox!
    WinButton b;
    MacCheckbox c;
    b.paint();
    c.paint();
    return 0;
}
