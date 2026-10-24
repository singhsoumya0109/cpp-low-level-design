// 02-classic-pattern.cpp: File System Tree via Composite Pattern
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class IFileSystemItem {
public:
    virtual ~IFileSystemItem() = default;
    virtual void print(int indent = 0) const = 0;
    virtual size_t getSize() const = 0;
};

class File : public IFileSystemItem {
private:
    std::string name_;
    size_t size_;
public:
    File(std::string name, size_t size) : name_(std::move(name)), size_(size) {}
    void print(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "📄 " << name_ << " (" << size_ << " KB)\n";
    }
    size_t getSize() const override { return size_; }
};

class Directory : public IFileSystemItem {
private:
    std::string name_;
    std::vector<std::unique_ptr<IFileSystemItem>> children_;
public:
    explicit Directory(std::string name) : name_(std::move(name)) {}

    void add(std::unique_ptr<IFileSystemItem> item) {
        children_.push_back(std::move(item));
    }

    void print(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "📁 " << name_ << "/\n";
        for (const auto& child : children_) {
            child->print(indent + 2);
        }
    }

    size_t getSize() const override {
        size_t total = 0;
        for (const auto& child : children_) total += child->getSize();
        return total;
    }
};

int main() {
    auto root = std::make_unique<Directory>("root");
    root->add(std::make_unique<File>("boot.ini", 2));

    auto docs = std::make_unique<Directory>("Documents");
    docs->add(std::make_unique<File>("resume.pdf", 120));
    docs->add(std::make_unique<File>("photo.png", 2400));
    root->add(std::move(docs));

    root->print();
    std::cout << "Total size: " << root->getSize() << " KB\n";
    return 0;
}
