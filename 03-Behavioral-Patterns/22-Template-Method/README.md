# Template Method Design Pattern

> **Category**: Behavioral Pattern

---

## 1. Intent
Defines the skeleton of an algorithm in an operation, deferring some steps to subclasses. Uses the Non-Virtual Interface (NVI) idiom in modern C++.

---

## 2. Architecture & UML

```mermaid
classDiagram
    class Context {
        +request()
    }
    class Handler {
        <<interface>>
        +handleRequest()*
    }
    Context --> Handler
```

---

## 3. Modern C++ Best Practices
- Prefer `std::function` or lambdas for simple callbacks instead of complex class hierarchies.
- Use `std::weak_ptr` for observer lists to prevent memory leaks and dangling circular references.
