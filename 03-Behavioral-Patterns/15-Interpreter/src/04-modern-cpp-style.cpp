#include <iostream>
#include <variant>
#include <memory>
#include <string>

// Modern C++17 AST using std::variant and std::visit
struct IntNode { int val; };
struct AddNode;
struct MulNode;

using ASTNode = std::variant<
    IntNode,
    std::unique_ptr<AddNode>,
    std::unique_ptr<MulNode>
>;

struct AddNode {
    ASTNode left;
    ASTNode right;
};

struct MulNode {
    ASTNode left;
    ASTNode right;
};

struct Evaluator {
    int operator()(const IntNode& n) const { return n.val; }
    int operator()(const std::unique_ptr<AddNode>& n) const {
        return std::visit(Evaluator{}, n->left) + std::visit(Evaluator{}, n->right);
    }
    int operator()(const std::unique_ptr<MulNode>& n) const {
        return std::visit(Evaluator{}, n->left) * std::visit(Evaluator{}, n->right);
    }
};

int main() {
    // Expression: 3 * (4 + 5)
    ASTNode expr = std::make_unique<MulNode>(MulNode{
        IntNode{3},
        std::make_unique<AddNode>(AddNode{IntNode{4}, IntNode{5}})
    });

    int res = std::visit(Evaluator{}, expr);
    std::cout << "3 * (4 + 5) = " << res << "\n";
    return 0;
}
