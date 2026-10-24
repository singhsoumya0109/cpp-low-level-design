# All 23 GoF Design Patterns: The 1-Page Master Cheat Sheet

A concise reference table covering the core intent, use case, and modern C++ mechanism for every classic pattern.

---

## 🏗️ Creational Patterns (5)

| Pattern | One-Line Intent | Use When... | Modern C++ Idiom |
|---|---|---|---|
| **Singleton** | Ensure exactly one instance with global access. | Managing shared hardware or centralized configurations. | Thread-safe Meyers' static local object (`static T instance;`). |
| **Factory Method** | Delegate instantiation logic to specialized subclasses or functions. | Object type cannot be anticipated before runtime. | Function returning `std::unique_ptr<Interface>`. |
| **Abstract Factory** | Create families of related or dependent objects without specifying classes. | Multi-platform UI widgets (Windows vs Mac UI). | Class with virtual methods returning `std::unique_ptr` products. |
| **Builder** | Separate complex construction steps from representation. | Creating objects with 5+ parameters or multiple variations. | Fluent / Step Builder returning `std::unique_ptr<Product>`. |
| **Prototype** | Create new objects by cloning an existing prototype. | Direct construction is expensive or hidden. | Virtual `clone()` method returning `std::unique_ptr<Self>`. |

---

## 🧱 Structural Patterns (7)

| Pattern | One-Line Intent | Use When... | Modern C++ Idiom |
|---|---|---|---|
| **Adapter** | Convert incompatible interface into an expected interface. | Integrating legacy or 3rd-party libraries. | Object Adapter holding `std::unique_ptr<Adaptee>`. |
| **Bridge** | Decouple abstraction from implementation so both vary independently. | Cross-platform rendering engines (Window vs Direct3D/OpenGL). | PImpl / Handle-Body idiom via smart pointers. |
| **Composite** | Treat individual objects and compositions uniformly. | UI widget trees, file systems, graphics groups. | `std::vector<std::unique_ptr<Component>>`. |
| **Decorator** | Dynamically attach additional responsibilities to an object. | Adding logging, encryption, or discounts without subclassing. | Wrapping inner interface pointer and delegating. |
| **Facade** | Provide a simplified high-level interface to a complex subsystem. | Video converter, payment SDK, compiler frontend. | Clean coordinator class encapsulating complex headers. |
| **Flyweight** | Share common state among many fine-grained objects to save memory. | Particle systems, text editor character glyphs. | Flyweight Factory returning shared `const` instances. |
| **Proxy** | Provide a surrogate or placeholder to control access. | Lazy resource loading (Virtual), security check (Protection), Cache. | Class implementing same interface holding underlying target pointer. |

---

## 🔄 Behavioral Patterns (11)

| Pattern | One-Line Intent | Use When... | Modern C++ Idiom |
|---|---|---|---|
| **Chain of Resp.** | Pass request along a chain of handlers until one handles it. | Middleware filters, authentication & authorization pipelines. | Linked list of `std::shared_ptr<Handler>` or `unique_ptr`. |
| **Command** | Encapsulate a request as an object to support undo/redo and queues. | GUI buttons, transactional tasks, thread pool work units. | Polymorphic `ICommand` or `std::function<void()>`. |
| **Interpreter** | Evaluate sentences in a specified grammar. | SQL parsing, regular expressions, calculation ASTs. | Composite-based AST traversal. |
| **Iterator** | Sequentially access elements without exposing internal structure. | Custom collections and containers. | Standard C++ iterators adhering to `std::iterator_traits`. |
| **Mediator** | Centralize complex communications between loosely-coupled objects. | Air traffic controller, chat room server, dialog UI controller. | Central mediator receiving event callbacks from components. |
| **Memento** | Capture and restore internal state without violating encapsulation. | Text editor history, checkpoint/rollback systems. | Private Memento state struct accessible only by `friend` originator. |
| **Observer** | Notify multiple dependent objects automatically on state change. | Event systems, stock tickers, MVC architectures. | `std::vector<std::weak_ptr<IObserver>>` to prevent memory leaks. |
| **State** | Alter object behavior dynamically when internal state transitions. | Vending machines, game character states, document workflows. | Polymorphic State classes or `std::variant` + `std::visit`. |
| **Strategy** | Define a family of interchangeable algorithms. | Sorting algorithms, fee calculation, compression formats. | `std::unique_ptr<IStrategy>` or `std::function`. |
| **Template Method** | Define algorithm skeleton in base class, deferring steps to child. | Data mining pipelines, game AI execution loops. | Non-Virtual Interface (NVI) idiom in C++. |
| **Visitor** | Add new operations to existing class hierarchy without modifying it. | Document exporters (HTML, PDF, Markdown), AST code generators. | Double dispatch (`accept`/`visit`) or `std::variant` with `std::visit`. |

