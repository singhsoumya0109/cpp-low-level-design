# 04 Refactoring Challenges

Hands-on exercises taking brittle, hardcoded legacy procedural code and transforming it into extensible, clean Modern C++17 designs.

---

## Challenge: The Monolithic Payment & Fee Processor

### Legacy Anti-Pattern Code:
```cpp
// Highly coupled, violates Open/Closed Principle (OCP) and Single Responsibility (SRP)
class OrderProcessor {
public:
    void processPayment(const std::string& type, double amount, const std::string& account) {
        double fee = 0.0;
        if (type == "CREDIT_CARD") {
            fee = amount * 0.029 + 0.30;
            // Connect to Stripe API...
            std::cout << "Processing Credit Card (" << account << "): $" << (amount + fee) << "\n";
        } else if (type == "PAYPAL") {
            fee = amount * 0.034;
            // Connect to PayPal REST API...
            std::cout << "Processing PayPal (" << account << "): $" << (amount + fee) << "\n";
        } else if (type == "CRYPTO") {
            fee = 0.0005 * 50000.0; // Fixed gas fee
            // Sign blockchain transaction...
            std::cout << "Processing Crypto (" << account << "): $" << (amount + fee) << "\n";
        } else {
            throw std::invalid_argument("Unsupported payment type: " + type);
        }
    }
};
```

### Step-by-Step Refactoring Plan:
1. **Identify Smells**:
   - `switch`/`if-else` chain branching on string payment type tags.
   - Adding a new payment method (e.g., Apple Pay) requires modifying `OrderProcessor`, risking regressions.
   - Fee calculation and gateway execution logic are entangled.
2. **Apply Strategy Pattern & Modern C++**:
   - Abstract `PaymentStrategy` interface with `process(double amount, std::string_view account)`.
   - Separate concrete strategies: `CreditCardPayment`, `PayPalPayment`, `CryptoPayment`.
   - Use `std::unique_ptr<PaymentStrategy>` or `std::function` for injection.
