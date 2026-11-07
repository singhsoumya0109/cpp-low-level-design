#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>

// Real-world: Boolean Rule Engine for User Authorization
using PermissionsContext = std::unordered_set<std::string>;

class BooleanExpression {
public:
    virtual ~BooleanExpression() = default;
    virtual bool evaluate(const PermissionsContext& ctx) const = 0;
};

class HasPermission : public BooleanExpression {
    std::string perm_;
public:
    explicit HasPermission(std::string p) : perm_(std::move(p)) {}
    bool evaluate(const PermissionsContext& ctx) const override {
        return ctx.find(perm_) != ctx.end();
    }
};

class AndExpression : public BooleanExpression {
    std::unique_ptr<BooleanExpression> left_, right_;
public:
    AndExpression(std::unique_ptr<BooleanExpression> l, std::unique_ptr<BooleanExpression> r)
        : left_(std::move(l)), right_(std::move(r)) {}

    bool evaluate(const PermissionsContext& ctx) const override {
        return left_->evaluate(ctx) && right_->evaluate(ctx);
    }
};

class OrExpression : public BooleanExpression {
    std::unique_ptr<BooleanExpression> left_, right_;
public:
    OrExpression(std::unique_ptr<BooleanExpression> l, std::unique_ptr<BooleanExpression> r)
        : left_(std::move(l)), right_(std::move(r)) {}

    bool evaluate(const PermissionsContext& ctx) const override {
        return left_->evaluate(ctx) || right_->evaluate(ctx);
    }
};

int main() {
    // Rule: (can_edit AND can_publish) OR is_admin
    auto rule = std::make_unique<OrExpression>(
        std::make_unique<AndExpression>(
            std::make_unique<HasPermission>("can_edit"),
            std::make_unique<HasPermission>("can_publish")
        ),
        std::make_unique<HasPermission>("is_admin")
    );

    PermissionsContext editor_perms{"can_edit", "can_publish"};
    PermissionsContext viewer_perms{"can_view"};
    PermissionsContext admin_perms{"is_admin"};

    std::cout << "Editor allowed: " << std::boolalpha << rule->evaluate(editor_perms) << "\n";
    std::cout << "Viewer allowed: " << std::boolalpha << rule->evaluate(viewer_perms) << "\n";
    std::cout << "Admin allowed: " << std::boolalpha << rule->evaluate(admin_perms) << "\n";
    return 0;
}
