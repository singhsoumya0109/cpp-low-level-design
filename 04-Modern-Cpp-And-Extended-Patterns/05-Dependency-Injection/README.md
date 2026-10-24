# Dependency Injection

> **Category**: Modern C++ Idiom & Extended Pattern

---

## 1. Core Concept
A design approach where classes receive their dependencies via constructor injection rather than creating them directly, enabling modularity and unit test mocking.

---

## 2. Why It Matters in C++
Unlike managed languages (Java/C#), C++ requires explicit control over compilation firewalls, cache locality, and deterministic resource reclamation.

---

## 3. Key Idioms
- Always wrap raw handles in RAII destructors.
- For PImpl, use `std::unique_ptr<Impl>` and declare the destructor in the implementation file (`.cpp`).
