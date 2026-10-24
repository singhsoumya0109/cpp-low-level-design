# C++17 Syntax Reference for LLD

```cpp
// 1. Structured Bindings
auto [key, value] = myMapEntry;

// 2. std::string_view (zero-copy string observation)
void log(std::string_view msg);

// 3. std::optional (explicit absence of value)
std::optional<User> findUser(int id);

// 4. std::variant & std::visit (type-safe sum types)
using Shape = std::variant<Circle, Rectangle>;
std::visit(ShapeDrawer{}, shape);

// 5. if-init statements
if (auto it = map.find(key); it != map.end()) {
    // it is scoped strictly to this if/else block
}
```
