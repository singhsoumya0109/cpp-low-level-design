# Pattern Selection Guide & Decision Trees

Choosing the right design pattern is about recognizing **the fundamental design tension** in your problem statement.

---

## 🧭 The Master Pattern Decision Flowchart

```mermaid
flowchart TD
    Start["What is your core design problem?"] --> P1{"Object Creation?"}
    Start --> P2{"Object Composition / Structure?"}
    Start --> P3{"Object Interaction / Behavior?"}

    P1 --> C1{"Need single global instance?"}
    C1 -->|Yes| Singleton["Meyers' Singleton"]
    C1 -->|No| C2{"Complex multi-step assembly?"}
    C2 -->|Yes| Builder["Builder Pattern"]
    C2 -->|No| C3{"Families of related products?"}
    C3 -->|Yes| AbsFactory["Abstract Factory"]
    C3 -->|No| Factory["Factory Method"]

    P2 --> S1{"Adapting incompatible interface?"}
    S1 -->|Yes| Adapter["Adapter Pattern"]
    S1 -->|No| S2{"Tree / Hierarchical structure?"}
    S2 -->|Yes| Composite["Composite Pattern"]
    S2 -->|No| S3{"Dynamic behavioral augmentation?"}
    S3 -->|Yes| Decorator["Decorator Pattern"]
    S3 -->|No| S4{"Control access / caching?"}
    S4 -->|Yes| Proxy["Proxy Pattern"]
    S4 -->|No| Facade["Facade Pattern"]

    P3 --> B1{"Object alters behavior on state change?"}
    B1 -->|Yes| State["State Pattern"]
    B1 -->|No| B2{"Interchangeable algorithms?"}
    B2 -->|Yes| Strategy["Strategy Pattern"]
    B2 -->|No| B3{"One-to-many event notification?"}
    B3 -->|Yes| Observer["Observer Pattern"]
    B3 -->|No| B4{"Undo/Redo or Queued actions?"}
    B4 -->|Yes| Command["Command Pattern"]
```

---

## Documents in This Section

- [`Pattern-Decision-Tree.md`](Pattern-Decision-Tree.md): Exhaustive decision tree mapping requirements to patterns.
- [`Problem-To-Pattern-Mapping.md`](Problem-To-Pattern-Mapping.md): Symptoms & code smells mapped to target patterns.
- [`Pattern-Relationships.md`](Pattern-Relationships.md): How patterns compose (e.g. Abstract Factory implemented via Factory Method or Prototype).
- [`Design-Tradeoffs.md`](Design-Tradeoffs.md): Memory, performance, and cognitive load trade-offs.
- [`When-Not-To-Use-Patterns.md`](When-Not-To-Use-Patterns.md): Overengineering antipatterns and YAGNI.
- [`Common-Anti-Patterns.md`](Common-Anti-Patterns.md): God Class, Anemic Domain Model, Golden Hammer, Lava Flow.

