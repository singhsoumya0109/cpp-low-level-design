# Behavioral Design Patterns in Modern C++

Behavioral patterns are concerned with algorithms and the assignment of responsibilities between objects, characterizing complex control flows that are difficult to follow at runtime.

---

## The 11 Behavioral Patterns

| Pattern | Intent | Key C++ Mechanism |
|---|---|---|
| **[13. Chain of Responsibility](13-Chain-of-Responsibility/)** | Passes requests along a chain of handlers until one handles it. | Linked list of handler smart pointers. |
| **[14. Command](14-Command/)** | Encapsulates a request as an object, enabling undo/redo and macro commands. | `std::function` or polymorphic `ICommand` with `execute()` / `undo()`. |
| **[15. Interpreter](15-Interpreter/)** | Given a language, defines a grammar representation along with an interpreter. | Abstract Syntax Tree (AST) node hierarchy. |
| **[16. Iterator](16-Iterator/)** | Provides sequential access to elements of an aggregate object without exposing representation. | Custom iterator complying with STL iterator traits (`std::iterator_traits`). |
| **[17. Mediator](17-Mediator/)** | Reduces chaotic dependencies between objects by forcing communication through a mediator. | Loose coupling with observer/dispatch callbacks. |
| **[18. Memento](18-Memento/)** | Captures and externalizes an object's internal state without violating encapsulation. | Private state snapshots accessible only by the Originator (`friend` class). |
| **[19. Observer](19-Observer/)** | Defines a one-to-many dependency so that when one object changes state, all dependents are notified. | Thread-safe subscriber lists with `std::weak_ptr` to avoid reference cycles. |
| **[20. State](20-State/)** | Allows an object to alter its behavior when its internal state changes. | Finite State Machine (FSM) via polymorphism or `std::variant`. |
| **[21. Strategy](21-Strategy/)** | Defines a family of interchangeable algorithms and encapsulates each one. | Runtime polymorphism (`unique_ptr<IStrategy>`) or compile-time Policy templates. |
| **[22. Template Method](22-Template-Method/)** | Defines the skeleton of an algorithm, deferring steps to subclasses. | Non-Virtual Interface (NVI) idiom in C++. |
| **[23. Visitor](23-Visitor/)** | Represents an operation to be performed on elements of an object structure. | Double dispatch (classic) vs `std::visit` with `std::variant`. |

