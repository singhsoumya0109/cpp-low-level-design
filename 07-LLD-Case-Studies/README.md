# Production Low-Level Design Case Studies

This module contains **10 complete, production-grade machine coding problems** covering the most frequently tested Low-Level Design interview scenarios at tier-1 and FAANG companies.

---

## 🏗️ The 10 Production Systems

### Tier 1: Core Enterprise & State Machine Systems

1. **[01. Parking Lot System](01-Parking-Lot/)**
   - *Key Patterns*: Factory Method, Strategy, State.
   - *Challenges*: Multi-floor allocation, dynamic hourly vs vehicle fee strategies, entry/exit gate coordination.
2. **[02. Elevator Management System](02-Elevator-System/)**
   - *Key Patterns*: State, Strategy, Dispatcher / Command.
   - *Challenges*: Multi-car dispatching algorithms (LOOK, SCAN, Shortest Seek Time First), internal vs external button requests.
3. **[03. Vending Machine](03-Vending-Machine/)**
   - *Key Patterns*: State Pattern (Finite State Machine), Command.
   - *Challenges*: State transitions (Ready, HasMoney, Dispensing, SoldOut), coin/cash validation, change return rollback.
4. **[04. Notification Service](04-Notification-System/)**
   - *Key Patterns*: Factory Method, Strategy, Decorator.
   - *Challenges*: Multi-channel routing (SMS, Email, Push), rate-limiting decorators, exponential backoff retries.
5. **[05. Order Management System](05-Order-Management-System/)**
   - *Key Patterns*: State, Observer, Command.
   - *Challenges*: Order lifecycle (Created, Paid, Packed, Shipped, Delivered, Cancelled), inventory reservation, payment webhooks.
6. **[06. In-Memory File System](06-File-System/)**
   - *Key Patterns*: Composite, Iterator, Visitor.
   - *Challenges*: Hierarchical directory trees, path parsing (`/a/b/c`), permissions, recursive size/search operations.

---

### Tier 2: Concurrency & High-Yield Algorithmic Systems

7. **[07. In-Memory Cache (LRU / LFU)](07-In-Memory-Cache-LRU-LFU/)**
   - *Key Patterns*: Strategy, Proxy.
   - *Challenges*: $O(1)$ operations with Doubly Linked List + Hash Map, TTL expiration policies, thread-safe reader-writer locking.
8. **[08. Distributed Rate Limiter](08-Rate-Limiter/)**
   - *Key Patterns*: Strategy, Decorator.
   - *Challenges*: Token Bucket, Leaky Bucket, Sliding Window Log, thread safety and atomic counter synchronization.
9. **[09. Splitwise Expense Sharing](09-Splitwise-Expense-Sharing/)**
   - *Key Patterns*: Strategy, Observer.
   - *Challenges*: Equal, Exact, and Percentage splits, Debt Simplification (Min-Cash Flow Graph Algorithm).
10. **[10. Movie Ticket Booking (BookMyShow)](10-Movie-Ticket-Booking-System/)**
    - *Key Patterns*: State, Strategy.
    - *Challenges*: Temporary seat locking with TTL (Time To Live), concurrent seat reservation race condition prevention, payment idempotency.

