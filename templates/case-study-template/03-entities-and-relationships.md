# 03 Entities and Relationships

---

## Core Entities
- Entity names, attributes, invariants, and ownership.

## Enums and Value Types
- Status codes, categories, and configuration options.

## Relationship Mapping
- Entity A *has-a* (owns) Entity B (`std::unique_ptr`).
- Entity C *observes* / references Entity A (`std::weak_ptr` or raw pointer / reference).
