# 05. Key Design Decisions & Trade-offs

1. **Spot Allocation Data Structure**:
   - *Option A*: Flat list scan $O(N)$ across all spots. (Too slow for large lots).
   - *Option B (Chosen)*: Per-level `std::set` or min-heap ordered by distance from entrance. Gives $O(\log N)$ allocation and $O(1)$ nearest spot retrieval.

2. **Decoupling Fee Calculation**:
   - Encapsulating pricing in `IFeeStrategy` ensures changing prices for weekends or adding subscription passes requires zero edits to `ParkingLot` or `Ticket`.
