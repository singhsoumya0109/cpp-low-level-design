# Modern C++ Implementation Checklist for LLD

Before finishing any interview or PR, verify these 10 points:

1. **Zero Raw `new` or `delete`**: Are all dynamically allocated objects held by `std::unique_ptr` or `std::shared_ptr`?
2. **Virtual Destructors**: Does every polymorphic base class declare `virtual ~Base() = default;`?
3. **Explicit `override`**: Are all overridden virtual functions marked with `override`?
4. **Const-Correctness**: Are member functions that do not mutate state marked `const`?
5. **No String Copies**: Are read-only string parameters passed as `std::string_view`?
6. **Sink Parameters**: Are constructors that store strings/containers taking them by value and using `std::move`?
7. **Thread Safety**: Are shared mutable resources protected by `std::mutex` or `std::shared_mutex` using RAII lock guards?
8. **RAII Locks**: Are you using `std::lock_guard` or `std::unique_lock` instead of manual `.lock()`/`.unlock()`?
9. **No Circular Shared Pointers**: Do parent-child relationships use `std::weak_ptr` for back-references?
10. **Clean Compiler Warnings**: Does the code compile cleanly with `-Wall -Wextra -Wpedantic`?
