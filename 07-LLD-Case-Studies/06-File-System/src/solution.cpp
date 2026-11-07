#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <sstream>

class FSNode {
protected:
    std::string name_;
public:
    explicit FSNode(std::string name) : name_(std::move(name)) {}
    virtual ~FSNode() = default;
    const std::string& name() const { return name_; }
    virtual bool is_directory() const = 0;
    virtual size_t size() const = 0;
};

class FileNode : public FSNode {
    std::string content_;
public:
    FileNode(std::string name, std::string content)
        : FSNode(std::move(name)), content_(std::move(content)) {}

    bool is_directory() const override { return false; }
    size_t size() const override { return content_.size(); }
    const std::string& content() const { return content_; }
    void write(const std::string& data) { content_ += data; }
};

class DirectoryNode : public FSNode {
    std::map<std::string, std::shared_ptr<FSNode>> children_;
public:
    explicit DirectoryNode(std::string name) : FSNode(std::move(name)) {}

    bool is_directory() const override { return true; }
    size_t size() const override {
        size_t total = 0;
        for (const auto& [_, child] : children_) total += child->size();
        return total;
    }

    void add_child(std::shared_ptr<FSNode> node) {
        children_[node->name()] = std::move(node);
    }

    std::shared_ptr<FSNode> get_child(const std::string& name) const {
        auto it = children_.find(name);
        return it != children_.end() ? it->second : nullptr;
    }

    const std::map<std::string, std::shared_ptr<FSNode>>& children() const {
        return children_;
    }
};

class InMemoryFileSystem {
    std::shared_ptr<DirectoryNode> root_ = std::make_shared<DirectoryNode>("/");

    std::vector<std::string> split_path(const std::string& path) const {
        std::vector<std::string> parts;
        std::stringstream ss(path);
        std::string token;
        while (std::getline(ss, token, '/')) {
            if (!token.empty()) parts.push_back(token);
        }
        return parts;
    }

public:
    bool mkdir(const std::string& path) {
        auto parts = split_path(path);
        auto curr = root_;
        for (const auto& part : parts) {
            auto next = curr->get_child(part);
            if (!next) {
                auto new_dir = std::make_shared<DirectoryNode>(part);
                curr->add_child(new_dir);
                curr = new_dir;
            } else if (next->is_directory()) {
                curr = std::static_pointer_cast<DirectoryNode>(next);
            } else {
                return false; // Collision with file
            }
        }
        return true;
    }

    bool create_file(const std::string& path, const std::string& content) {
        auto parts = split_path(path);
        if (parts.empty()) return false;
        std::string filename = parts.back();
        parts.pop_back();

        auto curr = root_;
        for (const auto& part : parts) {
            auto next = curr->get_child(part);
            if (!next || !next->is_directory()) return false;
            curr = std::static_pointer_cast<DirectoryNode>(next);
        }
        curr->add_child(std::make_shared<FileNode>(filename, content));
        return true;
    }

    void ls(const std::string& path) const {
        auto parts = split_path(path);
        auto curr = root_;
        for (const auto& part : parts) {
            auto next = curr->get_child(part);
            if (!next || !next->is_directory()) return;
            curr = std::static_pointer_cast<DirectoryNode>(next);
        }
        std::cout << "[ls " << path << "]:\n";
        for (const auto& [name, node] : curr->children()) {
            std::cout << "  " << (node->is_directory() ? "[DIR]  " : "[FILE] ")
                      << name << " (" << node->size() << " bytes)\n";
        }
    }
};

int main() {
    std::cout << "=== In-Memory File System Simulation ===\n";
    InMemoryFileSystem fs;
    fs.mkdir("/usr/local/bin");
    fs.create_file("/usr/local/bin/run.sh", "#!/bin/bash\necho ok");
    fs.create_file("/usr/local/readme.txt", "Hello C++17 LLD");

    fs.ls("/usr/local");
    fs.ls("/usr/local/bin");
    return 0;
}
