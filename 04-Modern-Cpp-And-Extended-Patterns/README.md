# Modern C++ & Extended Design Patterns

Patterns unique to or popularized by Modern C++ that take advantage of value semantics, templates, and compiler-enforced resource guarantees.

---

## Modern C++ Idioms & Patterns

1. **[01. RAII (Resource Acquisition Is Initialization)](01-RAII/)**
   - Binding the life cycle of a resource to the lifetime of an object. Scope guards and custom deleters.
2. **[02. PImpl (Pointer to Implementation)](02-PImpl/)**
   - Compilation firewall to break header dependencies, reduce compile times, and preserve ABI stability.
3. **[03. CRTP (Curiously Recurring Template Pattern)](03-CRTP/)**
   - Static polymorphism with zero runtime virtual dispatch overhead. Compile-time method injection.
4. **[04. Type Erasure](04-Type-Erasure/)**
   - How `std::function` and `std::any` work under the hood without requiring a common inheritance tree.
5. **[05. Dependency Injection](05-Dependency-Injection/)**
   - Constructor and factory-based dependency injection in C++ without heavy reflection frameworks.
6. **[06. Null Object Pattern](06-Null-Object/)**
   - Providing a default non-operational object to eliminate defensive `if (ptr != nullptr)` checks.
7. **[07. Thread-Safe Object Pool](07-Object-Pool/)**
   - Pre-allocating and recycling expensive resources (database connections, network sockets, particle buffers).

