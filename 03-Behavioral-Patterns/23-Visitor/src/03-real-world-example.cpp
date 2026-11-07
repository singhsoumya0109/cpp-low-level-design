#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Real-world: Compiler Abstract Syntax Tree (AST) Type Checking & Code Gen
class NumberNode;
class BinaryOpNode;

class IASTVisitor {
public:
    virtual ~IASTVisitor() = default;
    virtual void visit(const NumberNode& node) = 0;
    virtual void visit(const BinaryOpNode& node) = 0;
};

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void accept(IASTVisitor& visitor) const = 0;
};

class NumberNode : public ASTNode {
public:
    int value;
    explicit NumberNode(int v) : value(v) {}
    void accept(IASTVisitor& visitor) const override { visitor.visit(*this); }
};

class BinaryOpNode : public ASTNode {
public:
    char op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    BinaryOpNode(char o, std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r)
        : op(o), left(std::move(l)), right(std::move(r)) {}
    void accept(IASTVisitor& visitor) const override { visitor.visit(*this); }
};

class PrettyPrintVisitor : public IASTVisitor {
public:
    void visit(const NumberNode& n) override {
        std::cout << n.value;
    }
    void visit(const BinaryOpNode& b) override {
        std::cout << "(";
        b.left->accept(*this);
        std::cout << " " << b.op << " ";
        b.right->accept(*this);
        std::cout << ")";
    }
};

int main() {
    // AST: (10 + (2 * 5))
    auto ast = std::make_unique<BinaryOpNode>(
        '+',
        std::make_unique<NumberNode>(10),
        std::make_unique<BinaryOpNode>('*', std::make_unique<NumberNode>(2), std::make_unique<NumberNode>(5))
    );

    PrettyPrintVisitor printer;
    std::cout << "Pretty printed expression: ";
    ast->accept(printer);
    std::cout << "\n";
    return 0;
}
