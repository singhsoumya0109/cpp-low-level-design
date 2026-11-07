# Answer Keys & Grading Rubrics

Comprehensive grading rubrics and model solutions for all interview preparation modules.

---

## Evaluation Rubric (40-Point Scale)

### 1. Object-Oriented Design & Principles (10 Points)
- **Exemplary (9-10)**: Strict adherence to SOLID. Proper use of Composition over Inheritance. Interfaces are minimal and cohesive.
- **Competent (6-8)**: Good separation of concerns; minor coupling issues or mild violation of OCP/LSP.
- **Unsatisfactory (0-5)**: Monolithic God-classes, rampant `if-else` branching on type enums, high coupling.

### 2. Modern C++ Fluency & Idioms (10 Points)
- **Exemplary (9-10)**: Zero raw owning pointers. Correct usage of `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`. Proper use of `std::string_view`, `std::optional`, `override`, `noexcept`, `= delete`.
- **Competent (6-8)**: Generally clean C++ with minor inconsistencies (e.g. unnecessary string copies instead of `std::string_view`).
- **Unsatisfactory (0-5)**: C-with-classes, raw `new`/`delete`, memory leaks, non-virtual polymorphic destructors.

### 3. Concurrency & Memory Safety (10 Points)
- **Exemplary (9-10)**: Correct thread synchronization using RAII locks (`std::scoped_lock`, `std::shared_lock`). Lock-free atomics where appropriate. Deadlock-free ordering.
- **Competent (6-8)**: Basic mutex usage; some redundant lock acquisitions or wide critical sections.
- **Unsatisfactory (0-5)**: Data races, unsynchronized mutations, or deadlock vulnerabilities.

### 4. Working Code & Testability (10 Points)
- **Exemplary (9-10)**: Fully compiling and working solution with comprehensive assertions covering edge cases.
- **Competent (6-8)**: Compiles with minor warnings; primary happy-path covered but misses edge cases.
- **Unsatisfactory (0-5)**: Does not compile or crashes on basic operations.
