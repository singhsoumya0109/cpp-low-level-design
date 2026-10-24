# Case Study: In-Memory File System

> **Primary Patterns**: Composite, Iterator, Visitor

---

## 1. System Overview
Design an in-memory Unix-like hierarchical file system supporting files, directories, path resolution (/a/b/c), search, and recursive permissions.

---

## 2. Key Engineering Challenges
- **Thread Safety**: Concurrent requests must be synchronized using RAII locks without causing deadlocks or bottlenecks.
- **Extensibility**: Core logic must adhere to the Open/Closed Principle so new algorithms or entities can be added without modifying existing code.
- **Memory Management**: Zero memory leaks using `std::unique_ptr` and `std::shared_ptr`.
