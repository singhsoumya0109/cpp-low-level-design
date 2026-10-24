# Singleton Pattern Exercises

Test your understanding of the Singleton pattern by solving these three progressively challenging exercises.

---

## Exercise 1: The Basic Registry
Implement a thread-safe `SessionRegistry` singleton that stores active user session IDs in a `std::unordered_set<std::string>`.
- Provide methods: `addSession(std::string_view id)`, `removeSession(std::string_view id)`, and `bool isValid(std::string_view id) const`.
- Protect the internal container with `std::mutex`.

---

## Exercise 2: Refactoring Challenge
Refactor a legacy `AnalyticsCollector` class that currently uses global static pointers with unprotected `new` and dangling references into a clean Meyers' Singleton adhering to modern C++ best practices.

---

## Exercise 3: Interview Challenge (Thread-Safe Cache Singleton)
Create a thread-safe `InMemoryCache` singleton using `std::shared_mutex` (Reader-Writer lock):
- Read operations (`get`) must acquire `std::shared_lock` allowing concurrent reads.
- Write operations (`put`) must acquire `std::unique_lock` ensuring exclusive access.

