# RAII (Resource Acquisition Is Initialization)

> **Category**: Modern C++ Idiom & Extended Pattern

---

## 1. Core Concept
Guarantees that resource release is tied directly to object lifetime, preventing resource leaks in the presence of early returns and exceptions.

---

## 2. Why It Matters in C++
Unlike managed languages (Java/C#), C++ requires explicit control over compilation firewalls, cache locality, and deterministic resource reclamation.

---

## 3. Key Idioms
- Always wrap raw handles in RAII destructors.
- For PImpl, use `std::unique_ptr<Impl>` and declare the destructor in the implementation file (`.cpp`).
