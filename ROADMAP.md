# Low-Level Design & C++ Mastery Roadmap

A structured timeline to transition from basic OOP knowledge to passing LLD rounds at top tech companies.

---

## 📅 4-Week Milestone Timeline

```mermaid
gantt
    title Modern C++ LLD Study Roadmap
    dateFormat  YYYY-MM-DD
    section Phase 1: Foundations & Creational
    OOP & SOLID Principles       :a1, 2026-11-01, 3d
    Modern C++17 & Smart Pointers:a2, after a1, 2d
    Creational Patterns (5)      :a3, after a2, 3d
    section Phase 2: Structural & Behavioral
    Structural Patterns (7)      :b1, after a3, 4d
    Behavioral Patterns (11)     :b2, after b1, 6d
    Modern C++ Patterns (RAII,CRTP):b3, after b2, 3d
    section Phase 3: Case Studies
    Parking Lot & Elevator       :c1, after b3, 3d
    Vending Machine & Notification:c2, after c1, 3d
    Cache, Rate Limiter & Concurrency:c3, after c2, 4d
    Splitwise & BookMyShow       :c4, after c3, 3d
    section Phase 4: Mock Interviews & Polish
    Timed Mock Interviews        :d1, after c4, 4d
    Pattern Matrix & Review      :d2, after d1, 3d
```

---

## 🎯 Phase Breakdown

### Phase 1: Foundations & The Creational Family
- **Milestone 1.1**: Understand object ownership: when to use `std::unique_ptr` vs `std::shared_ptr` vs raw non-owning pointers/references.
- **Milestone 1.2**: Master all 5 SOLID principles with the exact subtyping rules for Liskov Substitution Principle (preconditions cannot be strengthened, postconditions cannot be weakened).
- **Milestone 1.3**: Implement the 5 creational patterns (Singleton, Factory Method, Abstract Factory, Builder, Prototype). Emphasize Scott Meyers' thread-safe Singleton and Fluent/Step Builder.

### Phase 2: Structural, Behavioral, and Modern Idioms
- **Milestone 2.1**: Implement the 7 structural patterns. Contrast Object Adapter vs Class Adapter, and understand the difference between Proxy, Decorator, and Adapter.
- **Milestone 2.2**: Implement the 11 behavioral patterns. Master State (FSM) vs Strategy, Observer (thread-safe publish/subscribe), and Command (Undo/Redo).
- **Milestone 2.3**: Learn modern C++ idioms: RAII, PImpl (compilation firewalls), CRTP (compile-time polymorphism), and Type Erasure.

### Phase 3: Real-World Case Studies (Machine Coding)
- **Milestone 3.1**: Design and code state-machine-driven systems (Vending Machine, Elevator System).
- **Milestone 3.2**: Design and code hierarchical/tree systems (In-Memory File System).
- **Milestone 3.3**: Design and code high-concurrency systems (Thread-safe LRU Cache with read-write locks, Rate Limiter with Token Bucket, Seat-locking BookMyShow).
- **Milestone 3.4**: Design complex algorithmic business systems (Splitwise debt simplification graph algorithm).

### Phase 4: Interview Mastery & Speed
- **Milestone 4.1**: Practice solving arbitrary problem statements using the 6-step LLD Interview Blueprint in under 45 minutes.
- **Milestone 4.2**: Complete all flashcards and 1-page summaries in the Revision Center.

