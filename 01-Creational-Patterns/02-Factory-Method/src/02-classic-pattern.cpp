/**
 * @file 02-classic-pattern.cpp
 * @brief Classic GoF Factory Method in Modern C++17 with std::unique_ptr.
 */
#include <iostream>
#include <memory>

class IDocument {
public:
    virtual ~IDocument() = default;
    virtual void open() const = 0;
};

class PdfDocument : public IDocument {
public:
    void open() const override { std::cout << "[PDF] Document rendered.\n"; }
};

class WordDocument : public IDocument {
public:
    void open() const override { std::cout << "[Word] Document rendered.\n"; }
};

// Abstract Creator defines the Factory Method
class Application {
public:
    virtual ~Application() = default;
    virtual std::unique_ptr<IDocument> createDocument() const = 0; // Factory Method

    void newDocument() const {
        auto doc = createDocument();
        doc->open();
    }
};

class PdfApplication : public Application {
public:
    std::unique_ptr<IDocument> createDocument() const override {
        return std::make_unique<PdfDocument>();
    }
};

class WordApplication : public Application {
public:
    std::unique_ptr<IDocument> createDocument() const override {
        return std::make_unique<WordDocument>();
    }
};

int main() {
    std::unique_ptr<Application> app = std::make_unique<PdfApplication>();
    app->newDocument();

    app = std::make_unique<WordApplication>();
    app->newDocument();
    return 0;
}
