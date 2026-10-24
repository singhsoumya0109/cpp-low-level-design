# Composition over Inheritance in C++

> *"Favor object composition over class inheritance."* — Gang of Four (*Design Patterns: Elements of Reusable Object-Oriented Software*)

While class inheritance is a powerful OOP feature, junior developers frequently overuse it, leading to rigid, brittle class hierarchies known as the **"Fragile Base Class Problem"**.

---

## 1. The Trap of Deep Inheritance Hierarchies

Imagine modeling birds:
- `Bird` $\rightarrow$ has `fly()` method.
- `Duck` is-a `Bird` $\rightarrow$ flies.
- Now you add `Penguin`. A Penguin is a bird, but it **cannot fly**!
  - If you inherit `Penguin` from `Bird`, you are forced to throw an exception in `fly()`, violating the **Liskov Substitution Principle**.
  - If you create `FlyingBird` and `NonFlyingBird`, what happens when you introduce `Swimming`?
  - You quickly hit the **Combinatorial Class Explosion** problem:
    `FlyingSwimmingBird`, `NonFlyingSwimmingBird`, `FlyingNonSwimmingBird`...

---

## 2. Comparing the Two Approaches

| Feature | Inheritance (White-Box Reuse) | Composition (Black-Box Reuse) |
|---|---|---|
| **Coupling** | **Tight**: Child depends directly on parent's implementation details. | **Loose**: Classes interact exclusively via public interfaces. |
| **Flexibility** | **Static**: Determined at compile time. Cannot change behavior at runtime. | **Dynamic**: Can swap behaviors at runtime by injecting new strategies. |
| **Encapsulation** | **Weak**: Subclasses often access `protected` members, breaking encapsulation. | **Strong**: Internal details remain completely hidden behind interfaces. |
| **Testing** | Harder: Subclasses inherit complex base state. | Easy: Dependencies can be mocked or stubbed with dummy implementations. |

---

## 3. The Refactoring: Using Strategy & Composition

### ❌ The Brittle Inheritance Approach

```cpp
class Hero {
public:
    virtual void attack() { std::cout << "Swinging sword!\n"; }
    virtual ~Hero() = default;
};

// What if the hero picks up a bow? Or a magic staff?
// You would need to create ArcherHero, MageHero, and destroy/recreate the hero object!
class ArcherHero : public Hero {
public:
    void attack() override { std::cout << "Shooting arrow!\n"; }
};
```

### ✅ The Flexible Composition Approach

```cpp
#include <iostream>
#include <memory>

class IAttackStrategy {
public:
    virtual ~IAttackStrategy() = default;
    virtual void execute() const = 0;
};

class SwordAttack : public IAttackStrategy {
public:
    void execute() const override { std::cout << "Swinging greatsword!\n"; }
};

class BowAttack : public IAttackStrategy {
public:
    void execute() const override { std::cout << "Flipping back and shooting arrow!\n"; }
};

class MagicAttack : public IAttackStrategy {
public:
    void execute() const override { std::cout << "Casting fireball spell!\n"; }
};

// Hero HAS-A attack strategy, not IS-A
class Hero {
private:
    std::string name_;
    std::unique_ptr<IAttackStrategy> weapon_;

public:
    Hero(std::string name, std::unique_ptr<IAttackStrategy> weapon)
        : name_(std::move(name)), weapon_(std::move(weapon)) {}

    void setWeapon(std::unique_ptr<IAttackStrategy> newWeapon) {
        weapon_ = std::move(newWeapon); // Runtime behavior change!
    }

    void attack() const {
        std::cout << name_ << " attacks: ";
        weapon_->execute();
    }
};

int main() {
    Hero hero("Arthur", std::make_unique<SwordAttack>());
    hero.attack(); // Arthur attacks: Swinging greatsword!

    // Hero loots a bow mid-game:
    hero.setWeapon(std::make_unique<BowAttack>());
    hero.attack(); // Arthur attacks: Flipping back and shooting arrow!
}
```

---

## 4. When IS Inheritance Appropriate?

Inheritance is NOT evil; it is simply specialized. Use inheritance only when:
1. **LSP is 100% strictly satisfied**: The subtype can transparently replace the parent in *every* imaginable scenario.
2. **You are implementing a pure interface**: Deriving from an abstract class with only pure virtual functions (`virtual ~Interface() = default;` and `virtual void foo() = 0;`) is the standard C++ realization mechanism.
3. **Template Method Pattern**: The base class controls the algorithm skeleton, and subclasses customize specific primitive steps.

