// 04-modern-cpp-style.cpp: CRTP Cloneable Helper (Boilerplate-free cloning)
#include <iostream>
#include <memory>

class BaseEntity {
public:
    virtual ~BaseEntity() = default;
    virtual std::unique_ptr<BaseEntity> clone() const = 0;
};

template <typename Derived>
class Cloneable : public BaseEntity {
public:
    std::unique_ptr<BaseEntity> clone() const override {
        return std::make_unique<Derived>(static_cast<const Derived&>(*this));
    }
};

class Soldier : public Cloneable<Soldier> {
public:
    void march() const { std::cout << "Soldier marching into battle.\n"; }
};

int main() {
    std::unique_ptr<BaseEntity> b = std::make_unique<Soldier>();
    auto c = b->clone();
    static_cast<Soldier*>(c.get())->march();
    return 0;
}
