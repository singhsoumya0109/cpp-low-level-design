# Common Compilation Errors & Troubleshooting

### 1. `undefined reference to vtable for ClassName`
- **Cause**: An abstract or derived class has a virtual function declared without an implementation, or missing virtual destructor definition.
- **Fix**: Ensure base classes have `virtual ~ClassName() = default;` and pure virtual methods have `= 0;`.

### 2. `static initialization order fiasco`
- **Cause**: Global variables across different translation units depending on each other during static startup.
- **Fix**: Use Scott Meyers' Singleton (local static variables inside a function).

### 3. `use of deleted function: std::unique_ptr copy constructor`
- **Cause**: Trying to pass a `std::unique_ptr` by value without `std::move`.
- **Fix**: Use `std::move(ptr)` when transferring ownership, or pass `const std::unique_ptr<T>&` / raw pointer `T*` for observation.
