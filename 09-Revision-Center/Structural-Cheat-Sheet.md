# Structural Patterns Cheat Sheet

| Pattern | Adapter | Bridge | Composite | Decorator | Facade | Flyweight | Proxy |
|---|---|---|---|---|---|---|---|
| **Intent** | Match interfaces | Split Abstraction & Impl | Part-whole tree | Dynamic augmentation | Simplified entry point | Share immutable state | Control access |
| **Target Count** | 1 adaptee | 1 implementation tree | N children | 1 wrapped target | N subsystem classes | Thousands of pooled items | 1 target subject |
| **Interface** | Changes interface | Distinct abstraction hierarchy | Same component interface | Exact same interface | Simplified new interface | Fine-grained interface | Exact same interface |
