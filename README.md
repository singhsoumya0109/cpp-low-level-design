# Modern C++ Low-Level Design (LLD) & Design Patterns Mastery

[![C++17](https://img.shields.io/badge/Standard-C%2B%2B17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![Build & Test](https://img.shields.io/badge/Build-CMake%20%7C%20Ninja-brightgreen.svg)](CMakeLists.txt)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Zero Fluff](https://img.shields.io/badge/Self--Sufficient-100%25-orange.svg)](#why-this-repository)

> **The definitive, fully self-sufficient Modern C++ (C++17) Low-Level Design and Object-Oriented Design resource.**
> Engineered to eliminate the need for external videos, courses, or editorials by providing complete conceptual clarity, bad-vs-good refactorings, Mermaid & ASCII UML diagrams, modern C++ idioms, interactive exercises with solutions, and production-grade case studies.

---

## Table of Contents

- [Why This Repository?](#why-this-repository)
- [How This Repository Is Structured](#how-this-repository-is-structured)
- [Repository Map](#repository-map)
- [Anatomy of Every Pattern](#anatomy-of-every-pattern)
- [Anatomy of Every Case Study](#anatomy-of-every-case-study)
- [Quick Start & Build Instructions](#quick-start--build-instructions)
- [Curriculum & Modules](#curriculum--modules)
  - [00. Foundations & Core OOP](#00-foundations)
  - [01. Creational Design Patterns](#01-creational-patterns)
  - [02. Structural Design Patterns](#02-structural-patterns)
  - [03. Behavioral Design Patterns](#03-behavioral-patterns)
  - [04. Modern C++ & Extended Patterns](#04-modern-c-and-extended-patterns)
  - [05. Pattern Comparisons](#05-pattern-comparisons)
  - [06. Pattern Selection Guide](#06-pattern-selection-guide)
  - [07. Production LLD Case Studies](#07-lld-case-studies)
  - [08. Interview Preparation & Mock Problems](#08-interview-preparation)
  - [09. Revision Center & Flashcards](#09-revision-center)
  - [10. References & Syntax Guide](#10-reference)
- [Study Guides & Roadmaps](#study-guides--roadmaps)
- [Contributing & Code Style](#contributing--code-style)
- [License](#license)

---

## Why This Repository?

Most design pattern and LLD repositories fall into one of two traps:
1. **Academic/Toy Code**: Snippets using raw pointers (`Dog* dog = new Dog()`), memory leaks, zero RAII, and outdated C++98 styles.
2. **Missing Intuition**: Presenting the final pattern without explaining *why* a naive approach fails or *how* to arrive at the solution under interview pressure.

This repository fixes that with four core pillars:
* **Pure Modern C++ (C++17)**: Uses RAII, `std::unique_ptr`, `std::shared_ptr`, `std::string_view`, `std::optional`, `std::variant`, and modern concurrency primitives. No raw `new`/`delete`.
* **Naive-to-Optimized Evolution**: Every concept starts with naive, tightly-coupled code violating SOLID, breaks down the failure points, and refactors into clean design.
* **Embedded Visual Diagrams**: High-clarity Mermaid UML and ASCII diagrams right in the documentation—no external image hosting or broken links.
* **Complete Test & Practice Suites**: Every pattern and case study includes unit tests, starter exercises, and complete reference solutions.

---

## Repository Map

```text
cpp-low-level-design/
├── 00-Foundations/                     # Core OOP, C++17 prereqs, ownership, SOLID, multithreading
├── 01-Creational-Patterns/             # Singleton, Factory Method, Abstract Factory, Builder, Prototype
├── 02-Structural-Patterns/             # Adapter, Bridge, Composite, Decorator, Facade, Flyweight, Proxy
├── 03-Behavioral-Patterns/             # Chain of Resp, Command, Iterator, Observer, State, Strategy, etc.
├── 04-Modern-Cpp-And-Extended-Patterns/# RAII, PImpl, CRTP, Type Erasure, DI, Null Object, Object Pool
├── 05-Pattern-Comparisons/             # Head-to-head deep dives (Strategy vs State, Factory vs Builder, etc.)
├── 06-Pattern-Selection-Guide/         # Decision trees, diagnostic problem-to-pattern tables, anti-patterns
├── 07-LLD-Case-Studies/                # 10 production-grade systems (Parking Lot, Elevator, Cache, etc.)
├── 08-Interview-Preparation/           # 45-min mock interviews, conceptual Q&A, refactoring challenges
├── 09-Revision-Center/                 # Flashcards, 1-page summaries, and interview checklists
├── 10-Reference/                       # Modern C++ syntax cheat sheet, smart pointer reference, glossary
├── templates/                          # Scaffolding templates for new patterns & case studies
└── scripts/                            # One-click build and verification scripts
```

---

## Anatomy of Every Pattern

Each design pattern directory (e.g., `01-Creational-Patterns/02-Factory-Method/`) is completely self-contained:

```text
[Pattern-Name]/
├── README.md                      # Complete guide: Intuition, Diagrams, Trade-offs, Modern C++ alternative
├── CMakeLists.txt                 # Standalone and parent-integrated build
├── src/
│   ├── 01-naive-approach.cpp      # Anti-pattern / naive implementation showing failure modes
│   ├── 02-classic-pattern.cpp     # Clean GoF implementation with smart pointers
│   ├── 03-real-world-example.cpp  # Production scenario (e.g. Cross-platform loggers, parsers)
│   └── 04-modern-cpp-style.cpp    # Idiomatic modern C++ alternative (std::variant, std::function, templates)
├── exercises/
│   ├── README.md                  # Practice problems: Basic, Refactoring, Interview challenge
│   ├── starter.cpp                # Skeleton code with TODO comments
│   └── solutions/                 # Full reference implementations
└── tests/
    └── test_[pattern].cpp         # Unit tests validating polymorphic behaviors and edge cases
```

---

## Anatomy of Every Case Study

Every machine coding problem in `07-LLD-Case-Studies/` (e.g., `01-Parking-Lot/`) provides full lifecycle coverage:

1. **`01-requirements.md`**: Functional, non-functional, and interview scope bounding.
2. **`02-use-cases.md`**: Actors, flows, and pre/post conditions.
3. **`03-entities-and-relationships.md`**: Core models, enums, and class relationships.
4. **`04-class-diagrams.md`**: Complete Mermaid UML class & sequence diagrams.
5. **`05-design-decisions.md`**: Architectural trade-offs and rationale.
6. **`06-pattern-justifications.md`**: Exact mapping of requirements to design patterns.
7. **`07-concurrency-and-edge-cases.md`**: Thread safety, race condition prevention, and resource limits.
8. **`08-extension-requirements.md`**: How the design absorbs future requirement changes gracefully.
9. **`09-interview-discussion.md`**: Deep follow-up questions asked by FAANG/tier-1 interviewers.
10. **`solution/`**: Full modular C++17 codebase (`include/`, `src/`, `main.cpp`).
11. **`starter/`**: Template for timed 45-minute practice.
12. **`tests/`**: Unit and concurrency test suite.

---

## Quick Start & Build Instructions

### Prerequisites
- Compiler: `GCC 9+`, `Clang 10+`, or `MSVC 2019+` (C++17 support required)
- Build System: `CMake 3.16+` and optional `Ninja`

### Build Everything
```bash
# Clone your repository
git clone <your-repo-url>
cd cpp-low-level-design

# Run the automated build script
./scripts/build-all.sh

# Run all unit tests
./scripts/test-all.sh
```

### Manual CMake Build
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
ctest --test-dir build --output-on-failure
```

---

## Case Studies Catalog

| # | System | Primary Patterns | Key Engineering Challenges |
|---|---|---|---|
| **01** | [Parking Lot](07-LLD-Case-Studies/01-Parking-Lot/) | Factory, Strategy, State | Multi-floor slot allocation, dynamic fee calculation, vehicle sizing |
| **02** | [Elevator System](07-LLD-Case-Studies/02-Elevator-System/) | State, Strategy, Dispatcher | Multi-car coordination, LOOK/SCAN dispatch scheduling, internal/external requests |
| **03** | [Vending Machine](07-LLD-Case-Studies/03-Vending-Machine/) | State, Command | State machine transitions, cash/change inventory, transaction rollback |
| **04** | [Notification System](07-LLD-Case-Studies/04-Notification-System/) | Factory, Strategy, Decorator | Multi-channel routing (SMS, Email, Push), rate limiting, exponential backoff retry |
| **05** | [Order Management](07-LLD-Case-Studies/05-Order-Management-System/) | State, Observer, Command | Lifecycle management, inventory reservation, payment webhooks |
| **06** | [In-Memory File System](07-LLD-Case-Studies/06-File-System/) | Composite, Iterator, Visitor | Tree-based directory structures, file operations, permissions, path resolution |
| **07** | [In-Memory Cache (LRU/LFU)](07-LLD-Case-Studies/07-In-Memory-Cache-LRU-LFU/) | Strategy, Proxy | $O(1)$ operations, TTL expiration, thread-safe read/write locking |
| **08** | [Distributed Rate Limiter](07-LLD-Case-Studies/08-Rate-Limiter/) | Strategy, Decorator | Token Bucket, Leaky Bucket, Sliding Window Log, concurrency |
| **09** | [Splitwise Expense Sharing](07-LLD-Case-Studies/09-Splitwise-Expense-Sharing/) | Strategy, Observer | Equal/Exact/Percent splits, Debt Simplification (Min-Cash Flow Graph Algorithm) |
| **10** | [Movie Ticket Booking](07-LLD-Case-Studies/10-Movie-Ticket-Booking-System/) | State, Strategy | Concurrency seat locking with TTL, idempotency, race condition prevention |

---

## Study Guides & Roadmaps

- ⏱️ **Short on time?** Read [`START-HERE.md`](START-HERE.md) for 7-day, 14-day, and 30-day fast-track guides.
- 🗺️ **Comprehensive Study Plan**: Follow [`ROADMAP.md`](ROADMAP.md) for an in-depth mastery trajectory.
- 📋 **Track Progress**: Use [`STUDY-TRACKER.md`](STUDY-TRACKER.md) to check off your milestones.
- ⚡ **Night Before Interview**: Jump straight to [`09-Revision-Center/All-23-Patterns-One-Page.md`](09-Revision-Center/All-23-Patterns-One-Page.md).

---

## Contributing & Code Style

Code follows modern C++17 idioms formatted with `.clang-format`:
- All memory allocations must be wrapped in `std::unique_ptr` or `std::shared_ptr`.
- Non-owning references must use raw pointers (`T*`), references (`const T&`), or `std::string_view`.
- Interfaces must have `virtual ~Interface() = default;`.
- Methods overriding base classes must explicitly declare `override`.

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

