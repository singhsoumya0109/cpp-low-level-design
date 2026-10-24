# Composite vs. Decorator

---

## Key Differences

| Dimension | Composite Pattern | Decorator Pattern |
|---|---|---|
| **Intent** | Represents **part-whole tree hierarchies** where groups and single items share an interface. | Adds **responsibilities to a single object** dynamically without inheritance. |
| **Child Count** | A composite container holds N children (`std::vector<std::unique_ptr<Component>>`). | A decorator wraps **exactly one** inner child component. |
| **Purpose** | Aggregation & structural traversal. | Behavioral enrichment. |
