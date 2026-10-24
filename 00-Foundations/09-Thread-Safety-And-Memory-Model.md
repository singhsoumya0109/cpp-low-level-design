# Thread Safety & Concurrency in Modern C++

In real-world LLD and senior interviews (FAANG, Uber, Stripe), you will be asked:
> *"How would you make this booking system / cache / singleton thread-safe when 10,000 requests hit it concurrently?"*

Modern C++ provides thread safety primitives in the `<thread>`, `<mutex>`, `<shared_mutex>`, `<atomic>`, and `<condition_variable>` headers.

---

## 1. Synchronization Primitives Comparison

| Primitive | Header | Use Case | Performance Overhead |
|---|---|---|---|
| `std::mutex` | `<mutex>` | Exclusive access to shared mutable state. | Moderate (kernel context switch if contended). |
| `std::shared_mutex` | `<shared_mutex>` | Reader-Writer Lock (Multiple readers OR one writer). | Higher setup cost, excellent for read-heavy workloads (caches). |
| `std::atomic<T>` | `<atomic>` | Lock-free synchronization for primitive types (`int`, `bool`, pointers). | Minimal (hardware atomic CPU instructions, e.g. `LOCK CMPXCHG`). |
| `std::condition_variable`| `<condition_variable>` | Thread signaling / notification (Producer-Consumer queue). | Efficient thread sleep without busy-spinning. |

---

## 2. RAII Lock Wrappers: Never Call `.lock()` Directly!

Always use RAII wrappers to prevent deadlocks caused by unhandled exceptions:

```cpp
#include <mutex>
#include <shared_mutex>

std::mutex mtx;
std::shared_mutex rw_mtx;

void safeFunction() {
    // 1. std::lock_guard: Simple, non-reentrant exclusive lock
    std::lock_guard<std::mutex> lock(mtx);
    // Mutex automatically released when lock goes out of scope (even if exception throws)
}

void advancedFunction() {
    // 2. std::unique_lock: Can defer locking, unlock early, or integrate with condition_variable
    std::unique_lock<std::mutex> lock(mtx);
    // ... work ...
    lock.unlock(); // Can unlock manually early
}

void readerFunction() {
    // 3. std::shared_lock: Multiple threads can hold this concurrently
    std::shared_lock<std::shared_mutex> readLock(rw_mtx);
    // Reading data...
}

void writerFunction() {
    // Exclusive lock: blocks all readers and writers
    std::unique_lock<std::shared_mutex> writeLock(rw_mtx);
    // Mutating data...
}
```

---

## 3. The Thread-Safe Meyers' Singleton (C++11 Guaranteed)

In C++11 and newer, `static` local variables are guaranteed by the C++ memory model to be initialized **exactly once**, in a thread-safe manner without manual locks!

```cpp
class DatabaseConnectionPool {
private:
    DatabaseConnectionPool() {
        // Expensive connection initialization
    }

public:
    // Delete copy and move operations
    DatabaseConnectionPool(const DatabaseConnectionPool&) = delete;
    DatabaseConnectionPool& operator=(const DatabaseConnectionPool&) = delete;
    DatabaseConnectionPool(DatabaseConnectionPool&&) = delete;
    DatabaseConnectionPool& operator=(DatabaseConnectionPool&&) = delete;

    static DatabaseConnectionPool& getInstance() {
        // Thread-safe initialization guaranteed by the standard!
        static DatabaseConnectionPool instance;
        return instance;
    }

    void executeQuery(const std::string& query) {
        // execute query safely
    }
};
```

---

## 4. Classic Producer-Consumer Queue (Thread-Safe)

A standard interview question asked across LLD rounds:

```cpp
#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

template <typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue_;
    mutable std::mutex mtx_;
    std::condition_variable cv_;
    bool stopped_{false};

public:
    void push(T value) {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            queue_.push(std::move(value));
        }
        cv_.notify_one(); // Wake up one waiting consumer thread
    }

    std::optional<T> pop() {
        std::unique_lock<std::mutex> lock(mtx_);
        // Wait until queue is not empty or queue has been stopped
        cv_.wait(lock, [this] { return !queue_.empty() || stopped_; });

        if (queue_.empty() && stopped_) {
            return std::nullopt;
        }

        T item = std::move(queue_.front());
        queue_.pop();
        return item;
    }

    void stop() {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            stopped_ = true;
        }
        cv_.notify_all(); // Wake up all waiting consumers to exit cleanly
    }
};
```

---

## 5. Deadlock Prevention Rules for Interviews

1. **Lock in a Fixed Global Order**: If two locks `A` and `B` are needed, every thread must acquire `A` before `B`.
2. **Use `std::lock` / `std::scoped_lock` (C++17)**: Automatically acquires multiple mutexes without risk of deadlock via deadlock-avoidance algorithms.
   ```cpp
   std::mutex m1, m2;
   // C++17 deadlock-free multi-lock:
   std::scoped_lock lock(m1, m2);
   ```
3. **Minimize Critical Section Scope**: Keep code inside lock blocks as short as possible. Never perform network I/O or disk operations while holding a lock.

