# Strategy vs. State

Structurally, both patterns share an identical UML diagram (Context delegates to an Interface), but their **intent and state transition mechanisms** are completely different.

---

## Key Differences

| Dimension | Strategy Pattern | State Pattern |
|---|---|---|
| **Intent** | Encapsulates **interchangeable algorithms** that the client or context chooses. | Encapsulates **state-dependent behaviors** where the object changes behavior as state transitions. |
| **Who Changes It?** | The **Client** typically configures the strategy once (or swaps it deliberately). | The **State objects or Context** automatically transition between states as actions happen. |
| **Awareness of Siblings** | Concrete strategies are completely unaware of each other. | Concrete states often know about and instantiate the next target state. |
| **Analogy** | Choosing a route algorithm: GPS chooses Walking, Biking, or Driving strategy. | Vending Machine: Transitions from `Idle` -> `HasMoney` -> `Dispensing` -> `SoldOut`. |
