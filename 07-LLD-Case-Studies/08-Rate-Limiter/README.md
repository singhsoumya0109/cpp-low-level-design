# Case Study: Distributed Rate Limiter

> **Primary Patterns**: Strategy, Decorator

---

## 1. System Overview
Design an API rate limiter supporting Token Bucket, Leaky Bucket, and Sliding Window Log algorithms with thread-safe atomic counter synchronization.

---

## 2. Key Engineering Challenges
- **Thread Safety**: Concurrent requests must be synchronized using RAII locks without causing deadlocks or bottlenecks.
- **Extensibility**: Core logic must adhere to the Open/Closed Principle so new algorithms or entities can be added without modifying existing code.
- **Memory Management**: Zero memory leaks using `std::unique_ptr` and `std::shared_ptr`.
