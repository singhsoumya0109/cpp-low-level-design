# CRTP (Curiously Recurring Template Pattern)

> **Category**: Modern C++ Idiom & Extended Pattern

---

## 1. Core Concept
A modern C++ static polymorphism idiom where a class derives from a class template instantiated with the class itself, achieving compile-time polymorphism with zero vtable overhead.

---

## 2. Why It Matters in C++
Unlike managed languages (Java/C#), C++ requires explicit control over compilation firewalls, cache locality, and deterministic resource reclamation.

---

## 3. Key Idioms
- Always wrap raw handles in RAII destructors.
- For PImpl, use `std::unique_ptr<Impl>` and declare the destructor in the implementation file (`.cpp`).
