# Decorator vs. Proxy

Both wrap an underlying target object and implement the same interface, but their intent is distinct.

---

## Key Differences

| Dimension | Decorator | Proxy |
|---|---|---|
| **Intent** | **Extends responsibilities dynamically** without modifying classes. | **Controls access** or manages the lifecycle of the target object. |
| **Target Creation** | Target object is created externally and passed into decorator constructor. | Proxy often manages the creation and deletion of the target (e.g. Virtual Proxy for lazy loading). |
| **Chain Composition** | Designed for arbitrary multi-layer stacking. | Usually a single stand-in wrapper between client and subject. |
| **Examples** | Adding border/scrollbar to UI component; gzip stream. | Caching results, authentication check, lazy loading high-res images. |
