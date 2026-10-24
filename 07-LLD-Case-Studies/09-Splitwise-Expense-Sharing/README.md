# Case Study: Splitwise Expense Sharing System

> **Primary Patterns**: Strategy, Observer

---

## 1. System Overview
Design an expense-sharing application supporting Equal, Exact, and Percentage splits with a Debt Simplification graph algorithm (Min-Cash Flow).

---

## 2. Key Engineering Challenges
- **Thread Safety**: Concurrent requests must be synchronized using RAII locks without causing deadlocks or bottlenecks.
- **Extensibility**: Core logic must adhere to the Open/Closed Principle so new algorithms or entities can be added without modifying existing code.
- **Memory Management**: Zero memory leaks using `std::unique_ptr` and `std::shared_ptr`.
