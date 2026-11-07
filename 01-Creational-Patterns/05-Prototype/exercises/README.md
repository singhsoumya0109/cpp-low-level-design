# Prototype Pattern Exercises

Master deep cloning of complex object graphs without coupling to concrete classes.

---

## Exercise: Game Monster Spawner
Implement a cloneable `Monster` base class with virtual `clone()` returning `std::unique_ptr<Monster>`. Concrete types: `Goblin` and `Dragon`. Verify modifying a clone's stats does not alter the prototype.
