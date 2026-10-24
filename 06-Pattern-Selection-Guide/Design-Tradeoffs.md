# Design Trade-offs & Engineering Costs

Applying a design pattern is an engineering trade-off. Patterns provide **extensibility** and **decoupling**, but they come with real costs:

| Pattern | Primary Benefit | Architectural Cost / Penalty |
|---|---|---|
| **Abstract Factory** | Easy to swap entire product families. | Extremely difficult to add a new product type (modifies all factories). |
| **Decorator** | Infinite dynamic flexibility without subclassing. | Many small nested wrapper objects; difficult to debug call stacks. |
| **Strategy** | Runtime algorithm flexibility. | Increases total number of classes; clients must be aware of strategies. |
| **Visitor** | Clean separation of algorithms from data structures. | Cyclic dependencies; breaks encapsulation if private data is required. |
| **Singleton** | Guaranteed single instance and global access. | Hidden dependencies; state pollution across parallel unit tests. |

---

## The Rule of Parsimony
> *"Do not introduce an abstraction until you have at least two concrete use cases or a clear requirement for variability."*
