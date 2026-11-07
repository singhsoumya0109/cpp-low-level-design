#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>

using Context = std::unordered_set<std::string>;

class IBoolExpr {
public:
    virtual ~IBoolExpr() = default;
    virtual bool eval(const Context& ctx) const = 0;
};

class FeatureFlag : public IBoolExpr {
    std::string flag_;
public:
    explicit FeatureFlag(std::string flag) : flag_(std::move(flag)) {}
    bool eval(const Context& ctx) const override {
        return ctx.count(flag_) > 0;
    }
};

class NotExpr : public IBoolExpr {
    std::unique_ptr<IBoolExpr> child_;
public:
    explicit NotExpr(std::unique_ptr<IBoolExpr> c) : child_(std::move(c)) {}
    bool eval(const Context& ctx) const override {
        return !child_->eval(ctx);
    }
};

class AndExpr : public IBoolExpr {
    std::unique_ptr<IBoolExpr> left_, right_;
public:
    AndExpr(std::unique_ptr<IBoolExpr> l, std::unique_ptr<IBoolExpr> r)
        : left_(std::move(l)), right_(std::move(r)) {}
    bool eval(const Context& ctx) const override {
        return left_->eval(ctx) && right_->eval(ctx);
    }
};

int main() {
    // Condition: beta_user AND NOT maintenance_mode
    auto rule = std::make_unique<AndExpr>(
        std::make_unique<FeatureFlag>("beta_user"),
        std::make_unique<NotExpr>(std::make_unique<FeatureFlag>("maintenance_mode"))
    );

    Context ctx1{"beta_user"};
    Context ctx2{"beta_user", "maintenance_mode"};

    assert(rule->eval(ctx1) == true);
    assert(rule->eval(ctx2) == false);

    std::cout << "Interpreter solution verified successfully!\n";
    return 0;
}
