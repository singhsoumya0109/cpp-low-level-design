# Common Object-Oriented Anti-Patterns

Anti-patterns are recurring patterns of code organization that seem intuitive at first, but lead to severe maintenance and scaling problems.

---

## 1. The God Object (The Blob)
- **Symptom**: A single massive class (`SystemManager`, `AppController`) with 2,000+ lines of code doing 20 different responsibilities.
- **Refactoring**: Apply the **Single Responsibility Principle**. Carve out cohesive components (e.g., Auth, Validation, Persistence, Notification).

---

## 2. Anemic Domain Model
- **Symptom**: Data classes with only getters and setters (dumb data holders) accompanied by procedural "Service" classes that manipulate the data from the outside.
- **Refactoring**: Move business behavior into the domain entities themselves (encapsulation).

---

## 3. Poltergeists (Gypsy Objects)
- **Symptom**: Short-lived transient classes whose sole purpose is to initialize another class or invoke a single method and disappear.
- **Refactoring**: Eliminate the intermediary class and call the target directly.

---

## 4. Lava Flow (Dead / Legacy Code)
- **Symptom**: Outdated classes, methods, or parameters that developers are afraid to remove because "something might break".
- **Refactoring**: Comprehensive unit test coverage + bold pruning of unreferenced code.

---

## 5. Golden Hammer
- **Symptom**: Assuming a familiar pattern (e.g. Singleton or Observer) solves every problem in the system.
- **Refactoring**: Consult the Pattern Decision Tree and evaluate architectural trade-offs objectively.
