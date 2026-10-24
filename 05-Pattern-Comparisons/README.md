# Pattern Comparisons: Head-to-Head Deep Dives

In technical interviews, interviewers frequently ask:
> *"Why did you choose Strategy over State here?"*  
> *"What is the architectural difference between a Decorator and a Proxy?"*

This module analyzes commonly confused patterns side-by-side with architectural diffs and use-case boundaries.

---

## Comparative Analyses

| Comparison Guide | Key Distinguishing Factor |
|---|---|
| **[Factory Method vs Abstract Factory](Factory-Method-vs-Abstract-Factory.md)** | Single product inheritance vs families of related products. |
| **[Factory vs Builder](Factory-vs-Builder.md)** | Single-shot creation vs multi-step complex construction. |
| **[Strategy vs State](Strategy-vs-State.md)** | External algorithm choice vs internal state-driven transitions. |
| **[Strategy vs Template Method](Strategy-vs-Template-Method.md)** | Composition/Delegation (Object scope) vs Inheritance (Class scope). |
| **[Adapter vs Bridge](Adapter-vs-Bridge.md)** | Fixing incompatible existing interfaces vs designing upfront for independent variation. |
| **[Adapter vs Decorator](Adapter-vs-Decorator.md)** | Changing interface without changing behavior vs keeping interface while augmenting behavior. |
| **[Decorator vs Proxy](Decorator-vs-Proxy.md)** | Adding responsibilities dynamically vs controlling access / lifetime to target object. |
| **[Observer vs Mediator](Observer-vs-Mediator.md)** | Distributed one-to-many event flow vs centralized coordination hub. |
| **[Composite vs Decorator](Composite-vs-Decorator.md)** | Aggregating part-whole hierarchies vs wrapping a single component to augment behavior. |
| **[Command vs Strategy](Command-vs-Strategy.md)** | Encapsulating requests with history & undo/redo vs encapsulating swappable algorithms. |

