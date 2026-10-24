# 03. Entities & Domain Dictionary

## Enums
```cpp
enum class VehicleType { Motorcycle, CompactCar, LargeTruck };
enum class SpotType { Motorcycle, Compact, Large };
enum class SpotStatus { Available, Occupied, Reserved, Maintenance };
```

## Core Domain Classes
- **`Vehicle`** (Base): `licensePlate`, `VehicleType`.
- **`ParkingSpot`**: `spotId`, `floorNumber`, `SpotType`, `SpotStatus`, `park(Vehicle*)`, `unpark()`.
- **`Level`**: `floorNumber`, holds collections of `ParkingSpot`s, tracks availability count.
- **`Ticket`**: `ticketId`, `licensePlate`, `allocatedSpotId`, `entryTime`.
- **`ParkingLot`**: Singleton coordinator holding levels, entry gates, and exit gates.
