# PImpl (Pointer to Implementation)

> **Category**: Modern C++ Idiom & Extended Pattern

---

## 1. Core Concept
A technique used to hide implementation details, reduce compilation dependencies, and maintain a stable ABI by placing private members in a forward-declared struct.

---

## 2. Why It Matters in C++
Unlike managed languages (Java/C#), C++ requires explicit control over compilation firewalls, cache locality, and deterministic resource reclamation.

---

## 3. Key Idioms
- Always wrap raw handles in RAII destructors.
- For PImpl, use `std::unique_ptr<Impl>` and declare the destructor in the implementation file (`.cpp`).
