# SOLID Principles in Modern C++

The SOLID principles are the bedrock of maintainable, extensible object-oriented design. In C++, understanding SOLID requires pairing the conceptual rules with **modern C++ ownership, interfaces, and zero-overhead abstractions**.

---

## The 5 Principles at a Glance

| Letter | Principle | Core Idea | Modern C++ Mechanism |
|:---:|---|---|---|
| **S** | **Single Responsibility Principle (SRP)** | A class should have only one reason to change. | Small, decoupled classes; free functions for utilities. |
| **O** | **Open/Closed Principle (OCP)** | Open for extension, closed for modification. | Pure virtual interfaces (`std::unique_ptr<Interface>`), Strategy pattern, or templates. |
| **L** | **Liskov Substitution Principle (LSP)** | Subtypes must be substitutable for their base types without altering correctness. | Strict adherence to pre/post conditions and class invariants. |
| **I** | **Interface Segregation Principle (ISP)** | Clients should not be forced to depend on methods they do not use. | Multiple inheritance of small, granular abstract base classes. |
| **D** | **Dependency Inversion Principle (DIP)** | Depend on abstractions, not on concrete implementations. | Constructor injection of abstract interfaces via smart pointers. |

---

## 1. Single Responsibility Principle (SRP)

> *"A class should have one, and only one, reason to change."* — Robert C. Martin

### ❌ The Anti-Pattern (God Class)
A `UserAccount` class that handles business validation, database persistence, and email notification.

```cpp
// BAD: Violates SRP. 3 reasons to change: business rules, DB schema, or email provider.
class UserAccount {
public:
    void registerUser(const std::string& email, const std::string& password) {
        // 1. Validation logic
        if (email.find('@') == std::string::npos) throw std::invalid_argument("Invalid email");

        // 2. Database logic
        std::cout << "INSERT INTO users VALUES ('" << email << "');\n";

        // 3. Email notification logic
        std::cout << "Sending welcome email via SMTP server...\n";
    }
};
```

### ✅ The Refactored Solution (Separation of Concerns)
Break the responsibilities into dedicated classes and coordinate them.

```cpp
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

// Responsibility 1: Validation
class UserValidator {
public:
    static void validate(const std::string& email, const std::string& password) {
        if (email.find('@') == std::string::npos) {
            throw std::invalid_argument("Invalid email format");
        }
        if (password.length() < 8) {
            throw std::invalid_argument("Password must be at least 8 characters");
        }
    }
};

// Responsibility 2: Persistence interface
class IUserRepository {
public:
    virtual ~IUserRepository() = default;
    virtual void save(const std::string& email) = 0;
};

class SqlUserRepository : public IUserRepository {
public:
    void save(const std::string& email) override {
        std::cout << "Saving user '" << email << "' to SQL Database.\n";
    }
};

// Responsibility 3: Notification interface
class INotificationService {
public:
    virtual ~INotificationService() = default;
    virtual void sendWelcomeEmail(const std::string& email) = 0;
};

class SmtpNotificationService : public INotificationService {
public:
    void sendWelcomeEmail(const std::string& email) override {
        std::cout << "Dispatching welcome email to " << email << " via SMTP.\n";
    }
};

// Coordinator: Sole reason to change is workflow orchestration
class UserService {
private:
    std::shared_ptr<IUserRepository> repo_;
    std::shared_ptr<INotificationService> notifier_;

public:
    UserService(std::shared_ptr<IUserRepository> repo,
                std::shared_ptr<INotificationService> notifier)
        : repo_(std::move(repo)), notifier_(std::move(notifier)) {}

    void registerUser(const std::string& email, const std::string& password) {
        UserValidator::validate(email, password);
        repo_->save(email);
        notifier_->sendWelcomeEmail(email);
    }
};
```

---

## 2. Open/Closed Principle (OCP)

> *"Software entities (classes, modules, functions, etc.) should be open for extension, but closed for modification."*

### ❌ The Anti-Pattern (Switch / If-Else Ladder)
Adding a new payment method requires modifying the existing `PaymentProcessor` class, risking regressions.

