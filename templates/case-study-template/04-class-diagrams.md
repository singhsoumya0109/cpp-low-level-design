# 04 Class Diagrams

---

## Mermaid UML Diagram

```mermaid
classDiagram
    class SystemController {
        +executeOperation()
    }
    class StrategyInterface {
        <<interface>>
        +compute()
    }
    class ConcreteStrategyA {
        +compute()
    }
    SystemController --> StrategyInterface
    StrategyInterface <|.. ConcreteStrategyA
```
