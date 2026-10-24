# Command Design Pattern

> **Category**: Behavioral Pattern

---

## 1. Intent
Encapsulates a request as an object, thereby letting you parameterize clients with different requests, queue or log requests, and support undo/redo.

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
