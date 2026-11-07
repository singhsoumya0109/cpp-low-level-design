#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Paragraph;
class Heading;

class IVisitor {
public:
    virtual ~IVisitor() = default;
    virtual void visit_paragraph(const Paragraph& p) = 0;
    virtual void visit_heading(const Heading& h) = 0;
};

class IDocumentNode {
public:
    virtual ~IDocumentNode() = default;
    virtual void accept(IVisitor& visitor) const = 0;
};

class Paragraph : public IDocumentNode {
    std::string text_;
public:
    explicit Paragraph(std::string t) : text_(std::move(t)) {}
    const std::string& get_text() const { return text_; }
    void accept(IVisitor& visitor) const override {
        visitor.visit_paragraph(*this);
    }
};

class Heading : public IDocumentNode {
    std::string text_;
    int level_;
public:
    Heading(std::string t, int lvl) : text_(std::move(t)), level_(lvl) {}
    const std::string& get_text() const { return text_; }
    int get_level() const { return level_; }
    void accept(IVisitor& visitor) const override {
        visitor.visit_heading(*this);
    }
};

class HTMLVisitor : public IVisitor {
public:
    void visit_paragraph(const Paragraph& p) override {
        std::cout << "<p>" << p.get_text() << "</p>\n";
    }
    void visit_heading(const Heading& h) override {
        std::cout << "<h" << h.get_level() << ">" << h.get_text() << "</h" << h.get_level() << ">\n";
    }
};

class MarkdownVisitor : public IVisitor {
public:
    void visit_paragraph(const Paragraph& p) override {
        std::cout << p.get_text() << "\n\n";
    }
    void visit_heading(const Heading& h) override {
        std::cout << std::string(h.get_level(), '#') << " " << h.get_text() << "\n\n";
    }
};

int main() {
    std::vector<std::unique_ptr<IDocumentNode>> doc;
    doc.push_back(std::make_unique<Heading>("Design Patterns", 1));
    doc.push_back(std::make_unique<Paragraph>("The Visitor pattern provides double dispatch."));

    HTMLVisitor html;
    std::cout << "--- HTML Export ---\n";
    for (const auto& node : doc) node->accept(html);

    MarkdownVisitor md;
    std::cout << "\n--- Markdown Export ---\n";
    for (const auto& node : doc) node->accept(md);

    return 0;
}
