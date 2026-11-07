#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

class Counter {
public:
    int val = 0;
};

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class IncrementCommand : public ICommand {
    Counter& c_;
public:
    explicit IncrementCommand(Counter& c) : c_(c) {}
    void execute() override { ++c_.val; }
    void undo() override { --c_.val; }
};

int main() {
    std::cout << "[TEST] Running Command tests...\n";
    Counter c;
    auto cmd = std::make_unique<IncrementCommand>(c);

    cmd->execute();
    assert(c.val == 1);
    cmd->undo();
    assert(c.val == 0);

    std::cout << "[TEST] All Command tests PASSED!\n";
    return 0;
}
