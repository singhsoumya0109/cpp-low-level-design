# Strategy Design Pattern

> **Category**: Behavioral Pattern

---

## 1. Intent
Defines a family of algorithms, encapsulates each one, and makes them interchangeable. Strategy lets the algorithm vary independently from clients that use it.

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
