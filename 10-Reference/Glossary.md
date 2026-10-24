# Low-Level Design Glossary

- **Cohesion**: How focused and closely related the responsibilities of a single module/class are. High cohesion is desirable.
- **Coupling**: The degree of direct dependency between modules. Loose coupling is desirable.
- **Inversion of Control (IoC)**: A design principle in which the framework or higher-level coordinator controls program flow rather than custom code.
- **Dynamic Dispatch**: Resolving which polymorphic method implementation to call at runtime via the virtual method table (vtable).
- **Static Dispatch**: Resolving function calls at compile time (templates, CRTP), eliminating vtable indirection overhead.
- **Devirtualization**: A compiler optimization where a virtual call is transformed into a direct function call when the concrete type can be deduced statically.
