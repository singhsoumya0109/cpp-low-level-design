#include <cassert>
#include <iostream>

class BaseWorkflow {
public:
    virtual ~BaseWorkflow() = default;
    int execute() {
        int a = step1();
        int b = step2();
        return a + b;
    }
protected:
    virtual int step1() { return 10; }
    virtual int step2() = 0;
};

class CustomWorkflow : public BaseWorkflow {
protected:
    int step2() override { return 32; }
};

int main() {
    std::cout << "[TEST] Running Template Method tests...\n";
    CustomWorkflow w;
    assert(w.execute() == 42);
    std::cout << "[TEST] All Template Method tests PASSED!\n";
    return 0;
}
