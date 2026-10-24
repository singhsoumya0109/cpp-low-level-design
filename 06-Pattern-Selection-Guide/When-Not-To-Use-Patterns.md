# When NOT to Use Design Patterns (Overengineering & YAGNI)

Software engineering is not about cramming as many design patterns into a file as possible. Overuse of patterns is called **"Patternitis"**.

---

## 5 Warning Signs of Overengineering

1. **The Single-Implementation Factory**:
   - Creating `IUserManagerFactory`, `UserManagerFactory`, `IUserManager`, and `UserManager` when only one implementation of `UserManager` will ever exist.
   - *Fix*: Just instantiate `UserManager` directly until a second variant is required.

2. **Singleton for Convenience**:
   - Making an object a Singleton simply because it is convenient to call from anywhere in the codebase.
   - *Fix*: Pass dependencies explicitly via constructors.

3. **Strategy Pattern for 2-Line Functions**:
   - Creating 3 classes and an interface to wrap a single arithmetic expression.
   - *Fix*: In modern C++, pass a `std::function` or a lambda instead of creating a heavyweight class hierarchy.

4. **Deep Decorator Pyramids**:
   - Stacking 7 layers of decorators for basic request transformation.
   - *Fix*: Use a simple pipeline function or a sequential loop.

5. **Visitor for Stable Types**:
   - Implementing classic double-dispatch Visitor on a class tree that never changes.
   - *Fix*: Just write a member function, or in modern C++, use `std::variant` and `std::visit`.
