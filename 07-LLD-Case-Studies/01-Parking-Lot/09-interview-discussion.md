# 09. Senior Interview Follow-Up Questions

1. **Q: How would you scale this design to a distributed multi-building airport parking lot with 50,000 spots?**
   - **A**: Shard available spot queues by building and level; use Redis for in-memory atomic reservation (`SETNX`) with TTL before committing to SQL.
2. **Q: How do you prevent thread starvation if 10 gates simultaneously request spots?**
   - **A**: Pre-partition spots across gates or use lock-free queues / segmented locks per level.
