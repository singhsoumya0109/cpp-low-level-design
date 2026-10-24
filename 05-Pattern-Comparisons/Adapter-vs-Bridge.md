# Adapter vs. Bridge

---

## Key Differences

| Dimension | Adapter Pattern | Bridge Pattern |
|---|---|---|
| **When Applied** | **Post-design / Retrofit**: Makes existing, incompatible systems work together. | **Pre-design / Upfront**: Designed from scratch so abstraction and implementation vary independently. |
| **Intent** | Fixes interface mismatches between legacy or 3rd-party code and new clients. | Prevents Cartesian product class explosions (e.g., `LinuxWindow`, `MacWindow`, `DirectXWindow`). |
| **Interface Impact** | Changes the interface of the adaptee to match client expectations. | Preserves abstraction and implementation as distinct, orthogonal hierarchies. |
