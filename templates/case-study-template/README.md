# [System Name] - Low-Level Design Case Study

> **Difficulty**: [Easy / Medium / Hard] | **Category**: [Games / Booking / Concurrency / Infrastructure]

---

## 1. System Overview

[Concise 1-2 paragraph description of what this system does and the core engineering challenge it tackles.]

---

## 2. Guide Directory & Documents

This case study contains a comprehensive 9-part breakdown:

- [`01-requirements.md`](01-requirements.md): Scope, functional & non-functional requirements.
- [`02-use-cases.md`](02-use-cases.md): Actors, step-by-step flows, error paths.
- [`03-entities-and-relationships.md`](03-entities-and-relationships.md): Class dictionary, enums, states.
- [`04-class-diagrams.md`](04-class-diagrams.md): Mermaid class and sequence diagrams.
- [`05-design-decisions.md`](05-design-decisions.md): Architectural trade-offs and rationale.
- [`06-pattern-justifications.md`](06-pattern-justifications.md): Why each design pattern was chosen.
- [`07-concurrency-and-edge-cases.md`](07-concurrency-and-edge-cases.md): Data races, thread safety, boundary limits.
- [`08-extension-requirements.md`](08-extension-requirements.md): Absorbing future requirement changes.
- [`09-interview-discussion.md`](09-interview-discussion.md): Deep follow-ups and discussion points.

---

## 3. Codebase Structure

- `starter/`: Skeleton code with interfaces and empty methods for timed mock interview practice.
- `solution/`: Complete production C++17 implementation:
  - `include/`: Header files organized by models, strategies, managers.
  - `src/`: Implementation files.
  - `main.cpp`: Interactive simulation driver demonstrating the full flow.
- `tests/`: Automated unit and concurrency test suite.

---

## 4. Build and Run

```bash
cmake -B build
cmake --build build
./build/07-LLD-Case-Studies/[Case-Study-Name]/solution/case_study_app
ctest --test-dir build --output-on-failure
```