```cpp
// BAD: Violates OCP. Adding 'Crypto' means modifying this function.
enum class PaymentType { CreditCard, PayPal, Crypto };

class BadPaymentProcessor {
public:
    void process(PaymentType type, double amount) {
        if (type == PaymentType::CreditCard) {
            std::cout << "Processing $" << amount << " via Credit Card.\n";
        } else if (type == PaymentType::PayPal) {
            std::cout << "Processing $" << amount << " via PayPal.\n";
        } else if (type == PaymentType::Crypto) {
            std::cout << "Processing $" << amount << " via Crypto.\n";
        }
    }
};
```

### ✅ The Refactored Solution (Strategy / Polymorphic Extension)
Extend functionality by adding new classes without editing tested existing code.

```cpp
#include <iostream>
#include <memory>

class IPaymentStrategy {
public:
    virtual ~IPaymentStrategy() = default;
    virtual void pay(double amount) = 0;
};

class CreditCardPayment : public IPaymentStrategy {
public:
    void pay(double amount) override {
        std::cout << "Paid $" << amount << " using Credit Card.\n";
    }
};

class PayPalPayment : public IPaymentStrategy {
public:
    void pay(double amount) override {
        std::cout << "Paid $" << amount << " using PayPal.\n";
    }
};

// Adding Crypto requires ZERO edits to existing code:
class CryptoPayment : public IPaymentStrategy {
public:
    void pay(double amount) override {
        std::cout << "Paid $" << amount << " using Bitcoin on Lightning Network.\n";
    }
};

class PaymentProcessor {
public:
    void executePayment(const IPaymentStrategy& strategy, double amount) {
        strategy.pay(amount);
    }
};
```

---

## 3. Liskov Substitution Principle (LSP)

> *"Let $\Phi(x)$ be a property provable about objects $x$ of type $T$. Then $\Phi(y)$ should be true for objects $y$ of type $S$ where $S$ is a subtype of $T$."* — Barbara Liskov

Subtypes must preserve the **contract** of the parent class:
1. **Preconditions cannot be strengthened** in a subtype (the child cannot require more strict input conditions than the parent).
2. **Postconditions cannot be weakened** in a subtype (the child must provide at least as much guarantee as the parent).
3. **Invariants must be preserved** in a subtype (class internal consistency guarantees remain true).
4. **Historical constraints must be preserved** (an immutable parent cannot have a mutable child).

### ❌ The Classic Violation: Rectangle vs. Square

```cpp
// BAD: Square inherits Rectangle but violates the rectangle's postcondition
class Rectangle {
protected:
    int width_{0};
    int height_{0};

public:
    virtual ~Rectangle() = default;
    virtual void setWidth(int w) { width_ = w; }
    virtual void setHeight(int h) { height_ = h; }
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    int getArea() const { return width_ * height_; }
};

class Square : public Rectangle {
public:
    void setWidth(int w) override {
        width_ = w;
        height_ = w; // Side effect! Violates Rectangle's independence contract
    }
    void setHeight(int h) override {
        width_ = h;
        height_ = h;
    }
};

// Client code that breaks with Square:
void resizeClient(Rectangle& r) {
    r.setWidth(10);
    r.setHeight(5);
    // Invariant for any Rectangle: width is 10, height is 5, area is 50.
    // If r is Square, width was overwritten to 5! Area is 25!
    assert(r.getArea() == 50); // FAILS FOR SQUARE!
}
```

### ✅ The Refactored Solution (Common Abstraction)
A Square is NOT a behavioral subtype of a mutable Rectangle. Separate their hierarchies or use a read-only `IShape`.

```cpp
class IShape {
public:
    virtual ~IShape() = default;
    virtual int getArea() const = 0;
};

class Rectangle : public IShape {
private:
    int width_;
    int height_;
public:
    Rectangle(int w, int h) : width_(w), height_(h) {}
    int getArea() const override { return width_ * height_; }
};

class Square : public IShape {
private:
    int side_;
public:
    explicit Square(int side) : side_(side) {}
    int getArea() const override { return side_ * side_; }
};
```

