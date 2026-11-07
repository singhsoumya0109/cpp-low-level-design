#include <iostream>
#include <string>

// Naive Approach: Direct point-to-point references between all UI elements
// Button needs pointer to Textbox, Checkbox, Dialog; Checkbox needs pointer to Button, etc.
// O(N^2) tightly coupled spaghetti dependencies!
class TextBox;
class Checkbox;

class SubmitButton {
    bool enabled_ = false;
public:
    void set_enabled(bool e) { enabled_ = e; }
    void render() { std::cout << "SubmitButton is " << (enabled_ ? "ENABLED" : "DISABLED") << "\n"; }
};

class Checkbox {
    SubmitButton* btn_ = nullptr;
public:
    void set_btn(SubmitButton* b) { btn_ = b; }
    void toggle(bool checked) {
        if (btn_) btn_->set_enabled(checked);
    }
};

int main() {
    SubmitButton btn;
    Checkbox terms_box;
    terms_box.set_btn(&btn);

    btn.render();
    terms_box.toggle(true);
    btn.render();
    return 0;
}
