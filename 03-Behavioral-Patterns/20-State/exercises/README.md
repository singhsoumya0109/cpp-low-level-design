# State Pattern Exercises

Eliminate brittle switch-case state logic by modeling states as distinct polymorphic objects.

---

## Exercise: Vending Machine State Controller
Model a vending machine:
- States: `IdleState`, `HasCoinState`, `DispensingState`, `SoldOutState`.
- Actions: `insert_coin()`, `eject_coin()`, `press_button()`, `dispense()`.
