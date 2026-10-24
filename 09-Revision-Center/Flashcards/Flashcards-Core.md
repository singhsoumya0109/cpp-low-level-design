# Core LLD Flashcards (Active Recall)

### Q1: Why is Scott Meyers' Singleton thread-safe in C++11?
> **Answer**: §6.7 of the C++ standard guarantees that local static variables are initialized synchronously and thread-safely by compiler-generated guard locks.

---

### Q2: How does Liskov Substitution Principle restrict preconditions and postconditions?
> **Answer**: 
> 1. Preconditions cannot be strengthened (derived class cannot demand more strict inputs).
> 2. Postconditions cannot be weakened (derived class must deliver at least the same guarantee as the parent).

---

### Q3: What is the Non-Virtual Interface (NVI) pattern?
> **Answer**: A base class defines a `public non-virtual` method that enforces preconditions and postconditions, which internally calls a `private virtual` method that derived classes override.

---

### Q4: When should you use `std::weak_ptr` in the Observer Pattern?
> **Answer**: Subjects should hold `std::weak_ptr<IObserver>` instead of `std::shared_ptr` to prevent circular dependencies and allow dead observers to be cleanly destroyed and deregistred.
