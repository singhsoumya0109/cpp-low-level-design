# Case Study: In-Memory Cache (LRU & LFU)

> **Primary Patterns**: Strategy, Proxy

---

## 1. System Overview
Design a high-performance in-memory key-value cache with O(1) get/put operations, pluggable eviction strategies (LRU/LFU), TTL support, and reader-writer thread safety.

---

## 2. Key Engineering Challenges
- **Thread Safety**: Concurrent requests must be synchronized using RAII locks without causing deadlocks or bottlenecks.
- **Extensibility**: Core logic must adhere to the Open/Closed Principle so new algorithms or entities can be added without modifying existing code.
- **Memory Management**: Zero memory leaks using `std::unique_ptr` and `std::shared_ptr`.
