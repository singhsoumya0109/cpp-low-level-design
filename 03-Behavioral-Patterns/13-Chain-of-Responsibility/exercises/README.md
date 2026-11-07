# Chain of Responsibility Exercises

Practice chaining polymorphic request handlers with dynamic escalation.

---

## Exercise: Expense Approval Chain
Implement an expense approval workflow:
- `Manager`: Approves up to $1,000.
- `Director`: Approves up to $10,000.
- `VP`: Approves up to $50,000.
- Requests over $50,000 require CEO or Board review.
