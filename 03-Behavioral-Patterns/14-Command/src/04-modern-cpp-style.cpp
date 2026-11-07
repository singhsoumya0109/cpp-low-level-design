#include <iostream>
#include <functional>
#include <vector>
#include <string>

// Modern C++17 Command using std::function closures
struct ActionCommand {
    std::function<void()> execute;
    std::function<void()> undo;
};

class ActionHistory {
    std::vector<ActionCommand> history_;
public:
    void run(ActionCommand cmd) {
        cmd.execute();
        history_.push_back(std::move(cmd));
    }

    void undo_last() {
        if (!history_.empty()) {
            history_.back().undo();
            history_.pop_back();
        }
    }
};

int main() {
    ActionHistory history;
    int counter = 0;

    auto make_add_command = [&](int delta) {
        return ActionCommand{
            [&counter, delta]() { counter += delta; std::cout << "Added " << delta << ", counter = " << counter << "\n"; },
            [&counter, delta]() { counter -= delta; std::cout << "Undid " << delta << ", counter = " << counter << "\n"; }
        };
    };

    history.run(make_add_command(10));
    history.run(make_add_command(5));

    history.undo_last();
    history.undo_last();
    return 0;
}
