# Case Study: Multi-Channel Notification Service

> **Primary Patterns**: Factory Method, Strategy, Decorator

---

## 1. System Overview
Design a notification routing engine supporting SMS, Email, and Push notifications with rate limiting, exponential backoff retries, and template formatting.

---

## 2. Key Engineering Challenges
- **Thread Safety**: Concurrent requests must be synchronized using RAII locks without causing deadlocks or bottlenecks.
- **Extensibility**: Core logic must adhere to the Open/Closed Principle so new algorithms or entities can be added without modifying existing code.
- **Memory Management**: Zero memory leaks using `std::unique_ptr` and `std::shared_ptr`.
