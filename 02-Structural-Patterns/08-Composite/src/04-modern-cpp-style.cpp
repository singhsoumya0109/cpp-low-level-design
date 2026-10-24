// 04-modern-cpp-style.cpp: Variant-based tree node
#include <iostream>
#include <variant>
#include <vector>
#include <memory>

struct FileNode { size_t size; };
struct FolderNode;
using Node = std::variant<FileNode, std::unique_ptr<FolderNode>>;
struct FolderNode { std::vector<Node> children; };

int main() {
    FolderNode root;
    root.children.push_back(FileNode{50});
    std::cout << "Variant-based tree node allocated.\n";
    return 0;
}
