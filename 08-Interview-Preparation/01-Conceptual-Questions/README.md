# 01 Conceptual Questions & Deep Dives

High-frequency questions testing object-oriented design, the C++ object and memory model, virtual dispatch, and the SOLID principles.

---

## 1. Object Model & Virtual Dispatch
### Q1: How does virtual function dispatch work in C++ under the hood? What is the memory and runtime overhead?
**Answer**:
- **Mechanism**: When a class declares or inherits at least one virtual function, the compiler creates a `vtable` (virtual method table)—an array of function pointers stored in static read-only memory (`.rodata`). Each object instance of that class contains an invisible pointer `vptr` (typically the first 8 bytes on 64-bit systems) pointing to its class's `vtable`.
- **Runtime Call**: `obj->foo()` translates roughly to `(*(obj->vptr[INDEX_OF_FOO]))(obj)`.
- **Overhead**:
  - *Memory*: 8 bytes per object instance for `vptr` + one `vtable` per polymorphic class.
  - *CPU*: Two pointer indirections per call + disables inline optimization across translation units (unless devirtualized).
  - *Cache*: Possible instruction and data cache misses when jumping through dynamic function pointer addresses.

### Q2: Why MUST base class destructors be marked `virtual` when deleting polymorphic pointers?
**Answer**:
- If a derived object allocated on the heap is deleted via a base class pointer (`Base* p = new Derived(); delete p;`), and `~Base()` is not virtual, the behavior is **undefined behavior (UB)** according to the C++ standard [expr.delete].
- In practice, only `~Base()` executes; `~Derived()` never runs. Member variables of `Derived` (e.g., file descriptors, mutex locks, vectors) are never destroyed, causing severe resource and memory leaks.
- *Rule of Thumb*: A base class destructor must be either `public virtual` or `protected non-virtual`.

### Q3: What is object slicing, and how do you prevent it in C++?
**Answer**:
- **Slicing**: Occurs when a derived class instance is assigned or passed by value to a base class variable (`Base b = derivedObj;`). The copy/move constructor of `Base` only copies the `Base` sub-object, silently stripping away all derived member fields and polymorphic dispatch (vptr becomes `Base`'s vptr).
- **Prevention**:
  1. Pass polymorphic types by reference (`const Base&`) or pointer (`const Base*` or smart pointers `std::unique_ptr<Base>`).
  2. Make base classes abstract by declaring pure virtual functions or a protected destructor, or mark base copy operations deleted (`Base(const Base&) = delete;`).

---

## 2. SOLID Principles in C++
### Q4: Explain the Liskov Substitution Principle (LSP) with the classic Square-Rectangle dilemma.
**Answer**:
- LSP states: *If S is a subtype of T, then objects of type T may be replaced with objects of type S without altering any of the desirable properties of the program.*
- **The Violation**: If `Square` inherits from `Rectangle`, a client expecting a `Rectangle` might call `r.setWidth(5); r.setHeight(10); assert(r.getArea() == 50);`. In `Square`, setting width modifies both width and height to 5, returning 25 and breaking caller invariants.
- **Modern C++ Solution**: A Square is mathematically related, but in software contract terms, they do not share a mutable interface. Model them as distinct types implementing an immutable `Shape` interface (`double area() const = 0;`), or separate value types.

### Q5: How does the Dependency Inversion Principle (DIP) differ from Dependency Injection (DI)?
**Answer**:
- **DIP**: High-level architectural principle: high-level business modules should not depend directly on low-level implementation details; both should depend on abstractions.
- **DI**: A concrete design technique/pattern used to realize DIP: dependencies are supplied ("injected") from the outside (via constructor, setter, or factory) rather than instantiated directly using `new` inside the consumer.

---

## 3. Concurrency & Modern C++ Memory Model
### Q6: What is a data race versus a race condition?
**Answer**:
- **Data Race**: Two threads accessing the same memory location concurrently where at least one is a write, without synchronization. In C++, any data race is strictly **Undefined Behavior (UB)**.
- **Race Condition**: A semantic flaw where the correctness of a program depends on the relative timing or interleaving of threads (e.g., check-then-act bug like `if (!queue.empty()) queue.pop();`). Race conditions can happen even when all individual memory accesses are protected by locks.

### Q7: Why is Double-Checked Locking Pattern (DCLP) unsafe in pre-C++11, and how does C++11 guarantee thread-safe static initialization (Meyer's Singleton)?
**Answer**:
- Pre-C++11 lacked a standardized memory model. Compilers and CPU hardware could reorder writes: allocating memory, assigning the pointer to `instance`, and *then* executing constructor code. Another thread could observe a non-null pointer before the object finished constructing.
- **C++11 Resolution**:
  - The C++11 standard (§6.7 [stmt.dcl]) specifies: *"If control enters the declaration concurrently while the variable is being initialized, the concurrent execution shall wait until completion of the initialization."*
  - Therefore, Meyer's Singleton (`static MyClass instance; return instance;`) is thread-safe without requiring manual locks or atomics.
