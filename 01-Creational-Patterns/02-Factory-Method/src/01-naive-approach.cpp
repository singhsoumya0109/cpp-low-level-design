/**
 * @file 01-naive-approach.cpp
 * @brief Anti-pattern: Hardcoded instantiation and if-else ladders violating OCP.
 */
#include <iostream>
#include <string>

class Document {
public:
    virtual void open() = 0;
    virtual ~Document() = default;
};

class PdfDocument : public Document {
public:
    void open() override { std::cout << "Opening PDF document.\n"; }
};

class WordDocument : public Document {
public:
    void open() override { std::cout << "Opening Word document.\n"; }
};

// BAD: Every new document type requires modifying this client class!
class Application {
public:
    void openDocument(const std::string& type) {
        if (type == "pdf") {
            PdfDocument doc;
            doc.open();
        } else if (type == "word") {
            WordDocument doc;
            doc.open();
        } else {
            std::cout << "Unknown document type!\n";
        }
    }
};

int main() {
    Application app;
    app.openDocument("pdf");
    app.openDocument("word");
    return 0;
}
