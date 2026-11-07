# 05 45-Minute Interview Mock Problems

Full simulated machine-coding problems designed for a standard 45-minute coding round at top tech firms.

---

## 45-Minute Interview Pacing Guide
| Time Window | Phase | Key Deliverables |
|---|---|---|
| **00:00 - 05:00** | Clarify Requirements & Scope | 3-5 functional requirements, constraints, clarify edge cases |
| **05:00 - 12:00** | Entities, State & Interfaces | Identify core entities, declare clean pure virtual interfaces |
| **12:00 - 30:00** | Core Implementation | Write clean C++17 code: smart pointers, RAII, thread safety |
| **30:00 - 38:00** | Extensibility & Tests | Implement unit tests and show how code accommodates a new feature |
| **38:00 - 45:00** | Concurrency & Wrap-up | Address concurrency, memory boundaries, and interviewer follow-ups |

---

## Mock Problem 1: In-Memory Key-Value Store with TTL & Transactions
- **Difficulty**: Hard | **Time Limit**: 45 Minutes
- **Requirements**:
  - Support `put(key, value, optional_ttl)` and `get(key)`.
  - Expired keys must not be returned.
  - Support atomic transactions: `begin()`, `commit()`, `rollback()` with nested transaction support.
  - Thread-safe under concurrent reads and writes (`std::shared_mutex`).

---

## Mock Problem 2: Rate Limiter Middleware
- **Difficulty**: Medium | **Time Limit**: 45 Minutes
- **Requirements**:
  - Allow $N$ requests per rolling window of $T$ seconds per client IP/ID.
  - Support multiple algorithms: Token Bucket, Sliding Window Counter, Leaky Bucket.
  - Seamlessly switch algorithm via Strategy pattern.
  - Thread-safe for multi-threaded web servers.
