#include <iostream>
#include <string>

// Naive Approach: UI Buttons directly modify document text
// Impossible to support Undo/Redo or macro actions cleanly
class Document {
public:
    std::string text;
};

class InsertButton {
public:
    void click(Document& doc, const std::string& str) {
        doc.text += str;
        // No way to undo!
    }
};

class DeleteButton {
public:
    void click(Document& doc, size_t count) {
        if (doc.text.size() >= count) {
            doc.text.erase(doc.text.size() - count);
        }
    }
};

int main() {
    Document doc;
    InsertButton ib;
    ib.click(doc, "Hello ");
    ib.click(doc, "World!");
    std::cout << "Doc: " << doc.text << "\n";
    return 0;
}
