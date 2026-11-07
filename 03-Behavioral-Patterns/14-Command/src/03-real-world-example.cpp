#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Receiver: Smart Bulb
class SmartBulb {
    int brightness_ = 0;
public:
    void set_brightness(int b) {
        brightness_ = b;
        std::cout << "[SmartBulb] Brightness set to " << brightness_ << "%\n";
    }
    int get_brightness() const { return brightness_; }
};

class IRemoteCommand {
public:
    virtual ~IRemoteCommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class SetBrightnessCommand : public IRemoteCommand {
    SmartBulb& bulb_;
    int new_brightness_;
    int prev_brightness_ = 0;
public:
    SetBrightnessCommand(SmartBulb& bulb, int b)
        : bulb_(bulb), new_brightness_(b) {}

    void execute() override {
        prev_brightness_ = bulb_.get_brightness();
        bulb_.set_brightness(new_brightness_);
    }

    void undo() override {
        bulb_.set_brightness(prev_brightness_);
    }
};

class MacroCommand : public IRemoteCommand {
    std::vector<std::unique_ptr<IRemoteCommand>> commands_;
public:
    void add(std::unique_ptr<IRemoteCommand> cmd) {
        commands_.push_back(std::move(cmd));
    }

    void execute() override {
        for (auto& cmd : commands_) cmd->execute();
    }

    void undo() override {
        for (auto it = commands_.rbegin(); it != commands_.rend(); ++it) {
            (*it)->undo();
        }
    }
};

int main() {
    SmartBulb living_room, bedroom;

    auto movie_mode = std::make_unique<MacroCommand>();
    movie_mode->add(std::make_unique<SetBrightnessCommand>(living_room, 20));
    movie_mode->add(std::make_unique<SetBrightnessCommand>(bedroom, 0));

    std::cout << "Activating Movie Mode Macro:\n";
    movie_mode->execute();

    std::cout << "\nUndoing Movie Mode Macro:\n";
    movie_mode->undo();

    return 0;
}
