#include <cassert>
#include <iostream>

class SubsystemA { public: int opA() const { return 10; } };
class SubsystemB { public: int opB() const { return 20; } };

class Facade {
    SubsystemA a_;
    SubsystemB b_;
public:
    int combined() const { return a_.opA() + b_.opB(); }
};

int main() {
    Facade f;
    assert(f.combined() == 30);
    std::cout << "[TEST] ✓ Facade unit test passed!\n";
    return 0;
}
