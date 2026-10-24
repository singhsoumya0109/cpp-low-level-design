# Command vs. Strategy

---

## Key Differences

| Dimension | Command Pattern | Strategy Pattern |
|---|---|---|
| **Intent** | Encapsulates a **request as an object** with parameters, state, and execution history. | Encapsulates an **algorithm or business calculation**. |
| **Undo / Redo** | Native support: stores inverse action or state snapshot to rollback. | No concept of undo/redo; purely computational. |
| **Lifecycle** | Can be queued, scheduled, serialized, and stored in a history stack. | Executed synchronously to produce a result. |
