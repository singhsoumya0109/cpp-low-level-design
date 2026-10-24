# 06. Design Pattern Justifications

| Pattern | Where Used | Justification |
|---|---|---|
| **Strategy Pattern** | `IParkingStrategy` | Easily swap allocation rules (e.g. Nearest First, Best Fit, Distributed across floors). |
| **Strategy Pattern** | `IFeeStrategy` | Supports dynamic hourly rates, weekend surge, or flat corporate discounts. |
| **Factory Method** | `VehicleFactory` | Cleanly instantiates concrete `Car`, `Motorcycle`, or `Truck` instances from input data. |
| **Observer Pattern** | Display Boards | Automatically updates floor occupancy boards whenever a spot is occupied or freed. |
