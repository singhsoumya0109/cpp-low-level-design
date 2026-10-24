# Strategy vs. Template Method

---

## Key Differences

| Dimension | Strategy Pattern | Template Method Pattern |
|---|---|---|
| **Mechanism** | **Composition & Delegation**: Context HAS-A Strategy object. | **Inheritance**: Subclass IS-A specialization of base class. |
| **Granularity** | Swaps the **entire algorithm** wholesale at runtime. | Base class fixes the algorithm skeleton; subclasses customize specific primitive steps. |
| **Runtime Swapping** | Supported (can inject a different strategy pointer at runtime). | Fixed at compile-time (subclass type is immutable once instantiated). |
| **C++ Idiom** | `std::unique_ptr<IStrategy>` or `std::function`. | Non-Virtual Interface (NVI) pattern (`public` non-virtual base function calling `private` virtual hooks). |
