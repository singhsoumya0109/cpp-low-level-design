// 03-real-world-example.cpp: UI Component Tree
#include <iostream>
#include <memory>
#include <vector>

class UIComponent {
public:
    virtual ~UIComponent() = default;
    virtual void render() const = 0;
};

class Button : public UIComponent {
public:
    void render() const override { std::cout << "  [Button]\n"; }
};

class Panel : public UIComponent {
private:
    std::vector<std::unique_ptr<UIComponent>> children_;
public:
    void add(std::unique_ptr<UIComponent> c) { children_.push_back(std::move(c)); }
    void render() const override {
        std::cout << "<Panel>\n";
        for (const auto& c : children_) c->render();
        std::cout << "</Panel>\n";
    }
};

int main() {
    Panel p;
    p.add(std::make_unique<Button>());
    p.add(std::make_unique<Button>());
    p.render();
    return 0;
}
