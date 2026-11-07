#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Type Erasure: Polymorphism without inheritance hierarchies
// Clients can wrap ANY type that satisfies the duck-typing contract: obj.render(os)
class AnyDrawable {
public:
    template <typename T>
    AnyDrawable(T val) : pimpl_(std::make_unique<Model<T>>(std::move(val))) {}

    void draw(std::ostream& os) const {
        pimpl_->draw(os);
    }

private:
    struct Concept {
        virtual ~Concept() = default;
        virtual void draw(std::ostream& os) const = 0;
    };

    template <typename T>
    struct Model : Concept {
        T data_;
        Model(T val) : data_(std::move(val)) {}
        void draw(std::ostream& os) const override {
            data_.render(os); // duck-typing constraint
        }
    };

    std::unique_ptr<Concept> pimpl_;
};

// Independent types with NO common base class:
struct Car {
    std::string model;
    void render(std::ostream& os) const {
        os << "Car: " << model << "\n";
    }
};

struct Person {
    std::string name;
    void render(std::ostream& os) const {
        os << "Person: " << name << "\n";
    }
};

struct CustomText {
    std::string text;
    void render(std::ostream& os) const {
        os << "Text: \"" << text << "\"\n";
    }
};

int main() {
    std::cout << "=== Modern C++ Type Erasure Demo ===\n";
    std::vector<AnyDrawable> scene;
    scene.emplace_back(Car{"Tesla Model S"});
    scene.emplace_back(Person{"Alice"});
    scene.emplace_back(CustomText{"Hello World!"});

    for (const auto& item : scene) {
        item.draw(std::cout);
    }
    return 0;
}
