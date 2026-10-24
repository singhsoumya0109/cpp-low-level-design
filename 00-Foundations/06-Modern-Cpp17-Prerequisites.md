# Modern C++17 Prerequisites for LLD

Modern C++ (C++17) introduces expressive, safe, zero-cost abstractions that eliminate the clunky boilerplate of classic C++98/03. Understanding these features is mandatory to write production-grade LLD code.

---

## 1. `std::string_view` (Zero-Copy String Inspection)

Instead of passing `const std::string&` (which forces allocation if passed a string literal `const char*`), use `std::string_view` for read-only parameters.

```cpp
#include <string_view>
#include <iostream>

// Zero heap allocation, works with std::string, const char*, or string literals
void printLog(std::string_view message) {
    std::cout << "[LOG] " << message << '\n';
}

int main() {
    printLog("Literal string"); // No std::string temporary created!
    std::string s = "Dynamic string";
    printLog(s); // Efficient non-owning view
}
```

---

## 2. `std::optional<T>` (Safe Absence of Value)

Eliminates magic numbers (`-1`, `null`) and dangerous nullable pointers when a method might not return a result.

```cpp
#include <optional>
#include <string>
#include <iostream>

struct User {
    std::string name;
    int id;
};

class UserRepository {
public:
    std::optional<User> findById(int id) {
        if (id == 42) {
            return User{"Alice", 42};
        }
        return std::nullopt; // Explicit absence of value
    }
};

int main() {
    UserRepository repo;
    auto user = repo.findById(10);
    if (user.has_value()) {
        std::cout << "Found: " << user->name << '\n';
    } else {
        std::cout << "User not found!\n";
    }

    // Default fallback idiom:
    User activeUser = repo.findById(99).value_or(User{"Guest", 0});
}
```

---

## 3. `std::variant` & `std::visit` (Type-Safe Algebraic Sum Types)

A type-safe union that holds one of several types. In modern C++, this is often a fast, cache-friendly alternative to classic inheritance and the Visitor pattern.

```cpp
#include <variant>
#include <iostream>
#include <string>

struct CreditCard { std::string cardNumber; };
struct PayPal { std::string email; };
struct Cash {};

using PaymentMethod = std::variant<CreditCard, PayPal, Cash>;

struct PaymentProcessor {
    void operator()(const CreditCard& cc) const {
        std::cout << "Charging Credit Card: " << cc.cardNumber << '\n';
    }
    void operator()(const PayPal& pp) const {
        std::cout << "Routing to PayPal: " << pp.email << '\n';
    }
    void operator()(const Cash&) const {
        std::cout << "Collecting physical cash.\n";
    }
};

int main() {
    PaymentMethod method = PayPal{"user@example.com"};
    std::visit(PaymentProcessor{}, method);
}
```

---

## 4. Structured Bindings (`auto [a, b] = ...`)

Allows unpacking tuples, pairs, structs, and maps directly into distinct variables.

```cpp
#include <map>
#include <string>
#include <iostream>

int main() {
    std::map<int, std::string> users = {{1, "Alice"}, {2, "Bob"}};

    // Clean map traversal without it->first, it->second
    for (const auto& [id, name] : users) {
        std::cout << "ID: " << id << " -> Name: " << name << '\n';
    }
}
```

---

## 5. Move Semantics & `std::move`

Pass by value and `std::move` inside constructors is the modern C++ idiom for sink parameters (taking ownership).

```cpp
#include <string>
#include <vector>
#include <utility>

class Document {
private:
    std::string title_;
    std::vector<std::string> paragraphs_;

public:
    // Takes ownership efficiently without redundant copies
    Document(std::string title, std::vector<std::string> paragraphs)
        : title_(std::move(title)), paragraphs_(std::move(paragraphs)) {}
};
```

---

## 6. Core Attributes & Specifiers for LLD

| Specifier | Purpose in LLD |
|---|---|
| `override` | Mandatory when overriding virtual methods. Ensures compiler error if signature changes. |
| `final` | Prevents further inheritance or method overrides (enables compiler devirtualization). |
| `[[nodiscard]]` | Emits compiler warning if caller ignores return value (e.g. status codes, newly created objects). |
| `noexcept` | Guarantees function does not throw; allows `std::vector` to use fast move reallocation instead of copy. |
| `= default` | Explicitly request compiler-generated special member functions (e.g., virtual destructor). |
| `= delete` | Explicitly disable functions (e.g., disabling copy constructor for Singletons). |

