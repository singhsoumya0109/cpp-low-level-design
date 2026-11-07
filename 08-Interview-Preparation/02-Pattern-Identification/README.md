# 02 Pattern Identification Drills

Scenario-based rapid identification exercises. Master the intuition to spot the optimal pattern in under 60 seconds during tech screens.

---

## Drill 1: The Multi-Step Notification Pipeline
**Scenario**: You are designing an alerting engine for an infrastructure monitoring platform. An incoming alert must sequentially pass through: (1) deduplication filter, (2) rate limiter, (3) severity enricher, and (4) routing to Slack/PagerDuty. New filters must be added or reordered without modifying the alerting engine.
- **Optimal Pattern**: **Chain of Responsibility** (or **Pipeline / Interceptor**)
- **Key Indicators**: Sequential processing chain, early exit if deduplicated or rate-limited, decoupled sender from handlers.
- **Alternative Considered**: Decorator (Decorator wraps calls recursively and typically modifies or augments behavior; Chain allows dynamic termination and independent linking).

---

## Drill 2: Document Editor with Reversible Formatting
**Scenario**: A markdown text editor needs rich undo/redo support across multiple operations (insert text, delete word, bold range, indent). Users can batch multiple operations into a macro and execute them together.
- **Optimal Pattern**: **Command** pattern paired with **Composite** (MacroCommand) and optional **Memento** (for large state rollback).
- **Key Indicators**: Reversible operations (`execute()` / `undo()`), request queuing, history stack, macro grouping.

---

## Drill 3: Cross-Platform UI Widget Toolkit
**Scenario**: You are developing a GUI toolkit supporting multiple windowing backends (macOS Cocoa, Windows Win32, Linux Wayland) across multiple widget shapes (Window, Button, ScrollBar). You want to prevent an $M \times N$ combinatorial explosion of classes like `MacButton`, `WinButton`, `WaylandButton`, `MacWindow`...
- **Optimal Pattern**: **Bridge**
- **Key Indicators**: Two orthogonal dimensions of variation (Widget Abstraction hierarchy vs Platform Implementation hierarchy).
- **Alternative Considered**: Abstract Factory (Used to create families of widgets, but Bridge decouples the runtime implementations). In practice, Abstract Factory often creates the Bridge implementations!

---

## Drill 4: In-Memory Trading Market Depth Feed
**Scenario**: Financial order book with millions of orders where symbol strings ("AAPL", "GOOG"), exchange codes ("NASDAQ", "NYSE"), and contract specifications are repeated across all orders, ballooning memory footprint to gigabytes.
- **Optimal Pattern**: **Flyweight**
- **Key Indicators**: Massive number of objects with large redundant, immutable shared state (intrinsic) vs volatile order quantities/prices (extrinsic).

---

## Drill 5: Smart Home Automation System
**Scenario**: Hundreds of smart sensors (temperature, motion, light) and actuators (HVAC, lights, blinds) communicate dynamically. When motion is detected, lights should adjust, HVAC should turn on, and blinds open based on temperature. Direct point-to-point connections create an entangled mesh.
- **Optimal Pattern**: **Mediator** (Hub) + **Observer** (Pub/Sub)
- **Key Indicators**: Many-to-many communication dependencies simplified into a central coordinator.
