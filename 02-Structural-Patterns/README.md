# Structural Design Patterns in Modern C++

Structural design patterns explain how to assemble objects and classes into larger, flexible, and efficient structures while keeping these structures flexible and efficient.

---

## The 7 Structural Patterns

| Pattern | Intent | Key C++ Mechanism |
|---|---|---|
| **[06. Adapter](06-Adapter/)** | Converts the interface of a class into another interface clients expect. | Object Adapter (`std::unique_ptr<Adaptee>`) vs Class Adapter (Multiple inheritance). |
| **[07. Bridge](07-Bridge/)** | Decouples an abstraction from its implementation so that the two can vary independently. | PImpl / Handle-Body idiom via smart pointers. |
| **[08. Composite](08-Composite/)** | Composes objects into tree structures to represent part-whole hierarchies. | Uniform polymorphic interface over leaves and containers (`std::vector<std::unique_ptr<Component>>`). |
| **[09. Decorator](09-Decorator/)** | Attaches additional responsibilities to an object dynamically. | Recursive wrapping of interface pointers. |
| **[10. Facade](10-Facade/)** | Provides a unified, simplified interface to a complex subsystem. | High-level coordinator class encapsulating subsystem headers. |
| **[11. Flyweight](11-Flyweight/)** | Supports large numbers of fine-grained objects efficiently by sharing common state. | Separation of Intrinsic (shared) vs Extrinsic (context) state. |
| **[12. Proxy](12-Proxy/)** | Provides a surrogate or placeholder for another object to control access to it. | Virtual, Protection, Caching, and Remote Proxies. |

