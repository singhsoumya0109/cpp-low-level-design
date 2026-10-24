# UML Class & Sequence Diagrams Reference

In Low-Level Design interviews and technical documentation, UML (Unified Modeling Language) allows you to visually communicate class hierarchies, dependencies, and execution lifecycles without getting bogged down in syntax.

---

## 1. Class Relationships Visual Matrix

| Relationship | Symbol (Mermaid) | Description | Lifecycle Coupling | Example |
|---|:---:|---|---|---|
| **Inheritance** | `A <|-- B` | `B` is-a `A`. Base class specialization. | Very High (Compile-time) | `Car` is-a `Vehicle` |
| **Realization** | `Interface <\|.. Impl` | Class implements an abstract interface. | Moderate (Decoupled) | `SmtpNotifier` implements `INotifier` |
| **Composition** | `Whole *-- Part` | Strong ownership. If Whole dies, Part dies. | Very High | `Car` owns its `Engine` |
| **Aggregation** | `Container o-- Item` | Weak ownership / Has-a. Item can outlive Container. | Low to Moderate | `Department` has `Employees` |
| **Association** | `A --> B` | Structural link. `A` holds a reference/pointer to `B`. | Low | `Customer` books `Ticket` |
| **Dependency** | `A ..> B` | Ephemeral use. `A` uses `B` as a local variable/parameter. | Very Low | `Calculator` uses `MathHelper` |

---

## 2. Mermaid Class Diagram Example

```mermaid
classDiagram
    class Vehicle {
        <<abstract>>
        #string licensePlate_
        #VehicleType type_
        +getLicensePlate() string
        +getType() VehicleType
        +calculateFee(int hours)* double
    }

    class Car {
        +calculateFee(int hours) double
    }

    class Motorcycle {
        +calculateFee(int hours) double
    }

    class IParkingStrategy {
        <<interface>>
        +findSpot(Level& level, VehicleType type)* ParkingSpot*
    }

    class NearestFirstStrategy {
        +findSpot(Level& level, VehicleType type) ParkingSpot*
    }

    class ParkingLot {
        -vector~Level~ levels_
        -unique_ptr~IParkingStrategy~ strategy_
        +parkVehicle(Vehicle& v) Ticket
        +unparkVehicle(Ticket& t) double
    }

    Vehicle <|-- Car
    Vehicle <|-- Motorcycle
    IParkingStrategy <|.. NearestFirstStrategy
    ParkingLot o-- IParkingStrategy : uses
    ParkingLot *-- Level : owns
```

---

## 3. Sequence Diagram Example (Booking Flow)

Visualizes the temporal message ordering between actors and objects:

```mermaid
sequenceDiagram
    autonumber
    actor Driver
    participant EntranceGate
    participant ParkingLot
    participant Strategy as IParkingStrategy
    participant Spot as ParkingSpot

    Driver->>EntranceGate: scanVehicle(car)
    EntranceGate->>ParkingLot: requestParking(car)
    ParkingLot->>Strategy: findAvailableSpot(levels, Car)
    Strategy->>Spot: checkAvailability()
    Spot-->>Strategy: isAvailable = true
    Strategy-->>ParkingLot: return targetSpot
    ParkingLot->>Spot: reserve(car)
    ParkingLot-->>EntranceGate: return Ticket
    EntranceGate-->>Driver: dispenseTicketAndOpenBarrier()
```

---

## 4. ASCII Notation for Whiteboard Interviews

During live coding or text-only interviews, use standardized ASCII box notations:

```text
+---------------------------------------+
|              <<interface>>            |
|            IPaymentProcessor          |
+---------------------------------------+
| + pay(amount: double): bool           |
| + refund(txnId: string): bool         |
+---------------------------------------+
                   ^
                   | implements
      +------------+------------+
      |                         |
+---------------+       +---------------+
|  StripeGateway|       |  PayPalGateway|
+---------------+       +---------------+
| - apiKey      |       | - oauthToken  |
+---------------+       +---------------+
| + pay(...)    |       | + pay(...)    |
+---------------+       +---------------+
```

