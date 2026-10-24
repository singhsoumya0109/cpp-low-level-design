# 07. Concurrency & Edge Cases

## Concurrency Hazards
- **Double Booking**: Two entrance gates find the same empty spot simultaneously and assign it to two different drivers.
- **Solution**:
  1. Fine-grained mutex per `ParkingSpot`: spot level `std::mutex` locked during status transition.
  2. Or synchronized `ParkingLotManager` protecting the available spots queue using `std::mutex` and RAII `std::lock_guard`.

## Edge Cases
1. **Lot is Completely Full**: Gracefully return `std::nullopt` instead of crashing or hanging.
2. **Lost Ticket**: Fallback flat fee calculation method.
3. **Oversized Vehicle**: Truck attempting to park in Motorcycle spot rejected by type validator.
