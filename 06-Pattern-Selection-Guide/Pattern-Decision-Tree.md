# Master Pattern Decision Tree

Use this decision tree during interview preparation or real-world system design to map requirements directly to design patterns.

---

## 1. Object Creation Problems
- **Need a single instance globally?** $ightarrow$ **Singleton (Scott Meyers')**
- **Need multi-step construction with many optional arguments?** $ightarrow$ **Builder**
- **Need to create families of related objects (e.g. cross-platform UI)?** $ightarrow$ **Abstract Factory**
- **Need to delegate instantiation to subclasses based on runtime input?** $ightarrow$ **Factory Method**
- **Creating new objects by copying an existing instance is cheaper?** $ightarrow$ **Prototype**

---

## 2. Structural & Composition Problems
- **Need an existing class with an incompatible interface to work with a client?** $ightarrow$ **Adapter**
- **Need abstraction and implementation to vary orthogonally?** $ightarrow$ **Bridge**
- **Need to represent recursive part-whole tree hierarchies (file system, UI)?** $ightarrow$ **Composite**
- **Need to add behavior dynamically without inheritance (logging, compression)?** $ightarrow$ **Decorator**
- **Need a simple interface to hide a complex subsystem?** $ightarrow$ **Facade**
- **Need to support millions of tiny objects sharing common state?** $ightarrow$ **Flyweight**
- **Need to control access, delay loading (lazy), or cache an object?** $ightarrow$ **Proxy**

---

## 3. Behavioral & Communication Problems
- **Object changes behavior based on its internal state?** $ightarrow$ **State**
- **Need interchangeable algorithms that can be swapped at runtime?** $ightarrow$ **Strategy**
- **One object changes state, and multiple listeners must react?** $ightarrow$ **Observer**
- **Need to encapsulate requests as objects with undo/redo and queueing?** $ightarrow$ **Command**
- **Pass a request along a sequence of potential handlers?** $ightarrow$ **Chain of Responsibility**
- **Reduce many-to-many communication chaos into a centralized coordinator?** $ightarrow$ **Mediator**
- **Save and restore snapshots of an object without breaking encapsulation?** $ightarrow$ **Memento**
- **Execute operations on elements of a complex tree without modifying them?** $ightarrow$ **Visitor**
- **Define algorithm skeleton in base class, deferring specific steps to subclasses?** $ightarrow$ **Template Method (NVI)**
