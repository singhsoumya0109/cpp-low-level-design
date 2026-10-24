# Symptom-To-Pattern Diagnostic Table

When you observe a specific code smell or system requirement, consult this table.

| Code Smell / Requirement | Architectural Problem | Recommended Pattern |
|---|---|---|
| Massive `switch-case` or `if-else` ladder on object type | Violates Open/Closed Principle | **Factory Method** or **Strategy** |
| Constructor with 7+ arguments, many defaulting to null/0 | Telescoping Constructor Anti-Pattern | **Builder** |
| Class doing business logic, database SQL, and email alerts | God Object (Violates SRP) | **Facade** + **Strategy** / **Observer** |
| Subclasses throwing `NotSupportedException` | Violates Liskov Substitution Principle | **Interface Segregation** + **Strategy** |
| High memory consumption due to millions of duplicate structs | Redundant immutable data | **Flyweight** |
| Tightly-coupled circular dependencies between UI components | Spaghetti dependencies | **Mediator** |
| Need undo/redo operations in an editor or game | Loss of action history | **Command** + **Memento** |
| Need to query an external slow network service only when accessed | High startup latency | **Virtual Proxy** (Lazy Loading) |
