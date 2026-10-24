#include <cassert>
#include <iostream>
#include <memory>
#include <unordered_map>

class Flyweight {
    int id_;
public:
    explicit Flyweight(int id) : id_(id) {}
    int getId() const { return id_; }
};

class FlyweightFactory {
    std::unordered_map<int, std::shared_ptr<Flyweight>> pool_;
public:
    std::shared_ptr<Flyweight> get(int id) {
        if (!pool_[id]) pool_[id] = std::make_shared<Flyweight>(id);
        return pool_[id];
    }
};

int main() {
    FlyweightFactory factory;
    auto f1 = factory.get(1);
    auto f2 = factory.get(1);
    assert(f1 == f2);
    std::cout << "[TEST] ✓ Flyweight unit test passed!\n";
    return 0;
}
