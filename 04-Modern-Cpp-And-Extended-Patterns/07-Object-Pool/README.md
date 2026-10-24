# Thread-Safe Object Pool

> **Category**: Modern C++ Idiom & Extended Pattern

---

## 1. Core Concept
A creational pattern that manages a cache of pre-allocated, reusable objects to avoid expensive repeated allocations and deallocations.

---

## 2. Why It Matters in C++
Unlike managed languages (Java/C#), C++ requires explicit control over compilation firewalls, cache locality, and deterministic resource reclamation.

---

## 3. Key Idioms
- Always wrap raw handles in RAII destructors.
- For PImpl, use `std::unique_ptr<Impl>` and declare the destructor in the implementation file (`.cpp`).
