# Adapter vs. Decorator

---

## Key Differences

| Dimension | Adapter | Decorator |
|---|---|---|
| **Interface Transformation** | **Changes the interface** to match what the client expects. | **Preserves the exact same interface** of the wrapped component. |
| **Behavioral Impact** | Does not add new business functionality; only translates calls. | **Augments behavior** (adds logging, compression, encryption, metrics). |
| **Recursion** | Typically 1-to-1 adaptation. | Can be composed recursively (`new Compression(new Encryption(new FileStream()))`). |