---

## 4. Interface Segregation Principle (ISP)

> *"Clients should not be forced to depend on methods they do not use."*

### ❌ The Anti-Pattern (Fat / Bloated Interface)

```cpp
// BAD: Fat interface forcing implementers into dummy/throwing stubs
class IMultiFunctionPrinter {
public:
    virtual ~IMultiFunctionPrinter() = default;
    virtual void print() = 0;
    virtual void scan() = 0;
    virtual void fax() = 0;
};

class BasicPrinter : public IMultiFunctionPrinter {
public:
    void print() override { std::cout << "Printing...\n"; }
    void scan() override { throw std::logic_error("Scan not supported!"); } // Violates ISP & LSP!
    void fax() override { throw std::logic_error("Fax not supported!"); }
};
```

### ✅ The Refactored Solution (Role Interfaces & Multiple Inheritance)

In C++, classes can inherit from multiple pure abstract interfaces with zero penalty.

```cpp
class IPrinter {
public:
    virtual ~IPrinter() = default;
    virtual void print() = 0;
};

class IScanner {
public:
    virtual ~IScanner() = default;
    virtual void scan() = 0;
};

class IFax {
public:
    virtual ~IFax() = default;
    virtual void fax() = 0;
};

// Basic Printer only depends on what it can do
class SimplePrinter : public IPrinter {
public:
    void print() override { std::cout << "Simple printing.\n"; }
};

// Enterprise Photocopier implements multiple interfaces
class AllInOneMachine : public IPrinter, public IScanner, public IFax {
public:
    void print() override { std::cout << "All-in-one print.\n"; }
    void scan() override { std::cout << "All-in-one scan.\n"; }
    void fax() override { std::cout << "All-in-one fax.\n"; }
};
```

---

## 5. Dependency Inversion Principle (DIP)

> *"1. High-level modules should not depend on low-level modules. Both should depend on abstractions.*  
> *2. Abstractions should not depend on details. Details should depend on abstractions."*

### ❌ The Anti-Pattern (Hardcoded Concrete Dependencies)

```cpp
// BAD: High-level Car directly creates and depends on concrete V8Engine
class V8Engine {
public:
    void start() { std::cout << "V8 roaring!\n"; }
};

class Car {
private:
    V8Engine engine_; // Tightly coupled! Can never test with MockEngine or switch to ElectricEngine
public:
    void drive() { engine_.start(); }
};
```

### ✅ The Refactored Solution (Dependency Injection via Smart Pointers)

```cpp
#include <iostream>
#include <memory>

class IEngine {
public:
    virtual ~IEngine() = default;
    virtual void start() = 0;
};

class V8Engine : public IEngine {
public:
    void start() override { std::cout << "V8 roaring!\n"; }
};

class ElectricMotor : public IEngine {
public:
    void start() override { std::cout << "Electric motor humming silently...\n"; }
};

// High-level Car depends ONLY on abstract IEngine
class Car {
private:
    std::unique_ptr<IEngine> engine_;
public:
    explicit Car(std::unique_ptr<IEngine> engine) : engine_(std::move(engine)) {}

    void drive() {
        engine_->start();
    }
};

int main() {
    Car gasCar(std::make_unique<V8Engine>());
    gasCar.drive();

    Car tesla(std::make_unique<ElectricMotor>());
    tesla.drive();
}
```

---

## SOLID Self-Assessment Checklist for Interviews

1. **SRP**: Does any class have the word "And" or "Manager" doing 5 unrelated tasks? If yes, split it.
2. **OCP**: Are you using `switch (type)` or `if (type == ...)`? Refactor to polymorphic strategy or factory.
3. **LSP**: Does any subclass throw `NotSupportedException` or do nothing in an overridden method? If yes, the inheritance hierarchy is wrong.
4. **ISP**: Does an interface have more than 3-5 methods? Break it into smaller role interfaces.
5. **DIP**: Are you calling `new ConcreteClass()` inside business logic? Inject abstractions through constructors instead.

