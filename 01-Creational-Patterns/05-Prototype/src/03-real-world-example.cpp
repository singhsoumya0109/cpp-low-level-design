// 03-real-world-example.cpp: Monster Registry in Game Engine
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class Monster {
public:
    virtual ~Monster() = default;
    virtual std::unique_ptr<Monster> clone() const = 0;
    virtual void roar() const = 0;
};

class Dragon : public Monster {
public:
    std::unique_ptr<Monster> clone() const override { return std::make_unique<Dragon>(*this); }
    void roar() const override { std::cout << "Dragon breathes fire!\n"; }
};

class Goblin : public Monster {
public:
    std::unique_ptr<Monster> clone() const override { return std::make_unique<Goblin>(*this); }
    void roar() const override { std::cout << "Goblin screeches!\n"; }
};

class MonsterSpawner {
private:
    std::unordered_map<std::string, std::unique_ptr<Monster>> prototypes_;
public:
    void registerMonster(const std::string& key, std::unique_ptr<Monster> m) {
        prototypes_[key] = std::move(m);
    }
    std::unique_ptr<Monster> spawn(const std::string& key) {
        return prototypes_[key]->clone();
    }
};

int main() {
    MonsterSpawner spawner;
    spawner.registerMonster("dragon", std::make_unique<Dragon>());
    spawner.registerMonster("goblin", std::make_unique<Goblin>());

    auto m1 = spawner.spawn("dragon");
    auto m2 = spawner.spawn("goblin");
    m1->roar();
    m2->roar();
    return 0;
}
