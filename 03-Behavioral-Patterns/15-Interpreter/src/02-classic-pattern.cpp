#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>

using Context = std::unordered_map<std::string, int>;

class Expression {
public:
    virtual ~Expression() = default;
    virtual int interpret(const Context& ctx) const = 0;
};

class Number : public Expression {
    int value_;
public:
    explicit Number(int v) : value_(v) {}
    int interpret(const Context&) const override { return value_; }
};

class Variable : public Expression {
    std::string name_;
public:
    explicit Variable(std::string name) : name_(std::move(name)) {}
    int interpret(const Context& ctx) const override {
        auto it = ctx.find(name_);
        return (it != ctx.end()) ? it->second : 0;
    }
};

class Add : public Expression {
    std::unique_ptr<Expression> left_, right_;
public:
    Add(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
        : left_(std::move(l)), right_(std::move(r)) {}

    int interpret(const Context& ctx) const override {
        return left_->interpret(ctx) + right_->interpret(ctx);
    }
};

class Subtract : public Expression {
    std::unique_ptr<Expression> left_, right_;
public:
    Subtract(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
        : left_(std::move(l)), right_(std::move(r)) {}

    int interpret(const Context& ctx) const override {
        return left_->interpret(ctx) - right_->interpret(ctx);
    }
};

int main() {
    // Expression: (x + 15) - y
    auto expr = std::make_unique<Subtract>(
        std::make_unique<Add>(
            std::make_unique<Variable>("x"),
            std::make_unique<Number>(15)
        ),
        std::make_unique<Variable>("y")
    );

    Context ctx{{"x", 25}, {"y", 10}};
    std::cout << "Result of (x + 15) - y with x=25, y=10: " << expr->interpret(ctx) << "\n";
    return 0;
}
