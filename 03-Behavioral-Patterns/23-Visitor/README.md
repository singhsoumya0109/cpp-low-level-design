# Visitor Design Pattern

> **Category**: Behavioral Pattern

---

## 1. Intent
Represents an operation to be performed on the elements of an object structure. Lets you define a new operation without changing the classes of the elements on which it operates.

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
