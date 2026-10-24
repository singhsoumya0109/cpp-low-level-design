// 02-classic-pattern.cpp: Tree Forest Flyweight (Intrinsic vs Extrinsic state)
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// Intrinsic state: shared immutable texture & color
class TreeType {
private:
    std::string name_;
    std::string color_;
public:
    TreeType(std::string name, std::string color) : name_(std::move(name)), color_(std::move(color)) {}
    void draw(int x, int y) const {
        std::cout << "Tree [" << name_ << ", " << color_ << "] at (" << x << ", " << y << ")\n";
    }
};

class TreeFactory {
private:
    static std::unordered_map<std::string, std::shared_ptr<TreeType>> types_;
public:
    static std::shared_ptr<TreeType> getTreeType(const std::string& name, const std::string& color) {
        std::string key = name + "_" + color;
        if (types_.find(key) == types_.end()) {
            types_[key] = std::make_shared<TreeType>(name, color);
        }
        return types_[key];
    }
};
std::unordered_map<std::string, std::shared_ptr<TreeType>> TreeFactory::types_;

// Extrinsic state: specific coordinates per tree
class Tree {
private:
    int x_, y_;
    std::shared_ptr<TreeType> type_;
public:
    Tree(int x, int y, std::shared_ptr<TreeType> type) : x_(x), y_(y), type_(std::move(type)) {}
    void draw() const { type_->draw(x_, y_); }
};

int main() {
    auto pine = TreeFactory::getTreeType("Pine", "DarkGreen");
    Tree t1(10, 20, pine);
    Tree t2(15, 25, pine);
    t1.draw();
    t2.draw();
    return 0;
}
