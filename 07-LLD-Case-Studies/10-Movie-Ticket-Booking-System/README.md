# Case Study: Movie Ticket Booking (BookMyShow)

> **Primary Patterns**: State, Strategy

---

## 1. System Overview
Design a cinema ticket booking platform supporting concurrent seat selection with temporary TTL seat locking, payment idempotency, and race condition prevention.

---

## 2. Key Engineering Challenges
- **Thread Safety**: Concurrent requests must be synchronized using RAII locks without causing deadlocks or bottlenecks.
- **Extensibility**: Core logic must adhere to the Open/Closed Principle so new algorithms or entities can be added without modifying existing code.
- **Memory Management**: Zero memory leaks using `std::unique_ptr` and `std::shared_ptr`.
