# 02. Use Cases & Actor Flows

## Actors
- **Driver**: Enters lot, parks, pays fee, exits.
- **Entrance Gate (Kiosk)**: Scans vehicle, allocates spot, dispenses ticket.
- **Exit Gate (Kiosk)**: Validates ticket, processes payment, frees spot.
- **Admin**: Configures parking rates, adds levels/spots.

---

## Use Case 1: Vehicle Entry
1. Driver arrives at Entrance Gate.
2. Gate sensor detects vehicle type.
3. System queries allocation strategy for the nearest vacant spot matching vehicle dimensions.
4. If found: spot status is marked `Occupied`, a `Ticket` is generated with unique ID and timestamp, and the barrier opens.
5. If full: entrance display board shows "FULL" and gate remains closed.

---

## Use Case 2: Vehicle Exit & Payment
1. Driver presents `Ticket` at Exit Gate.
2. System computes duration = `exit_time - entry_time`.
3. System applies `IFeeCalculationStrategy` to calculate amount owed.
4. Driver pays; payment is confirmed.
5. Spot is updated to `Available`, display boards are updated, and barrier opens.
