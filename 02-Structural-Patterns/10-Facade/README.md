# Facade Design Pattern

> **Category**: Structural Pattern

---

## 1. Intent
Provides a unified, simplified high-level interface to a complex subsystem of classes, libraries, or frameworks.

---

## 2. Architecture & UML

```mermaid
classDiagram
    class Target {
        <<interface>>
        +request()* void
    }
    class Client {
        -Target* target_
    }
    Client --> Target
```

---

## 3. Modern C++ Implementation Notes
- Store wrapped objects using `std::unique_ptr<Component>` for exclusive ownership.
- Use `const &` or non-owning raw pointers for non-owning structural references.
