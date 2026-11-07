# Bridge Pattern Exercises

Decouple an abstraction hierarchy from its implementation hierarchy to prevent combinatorial subclass explosion.

---

## Exercise: Message Sender Bridge
Decouple `Message` abstraction (with `NormalMessage` and `EncryptedMessage`) from `IMessageSender` implementation (with `SmsSender` and `EmailSender`).
