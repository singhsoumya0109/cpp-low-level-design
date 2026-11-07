# Template Method Exercises

Enforce algorithm structure while allowing subclasses to customize individual steps.

---

## Exercise: Beverage Brewing Machine
Implement a `BeverageMaker` with template method `prepare_recipe()`:
- Common steps: `boil_water()`, `pour_in_cup()`.
- Primitive operations: `brew()`, `add_condiments()`.
- Subclasses: `Coffee` and `Tea`.
