# Creational Design Patterns in Modern C++

Creational design patterns abstract the instantiation process. They help make a system independent of how its objects are created, composed, and represented. A class creational pattern uses inheritance to vary the class that's instantiated, whereas an object creational pattern will delegate instantiation to another object.

---

## The 5 Creational Patterns

| Pattern | Intent | Key C++ Mechanism |
|---|---|---|
| **[01. Singleton](01-Singleton/)** | Ensures a class has only one instance and provides a global point of access to it. | Meyer's Singleton (thread-safe static local variable, C++11 magic statics). Deleted copy/move operations. |
| **[02. Factory Method](02-Factory-Method/)** | Defines an interface for creating an object, but lets subclasses decide which class to instantiate. | Virtual creation method returning `std::unique_ptr<Base>`, or lambda/function registration tables. |
| **[03. Abstract Factory](03-Abstract-Factory/)** | Provides an interface for creating families of related or dependent objects without specifying their concrete classes. | Pure virtual interface returning `std::unique_ptr<FamilyProduct>`, or template policy-based factories. |
| **[04. Builder](04-Builder/)** | Separates the construction of a complex object from its representation so that the same construction process can create different representations. | Fluent interface with method chaining (`return *this`), move-semantics build method, and optional Director. |
| **[05. Prototype](05-Prototype/)** | Specifies the kinds of objects to create using a prototypical instance, and creates new objects by copying this prototype. | Virtual `clone()` method returning `std::unique_ptr<Base>`, leveraging covariant return types or modern smart pointer wrappers. |

---

## Creational Patterns Comparison Matrix

| Feature | Singleton | Factory Method | Abstract Factory | Builder | Prototype |
|---|---|---|---|---|---|
| **Complexity** | Low | Low-Medium | Medium-High | Medium | Low-Medium |
| **Creation Target** | Single shared instance | Single product via inheritance | Families of related products | Complex multi-part object | Clones of existing objects |
| **Key Modern C++ Feature** | Static local initialization | `std::unique_ptr`, `std::function` | Variadic templates, smart pointers | Fluent API, rvalue references (`&&`) | Virtual `clone()`, copy constructors |
| **Coupling** | High (global state risk) | Low (polymorphic decoupling) | Low (abstract family decoupling) | Low (stepwise encapsulation) | Low (decoupled from concrete types) |

---

## Choosing the Right Creational Pattern

```
Do you need only one instance throughout the application lifecycle?
  ├── YES ──► Singleton (Meyer's idiom)
  └── NO  ──► Do you need to copy existing complex objects without coupling to concrete classes?
                ├── YES ──► Prototype (clone() pattern)
                └── NO  ──► Is object construction a complex multi-step process with many configurations?
                              ├── YES ──► Builder
                              └── NO  ──► Are you creating families of related products?
                                            ├── YES ──► Abstract Factory
                                            └── NO  ──► Factory Method
```
