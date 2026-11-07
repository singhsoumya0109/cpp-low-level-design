#include <iostream>
#include <vector>
#include <string>

// Naive Approach: Adding new export operations directly into element classes
// Every time a new format (e.g. YAML) is needed, EVERY element class must be modified!
class Element {
public:
    virtual ~Element() = default;
    virtual void export_html() const = 0;
    virtual void export_json() const = 0; // Pollution
    virtual void export_markdown() const = 0; // More pollution
};

class Paragraph : public Element {
    std::string text_ = "Hello world";
public:
    void export_html() const override { std::cout << "<p>" << text_ << "</p>\n"; }
    void export_json() const override { std::cout << "{\"type\":\"p\",\"text\":\"" << text_ << "\"}\n"; }
    void export_markdown() const override { std::cout << text_ << "\n\n"; }
};

int main() {
    Paragraph p;
    p.export_html();
    p.export_json();
    return 0;
}
