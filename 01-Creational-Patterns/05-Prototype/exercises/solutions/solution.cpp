#include <cassert>
#include <iostream>
#include <memory>
#include <string>

class Monster {
public:
    virtual ~Monster() = default;
    virtual std::unique_ptr<Monster> clone() const = 0;
    virtual int get_health() const = 0;
    virtual void take_damage(int dmg) = 0;
    virtual std::string get_name() const = 0;
};

class Goblin : public Monster {
    std::string name_;
    int health_;
public:
    Goblin(std::string name, int health) : name_(std::move(name)), health_(health) {}
    std::unique_ptr<Monster> clone() const override {
        return std::make_unique<Goblin>(*this);
    }
    int get_health() const override { return health_; }
    void take_damage(int dmg) override { health_ -= dmg; }
    std::string get_name() const override { return name_; }
};

int main() {
    auto prototype_goblin = std::make_unique<Goblin>("Standard Goblin", 50);

    auto spawn1 = prototype_goblin->clone();
    auto spawn2 = prototype_goblin->clone();

    spawn1->take_damage(20);

    assert(prototype_goblin->get_health() == 50);
    assert(spawn1->get_health() == 30);
    assert(spawn2->get_health() == 50);

    std::cout << "Prototype solution verified successfully!\n";
    return 0;
}
