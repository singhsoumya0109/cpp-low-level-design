# Behavioral Patterns Cheat Sheet

| Pattern | Chain of Resp | Command | Iterator | Observer | State | Strategy | Template Method | Visitor |
|---|---|---|---|---|---|---|---|---|
| **Core Idea** | Sequential handlers | Request as object | Traverse collections | One-to-many publish | FSM state transitions | Interchangeable algorithms | Algorithm skeleton | Double dispatch operations |
| **Coupling** | Weak (successor link) | Decoupled invoker & receiver | Abstract iterator | Weak (IObserver) | Context delegates to State | Context delegates to Strategy | Base class controls child | Visitor knows all node types |
| **Modern C++** | Smart pointer chain | `std::function` / lambdas | `std::iterator_traits` | `std::weak_ptr` list | `std::variant` / classes | `std::function` or policy template | NVI idiom | `std::visit` + `std::variant` |
