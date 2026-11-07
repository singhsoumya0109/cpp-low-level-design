#include <iostream>
#include <string>
#include <vector>

// Modern C++17 Memento: Value-semantic immutable snapshot token
struct EditorSnapshot {
    std::string text;
    size_t cursor;
};

class ModernEditor {
    std::string text_;
    size_t cursor_ = 0;
public:
    void type(const std::string& str) {
        text_ += str;
        cursor_ = text_.size();
    }

    EditorSnapshot take_snapshot() const {
        return EditorSnapshot{text_, cursor_};
    }

    void restore(EditorSnapshot snapshot) {
        text_ = std::move(snapshot.text);
        cursor_ = snapshot.cursor;
    }

    const std::string& text() const { return text_; }
};

int main() {
    ModernEditor editor;
    std::vector<EditorSnapshot> history;

    editor.type("Modern C++17");
    history.push_back(editor.take_snapshot());

    editor.type(" adds exciting features!");
    std::cout << "Text: " << editor.text() << "\n";

    editor.restore(std::move(history.back()));
    history.pop_back();
    std::cout << "After Rollback: " << editor.text() << "\n";
    return 0;
}
