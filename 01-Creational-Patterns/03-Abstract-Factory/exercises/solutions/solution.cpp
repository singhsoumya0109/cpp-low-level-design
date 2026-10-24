#include <iostream>
#include <memory>
class ITheme { public: virtual ~ITheme() = default; virtual void apply() = 0; };
class DarkTheme : public ITheme { public: void apply() override { std::cout << "Dark theme applied\n"; } };
int main() { auto t = std::make_unique<DarkTheme>(); t->apply(); return 0; }
