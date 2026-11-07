#include <iostream>
#include <string>

// Naive Approach: Violates Encapsulation
// External class directly peeks and modifies private internal state
class TextEditor {
public:
    std::string text;
    int cursor_pos = 0;
    int font_size = 12;
};

class HistoryCaretaker {
public:
    std::string saved_text;
    int saved_cursor;
    int saved_font;
    void save(const TextEditor& e) {
        saved_text = e.text;
        saved_cursor = e.cursor_pos;
        saved_font = e.font_size;
    }
    void restore(TextEditor& e) {
        e.text = saved_text;
        e.cursor_pos = saved_cursor;
        e.font_size = saved_font;
    }
};

int main() {
    TextEditor editor{"Hello", 5, 12};
    HistoryCaretaker history;
    history.save(editor);

    editor.text = "Hello World!";
    std::cout << "Edited text: " << editor.text << "\n";

    history.restore(editor);
    std::cout << "Restored text: " << editor.text << "\n";
    return 0;
}
