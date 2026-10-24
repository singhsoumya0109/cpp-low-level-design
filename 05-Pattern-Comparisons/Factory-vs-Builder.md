# Factory vs. Builder

---

## Quick Comparison Matrix

| Dimension | Factory (Simple/Method) | Builder |
|---|---|---|
| **Creation Process** | **Single-step**: Returns fully initialized product in one call. | **Multi-step**: Configures object step-by-step (`setName()`, `setPort()`, `build()`). |
| **Object Complexity** | Simpler objects with few constructor parameters. | Highly complex objects with many optional parameters (5+ parameters). |
| **Product Representation** | Creates products sharing a common interface. | Can create disparate objects; focuses on the construction process. |
| **Immutability** | Created object can be immutable or mutable. | Ensures target object is constructed validly before being made immutable. |

---

## When to Choose Which?

- Use **Factory** when you have a polymorphic interface and want to return different subtypes based on input.
- Use **Builder** when constructing a single complex object that would otherwise suffer from the **Telescoping Constructor Anti-Pattern** (too many overloaded constructors with default arguments).
