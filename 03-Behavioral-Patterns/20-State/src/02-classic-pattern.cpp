#include <iostream>
#include <memory>
#include <string>

class Document;

class IDocumentState {
public:
    virtual ~IDocumentState() = default;
    virtual void edit(Document& doc, const std::string& text) = 0;
    virtual void submit_review(Document& doc) = 0;
    virtual void publish(Document& doc) = 0;
    virtual std::string get_name() const = 0;
};

class Document {
    std::unique_ptr<IDocumentState> state_;
    std::string content_;
public:
    explicit Document(std::unique_ptr<IDocumentState> initial_state);
    void change_state(std::unique_ptr<IDocumentState> state) {
        state_ = std::move(state);
    }
    void edit(const std::string& text) { state_->edit(*this, text); }
    void submit_review() { state_->submit_review(*this); }
    void publish() { state_->publish(*this); }

    void append_content(const std::string& text) { content_ += text; }
    const std::string& get_content() const { return content_; }
    std::string get_state_name() const { return state_->get_name(); }
};

class PublishedState : public IDocumentState {
public:
    void edit(Document&, const std::string&) override {
        std::cout << "[Published] Cannot edit a published document!\n";
    }
    void submit_review(Document&) override {
        std::cout << "[Published] Document is already published.\n";
    }
    void publish(Document&) override {
        std::cout << "[Published] Document is already published.\n";
    }
    std::string get_name() const override { return "PUBLISHED"; }
};

class ReviewState : public IDocumentState {
public:
    void edit(Document&, const std::string&) override {
        std::cout << "[Review] Document under review cannot be modified.\n";
    }
    void submit_review(Document&) override {
        std::cout << "[Review] Already under review.\n";
    }
    void publish(Document& doc) override;
    std::string get_name() const override { return "IN_REVIEW"; }
};

class DraftState : public IDocumentState {
public:
    void edit(Document& doc, const std::string& text) override {
        doc.append_content(text);
        std::cout << "[Draft] Appended text. Content: " << doc.get_content() << "\n";
    }
    void submit_review(Document& doc) override {
        std::cout << "[Draft] Submitting to review state.\n";
        doc.change_state(std::make_unique<ReviewState>());
    }
    void publish(Document&) override {
        std::cout << "[Draft] Cannot directly publish from draft. Must submit review first.\n";
    }
    std::string get_name() const override { return "DRAFT"; }
};

void ReviewState::publish(Document& doc) {
    std::cout << "[Review] Approved! Moving to Published state.\n";
    doc.change_state(std::make_unique<PublishedState>());
}

Document::Document(std::unique_ptr<IDocumentState> initial_state)
    : state_(std::move(initial_state)) {}

int main() {
    Document doc(std::make_unique<DraftState>());
    doc.edit("Initial chapter draft. ");
    doc.publish(); // Blocked
    doc.submit_review(); // Draft -> Review
    doc.edit("New edits"); // Blocked
    doc.publish(); // Review -> Published
    return 0;
}
