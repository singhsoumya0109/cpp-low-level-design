#include <iostream>
#include <functional>

// Modern C++17 Template Method via Non-Virtual Interface (NVI) & Lambdas
class ExecutionTimer {
public:
    template <typename Func>
    static void execute_with_lifecycle(Func step) {
        std::cout << "[NVI] Setup: Allocating scratch buffers\n";
        step();
        std::cout << "[NVI] Teardown: Clearing scratch buffers\n";
    }
};

int main() {
    ExecutionTimer::execute_with_lifecycle([]() {
        std::cout << "   -> Running core business computation\n";
    });
    return 0;
}
