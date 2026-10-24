# 01. Requirements & Scope Bounding

## Functional Requirements
1. **Multi-Floor Layout**: The parking lot consists of multiple floors/levels, each having multiple parking spots.
2. **Vehicle Sizing**: Supports Motorcycle, Car, and Large Truck/Bus. Spots are typed accordingly (MotorcycleSpot, CompactSpot, LargeSpot).
3. **Automated Ticketing**: An entrance gate issues a timestamped Ticket when a vehicle enters if a suitable spot is available.
4. **Dynamic Spot Allocation**: The system assigns the closest available spot to the entrance based on a configurable allocation strategy.
5. **Fee Calculation**: Upon exit, fees are calculated based on duration and vehicle type (e.g., hourly rates, flat rates).
6. **Real-Time Display**: Each floor has an availability display board showing vacant spots per vehicle type.

## Non-Functional Requirements
1. **Thread Safety**: Multiple entrance and exit gates must be able to park/unpark vehicles concurrently without double-booking spots.
2. **Low Latency**: Slot allocation must be $O(1)$ or $O(\log N)$.
3. **Extensibility (OCP)**: New fee schemes (surge pricing, holiday discounts) or vehicle types (EVs) must be addable without altering core parking logic.
