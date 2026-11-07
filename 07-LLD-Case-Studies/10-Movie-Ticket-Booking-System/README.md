# Case Study 10: Movie Ticket Booking System (BookMyShow)

> **Difficulty**: Hard | **Primary Patterns**: State, Factory, Concurrency Lock Manager | **Concurrency**: Pessimistic Temporary Seat Locks

---

## 1. System Overview
Design a high-concurrency movie cinema reservation system. Prevents double-booking during peak ticket release events by employing temporary seat locking with automatic lease expiration timers.

```mermaid
stateDiagram-v2
    [*] --> Available
    Available --> Locked : lock_seat() [User selecting seat]
    Locked --> Available : lock_timeout_expired() [e.g. 10s]
    Locked --> Booked : confirm_payment()
    Booked --> [*]
```

---

## 2. Build and Test
```bash
clang++ -std=c++17 -Wall -Wextra src/solution.cpp -o movie_demo && ./movie_demo
clang++ -std=c++17 -Wall -Wextra tests/test_movie.cpp -o test_movie && ./test_movie
```
