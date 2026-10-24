# Observer vs. Mediator

---

## Key Differences

| Dimension | Observer Pattern | Mediator Pattern |
|---|---|---|
| **Communication Flow** | **One-to-Many**: One Subject broadcasts events unidirectionally to many Observers. | **Many-to-Many**: Multiple Colleague objects communicate bidirectionally through a central hub. |
| **Coupling** | Subject only knows `IObserver` interface. Loose coupling. | Colleagues know only the Mediator; Mediator knows concrete colleague components. |
| **State Distribution** | State is held in the Subject and observed by subscribers. | Coordination logic is centralized entirely inside the Mediator. |
