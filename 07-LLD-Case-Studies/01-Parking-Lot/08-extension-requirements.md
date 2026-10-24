# 08. Extension Requirements

How our design absorbs changes:
1. **EV Charging Stations**: Add `bool hasCharger` to `ParkingSpot` and an `ElectricChargingFeeDecorator` wrapping `IFeeStrategy`.
2. **Valet Parking**: Add a `ValetService` coordinator interacting with `IParkingStrategy`.
3. **Automated License Plate Recognition (ALPR)**: Add an ALPR camera reader feeding plate numbers directly into `EntranceGate`.
