# Case Study: Vending Machine System

> **Primary Patterns**: State, Command

---

## 1. System Overview
Design an automated vending machine using a Finite State Machine (FSM) to manage state transitions (Idle, HasMoney, Dispensing, SoldOut), coin/cash validation, and inventory deduction.

---

## 2. Key Engineering Challenges
- **Thread Safety**: Concurrent requests must be synchronized using RAII locks without causing deadlocks or bottlenecks.
- **Extensibility**: Core logic must adhere to the Open/Closed Principle so new algorithms or entities can be added without modifying existing code.
- **Memory Management**: Zero memory leaks using `std::unique_ptr` and `std::shared_ptr`.
