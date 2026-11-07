#include <iostream>
#include <memory>
#include <stack>
#include <vector>

// In-Order Iterator over Binary Search Tree
struct TreeNode {
    int val;
    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;
    explicit TreeNode(int v) : val(v) {}
};

class BSTIterator {
    std::stack<const TreeNode*> stack_;

    void push_left(const TreeNode* node) {
        while (node) {
            stack_.push(node);
            node = node->left.get();
        }
    }
public:
    explicit BSTIterator(const TreeNode* root) {
        push_left(root);
    }

    bool has_next() const {
        return !stack_.empty();
    }

    int next() {
        const TreeNode* top = stack_.top();
        stack_.pop();
        if (top->right) {
            push_left(top->right.get());
        }
        return top->val;
    }
};

int main() {
    // Tree:
    //      4
    //     / \
    //    2   6
    //   / \
    //  1   3
    auto root = std::make_unique<TreeNode>(4);
    root->left = std::make_unique<TreeNode>(2);
    root->right = std::make_unique<TreeNode>(6);
    root->left->left = std::make_unique<TreeNode>(1);
    root->left->right = std::make_unique<TreeNode>(3);

    BSTIterator it(root.get());
    std::cout << "In-order BST Traversal: ";
    while (it.has_next()) {
        std::cout << it.next() << " ";
    }
    std::cout << "\n";
    return 0;
}
