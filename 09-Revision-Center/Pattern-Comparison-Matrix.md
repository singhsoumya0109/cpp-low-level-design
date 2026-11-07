# Design Patterns Master Comparison Matrix

A comprehensive, side-by-side quick-reference comparing all 23 Gang of Four (GoF) patterns and core Modern C++ idioms.

---

## 🏗️ Creational Patterns

| Pattern | Primary Intent | Key Problem Solved | Modern C++ Idiom / Mechanism | Trade-Offs |
|---|---|---|---|---|
| **Singleton** | Ensure exactly one instance with global access | Shared resource coordination (loggers, configs) | Meyer's Singleton (static local, thread-safe via magic statics), deleted copy/move | Hidden dependencies, testing difficulties |
| **Factory Method** | Subclass-deferred instantiation | Decoupling creation from polymorphic usage | Virtual factory method returning `std::unique_ptr<T>`, lambdas in map | Subclass proliferation for simple types |
| **Abstract Factory** | Create families of related objects | Inconsistent cross-family components | Pure virtual interfaces returning smart pointers, template factories | Adding new product families requires changing base interface |
| **Builder** | Stepwise construction of complex objects | Telescoping constructors, parameter explosion | Fluent API (`return *this;`), rvalue builders with `std::move` | Additional builder classes, boilerplate |
| **Prototype** | Clone existing objects | Expensive initialization or hidden concrete classes | Virtual `clone()` returning `std::unique_ptr<Base>`, CRTP clone | Deep copying pointer graphs can be complex |

---

## 🧱 Structural Patterns

| Pattern | Primary Intent | Key Problem Solved | Modern C++ Idiom / Mechanism | Trade-Offs |
|---|---|---|---|---|
| **Adapter** | Convert an existing interface to match client expectations | Incompatible third-party APIs | Composition (`std::unique_ptr<Adaptee>`) or multiple inheritance | Small indirection overhead |
| **Bridge** | Decouple abstraction from implementation hierarchy | Class explosion from multi-dimensional variance | PImpl / Handle-Body idiom via smart pointers | Increased conceptual complexity |
| **Composite** | Uniformly treat individual objects and compositions | Tree hierarchies (UI trees, ASTs, file systems) | `std::vector<std::unique_ptr<Component>>`, recursive traversal | Hard to restrict component types at compile time |
| **Decorator** | Dynamically add responsibilities without subclassing | Feature combinatorics, runtime extensions | Wrapper classes wrapping `std::unique_ptr<Component>`, template decorators | Many small wrapper objects, identity mismatch |
| **Facade** | Provide unified, simplified interface to complex subsystem | Overwhelming subsystem dependencies | High-level controller class orchestrating internal components | Risk of creating an all-knowing "God object" |
| **Flyweight** | Share common state among many fine-grained objects | High memory consumption from redundant state | Split into intrinsic (cached shared) and extrinsic (context passed by param) | CPU vs memory trade-off; thread safety on shared pool |
| **Proxy** | Control access, lazy load, or cache an underlying object | Expensive instantiation, access validation, remote calls | Wrapper with identical interface, lazy `std::unique_ptr` initialization | Added layer of indirection |

---

## 🔄 Behavioral Patterns

| Pattern | Primary Intent | Key Problem Solved | Modern C++ Idiom / Mechanism | Trade-Offs |
|---|---|---|---|---|
| **Chain of Responsibility** | Pass requests along a handler chain | Hardcoded multi-stage request handling | Linked list of handler pointers or `std::vector<std::function>` | Request might fall through unhandled |
| **Command** | Encapsulate request as an object | Undo/redo, job queues, deferred execution | Polymorphic `execute()`/`undo()`, `std::function<void()>`, lambdas | Proliferation of command classes |
| **Interpreter** | Evaluate grammar sentences in a language | Domain-specific languages, expression parsing | Composite AST nodes with `evaluate(Context&)` | Inefficient for complex grammars (use parser generators) |
| **Iterator** | Sequentially access container elements without exposing structure | Container-agnostic traversal | C++ iterator traits (`begin()`, `end()`, operator++, operator*) | Often native STL iterators suffice |
| **Mediator** | Centralize complex communications between objects | Many-to-many tight coupling | Hub object coordinating spokes; weak pointers to prevent cycles | Mediator itself can become overly complex |
| **Memento** | Capture and restore object internal state without violating encapsulation | Snapshots, undo mechanisms | Opaque token object, private friend access or serialized state | High memory footprint if state is large |
| **Observer** | Publish-subscribe 1-to-many dependency updates | Tight coupling between subject and listeners | `std::vector<std::weak_ptr<Observer>>`, functional signal/slots | Notification order nondeterminism, dangling references |
| **State** | Alter object behavior when its internal state changes | Complex nested `switch/case` state machines | Polymorphic state hierarchy or `std::variant` + `std::visit` | Class explosion if states are numerous |
| **Strategy** | Family of interchangeable algorithms | Hardcoded runtime algorithmic variations | `std::unique_ptr<Strategy>` or `std::function<Algorithm>` | Client must be aware of strategy differences |
| **Template Method** | Define algorithm skeleton, defer steps to subclasses | Code duplication across algorithmic variants | Non-Virtual Interface (NVI) idiom, CRTP | Subclasses tightly coupled to base class skeleton |
| **Visitor** | Add new operations to object structure without modifying classes | Operations scattered across class hierarchies | Double dispatch (`accept(Visitor&)`), or `std::visit` on `std::variant` | Adding new concrete elements is hard |

---

## ⚡ Modern C++ & Extended Idioms

| Idiom | Core Concept | C++17 Standard Feature | Replaces Classic GoF |
|---|---|---|---|
| **RAII / ScopeGuard** | Resource lifecycle tied to object lifetime | Destructors, stack unwinding | Manual cleanup, `finally` blocks |
| **PImpl** | Opaque pointer hiding implementation details | `std::unique_ptr<Impl>` in source | Headers exposing private implementation |
| **CRTP** | Static polymorphism via base class templated on derived | `template <typename Derived> class Base` | Virtual function table overhead |
| **Type Erasure** | Polymorphism without common inheritance | `std::function`, `std::any`, custom model/concept | Rigid inheritance hierarchies |
| **Object Pool** | Reusable cache of expensive objects | Thread-safe queue + smart pointer custom deleters | Repeated allocation/deallocation |
