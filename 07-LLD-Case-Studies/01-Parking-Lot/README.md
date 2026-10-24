# Case Study 01: Multi-Floor Parking Lot System

> **Difficulty**: Medium | **Primary Patterns**: Factory Method, Strategy, State

---

## System Overview
Design an automated, multi-floor parking lot management system capable of assigning slots to different vehicle types, calculating dynamic fees upon exit, tracking real-time floor availability, and coordinating multiple entry and exit gates concurrently.

---

## Complete Case Study Documentation
1. [`01-requirements.md`](01-requirements.md): Functional and non-functional requirements.
2. [`02-use-cases.md`](02-use-cases.md): Actor use-case specifications (Entry, Parking, Exit, Payment).
3. [`03-entities-and-relationships.md`](03-entities-and-relationships.md): Core domain models, enums, and class associations.
4. [`04-class-diagrams.md`](04-class-diagrams.md): Mermaid UML class diagrams and entry/exit sequence diagrams.
5. [`05-design-decisions.md`](05-design-decisions.md): Architectural trade-offs (e.g. flat vs multi-floor lookup).
6. [`06-pattern-justifications.md`](06-pattern-justifications.md): Justifications for Factory, Strategy, and State patterns.
7. [`07-concurrency-and-edge-cases.md`](07-concurrency-and-edge-cases.md): Simultaneous gate bookings and race conditions.
8. [`08-extension-requirements.md`](08-extension-requirements.md): EV charging spots, surge pricing, valet parking.
9. [`09-interview-discussion.md`](09-interview-discussion.md): Senior interview follow-ups and system bottlenecks.
