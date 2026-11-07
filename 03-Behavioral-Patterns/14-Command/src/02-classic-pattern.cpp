#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Receiver
class TextEditor {
    std::string content_;
public:
    void append(const std::string& text) { content_ += text; }
    void erase(size_t len) {
        if (len <= content_.size()) {
            content_.erase(content_.size() - len);
        }
    }
    const std::string& get_content() const { return content_; }
};

// Command Interface
class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// Concrete Command
class AppendCommand : public ICommand {
    TextEditor& editor_;
    std::string text_;
public:
    AppendCommand(TextEditor& editor, std::string text)
        : editor_(editor), text_(std::move(text)) {}

    void execute() override { editor_.append(text_); }
    void undo() override { editor_.erase(text_.size()); }
};

// Invoker with Undo/Redo Stacks
class HistoryManager {
    std::vector<std::unique_ptr<ICommand>> undo_stack_;
    std::vector<std::unique_ptr<ICommand>> redo_stack_;
public:
    void execute_command(std::unique_ptr<ICommand> cmd) {
        cmd->execute();
        undo_stack_.push_back(std::move(cmd));
        redo_stack_.clear();
    }

    void undo() {
        if (undo_stack_.empty()) return;
        auto cmd = std::move(undo_stack_.back());
        undo_stack_.pop_back();
        cmd->undo();
        redo_stack_.push_back(std::move(cmd));
    }

    void redo() {
        if (redo_stack_.empty()) return;
        auto cmd = std::move(redo_stack_.back());
        redo_stack_.pop_back();
        cmd->execute();
        undo_stack_.push_back(std::move(cmd));
    }
};

int main() {
    TextEditor editor;
    HistoryManager history;

    history.execute_command(std::make_unique<AppendCommand>(editor, "Design "));
    history.execute_command(std::make_unique<AppendCommand>(editor, "Patterns "));
    std::cout << "Content: " << editor.get_content() << "\n";

    history.undo();
    std::cout << "After Undo: " << editor.get_content() << "\n";

    history.redo();
    std::cout << "After Redo: " << editor.get_content() << "\n";
    return 0;
}
