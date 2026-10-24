# Factory Method vs. Abstract Factory

Both patterns decouple the client from concrete class instantiation, but operate at different architectural scopes.

---

## Quick Comparison Matrix

| Dimension | Factory Method | Abstract Factory |
|---|---|---|
| **Intent** | Creates **one product** using inheritance or function delegation. | Creates **families of related or dependent products** without specifying concrete classes. |
| **Mechanism** | Subclassing or virtual method override. | Object composition (`IUIFactory` has `createButton()`, `createCheckbox()`). |
| **Scope** | Class-level (often single virtual method). | Object-level (factory object injected into client). |
| **Adding New Products** | Easy to add a new product variant by adding a new creator subclass. | Difficult: adding a new product type requires changing every concrete factory interface. |

---

## Code Comparison in C++17

### Factory Method (Single Product)
```cpp
class Dialog {
public:
    virtual ~Dialog() = default;
    virtual std::unique_ptr<IButton> createButton() const = 0; // Factory Method
    void render() {
        auto btn = createButton();
        btn->onClick();
    }
};
```

### Abstract Factory (Product Families)
```cpp
class IUIFactory {
public:
    virtual ~IUIFactory() = default;
    virtual std::unique_ptr<IButton> createButton() const = 0;
    virtual std::unique_ptr<ICheckbox> createCheckbox() const = 0;
};

class WindowsUIFactory : public IUIFactory {
public:
    std::unique_ptr<IButton> createButton() const override { return std::make_unique<WindowsButton>(); }
    std::unique_ptr<ICheckbox> createCheckbox() const override { return std::make_unique<WindowsCheckbox>(); }
};
```
