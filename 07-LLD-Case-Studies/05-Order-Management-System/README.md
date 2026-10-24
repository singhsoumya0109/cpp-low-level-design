# Case Study: Order Management System

> **Primary Patterns**: State, Observer, Command

---

## 1. System Overview
Design an e-commerce order lifecycle manager tracking order states (Created, Paid, Packed, Shipped, Delivered, Cancelled) with inventory reservation and webhook notifications.

---

## 2. Key Engineering Challenges
- **Thread Safety**: Concurrent requests must be synchronized using RAII locks without causing deadlocks or bottlenecks.
- **Extensibility**: Core logic must adhere to the Open/Closed Principle so new algorithms or entities can be added without modifying existing code.
- **Memory Management**: Zero memory leaks using `std::unique_ptr` and `std::shared_ptr`.
