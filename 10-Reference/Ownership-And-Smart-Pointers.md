# Ownership & Smart Pointer Reference

| Type | Overhead | Copyable? | Movable? | Typical LLD Use |
|---|---|---|---|---|
| `std::unique_ptr<T>` | 0 bytes (zero-cost) | No | Yes | Exclusive ownership (Factories, Builders, Strategies) |
| `std::shared_ptr<T>` | Control block (2 atomics) | Yes | Yes | Co-ownership (Graph nodes, Shared caches) |
| `std::weak_ptr<T>` | Observes control block | Yes | Yes | Observers, Cycle breaking |
| `const T&` / `T*` | 0 bytes | Yes | Yes | Non-owning observer parameter |
