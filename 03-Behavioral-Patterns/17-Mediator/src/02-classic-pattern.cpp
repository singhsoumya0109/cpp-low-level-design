#include <iostream>
#include <memory>
#include <string>
#include <vector>

class IMediator;

class Colleague {
protected:
    IMediator* mediator_;
public:
    explicit Colleague(IMediator* m) : mediator_(m) {}
    virtual ~Colleague() = default;
};

class IMediator {
public:
    virtual ~IMediator() = default;
    virtual void notify(Colleague* sender, const std::string& event) = 0;
};

class Button : public Colleague {
    bool enabled_ = false;
public:
    using Colleague::Colleague;
    void set_enabled(bool e) { enabled_ = e; }
    bool is_enabled() const { return enabled_; }
};

class Checkbox : public Colleague {
    bool checked_ = false;
public:
    using Colleague::Colleague;
    void check() {
        checked_ = true;
        mediator_->notify(this, "check");
    }
    bool is_checked() const { return checked_; }
};

class DialogMediator : public IMediator {
public:
    Button submit_button{this};
    Checkbox agree_checkbox{this};

    void notify(Colleague* sender, const std::string& event) override {
        if (sender == &agree_checkbox && event == "check") {
            submit_button.set_enabled(true);
            std::cout << "[Mediator] Checkbox checked -> enabled submit button.\n";
        }
    }
};

int main() {
    DialogMediator dialog;
    std::cout << "Initial button state: " << (dialog.submit_button.is_enabled() ? "ENABLED" : "DISABLED") << "\n";
    dialog.agree_checkbox.check();
    std::cout << "Updated button state: " << (dialog.submit_button.is_enabled() ? "ENABLED" : "DISABLED") << "\n";
    return 0;
}
