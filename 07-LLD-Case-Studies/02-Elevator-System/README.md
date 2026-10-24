# Case Study: Elevator Management System

> **Primary Patterns**: State, Strategy, Dispatcher / Command

---

## 1. System Overview
Design a multi-car elevator control system optimizing passenger wait times using LOOK/SCAN dispatch scheduling algorithms, handling internal car requests and external floor summons.

---

## 2. Key Engineering Challenges
- **Thread Safety**: Concurrent requests must be synchronized using RAII locks without causing deadlocks or bottlenecks.
- **Extensibility**: Core logic must adhere to the Open/Closed Principle so new algorithms or entities can be added without modifying existing code.
- **Memory Management**: Zero memory leaks using `std::unique_ptr` and `std::shared_ptr`.
