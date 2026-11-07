# Factory Method Exercises

Practice creating flexible factory hierarchies and decoupled polymorphic instantiation.

---

## Exercise: Notification Service Dispatcher
Design a notification service dispatch system:
- Base class `Notification` with pure virtual `send(std::string_view recipient, std::string_view msg)`.
- Concrete implementations: `EmailNotification`, `SMSNotification`, `PushNotification`.
- Creator hierarchy: `NotificationCreator` base with factory method `createNotification()` and template registration.
