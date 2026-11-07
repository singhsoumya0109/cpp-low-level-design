#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Classic Memento: State is fully encapsulated.
// Only Originator has access to Memento's private state via friend declaration.
class EditorMemento {
    friend class TextEditor;
    std::string text_;
    int cursor_;
    EditorMemento(std::string text, int cursor) : text_(std::move(text)), cursor_(cursor) {}
};

class TextEditor {
    std::string text_;
    int cursor_ = 0;
public:
    void write(const std::string& str) {
        text_ += str;
        cursor_ = static_cast<int>(text_.size());
    }

    std::unique_ptr<EditorMemento> save() const {
        return std::unique_ptr<EditorMemento>(new EditorMemento(text_, cursor_));
    }

    void restore(const EditorMemento& memento) {
        text_ = memento.text_;
        cursor_ = memento.cursor_;
    }

    const std::string& get_text() const { return text_; }
    int get_cursor() const { return cursor_; }
};

int main() {
    TextEditor editor;
    std::vector<std::unique_ptr<EditorMemento>> history;

    editor.write("Design ");
    history.push_back(editor.save());

    editor.write("Patterns in C++");
    std::cout << "Current text: " << editor.get_text() << "\n";

    editor.restore(*history.back());
    std::cout << "Restored text: " << editor.get_text() << "\n";
    return 0;
}
